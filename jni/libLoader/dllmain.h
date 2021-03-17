#pragma once 

#define VERSION 2.0

#define PADDING(x,y) uint8_t x[y]
#define IN_VEHICLE(x) ((x->dwStateFlags & 0x100) >> 8)

#include <cstdlib>
#include <string>
#include <vector>
#include <list>
#include <unistd.h>

#include "events.h"
#include "cleo.h"

#include "SDK/vendor.h"
#include "SDK/gui/console.h"
#include "SDK/game/game_sa.h"

extern uintptr_t g_libGTASA;
extern uintptr_t g_libCLEO;
extern uintptr_t g_libSAMP;
extern uintptr_t g_libSTUFF;

extern const char* GameStorage;
extern const char* RootStorage;

void LoadPlugins();