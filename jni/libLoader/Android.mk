LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := util
LOCAL_LDLIBS := -llog

LOCAL_C_INCLUDES := $(LOCAL_PATH)/include
LOCAL_EXPORT_C_INCLUDES := $(LOCAL_C_INCLUDES)

FILE_LIST := $(wildcard $(LOCAL_PATH)/*.cpp)
FILE_LIST += $(wildcard $(LOCAL_PATH)/SDK/include/*.*)
FILE_LIST += $(wildcard $(LOCAL_PATH)/SDK/vendor/*.cpp)
FILE_LIST += $(wildcard $(LOCAL_PATH)/SDK/vendor/*/*.cpp)
FILE_LIST += $(wildcard $(LOCAL_PATH)/SDK/vendor/*/*.c)
FILE_LIST += $(wildcard $(LOCAL_PATH)/SDK/vendor/*/*/*.cpp)

FILE_LIST += $(wildcard $(LOCAL_PATH)/SDK/game/*.cpp)
FILE_LIST += $(wildcard $(LOCAL_PATH)/SDK/game/*/*.cpp)

FILE_LIST += $(wildcard $(LOCAL_PATH)/SDK/gui/*.cpp)

LOCAL_SRC_FILES := $(FILE_LIST:$(LOCAL_PATH)/%=%)

LOCAL_CPPFLAGS := -w -s -std=c++14
include $(BUILD_SHARED_LIBRARY)