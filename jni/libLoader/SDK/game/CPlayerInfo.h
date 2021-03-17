#pragma once
#include "../../dllmain.h"

#pragma pack(push, 1)
class CPlayerInfo {
public:
    PADDING(_pad000, 98);
    RwTexture* pSkinTexture;    //098-102 
    PADDING(_pad102, 357-102);
    char szSkinName[32];        //357-389
    PADDING(_pad389, 100);

    bool IsPlayerInRemoteMode();
};
#pragma pack(pop)