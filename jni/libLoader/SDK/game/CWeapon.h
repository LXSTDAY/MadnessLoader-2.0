#pragma once
#include "../../dllmain.h"

#pragma pack(push, 1)
class CWeapon
{
public:
    uint32_t dwType;
	uint32_t dwState;
	uint32_t dwAmmoInClip;
	uint32_t dwAmmo;
	PADDING(_pwep1,12);
};
#pragma pack(pop)