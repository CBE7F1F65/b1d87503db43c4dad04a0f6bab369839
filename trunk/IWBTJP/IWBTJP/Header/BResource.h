#pragma once

#include "MainDependency.h"
#include "DataStruct.h"

#define RSIZE_TEXTURE		(sizeof(textureData) * TEXMAX)
#define RSIZE_MUSIC			(sizeof(musicData) * MUSICMAX)
#define RSIZE_SPRITE		(sizeof(spriteData) * spritenumber)
#define RSIZE_SPRITENUMBER	(sizeof(int))

#define BRES_SPRITETABLEID	0x4B
#define BRES_TEXTURETABLEID	0x53

class BResource
{
public:
	static BResource& getInstance() { static BResource instance; return instance; }

private:
	BResource();
	~BResource();
	BResource(BResource const&);
	void operator=(BResource const&);

public:

	bool ReadTables();
	bool ReadTextureTable();
	bool ReadSpriteTable();

	void InitTexinfo();
	bool LoadTexture(int texindex=-1);
	bool FreeTexture(int texindex=-1);

	void ReleaseSpriteData();
	void InitSpriteData();

	musicData musdata[MUSICMAX];
	spriteData * spritedata;
	int spritenumber;
	textureData texturedata[TEXMAX];

	//texture
	HTEXTURE	tex[TEXMAX];
	hgeTextureInfo texinfo[TEXMAX];
};

extern HGE * hge;