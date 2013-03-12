#pragma once

#include "MainDependency.h"
#include "Const.h"

enum
{
	PQUIT,
	PGO,
	POK,
	PBACK,
	PTURN,
	PSKIP
};

enum{
	STATE_START,
	STATE_DEAD,
	STATE_TITLE,
	STATE_INIT,
};

class Process 
{
public:
	static Process* PIns() { static Process instance; return &instance; }

private:
	Process();
	~Process();
	Process(Process const&);
	void operator=(Process const&);

public:

	void Init();
	void Release();

	bool SyncInputAndCheckEscSnap();
	void SnapShot();

	bool	reload();

	int		getInput();
	char	getInputNowChar(bool wide);

	int frame();
	void	frameStart();
	void	frameEnd();

	int		render();
	void	_Render(BYTE renderflag=M_RENDER_NULL);
	void	_RenderTar();
	int		renderInit();

	int processTitle();
	int processStart();
	int processDead();
	int processInit();


#ifdef _DEBUG
	void Debug_Test();
#endif
	
	int state;

	int gametime;
	int lasttime;

	int worldxoff;
	int worldyoff;
	int screenwidth;
	int screenheight;
}; 

extern HGE * hge;