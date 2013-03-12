#pragma once

#include "MainDependency.h"
#include "DataStruct.h"
#include "Player.h"

#define RSIZE_TEXTURE		(sizeof(textureData) * TEXMAX)
#define RSIZE_MUSIC			(sizeof(musicData) * MUSICMAX)
#define RSIZE_SPRITE		(sizeof(spriteData) * spritenumber)
#define RSIZE_SPRITENUMBER	(sizeof(int))
#define RSIZE_PLAYERMOTION	(sizeof(playerMotionData) * PLAYERMOTIONSETMAX)

#define BRES_SPRITETABLEID			0x4B
#define BRES_TEXTURETABLEID			0x53
#define BRES_PLAYERMOTIONTABLEID	0x56

class BResource
{
public:
	static BResource* PIns() { static BResource instance; return &instance; }

private:
	BResource();
	~BResource();
	BResource(BResource const&);
	void operator=(BResource const&);

public:

	bool ReadTables();
	bool ReadTextureTable();
	bool ReadSpriteTable();
	bool ReadPlayerMotionTable();

	void InitTexinfo();
	bool LoadTexture(int texindex=-1);
	bool FreeTexture(int texindex=-1);

	void ReleaseSpriteData();
	void InitSpriteData();

	musicData musdata[MUSICMAX];
	spriteData * spritedata;
	int spritenumber;
	textureData texturedata[TEXMAX];
	playerMotionData playermotiondata[PLAYERMOTIONSETMAX];

	//texture
	HTEXTURE	tex[TEXMAX];
	hgeTextureInfo texinfo[TEXMAX];
};

extern HGE * hge;