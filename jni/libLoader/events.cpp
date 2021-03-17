#include "dllmain.h"
#include "Events.h"

uintptr_t   Events::FuncPool::InitRWBefore[MAX_FUNCS],
            Events::FuncPool::InitRWAfter[MAX_FUNCS],
            Events::FuncPool::ImGuiRender[MAX_FUNCS],
            Events::FuncPool::Render2d[MAX_FUNCS],
            Events::FuncPool::GameProcBefore[MAX_FUNCS],
            Events::FuncPool::GameProcAfter[MAX_FUNCS],
            Events::FuncPool::TouchEvent[MAX_FUNCS],
            Events::FuncPool::MenuScreenUpdate[MAX_FUNCS];