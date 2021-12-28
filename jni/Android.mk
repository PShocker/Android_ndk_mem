LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := jni_test

LOCAL_SRC_FILES := jni_test.cpp

LOCAL_CPP_INCLUDES += $(LOCAL_PATH)


include $(BUILD_EXECUTABLE)




