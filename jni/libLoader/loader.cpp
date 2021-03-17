#include "dllmain.h"
#include <dlfcn.h>
#include <ftw.h>
#include <fnmatch.h>

char buff[0x7F];
char* PLAYERS_REALLOC = nullptr;

void InitLoaderStuff()
{   
    const char* thumb = "texdb/%s/%s.dxt.tmb";
    const char* dataoff = "texdb/%s/%s.dxt";
    PLAYERS_REALLOC = (( char* (*)(int))(g_libGTASA+0x179B40))(404*1004);
	CPatch::UnFuck(g_libGTASA+0x5D021C);
	PLAYERS_REALLOC = *(char**)(g_libGTASA+0x5D021C);

    /*CPatch::WriteMemory(g_libGTASA + 0x573648, thumb, 20);
    CPatch::WriteMemory(g_libGTASA + 0x57365C, thumb, 20);
    CPatch::WriteMemory(g_libGTASA + 0x573670, thumb, 20);
    CPatch::WriteMemory(g_libGTASA + 0x573684, thumb, 20);

    CPatch::WriteMemory(g_libGTASA + 0x5736AC, dataoff, 16);
    CPatch::WriteMemory(g_libGTASA + 0x5736BC, dataoff, 16);
    CPatch::WriteMemory(g_libGTASA + 0x5736CC, dataoff, 16);
    CPatch::WriteMemory(g_libGTASA + 0x5736DC, dataoff, 16);*/

    uintptr_t g_libSCAnd = CPatch::FindLibrary("libSCAnd.so");
	CPatch::WriteMemory(g_libSCAnd + 0x1E16DC, cryptor::create("com/rockstargames/hal/andViewManager", 37).decrypt(), 37);
	CPatch::WriteMemory(g_libSCAnd + 0x1E1738, cryptor::create("staticExitSocialClub", 21).decrypt(), 21);
	CPatch::WriteMemory(g_libSCAnd + 0x1E080C, cryptor::create("()V", 4).decrypt(), 4);

    CText::RegisterNewGXT("CMD__PM", "CmdLine");
}

static const char *filters[] = {
    "*.pm"
};

static int Callback(const char *fpath, const struct stat *sb, int typeflag) {
    /* if it's a file */
    if (typeflag == FTW_F) 
    {
        int i;
        /* for each filter, */
        for (i = 0; i < sizeof(filters) / sizeof(filters[0]); i++) 
        {
            /* if the filename matches the filter, */
            if (fnmatch(filters[i], fpath, FNM_CASEFOLD) == 0) 
            {
                /* do something */
                
                string file_ = fpath;
                int i = file_.find_last_of("/");
                file_ = file_.substr(i + 1, file_.size() - i - 1);
                i = file_.find(".");
                file_ = file_.erase(i, i + 2);

                Log("LOADER >> found plugin \"%s\", loading..", file_.c_str());
                CopyFile(file_.c_str());

                char buff[0xff];
                sprintf(buff, "%scache/lib%s.so", RootStorage, file_.c_str());
			    void* v0 = dlopen(buff, 3);
			    if (!v0) { Log("LOADER >> plugin \"%s\" not installed!", file_.c_str()); }

                break;
            }
        }
    }

    /* tell ftw to continue */
    return 0;
}

void LoadPlugins()
{	
	char path[0xff];
    sprintf(path, "%splugins/", GameStorage);
    ftw(path, Callback, 512);	
}
