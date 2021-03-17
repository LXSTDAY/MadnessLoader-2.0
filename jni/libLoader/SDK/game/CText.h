#pragma once
#include "../../dllmain.h"

class CText
{
private:
    /* data */
public:

    static const char* gxt_parts[512];
    static const char* gxt_texts[512];
    static void RegisterNewGXT(const char* gxt_name, const char* gxt_text);
};