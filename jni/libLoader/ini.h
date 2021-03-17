#pragma once
#include "dllmain.h"

struct inifile
{   
    
    // global
    bool bEnableLogs;
    bool bMultiplayer;
    int iServer;

    // gui
    string sFont;
};


class CLoaderINI
{
private:
    //sections
    char* section_global = "global";
    char* section_gui = "gui";
    inifile m_LoaderINI;
public:
    CLoaderINI();
    ~CLoaderINI();

    inifile& Get() { return m_LoaderINI; }
};


