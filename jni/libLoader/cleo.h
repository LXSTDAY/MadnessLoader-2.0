#pragma once

class CLEO
{
public:
    static bool m_bInstalled_hooks, m_bInstalled_patches, m_bInitedInGame; 
    
public:
    CLEO(/* args */) {}
    ~CLEO() {}

    static void InitInGame();
    static void InstallHooks();
    static void ApplyPatches();
    static bool IsAlreadyInstalled() { if(m_bInstalled_hooks && m_bInstalled_patches && m_bInitedInGame) return true; else return false; }

};
