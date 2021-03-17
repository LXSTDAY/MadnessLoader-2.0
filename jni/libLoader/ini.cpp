#include "ini.h"
#include "dllmain.h"

CLoaderINI::CLoaderINI()
{   
    char buff[0xff];
    sprintf(buff, "%sload.ini", GameStorage);
    INIReader ini(buff);

    //global
    m_LoaderINI.bEnableLogs     = ini.GetBoolean(section_global, "debuglog", true);
    m_LoaderINI.bMultiplayer    = ini.GetBoolean(section_global, "samp", false);
    m_LoaderINI.iServer         = ini.GetInteger(section_global, "server", 0);

    // gui
    m_LoaderINI.sFont = ini.GetString(section_gui, "font", "plugins/files/font.ttf");
}