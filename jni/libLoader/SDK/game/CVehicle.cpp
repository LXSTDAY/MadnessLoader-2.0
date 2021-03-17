#include "../../dllmain.h"

bool CVehicle::IsDriver(CPlayerPed* ped)
{
    return CPatch::CallFunction<bool>(g_libGTASA+0x5105E0+1, this, ped);
}