#ifndef _UIRENDERMANAGER_H
#define _UIRENDERMANAGER_H

#include "UIFrame.h"

#define TEXTURE_WHITE	0

class UIRenderManager
{
public:
	UIRenderManager();
	~UIRenderManager();

	static UIRenderManager * getSingleton();
	
	void RenderColoredRect(UIColoredRect * rect, float alphamul=1.0f);
	void RenderShadow(UIColoredRect * rect, float alphamul=1.0f);
	void RenderIcon(UIImage * icon, float alphamul=1.0f);
	void RenderFrame(UIColoredRect * rect, float alphamul=1.0f);

	HTEXTURE LoadTexture(const char * filename);

	static UIRenderManager * rendermanager;
};

#endif