#include "../Header/Main.h"
#include "../Header/Export.h"


#ifdef __PSP
#include <pspkernel.h>
PSP_MODULE_INFO("h5nc", 0, 1, 1);
PSP_MAIN_THREAD_ATTR(0);
PSP_HEAP_SIZE_KB(-256);
extern "C"
{
#include "../../../include/exception.h"
};
#endif // __PSP

HGE *hge = NULL;
/*
int gametime = 0;

bool binit = false;
#include "../Header/BResource.h"
#include "../Header/SpriteItemManager.h"
hgeSprite * sp=NULL;
*/

#include "../Header/Process.h"

bool RenderFunc()
{
	/*
	hge->Gfx_BeginScene();
	hge->Gfx_Clear(0xffff00ff);

	if (sp)
	{
		SpriteItemManager::getInstance().RenderSprite(sp, 100, 100);
	}

	hge->Gfx_EndScene();
	*/

	Process::getInstance().render();
	
	return false;
}


bool FrameFunc()
{
	/*
	if (!binit)
	{
		BResource * pbres = &BResource::getInstance();
		pbres->ReadTables();
		pbres->LoadTexture(-1);
		SpriteItemManager::getInstance().CreateSprite(10, &sp);
		Export::clientAdjustWindow();
		binit = true;
	}
	*/
	Process * pp = &Process::getInstance();
	if (pp->SyncInputAndCheckEscSnap())
	{
		return true;
	}

	if(pp->frame() == PQUIT)
	{
		return true;
	}

	return false;
}

#ifdef __WIN32
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
#else
int main(int argc, char* argv[])
#endif
{
#ifdef __PSP
	initExceptionHandler();
#endif
	hge = hgeCreate(HGE_VERSION);
	
	hge->System_SetState(HGE_FRAMEFUNC, FrameFunc);
	hge->System_SetState(HGE_RENDERFUNC, RenderFunc);

	Export::clientInitial();

	if(hge->System_Initiate())
	{
		Process::getInstance().Init();
		hge->System_Start();
	}

	//
	//////////////////////////////////////////////////////////////////////////
//	Process::mp.Realease();

//	hge->System_Shutdown();
	Process::getInstance().Release();
	Export::Release();

	return 0;
}