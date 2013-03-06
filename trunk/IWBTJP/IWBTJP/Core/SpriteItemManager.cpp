#include "../Header/SpriteItemManager.h"
#include "../Header/BResource.h"


SpriteItemManager::SpriteItemManager()
{
	Init();
}

SpriteItemManager::~SpriteItemManager()
{
	Release();
}

bool SpriteItemManager::LoadTextureWhenNeededCallBack()
{
	return LoadTextureWhenNeeded(*(hge->Texture_GetTextureToLoad()));
}

void SpriteItemManager::Init()
{
	hge->System_SetState(HGE_LOADTEXTUREFUNC, SpriteItemManager::LoadTextureWhenNeededCallBack);
}

void SpriteItemManager::Release()
{
}

HTEXTURE SpriteItemManager::GetTexture(int index)
{
	BResource * pbres = &BResource::getInstance();
	if (index < 0 || index >= pbres->spritenumber)
	{
		return NULL;
	}
	return pbres->tex[pbres->spritedata[index].tex];
}

float SpriteItemManager::GetTexX(int index)
{
	BResource * pbres = &BResource::getInstance();
	if (index < 0 || index >= pbres->spritenumber)
	{
		return 0;
	}
	return pbres->spritedata[index].tex_x;
}

float SpriteItemManager::GetTexY(int index)
{
	BResource * pbres = &BResource::getInstance();
	if (index < 0 || index >= pbres->spritenumber)
	{
		return 0;
	}
	return pbres->spritedata[index].tex_y;
}

float SpriteItemManager::GetTexW(int index)
{
	BResource * pbres = &BResource::getInstance();
	if (index < 0 || index >= pbres->spritenumber)
	{
		return 0;
	}
	return pbres->spritedata[index].tex_w;
}

float SpriteItemManager::GetTexH(int index)
{
	BResource * pbres = &BResource::getInstance();
	if (index < 0 || index >= pbres->spritenumber)
	{
		return 0;
	}
	return pbres->spritedata[index].tex_h;
}

int SpriteItemManager::GetIndexByName(const char * spritename)
{
	if (!spritename)
	{
		return -1;
	}
	if (!strlen(spritename))
	{
		return -1;
	}
	BResource * pbres = &BResource::getInstance();
	for (int i=0; i<pbres->spritenumber; i++)
	{
		if (!strcmp(spritename, pbres->spritedata[i].spritename))
		{
			return i;
			break;
		}
	}
	return -1;
}

spriteData * SpriteItemManager::CastSprite(int index)
{
	BResource * pbres = &BResource::getInstance();
	if (index >= 0 && index < pbres->spritenumber)
	{
		return &(pbres->spritedata[index]);
	}
	return NULL;
}

bool SpriteItemManager::SetSprite(int index, hgeSprite * sprite)
{
	if (!sprite)
	{
		return false;
	}
	if (index < 0)
	{
		SetSpriteTextureRect(sprite, 0, 0, 0, 0);
		return true;
	}
	spriteData * _sd = CastSprite(index);
	if (!_sd)
	{
		return false;
	}
	HTEXTURE tex(_sd->tex, NULL);
	SetSpriteData(sprite, tex, _sd->tex_x, _sd->tex_y, 
		_sd->tex_w < 0 ? hge->Texture_GetWidth(tex)-_sd->tex_x : _sd->tex_w, 
		_sd->tex_h < 0 ? hge->Texture_GetHeight(tex)-_sd->tex_y : _sd->tex_h);
	return true;
}

hgeSprite * SpriteItemManager::CreateNullSprite()
{
	hgeSprite * sprite;
	sprite = CreateSprite(0);
	return sprite;
}

hgeSprite * SpriteItemManager::CreateSprite(int index)
{
	hgeSprite * sprite;
//	sprite = CreateNullSprite();
	sprite = new hgeSprite();
	if (index < 0)
	{
		return sprite;
	}
	BResource * pbres = &BResource::getInstance();
	HTEXTURE tex(pbres->spritedata[index].tex, NULL);
	SetSpriteData(sprite, tex, pbres->spritedata[index].tex_x, pbres->spritedata[index].tex_y, pbres->spritedata[index].tex_w, pbres->spritedata[index].tex_h);
	return sprite;
}

bool SpriteItemManager::SetSpriteData(hgeSprite * sprite, HTEXTURE _tex, float texx, float texy, float texw, float texh, bool flipx/* =false */, bool flipy/* =false */)
{
	if (!sprite)
	{
		return false;
	}
	sprite->SetTexture(_tex);
	if (!SetSpriteTextureRect(sprite, texx, texy, texw, texh))
	{
		return false;
	}
	if (!SetSpriteFlip(sprite, flipx, flipy))
	{
		return false;
	}
	return true;
}

bool SpriteItemManager::SetSpriteTextureRect(hgeSprite * sprite, float texx, float texy, float texw, float texh)
{
	if (!sprite)
	{
		return false;
	}
	sprite->SetTextureRect(texx, texy, texw, texh);
	return true;
}

bool SpriteItemManager::SetSpriteHotSpot(hgeSprite * sprite, float hotx, float hoty)
{
	if (!sprite)
	{
		return false;
	}
	sprite->SetHotSpot(hotx, hoty);
	return true;
}

bool SpriteItemManager::SetSpriteFlip(hgeSprite * sprite, bool flipx/* =false */, bool flipy/* =false */)
{
	if (!sprite)
	{
		return false;
	}
	sprite->SetFlip(flipx, flipy);
	return true;
}

bool SpriteItemManager::CreateSprite(int index, hgeSprite ** sprite)
{
	if (!sprite)
	{
		return false;
	}
	*sprite = CreateSprite(index);
	if (*sprite)
	{
		return true;
	}
	return false;
}

bool SpriteItemManager::ChangeSprite(int index, hgeSprite * sprite)
{
	if (!sprite || index < 0)
	{
		return false;
	}
	BResource * pbres = &BResource::getInstance();
	HTEXTURE tex(pbres->spritedata[index].tex, NULL);
	SetSpriteData(sprite, tex, pbres->spritedata[index].tex_x, pbres->spritedata[index].tex_y, pbres->spritedata[index].tex_w, pbres->spritedata[index].tex_h);
	return true;
}

hgeSprite * SpriteItemManager::CreateSpriteByName(const char * spritename)
{
	int index = GetIndexByName(spritename);
	if (index >= 0)
	{
		return CreateSprite(index);
	}
	return NULL;
}

bool SpriteItemManager::CreateSpriteByName(const char * spritename, hgeSprite ** sprite)
{
	if (!sprite)
	{
		return false;
	}
	*sprite = CreateSpriteByName(spritename);
	if (*sprite)
	{
		return true;
	}
	return false;
}

void SpriteItemManager::FreeSprite(hgeSprite ** sprite)
{
	if (sprite && *sprite)
	{
		free(*sprite);
		*sprite = NULL;
	}
}

bool SpriteItemManager::LoadTextureWhenNeeded(HTEXTURE tex)
{
	if (hge->Texture_GetTexture(tex) == NULL)
	{
		BResource * pbres = &BResource::getInstance();
		pbres->LoadTexture(tex.texindex);
		return true;
	}
	return false;
}

void SpriteItemManager::RenderSprite( hgeSprite * sprite, float x, float y )
{
	if (!sprite)
	{
		return;
	}
//	LoadTextureWhenNeeded(sprite->quad.tex);
	sprite->Render(x, y);
}

void SpriteItemManager::RenderSpriteEx( hgeSprite * sprite, float x, float y, float rot, float hscale/*=1.0f*/, float vscale/*=0.0f*/ )
{
	if (!sprite)
	{
		return;
	}
//	LoadTextureWhenNeeded(sprite->quad.tex);
	sprite->RenderEx(x, y, rot, hscale, vscale);
}

void SpriteItemManager::FontPrintf( hgeFont * font, float x, float y, int align, const char * str)
{
	if (!font)
	{
		return;
	}
	font->printf(x, y, align, str);
}

void SpriteItemManager::FontPrintfb( hgeFont * font, float x, float y, float w, float h, int align, const char * str)
{
	if (!font)
	{
		return;
	}
	font->printfb(x, y, w, h, align, str);
}

void SpriteItemManager::EffectSystemRender( hgeEffectSystem * eff, hge3DPoint *ptfar, DWORD colormask )
{
	if (!eff)
	{
		return;
	}
//	LoadTextureWhenNeeded(eff->ebi.tex);
	eff->Render(ptfar, colormask);
}

void SpriteItemManager::RenderQuad( hgeQuad * quad )
{
	if (!quad)
	{
		return;
	}
//	LoadTextureWhenNeeded(quad->tex);
	hge->Gfx_RenderQuad(quad);
}