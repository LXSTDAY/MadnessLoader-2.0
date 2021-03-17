#include "dllmain.h"
#include "cleo.h"

bool CLEO::m_bInitedInGame      = 0;
bool CLEO::m_bInstalled_hooks   = 0;
bool CLEO::m_bInstalled_patches = 0;

void CLEO::InstallHooks()
{     
    m_bInstalled_hooks = false;
    //CLEO_NvFOpen_addr = g_libCLEO + 0x67B8; AddrHook(CLEO_NvFOpen_addr, (uintptr_t)CLEO_NvFOpen_hook, (uintptr_t*)&CLEO_NvFOpen);
    m_bInstalled_hooks = true;
}

void CLEO::ApplyPatches()
{   
    m_bInstalled_patches = false;
    // CText_Get_hook
    //NOP(g_libCLEO + 0x04DB8, 2); // delete hook
    //WriteMemory(g_libCLEO + 0x058B6, (uintptr_t)"\x00\x20\x00\x20\xF7\x46", 6); // return 0
    m_bInstalled_patches = true;
}

void CLEO::InitInGame()
{   
    m_bInitedInGame = false;
    CPatch::CallFunction<void>(g_libCLEO + 0x536C +1);
    m_bInitedInGame= true;
}