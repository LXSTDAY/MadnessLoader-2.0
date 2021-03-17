#include "dllmain.h"
#include "samp.h"
#include "ini.h"
#include <dlfcn.h>

extern CLoaderINI *pLoaderINI;

CSAMP::CSAMP(JavaVM *vm)
{
    bInited = false;
    g_lib   = 0;

	bool samp = pLoaderINI->Get().bMultiplayer;
	if(samp) LoadLib(vm);
}

CSAMP::~CSAMP()
{}

void CSAMP::LoadLib(JavaVM *vm)
{
    JNIEnv* m_pJniEnv = getJniEnv(vm);

    SAMPLoad(true);
    sprintf(buff, "%slib/libbass.so", RootStorage);
    if(!jni_load(m_pJniEnv, buff)) exit(1);
	sprintf(buff, "%scache/libsamp.so", RootStorage);
    if(!jni_load(m_pJniEnv, buff)) exit(1);
    g_lib = CPatch::FindLibrary("libsamp.so");
    
    bInited = true;
}
