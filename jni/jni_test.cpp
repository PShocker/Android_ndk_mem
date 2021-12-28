#include <unistd.h>
#include <iostream>
#include <fstream>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>

#include "Memory.h"
#include "AOBScan.h"

char pattern[] = {0x32, 0x00, 0x00, 0x00, 0x0A, 0x00, 0x00, 0x00};

int main(int argc, char *argv[])
{
    auto pid = find_pid("com.popcap.pvz");//获取pid
    if (pid == 0)
    {
        printf("Can't find pid\n");
        return -1;
    }
    else
    {
        printf("%d\n", pid);
    }

    PModuleListEntry ml = get_process_map(pid);//读取进程的模块信息,PModuleListEntry是一个链表

    while (ml->next_ptr != nullptr)//循环所有的模块
    {
        if (!ml->moduleName[0]) //判断是否有模块名,注意,这个例子是没有模块名的.
        {
            int size = ml->moduleSize;
            char *target = (char *)malloc(size);
            char *target_ = target;
            int r = ReadProcessMemory(pid, (void *)ml->baseAddress, target, size);//读取内存
            if (r == 0)
            {
                goto lable; //unreadable
            }
            while (true) //循环搜索所有匹配到的特征地址
            {
                int offset = AOBScan(target, size, pattern, sizeof(pattern));
                if (offset != -1)
                {
                    target += offset + sizeof(pattern);
                    size -= offset + sizeof(pattern);
                    unsigned long long offset_ = target - target_ - sizeof(pattern);//这里是拿到偏移
                    unsigned long long address = ml->baseAddress + offset_;//搜索到的目标进程的内存地址
                    // printf("offset_:%llx\n", offset_);
                    printf("%llx\n", address);
                    unsigned int data[] = {0x12345678};
                    WriteProcessMemory(pid, (void *)address, (void *)data, sizeof(data)/sizeof(unsigned int));//写内存
                    continue;
                }
                break;
            }
            free(target_);
        }
    lable:
        ml = (PModuleListEntry)ml->next_ptr;
    }

    return 0;
}