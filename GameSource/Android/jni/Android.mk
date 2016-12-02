LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := monstone_jni_lib
LOCAL_CFLAGS := -DANDROID_NDK
LOCAL_SRC_FILES := NativeCall.c GLGameRenderer.c
LOCAL_LDLIBS := -lGLESv2\
				-llog

include $(BUILD_SHARED_LIBRARY)
APP_PLATFORM    := android-10