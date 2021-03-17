#include "main.h"

void MainHooks();

void ApplyPatches()
{	
	CPatch::NOP(g_libGTASA + 0x39B36A, 2); // NOP RenderEffects
	CPatch::NOP(g_libGTASA + 0x39ADE6, 2); // NOP CCoronas::RenderSunReflection
	CPatch::WriteMemory(g_libGTASA + 0x52DD38, "\x00\x20\xf7\x46", 4); // return 0 CCoronas::RenderReflections
}

void DebugWindow()
{

}

plugin::plugin()
{	
	ApplyPatches();
	Events::ImGuiRender(&DebugWindow);
}
plugin Plugin;

