#include "../Header/Main.h"
#include "../Header/Export.h"

#include "../Header/CheatsIO.h"


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

#ifdef __IPHONE
#include "MainApplicationFunctions.h"
#endif

HGE *hge = NULL;

int gametime = 0;

HTEXTURE ptex;

bool RenderFunc()
{
//	hge->Gfx_BeginScene();
//	hge->Gfx_Clear(0x00000000);
	
	return CheatsIO::cheatsio.RenderFunc();
	
}

bool FrameFunc()
{
	return CheatsIO::cheatsio.FrameFunc();
	return false;
}

int GameStart(int seed)
{
#ifdef __PSP
	initExceptionHandler();
#endif
	
	Export::clientInitial(true);
	
	if(hge->System_Initiate())
	{
		gametime = 0;
		//		Process::mp.state = STATE_INIT;
#ifndef __IPHONE
		hge->System_Start();
#endif
	}
	
}


#if defined __IPHONE
void TouchCallback_ButtonDown(float x, float y, int ID)
{
	CheatsIO::cheatsio.touches[ID].x = y;
	CheatsIO::cheatsio.touches[ID].y = 320-x;
	CheatsIO::cheatsio.touches[ID].on = true;
//	hge->Input_SetTouchPos(ID, y, x);
}
void TouchCallback_ButtonUp(float x, float y, int ID)
{
	CheatsIO::cheatsio.touches[ID].on = false;
//	hge->Input_SetTouchPos(ID, y, x);
}
void TouchCallback_Move(float x, float y, int ID)
{
	CheatsIO::cheatsio.touches[ID].x = y;
	CheatsIO::cheatsio.touches[ID].y = 320-x;
	CheatsIO::cheatsio.touches[ID].on = true;
//	hge->Input_SetTouchPos(ID, y, x);
}
#endif

int GameEnd()
{
	//
	//////////////////////////////////////////////////////////////////////////
	//	Process::mp.Realease();
	CheatsIO::cheatsio.Release();
	
	//	hge->System_Shutdown();
	Export::Release();
	hge->Release();
	return 0;
}

#if defined __IPHONE
int Application_Loop()
{
//	Export::clientSetMatrix();
	hge->System_Start();
	return 0;
}
int Application_Quit()
{
	GameEnd();
	return 1;
}
#endif

#if defined __WIN32
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
#elif defined __PSP
int main(int argc, char* argv[])
#elif defined __IPHONE
int Application_Init()
#endif
{
	hge = hgeCreate(HGE_VERSION);
	
	hge->System_SetState(HGE_FRAMEFUNC, FrameFunc);
	hge->System_SetState(HGE_RENDERFUNC, RenderFunc);
	
#if defined __IPHONE
	hge->Resource_SetPath(ResourceGetBaseDirectory());
	hge->Resource_SetPath(ResourceGetAppDirectory());
	hge->System_SetState(HGE_USESOUND, false);
	hge->System_SetState(HGE_MANAGELOOP, false);
#endif


	GameStart();
#ifndef __IPHONE
	GameEnd();
#endif

	return 0;
}