#pragma once
#include "dllmain.h"
#define MAX_FUNCS 512

typedef void addrfunc();

enum typeEvents
{
    TYPE_BEFORE,
    TYPE_AFTER
};

namespace Events
{
    class FuncPool
{
public:
    static uintptr_t    InitRWBefore[MAX_FUNCS],
                        InitRWAfter[MAX_FUNCS],
                        ImGuiRender[MAX_FUNCS],
                        Render2d[MAX_FUNCS],
                        GameProcBefore[MAX_FUNCS],
                        GameProcAfter[MAX_FUNCS],
                        TouchEvent[MAX_FUNCS],
                        MenuScreenUpdate[MAX_FUNCS];

    FuncPool()
    {
        for(int i = 0; i < MAX_FUNCS; i++)
        {
        ImGuiRender[i] = 0;
        Render2d[i] = 0;

        InitRWBefore[i] = 0;
        InitRWAfter[i] = 0;

        GameProcBefore[i] = 0;
        GameProcAfter[i] = 0;
        
        TouchEvent[i] = 0;

        MenuScreenUpdate[i] = 0;
        }
    }
};
} // namespace Events



namespace Events
{   
    template<typename Func, typename Pool>
    static void AttachToPool(Func func, Pool pool) {
        for(int i = 0; i < MAX_FUNCS; i++)
        {   
            if(pool[i] == 0)
            {
                pool[i] = (uintptr_t)func;
                break; 
            }
        }
    }
    
    static void InitRW(typeEvents type, addrfunc* func) 
    {
        if(type == TYPE_BEFORE) AttachToPool(func, FuncPool::InitRWBefore);
        if(type == TYPE_AFTER) AttachToPool(func, FuncPool::InitRWAfter); 
    }
    static void ImGuiRender(addrfunc* func) { AttachToPool(func, FuncPool::ImGuiRender); }
    static void Render2d(addrfunc* func) { AttachToPool(func, FuncPool::Render2d); }
    static void GameProcess(typeEvents type, addrfunc* func)
    {
        if(type == TYPE_BEFORE) AttachToPool(func, FuncPool::GameProcBefore);
        if(type == TYPE_AFTER ) AttachToPool(func, FuncPool::GameProcAfter);
    }
    static void TouchEvent(addrfunc* func) { AttachToPool(func, FuncPool::TouchEvent); }
    static void MenuScreenUpdate(addrfunc* func) { AttachToPool(func, FuncPool::MenuScreenUpdate); }
    
    
};