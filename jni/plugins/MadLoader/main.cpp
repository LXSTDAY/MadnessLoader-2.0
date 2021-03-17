#include "main.h"

//plugin stuff//
void MainHooks();

class plugin
{
public:
    plugin()
	{	
		Events::InitRW(TYPE_BEFORE, &InitRW);
	}

	static void InitRW()
	{
		MainHooks();
	}
};

plugin Plugin;

