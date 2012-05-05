#ifndef _MAIN_H
#define _MAIN_H

#include "MainDependency.h"

bool RenderFunc();
bool FrameFunc();
bool GfxRestoreFunc();
bool ExitFunc();

int GameStart(int seed=0);
int GameEnd();

extern HGE * hge;

extern int gametime;

#endif