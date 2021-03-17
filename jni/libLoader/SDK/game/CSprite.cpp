/*
    Plugin-SDK (Grand Theft Auto San Andreas) source file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#include "../../dllmain.h"

void CSprite::RenderOneXLUSprite(float x, float y, float z, float halfWidth, float halfHeight, 
								 unsigned char red, unsigned char green, unsigned char blue, 
								 short alpha, float rhw, unsigned char intensity, unsigned char udir, 
								 unsigned char vdir)
{
	CPatch::CallFunction<void>(g_libGTASA+0x54F688+1, x, y, z, halfWidth, halfHeight, red, green, blue, alpha, rhw, intensity, udir, vdir);
}

bool CSprite::CalcScreenCoors(RwV3d const &posn, RwV3d *out, float *w, float *h, bool checkMaxVisible, bool checkMinVisible)
{
	return CPatch::CallFunction<bool>(g_libGTASA+0x54EEC0+1, posn, out, w, h, checkMaxVisible, checkMinVisible);
}