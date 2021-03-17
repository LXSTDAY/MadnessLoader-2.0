#include "../../dllmain.h"

bool CPlayerInfo::IsPlayerInRemoteMode()
{
    return CPatch::CallFunction<bool>(g_libGTASA+0x3ABD28+1, this);
}