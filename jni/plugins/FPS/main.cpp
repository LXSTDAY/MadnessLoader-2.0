#include "main.h"

void MainHooks();

void ShowFPS()
{	
	CPatch::CallFunction<void>(g_libGTASA + 0x39A0C4 + 1);
	char buff[50];
	float count = CPatch::CallFunction<float>(g_libGTASA + 0x39A054 + 1);
	sprintf(buff, "FPS: %.2f", count);
	ImGui::GetBackgroundDrawList()->AddText(ImVec2(5, 5), ImColor(255, 255, 255), buff);
}

plugin::plugin()
{	
	// fps patches
	CPatch::WriteMemory(g_libGTASA + 0x463FE8, "\x3C", 1);
	CPatch::WriteMemory(g_libGTASA + 0x56C1F6, "\x3C", 1);
	CPatch::WriteMemory(g_libGTASA + 0x56C126, "\x3C", 1);
	CPatch::WriteMemory(g_libGTASA + 0x95B074, "\x3C", 1);
	CPatch::WriteMemory(g_libGTASA + 0x56C1A2, "\x3C", 1);
	
	Events::ImGuiRender(&ShowFPS);
}
plugin Plugin;

