#pragma once
#include "dllmain.h"
#include <jni.h>

class CSAMP
{
public:
    CSAMP(JavaVM *vm);
    ~CSAMP();
    
    void LoadLib(JavaVM *vm);
    uintptr_t GetBaseAddress() { return g_lib; }
    
public:
	char buff[0x7F];
    bool        bInited;
    uintptr_t   g_lib;
};
