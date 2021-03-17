#include "dllmain.h"
#include <jni.h>
extern const char* ThreadName;
JNIEnv* getJniEnv(JavaVM *vm)
{
    JavaVMAttachArgs attachArgs;
    attachArgs.version = JNI_VERSION_1_4;
    attachArgs.name = ThreadName;
    attachArgs.group = NULL;
    JNIEnv* env = nullptr;
    if(vm->AttachCurrentThread(&env, &attachArgs) != JNI_OK)
    {
        env = nullptr;
    }
   
    return env;
}
 
bool jni_load(JNIEnv* p, const char * libPath)
{
    jclass sysClass = p->FindClass("java/lang/System");
 
    if(!sysClass)
    {
        return false;
    }
 
    jmethodID loadMethod = p->GetStaticMethodID(sysClass, "load", "(Ljava/lang/String;)V");
    jstring jStr = p->NewStringUTF(libPath);
    p->CallStaticByteMethod(sysClass, loadMethod, jStr);

    return true;
}

bool jni_loadLibrary(JNIEnv* p, const char * libPath)
{
    jclass sysClass = p->FindClass("java/lang/System");
 
    if(!sysClass)
    {
        return false;
    }
 
    jmethodID loadMethod = p->GetStaticMethodID(sysClass, "loadLibrary", "(Ljava/lang/String;)V");
    jstring jStr = p->NewStringUTF(libPath);
    p->CallStaticByteMethod(sysClass, loadMethod, jStr);

    return true;
}