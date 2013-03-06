#ifndef _SPRITEITEMMANAGER_H
#define _SPRITEITEMMANAGER_H

#include "MainDependency.h"
#include "DataStruct.h"

class SpriteItemManager
{
public:
	static SpriteItemManager& getInstance() { static SpriteItemManager instance; return instance; }

private:
	SpriteItemManager();
	~SpriteItemManager();
	SpriteItemManager(SpriteItemManager const&);
	void operator=(SpriteItemManager const&);
public:
	void Init();
	void Release();

	hgeSprite * CreateSprite(int index);
	bool CreateSprite(int index, hgeSprite ** sprite);
	bool ChangeSprite(int index, hgeSprite * sprite);
	int GetIndexByName(const char * spritename);
	hgeSprite * CreateSpriteByName(const char * spritename);
	bool CreateSpriteByName(const char * spritename, hgeSprite ** sprite);
	void FreeSprite(hgeSprite ** sprite);
	spriteData * CastSprite(int index);

	hgeSprite * CreateNullSprite();
	bool SetSpriteData(hgeSprite * sprite, HTEXTURE tex, float texx, float texy, float texw, float texh, bool flipx=false, bool flipy=false);
	bool SetSpriteTextureRect(hgeSprite * sprite, float texx, float texy, float texw, float texh);
	bool SetSpriteFlip(hgeSprite * sprite, bool flipx=false, bool flipy=false);
	bool SetSpriteHotSpot(hgeSprite * sprite, float hotx, float hoty);

	bool SetSprite(int index, hgeSprite * sprite);

	HTEXTURE GetTexture(int index);
	float GetTexX(int index);
	float GetTexY(int index);
	float GetTexW(int index);
	float GetTexH(int index);

	static bool LoadTextureWhenNeeded(HTEXTURE tex);
	static bool LoadTextureWhenNeededCallBack();

	void RenderSprite(hgeSprite * sprite, float x, float y);
	void RenderSpriteEx(hgeSprite * sprite, float x, float y, float rot, float hscale=1.0f, float vscale=0.0f);
	void FontPrintf(hgeFont * font, float x, float y, int align, const char * str);
	void FontPrintfb(hgeFont * font, float x, float y, float w, float h, int align, const char * str);
	void EffectSystemRender(hgeEffectSystem * eff, hge3DPoint *ptfar=NULL, DWORD colormask=0xffffffff);
	void RenderQuad(hgeQuad * quad);
};

#endif