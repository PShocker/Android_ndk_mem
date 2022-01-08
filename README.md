# Android_ndk_mem
ndk编译可执行文件跨进程读写app内存

游戏app:
链接：https://pan.baidu.com/s/15N_GaoDQBGPfIfXwfvA9dA 
提取码：zd68

请在开局150阳光下执行./libs/xx/jni_test

# 编译流程
## 配置ndk环境
下载Android Studio

点击左上角 File->Project Structure->SDK Location
在Android NDK Location 
下点击Download Android NDK
![image](img/1640684959(1).jpg)

下载完成后配置ndk环境变量
编辑Path,新增ndk路径
![image](img/1640685183(1).jpg)

## 编译项目
进入jni目录,执行ndk-build
```
cd jni
ndk-build
```