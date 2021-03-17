#include "dllmain.h"
#include "samp.h"
#include "ini.h"
#include <jni.h>
#include <dlfcn.h>
#include <android/log.h>

CLoaderINI *pLoaderINI = nullptr;
CSAMP* pSAMP = nullptr;

#define STANDART_VER
//#define SANTROPE_VER
//#define MORDOR_VER
//#define FLIN_VER

#ifdef STANDART_VER
	const char* GameStorage = "/storage/emulated/0/Android/data/com.madness.game/";
	const char* RootStorage = "/data/data/com.madness.game/";
#endif

#ifdef SANTROPE_VER
	const char* GameStorage = "/storage/emulated/0/Android/data/com.santrope.game/";
	const char* RootStorage = "/data/data/com.santrope.game/";
	const char* ThreadName  = "com.santrope.game";
#endif

#ifdef MORDOR_VER
	const char* GameStorage = "/storage/emulated/0/Android/data/com.rockstargames.gtasa/";
	const char* RootStorage = "/data/data/com.rockstargames.gtasa/";
#endif

#ifdef FLIN_VER
	const char* GameStorage = "/storage/emulated/0/Android/data/com.flin.sa/";
	const char* RootStorage = "/data/data/com.com.flin.sa/";
#endif

 
uintptr_t g_libGTASA = 0;
uintptr_t g_libSAMP  = 0;
uintptr_t g_libCLEO  = 0;
uintptr_t g_libSTUFF = 0;

void InitLoaderStuff();
void InitInGameStuff();

jint JNI_OnLoad(JavaVM *vm, void *reserved)
{
	g_libGTASA = CPatch::FindLibrary("libGTASA.so");
    if (!g_libGTASA) return 0;
	
	pLoaderINI = new CLoaderINI();
	Log("\nLOADER >> Sucessfull started!");
	Log("LOADER >> Build %.1f", VERSION);

	Log("LOADER >> starting game..");
	CPatch::InitHookStuff(); 
	if(pLoaderINI->Get().bMultiplayer) // is needed multiplayer
	{	
		Log("LOADER >> Multiplayer selected, loading..");
		pSAMP = new CSAMP(vm);
		g_libSAMP = pSAMP->GetBaseAddress();
	}
	else // is needed only singleplyer
	{	
		Log("LOADER >> Singleplayer selected, loading..");
		g_libCLEO = CPatch::FindLibrary("libcleo.so"); // needed modified library for hooks ( already installed in apk )
		Log("LOADER >> Install cleo hooks/patches..");
#ifndef SANTROPE_VER
#ifndef FLIN_VER
		CLEO::InstallHooks();
		CLEO::ApplyPatches();
		CLEO::InitInGame();
		if(CLEO::IsAlreadyInstalled()) Log("CLEO >> Already installed in game!");
#endif
#endif
	}

	Log("LOADER >> Init stuff..");
	InitLoaderStuff();
	Log("LOADER >> Init 'InGame' stuff..");
	InitInGameStuff();
	
	return JNI_VERSION_1_4;
}
