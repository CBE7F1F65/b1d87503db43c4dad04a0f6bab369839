#include "../include/UIRnederManager.h"
#include <cassert>
#include "../../Header/Main.h"

UIRenderManager * UIRenderManager::rendermanager = 0;

UIRenderManager::UIRenderManager()
{
	if (rendermanager)
	{
		assert(true);
	}
}
UIRenderManager::~UIRenderManager()
{
	if (rendermanager)
	{
		delete rendermanager;
		rendermanager = NULL;
	}
}
UIRenderManager * UIRenderManager::getSingleton()
{
	if (!rendermanager)
	{
		rendermanager = new UIRenderManager();
	}
	return rendermanager;
}

HTEXTURE UIRenderManager::LoadTexture( const char * filename )
{
	HTEXTURE tex = hge->Texture_Load(filename);
	return tex;
}

void UIRenderManager::RenderColoredRect( UIColoredRect * rect, float alphamul )
{
	hgeQuad quad;
	quad.blend = BLEND_DEFAULT;
	quad.tex = TEXTURE_WHITE;

	quad.v[0].tx = 0;	quad.v[0].ty = 0;
	quad.v[1].tx = 1;	quad.v[1].ty = 0;
	quad.v[2].tx = 1;	quad.v[2].ty = 1;
	quad.v[3].tx = 0;	quad.v[3].ty = 1;

	for (int i=0; i<4; i++)
	{
		quad.v[i].col = SETA(rect->color[i], GETA(rect->color[i])*alphamul);
		quad.v[i].z = 0;
	}

	quad.v[0].x = rect->x;	quad.v[0].y = rect->y;
	quad.v[1].x = rect->x+rect->w;	quad.v[1].y = rect->y;
	quad.v[2].x = rect->x+rect->w;	quad.v[2].y = rect->y+rect->h;
	quad.v[3].x = rect->x;	quad.v[3].y = rect->y+rect->h;

	hge->Gfx_RenderQuad(&quad);

	RenderFrame(rect);
}

void UIRenderManager::RenderFrame( UIColoredRect * rect, float alphamul )
{
	hge->Gfx_RenderLine(rect->x, rect->y, rect->x+rect->w, rect->y, SETA(rect->boundarycolor[0], GETA(rect->boundarycolor[0])*alphamul));
	hge->Gfx_RenderLine(rect->x+rect->w, rect->y, rect->x+rect->w, rect->y+rect->h, SETA(rect->boundarycolor[1], GETA(rect->boundarycolor[1])*alphamul));
	hge->Gfx_RenderLine(rect->x+rect->w, rect->y+rect->h, rect->x, rect->y+rect->h, SETA(rect->boundarycolor[2], GETA(rect->boundarycolor[2])*alphamul));
	hge->Gfx_RenderLine(rect->x, rect->y+rect->h, rect->x, rect->y, SETA(rect->boundarycolor[3], GETA(rect->boundarycolor[3])*alphamul));
}

void UIRenderManager::RenderIcon( UIImage * icon, float alphamul )
{
	hgeQuad quad;
	quad.blend = BLEND_DEFAULT;
	quad.tex = icon->tex;

	quad.v[0].x = icon->texcoord.x;	quad.v[0].y = icon->texcoord.y;
	quad.v[1].x = icon->texcoord.x+icon->texcoord.w;	quad.v[1].y = icon->texcoord.y;
	quad.v[2].x = icon->texcoord.x+icon->texcoord.w;	quad.v[2].y = icon->y+icon->texcoord.h;
	quad.v[3].x = icon->texcoord.x;	quad.v[3].y = icon->texcoord.y+icon->texcoord.h;

	for (int i=0; i<4; i++)
	{
		quad.v[i].col = SETA(icon->color[i], GETA(icon->color[i])*alphamul);
		quad.v[i].z = 0;
	}

	quad.v[0].x = icon->x;	quad.v[0].y = icon->y;
	quad.v[1].x = icon->x+icon->w;	quad.v[1].y = icon->y;
	quad.v[2].x = icon->x+icon->w;	quad.v[2].y = icon->y+icon->h;
	quad.v[3].x = icon->x;	quad.v[3].y = icon->y+icon->h;

	hge->Gfx_RenderQuad(&quad);

	RenderFrame(icon);
}

void UIRenderManager::RenderShadow(UIColoredRect * rect, float alphamul)
{
#define _SHADOW_LAYER		5
#define _SHADOW_BEGIN		0
#define _SHADOW_MERGE		10
#define _SHADOW_SOLIDBEGIN	(_SHADOW_BEGIN+_SHADOW_MERGE)
#define _SHADOW_MINSIZE		20
	if (rect->w < _SHADOW_MINSIZE || rect->h < _SHADOW_MINSIZE)
	{
		return;
	}
	for (int i=0; i<_SHADOW_LAYER; i++)
	{
		float af = (float)0x100*(_SHADOW_LAYER-i)/(float)(_SHADOW_LAYER+2);
		BYTE a = af * alphamul;
		BYTE c = i*0x80/_SHADOW_LAYER;
		DWORD col = ARGB(a, c, c, c);
		hge->Gfx_RenderLine(rect->x+_SHADOW_SOLIDBEGIN+i+1, rect->y+rect->h+i+1, rect->x+rect->w+1, rect->y+rect->h+i+1, col);
		hge->Gfx_RenderLine(rect->x+rect->w+i+1, rect->y+_SHADOW_SOLIDBEGIN+i+1, rect->x+rect->w+i+1, rect->y+rect->h+1, col);

		hge->Gfx_RenderLine2(rect->x+_SHADOW_BEGIN+i+1, rect->y+rect->h+i+1, rect->x+_SHADOW_SOLIDBEGIN+i+1, rect->y+rect->h+i+1, 0, col);
		hge->Gfx_RenderLine2(rect->x+rect->w+i+1, rect->y+_SHADOW_BEGIN+i+1, rect->x+rect->w+i+1, rect->y+_SHADOW_SOLIDBEGIN+i+1, 0, col);
		hge->Gfx_RenderLine(rect->x+rect->w+1, rect->y+rect->h+i+1, rect->x+rect->w+i+1, rect->y+rect->h+1, col);
	}
}