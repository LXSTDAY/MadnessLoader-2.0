#include "../../dllmain.h"

CPlayerPed *FindPlayerPed(int playerId)
{
	return CPatch::CallFunction<CPlayerPed*>(g_libGTASA+0x3AC5DC+1, playerId);
}

CEntity *FindPlayerEntity(int playerId)
{
	return CPatch::CallFunction<CEntity*>(g_libGTASA+0x3AC554+1, playerId);
}

CVehicle *FindPlayerVehicle(int playerId, bool bIncludeRemote)
{
	return CPatch::CallFunction<CVehicle*>(g_libGTASA+0x3AC4AC+1, playerId, bIncludeRemote);
}

CVector const& FindPlayerSpeed(int playerId)
{
	return CPatch::CallFunction<CVector const&>(g_libGTASA+0x3AC45C+1, playerId);
}

void FindPlayerCoors(CVector*pos, int playerId)
{
	CPatch::CallFunction<void>(g_libGTASA+0x3AC3E4+1, pos, playerId);
}

void DefinedState() 
{
    CPatch::CallFunction<void>(g_libGTASA+0x559008+1);
}

void DefinedState2d()
{
    CPatch::CallFunction<void>(g_libGTASA+0x5590B0+1);
}

void cp1251_to_utf8(char *out, const char *in, unsigned int len)
{
    static const int table[128] = 
    {                    
        // 80
        0x82D0,     0x83D0,     0x9A80E2,   0x93D1,     0x9E80E2,   0xA680E2,   0xA080E2,   0xA180E2,
        0xAC82E2,   0xB080E2,   0x89D0,     0xB980E2,   0x8AD0,     0x8CD0,     0x8BD0,     0x8FD0,
        // 90
        0x92D1,     0x9880E2,   0x9980E2,   0x9C80E2,   0x9D80E2,   0xA280E2,   0x9380E2,   0x9480E2,
        0,          0xA284E2,   0x99D1,     0xBA80E2,   0x9AD1,     0x9CD1,     0x9BD1,     0x9FD1,
        // A0
        0xA0C2,     0x8ED0,     0x9ED1,     0x88D0,     0xA4C2,     0x90D2,     0xA6C2,     0xA7C2,              
        0x81D0,     0xA9C2,     0x84D0,     0xABC2,     0xACC2,     0xADC2,     0xAEC2,     0x87D0,
        // B0
        0xB0C2,     0xB1C2,     0x86D0,     0x96D1,     0x91D2,     0xB5C2,     0xB6C2,     0xB7C2,              
        0x91D1,     0x9684E2,   0x94D1,     0xBBC2,     0x98D1,     0x85D0,     0x95D1,     0x97D1,
        // C0
        0x90D0,     0x91D0,     0x92D0,     0x93D0,     0x94D0,     0x95D0,     0x96D0,     0x97D0,
        0x98D0,     0x99D0,     0x9AD0,     0x9BD0,     0x9CD0,     0x9DD0,     0x9ED0,     0x9FD0,
        // D0
        0xA0D0,     0xA1D0,     0xA2D0,     0xA3D0,     0xA4D0,     0xA5D0,     0xA6D0,     0xA7D0,
        0xA8D0,     0xA9D0,     0xAAD0,     0xABD0,     0xACD0,     0xADD0,     0xAED0,     0xAFD0,
        // E0
        0xB0D0,     0xB1D0,     0xB2D0,     0xB3D0,     0xB4D0,     0xB5D0,     0xB6D0,     0xB7D0,
        0xB8D0,     0xB9D0,     0xBAD0,     0xBBD0,     0xBCD0,     0xBDD0,     0xBED0,     0xBFD0,
        // F0
        0x80D1,     0x81D1,     0x82D1,     0x83D1,     0x84D1,     0x85D1,     0x86D1,     0x87D1,
        0x88D1,     0x89D1,     0x8AD1,     0x8BD1,     0x8CD1,     0x8DD1,     0x8ED1,     0x8FD1
    };

    int count = 0;

    while (*in)
    {
        if(len && (count >= len)) break;

        if (*in & 0x80)
        {
            register int v = table[(int)(0x7f & *in++)];
            if (!v)
                continue;   
            *out++ = (char)v;
            *out++ = (char)(v >> 8);
            if (v >>= 16)
                *out++ = (char)v;
        }
        else // ASCII
            *out++ = *in++;

        count++;
    }

    *out = 0;
}

RwTexture* LoadTexFromFile(const char* filename)
{
    RwInt32 width, height, depth, flags;
    RwImage *image = RtPNGImageRead(filename);
    if(!image) return 0;

    RwImageFindRasterFormat(image, 4, &width, &height, &depth, &flags);
    RwRaster *raster = RwRasterCreate(width, height, depth, flags);
    RwRasterSetFromImage(raster, image);

    RwImageDestroy(image);
    return RwTextureCreate(raster);
}

uintptr_t GetTexture(std::string szTexName) 
{
	uintptr_t pRwTexture = ((uintptr_t(*)(char const*))(g_libGTASA + 0x001BE990 + 1))(szTexName.c_str());
	if (pRwTexture) 
    {
		++* (uint32_t*)(pRwTexture + 0x54);
	}
	return pRwTexture;
}

uintptr_t FindRwTexture(std::string szTexDb, std::string szTexName) 
{
	uintptr_t pRwTexture = GetTexture(szTexName + std::string("_") + szTexDb);
	if (!pRwTexture) 
    {
		pRwTexture = GetTexture(szTexDb + std::string("_") + szTexName);
		if (!pRwTexture) 
        {
			pRwTexture = GetTexture(szTexName);
			if (!pRwTexture) 
            {
				return 0;
			}
		}
	}
	return pRwTexture;
}

bool IsPointInRect(int pointX, int pointY, float rectX1, float rectY1, float rectX2, float rectY2)
{
	if(
        (pointX >= rectX1 && pointX <= rectX2) 
        &&
        (pointY >= rectY1 && pointY <= rectY2)
    ) 
	{
		return true;
	}
	else return false;
}