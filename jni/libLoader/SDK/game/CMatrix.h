#pragma once
#include "../../dllmain.h"
#include "CVector.h"

#pragma pack(push, 1)
class CMatrix {
public:
    // RwV3d-like:
    CVector      right;
    unsigned int flags;
    CVector      up;
    unsigned int pad1;
    CVector      at;
    unsigned int pad2;
    CVector      pos;
    unsigned int pad3;
};
#pragma pack(pop)