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

int gametime = 0;

#include "../UIBase/include/UIFrame.h"


bool RenderFunc()
{
	hge->Gfx_BeginScene();
	hge->Gfx_Clear(0x00000000);

	UIFrameNode::GlobalRender();

	hge->Gfx_EndScene();
	
	return false;
}

UIContainer container;
UIContainer frame;

#define _NUM 4
UIButton button[_NUM];
UIStatusFrame status[_NUM];
UIHoverFrame hover[_NUM];
UIButtonHelpFloatingContainer bhfc[_NUM];
bool init = false;

bool FrameFunc()
{
	UIFrameNode::GlobalUpdate();

	if (!init)
	{
		for (int i=0; i<_NUM; i++)
		{
			status[i].SetXYWH(i*50+1, 1, 48, 48);
			hover[i].SetXYWH(i*50+1, 1, 48, 48);
			button[i].SetXYWH(i*50, 0, 50, 50);
			bhfc[i].SetXYWH(i*50+60, 60, 100, 100);
		}
		container.SetXYWH(0, 0, 400, 200);
		frame.SetXYWH(00, 0, 350, 150);

		UIFrameNode::basenode.AddChild(&container);
		container.AddChild(&frame);
		for (int i=0; i<_NUM; i++)
		{
			frame.AddChild(&button[i]);
			button[i].AddChild(&hover[i]);
			button[i].AddChild(&status[i]);
			button[i].AddChild(&bhfc[i]);
		}

		init = true;
	}
//	container.OnUpdate();

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
		gametime = 0;
//		Process::mp.state = STATE_INIT;
		hge->System_Start();
	}

	//
	//////////////////////////////////////////////////////////////////////////
//	Process::mp.Realease();

//	hge->System_Shutdown();
	Export::Release();

	return 0;
}