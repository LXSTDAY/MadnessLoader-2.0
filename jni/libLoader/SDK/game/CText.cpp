#include "../../dllmain.h"

const char* CText::gxt_parts[512];
const char* CText::gxt_texts[512];

void CText::RegisterNewGXT(const char* gxt_name, const char* gxt_text)
{
    for (int i = 0; i < 512; i++)
    {   
        if (!gxt_parts[i] && !gxt_texts[i])
        {
            gxt_parts[i] = gxt_name;
            gxt_texts[i] = gxt_text;
            break;
        }
        else if(!strcmp(gxt_parts[i], gxt_name))
        {
            gxt_parts[i] = gxt_name;
            gxt_texts[i] = gxt_text;
            break;
        }   
    }

    Log("GXT index: %s | Added text: \"%s\"", gxt_name, gxt_text);
}