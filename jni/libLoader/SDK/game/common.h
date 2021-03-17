#pragma once
#include "../../dllmain.h"
#include "CPlayerPed.h"
#include "CEntity.h"
#include "CVehicle.h"
#include "CVector.h"

// returns player ped
CPlayerPed *FindPlayerPed(int playerId = -1);
// returns player entity
CEntity *FindPlayerEntity(int playerId = -1);
// returns player vehicle
CVehicle *FindPlayerVehicle(int playerId, bool bIncludeRemote);
// returns player speed
CVector const& FindPlayerSpeed(int playerId);
void FindPlayerCoors(CVector*pos, int playerId = -1);

void DefinedState();
void DefinedState2d();

struct SCREEN2D_DATA
{
    int sizeX = RsGlobal->maximumWidth;
    int sizeY = RsGlobal->maximumHeight;

    float globalPointX = sizeX / 640.0f;
    float globalPointY = sizeY / 448.0f;

    float scaleX = sizeX * (1.0f / 1920);
    float scaleY = sizeX * (1.0f / 1080);
};

void cp1251_to_utf8(char *out, const char *in, unsigned int len = 0);

RwTexture* LoadTexFromFile(const char* filename);
uintptr_t GetTexture(std::string szTexName);
uintptr_t FindRwTexture(std::string szTexDb, std::string szTexName);

bool IsPointInRect(int pointX, int pointY, float rectX1, float rectY1, float rectX2, float rectY2);