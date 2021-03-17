#pragma once
#include <jni.h>

extern JNIEnv* getJniEnv(JavaVM *vm);
extern bool jni_load(JNIEnv* p, const char * libPath);
extern bool jni_loadLibrary(JNIEnv* p, const char * libPath);