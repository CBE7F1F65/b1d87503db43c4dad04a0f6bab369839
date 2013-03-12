#ifndef _DATASTRUCT_H
#define _DATASTRUCT_H

#include "Const.h"
#include "InterObj.h"

struct textureData
{
	char texfilename[M_STRMAX];
	int width;
	int height;
};

struct musicData{
	char musicname[M_STRMAX];
	char musicfilename[M_PATHMAX];
#ifdef __IPHONE
	char _unused[4];
#endif
	LONGLONG startpos;
	LONGLONG introlength;
	LONGLONG alllength;
};

struct spriteData 
{
	char spritename[M_STRMAX];
	int tex_x;
	int tex_y;
	int tex_w;
	int tex_h;
	int tex;
};

struct playerMotionData
{
	int basesiid;
	int siidoffset[ANIMATIONMAX-1];
	int duration[ANIMATIONMAX];
	float bbxoff;
	float bbyoff;
	float bbw;
	float bbh;
};

#endif