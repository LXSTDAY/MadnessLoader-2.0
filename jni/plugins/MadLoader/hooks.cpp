#include "main.h"
#include <ftw.h>
#include <fnmatch.h>

RwTexDictionary *TXD[512];
static const char *filters[] = {
    "*.txd"
};

static const char *filtersAllFiles[] = {
    "*.dat", "*.img", "*.ifp", "*.osw", ".idx", 
    "*.ipl", "*.ide", "*.col", "*.fxp", "*.cfg", 
    "*.zon", "*.gxt", "*.png", "*.scm", "*.dff"
};

static const char *filtersImgs[] = {
    "*.img"
};

static int CallbackTXD(const char *fpath, const struct stat *sb, int typeflag) {
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
                int i = file_.find("/madloader/");
                file_ = file_.substr(i, file_.size() - i);

                i = file_.find("/");
                file_ = file_.erase(i, i + 11);

                while (file_.find("/") != std::string::npos)
                {
                    int b = file_.find("/");
                    file_[b] = '\\';
                }

                Log("found txd: %s, loading..", file_.c_str());

                char buff[0xff];
                sprintf(buff, "..\\plugins\\madloader\\%s", file_.c_str());

                for (int i = 1; i < 100 + 1; i++)
                {
                    if (!TXD[i])
                    {
                        TXD[i] = CPatch::CallFunction<RwTexDictionary*>(g_libGTASA + 0x3FFBBC +1, buff);
                        break;
                    }
                    
                }
                

                break;
            }
        }
    }

    /* tell ftw to continue */
    return 0;
}
RwStream* bmx;
void LoadTxdFromFolder()
{	
	char path[0xff];
    sprintf(path, "%splugins/madloader/", GameStorage);
    ftw(path, CallbackTXD, 100);
}

HOOK_DATA GetTexture_data;
RwTexture* GetTexture_hook(const char *name)
{   
    static bool bLoaded = false;
    RwTexture*   origTex;
    RwTexture*   newTex;

    if(!bLoaded) LoadTxdFromFolder();
    
    origTex = CPatch::CallFrom<RwTexture*>(&GetTexture_data, name);

    for (int i = 1; i <= 100 + 1; i++)
    {   
                                 // RwTexDictionaryFindNamedTexture
        if(TXD[i] != 0) newTex = CPatch::CallFunction<RwTexture*>(g_libGTASA + 0x001B1CC0 + 1, TXD[i], name);
        if(newTex) 
        {
            Log("texture \"%s\" replaced", name);
            break;
        }
    }

    bLoaded = true;
    
    if(newTex) return newTex;
    return origTex;
}

/* ====================================================== */

void MainHooks()
{
    CPatch::AddrHook(g_libGTASA + 0x1BE990, &GetTexture_data, &GetTexture_hook);
}