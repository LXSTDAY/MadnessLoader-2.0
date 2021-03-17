#pragma once
#include "../../dllmain.h"
#include "CEntity.h"
#include "CPlayerPed.h"
#include "CPhysical.h"

class CPlayerPed;

#pragma pack(push, 1)
class CVehicle : public CPhysical
{
public:
	PADDING(_pad201, 885);		// 0184-1069
	uint8_t _pad2011 : 7;		// 1069-1070 	(bits 0..6)
	uint8_t byteSirenOn : 1;	// 1069-1070	(bit 7)
	PADDING(_pad2012, 6);		// 1070-1076
	uint8_t byteColor1;			// 1076-1077	;byteColor1
	uint8_t byteColor2;			// 1077-1078	;byteColor2
	uint8_t byteColor3;			// 1078-1079
    uint8_t byteColor4;			// 1079-1080
    char   anExtras[2];			// 1080-1082
    short  anUpgrades[15];		// 1082-1112
    float    fWheelScale;		// 1112-1116
    uint16_t nAlarmState;		// 1116-1118
    short  nForcedRandomRouteSeed; // 1118-1120 if this is non-zero the random wander gets deterministic
	CPlayerPed *pDriver;		// 1120-1124	;driver
	CPlayerPed *pPassengers[7];	// 1124-1152	;pPassengers
	PADDING(_pad202, 72);		// 1152-1224
	float fHealth;				// 1224-1228	;fHealth
	PADDING(_pad203, 56);		// 1228-1284
	uint32_t dwDoorsLocked;		// 1284-1288	;dwDoorsLocked

	bool IsDriver(CPlayerPed* ped);
};
#pragma pack(pop)