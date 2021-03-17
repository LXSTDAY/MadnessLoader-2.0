
#include "../../Events.h"
#include "../../ini.h"
#include "gui.h"
#include "keyboard.h"
#include "console.h"

extern CLoaderINI *pLoaderINI;
extern CKeyBoard *pKeyBoard;
extern ConsoleGUI *pConsoleGUI;

/* imgui_impl_renderware.h */
void ImGui_ImplRenderWare_RenderDrawData(ImDrawData* draw_data);
bool ImGui_ImplRenderWare_Init();
void ImGui_ImplRenderWare_NewFrame();
void ImGui_ImplRenderWare_ShutDown();

/*
	Все координаты GUI-элементов задаются
	относительно разрешения 1920x1080
*/

#define MULT_X	0.00052083333f	// 1/1920
#define MULT_Y	0.00092592592f 	// 1/1080

CGUI::CGUI()
{
	// setup ImGUI
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO &io = ImGui::GetIO();

	ImGui_ImplRenderWare_Init();

	// scale
	m_vecScale.x = io.DisplaySize.x * MULT_X;
	m_vecScale.y = io.DisplaySize.y * MULT_Y;
	// font Size
	m_fFontSize = ScaleY( 30 );

	// mouse/touch
	m_bMousePressed = false;
	m_vecMousePos = ImVec2(0, 0);

    ImGui::StyleColorsDark();

	// buttons
	m_bKeysStatus = false;

	// load fonts
	char path[0xFF];
	sprintf(path, "%s%s", GameStorage, pLoaderINI->Get().sFont.c_str());
	
	// cp1251 ranges
	static const ImWchar ranges[] =
	{
		0x0020, 0x0080,
		0x00A0, 0x00C0,
		0x0400, 0x0460,
		0x0490, 0x04A0,
		0x2010, 0x2040,
		0x20A0, 0x20B0,
		0x2110, 0x2130,
		0
	};

	m_pFont = io.Fonts->AddFontFromFileTTF(path, m_fFontSize, nullptr, ranges);

	
}


CGUI::~CGUI()
{
	ImGui_ImplRenderWare_ShutDown();
	ImGui::DestroyContext();
}

extern bool bShowImGui;
void CGUI::Render()
{
	ImGuiIO& io = ImGui::GetIO();

	ImGui_ImplRenderWare_NewFrame();
	ImGui::NewFrame();
	
	for(int i = 0; i < MAX_FUNCS; i++)
	{
	    if(Events::FuncPool::ImGuiRender[i] != 0)
	    {
			CPatch::CallFunction<void>(Events::FuncPool::ImGuiRender[i]);
	    }
	}

	if(bShowImGui) pConsoleGUI->Render();

	if(pKeyBoard) pKeyBoard->Render();
	
	ImGui::EndFrame();
	ImGui::Render();
	ImGui_ImplRenderWare_RenderDrawData(ImGui::GetDrawData());

	if(m_bNeedClearMousePos)
	{
		io.MousePos = ImVec2(-1, -1);
		m_bNeedClearMousePos = false;
	}
}

bool CGUI::OnTouchEvent(int type, bool multi, int x, int y)
{
	ImGuiIO& io = ImGui::GetIO();

	if(pKeyBoard) pKeyBoard->OnTouchEvent(type, multi, x, y);
	if(pKeyBoard->m_bEnable) return false;

	switch(type)
	{
		case TOUCH_PUSH:
		io.MousePos = ImVec2(x, y);
		io.MouseDown[0] = true;
		break;

		case TOUCH_POP:
		io.MouseDown[0] = false;
		m_bNeedClearMousePos = true;
		break;

		case TOUCH_MOVE:
		io.MousePos = ImVec2(x, y);
		break;
	}

	return true;
}

