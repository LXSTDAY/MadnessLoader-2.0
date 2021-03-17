#include "dllmain.h"
#include "SDK/gui/gui.h"
#include "SDK/gui/keyboard.h"
#include "SDK/gui/console.h"
#include "Events.h"

CGUI *pGUI = nullptr;
CKeyBoard *pKeyBoard = nullptr;
ConsoleGUI *pConsoleGUI = nullptr;

void InitRenderWareFunctions();

/* ====================================================== */

HOOK_DATA render2d_data;
void render2d_hook()
{   
    CPatch::CallFrom<void>(&render2d_data);

    for(int i = 0; i < MAX_FUNCS; i++)
	{
	    if(Events::FuncPool::Render2d[i] != 0)
	    {
		    CPatch::CallFunction<void>(Events::FuncPool::Render2d[i]);
	    }
	}
	
	if(pGUI) pGUI->Render();
}

/* ====================================================== */

HOOK_DATA touchEvent_data;
void touchEvent_hook(int type, int num, int posX, int posY)
{   
    bool bNext = false;
	if(pGUI) bNext = pGUI->OnTouchEvent(type, num, posX, posY);
	
	if(bNext)
	{
	    for(int i = 0; i < MAX_FUNCS; i++)
	    {
	        if(Events::FuncPool::TouchEvent[i] != 0)
	        {
			    CPatch::CallFunction<void>(Events::FuncPool::TouchEvent[i], type, num, posX, posY);
	        }
	    }
	}

	if(bNext) CPatch::CallFrom<void>(&touchEvent_data, type, num, posX, posY);    
}

/* ====================================================== */

HOOK_DATA CGame_Process_data;
void CGame_Process_hook()
{	
	for(int i = 0; i < MAX_FUNCS; i++)
	{
	    if(Events::FuncPool::GameProcBefore[i] != 0)
	    {
			CPatch::CallFunction<void>(Events::FuncPool::GameProcBefore[i]);
	    }
	}
	
	CPatch::CallFrom<void>(&CGame_Process_data);

	for(int i = 0; i < MAX_FUNCS; i++)
	{
	    if(Events::FuncPool::GameProcAfter[i] != 0)
	    {
			CPatch::CallFunction<void>(Events::FuncPool::GameProcAfter[i]);
	    }
	}
}

void Render2dHook()
{	
    CPatch::AddrHook(g_libGTASA + 0x39B098, &render2d_data, &render2d_hook);
	CPatch::AddrHook(g_libGTASA + 0x3986CC, &CGame_Process_data, &CGame_Process_hook);
	CPatch::AddrHook(g_libGTASA + 0x239D5C, &touchEvent_data, &touchEvent_hook);
}

/* ====================================================== */

bool Inited2 = false;

HOOK_DATA init2_data;
void init2_hook()
{   
    CPatch::CallFrom<void>(&init2_data);
	CPatch::WriteMemory(init2_data.addr, init2_data.orig, 16);

    if(!Inited2) 
    {   
		Render2dHook();
        InitScripting();
        Inited2 = true;
    }
}

/* ====================================================== */

HOOK_DATA initrw_data;
void initrw_hook()
{   
	for(int i = 0; i < MAX_FUNCS; i++)
	{
	    if(Events::FuncPool::InitRWBefore[i] != 0)
	    {
		    CPatch::CallFunction<void>(Events::FuncPool::InitRWBefore[i]);
	    }
	}

    CPatch::CallFrom<void>(&initrw_data); // orig

	for(int i = 0; i < MAX_FUNCS; i++)
	{
	    if(Events::FuncPool::InitRWAfter[i] != 0)
	    {
		    CPatch::CallFunction<void>(Events::FuncPool::InitRWAfter[i]);
	    }
	}   

	pGUI = new CGUI(); 
	pKeyBoard = new CKeyBoard(); 
	pConsoleGUI = new ConsoleGUI();

	
}

/* ====================================================== */

void Init2()
{
    CPatch::AddrHook(g_libGTASA + 0x45B328, &init2_data, &init2_hook); 
    CPatch::AddrHook(g_libGTASA + 0x40C530, &initrw_data, &initrw_hook); //renderware init
}

/* ====================================================== */

HOOK_DATA init_data;
int init_hook(int r1, int r2, int r3)
{   
	static bool Inited = false;
    int num = CPatch::CallFrom<int>(&init_data, r1, r2, r3);
    if(!Inited) 
	{
	    Events::FuncPool* funcPool = new Events::FuncPool();
		InitRenderWareFunctions();
		Init2(); 	 
        LoadPlugins();      
		Inited = true; 
	}
	
	return num;
}

/* ====================================================== */

uint16_t gxt_string[0x7F];
HOOK_DATA CText_Get_data;
uint16_t* CText_Get_hook(uintptr_t thiz, const char* text)
{

	uint16_t* ret = CPatch::CallFrom<uint16_t*>(&CText_Get_data, thiz, text);

	for (int i = 0; i < MAX_FUNCS; i++)
	{
		if (CText::gxt_parts[i] != 0 && CText::gxt_texts[i] != 0)
		{
			if(!strcmp(text, CText::gxt_parts[i]))
			{
				CFont::AsciiToGxtChar(CText::gxt_texts[i], gxt_string);
				ret = gxt_string;
				break;
			}
		}		
	}
		
	
	return ret;
}

/* ====================================================== */

bool bShowImGui = false;
void Show_ImGui()
{
	if(!bShowImGui) bShowImGui = true;
	else bShowImGui = false;
}

HOOK_DATA MenuItem_add_data;
void MenuItem_add_hook(int r0, uintptr_t r1)
{
	static bool bMenuInited = false;
	char* name = *(char**)(r1+4);

	if(!strcmp(name, "FEP_RES"))
	{
		CPatch::CallFrom<void>(&MenuItem_add_data, r0, r1); // orig
	    
	    if (!Inited2) return;
        
        *(char**)(r1+4) = "CMD__PM";
		*(RwTexture**)r1 = LoadTexFromFile("../plugins/files/cmdline.png");
		*(uintptr_t*)(r1+8) = (uintptr_t)Show_ImGui;

        
		goto ret;
	}

ret:
	CPatch::CallFrom<void>(&MenuItem_add_data, r0, r1); // orig
}

/* ====================================================== */

HOOK_DATA MenuScreen_Update_data;
uintptr_t MenuScreen_Update_hook(uintptr_t thiz, float a1)
{
	uintptr_t ret = CPatch::CallFrom<uintptr_t>(&MenuScreen_Update_data, thiz, a1);

		for (int i = 0; i < MAX_FUNCS; i++)
		{
			if(Events::FuncPool::MenuScreenUpdate[i] != 0)
			{
				CPatch::CallFunction<void>(Events::FuncPool::MenuScreenUpdate[i]);
			}
		}

	return ret;
}

/* ====================================================== */

char* nickNames =  "Dev: Fierrum COBALT GOR Foretti Doomer kronka, thanks for plugin-sdk and Subscribes :3"  ; 

HOOK_DATA MenuScreen_Render_data;
void MenuScreen_Render_hook(uintptr_t thiz)
{
	CPatch::CallFrom<void>(&MenuScreen_Render_data, thiz);

	CFont::SetColor(CRGBA(255, 255, 255, 255));
	CFont::SetFontStyle(FONT_SUBTITLES);
	CFont::SetScaleXY(1.0, 2.0);
	CFont::SetCentreSize(0);
	CFont::SetJustify(false);
	CFont::SetRightJustifyWrap(0);
	
	if(pGUI)
	{
		static float fPosX = 0;
		if(fPosX < pGUI->ScaleX(1920))
		{
			fPosX += pGUI->ScaleX(2.0f);
			CFont::PrintString(fPosX, pGUI->ScaleY(1035), nickNames);
		}
		else
		{
			CFont::PrintString(pGUI->ScaleX(5), pGUI->ScaleY(1035), "PM Mods");
		}
		
	}
}


void InitInGameStuff()
{ 
    CPatch::AddrHook(g_libGTASA + 0x244F2C, &init_data, &init_hook); //Java
    CPatch::AddrHook(g_libGTASA + 0x269974, &MenuItem_add_data, &MenuItem_add_hook);
	CPatch::AddrHook(g_libGTASA + 0x4D3864, &CText_Get_data, &CText_Get_hook);
	CPatch::AddrHook(g_libGTASA + 0x25E660, &MenuScreen_Update_data, &MenuScreen_Update_hook);
	CPatch::AddrHook(g_libGTASA + 0x259008, &MenuScreen_Render_data, &MenuScreen_Render_hook);
}