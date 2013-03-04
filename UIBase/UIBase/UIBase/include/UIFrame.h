#ifndef _UIFRAME_H
#define _UIFRAME_H

#include "../../../../include/hge.h"
#include "../../../../include/hgesprite.h"
#include <list>
using namespace std;

class UIFrameRect
{
public:
	UIFrameRect();
	~UIFrameRect();

	void SetXYWH(float x, float y, float w=-1, float h=-1);

	float x;
	float y;
	float w;
	float h;
};

class UIColoredRect : public UIFrameRect
{
public:
	UIColoredRect();
	~UIColoredRect();

	void SetColor(DWORD color, int i=-1);
	void SetColor(DWORD col0, DWORD col1, DWORD col2, DWORD col3);
	void SetBoundaryColor(DWORD color, int i=-1);
	void SetBoundaryColor(DWORD col0, DWORD col1, DWORD col2, DWORD col3);

	enum{
		UICS_BLANK,
		UICS_CONTAINER,
		UICS_FRAME,
		UICS_BUTTON,
		UICS_HOVER,
		UICS_STATUS,
		UICS_FORCEDWORD = 0xffffffff
	};

	void ApplyColorStyle(DWORD style);

	virtual void OnRender(float alphamul=1.0f);

	DWORD color[4];
	DWORD boundarycolor[4];
};

class UIImage : public UIColoredRect
{
public:
	UIImage();
	~UIImage();

	virtual void Render();

	HTEXTURE tex;
	UIFrameRect texcoord;
};

class UIFrameNode : public UIColoredRect
{
public:
	UIFrameNode();
	~UIFrameNode();

	static void GlobalUpdate();
	static void GlobalRender();
	static UIFrameNode basenode;

	void SetParent(UIFrameNode * parent);
	void AddChild(UIFrameNode * child);

	virtual void OnInit();
	virtual void OnEnter();
	virtual void OnHover();
	virtual void OnHoverOff();
	virtual void OnActive();
	virtual void OnInActive();
	virtual void OnClickOn();
	virtual void OnClick();
	virtual void OnRightClick();
	virtual void OnUpdate();
	virtual void OnRender(float alphamul=1.0f);

	void SortChildren();
	bool operator < (const UIFrameNode &right) const;

	UIFrameNode * GetParent()	{return parent;};


	UIFrameNode * parent;
	list<UIFrameNode *> children;

	bool isInRect;
	bool isHover;
	bool isUpdate;
	bool isActive;
	bool isRender;
	bool isClickon;
	bool isClickable;

	void SetUpdate(bool bupdate);
	void SetInRect(bool binrect);
	void SetHover(bool bhover);
	void SetActive(bool bactive);
	void SetRender(bool brender);
	void SetClickOn(bool bclickon);
	void SetClickable(bool bclickable);
	
	int timer;

	static float mx;
	static float my;
	static bool mdown;
	static UIFrameNode * mdownnode;

	static int hoveronitemtimer;
	static int hoveronitemtimermax;
};


class UIFrame : public UIFrameNode
{
public:
	UIFrame();
	~UIFrame();

	virtual void OnInit();
//	virtual void Render();
};

class UIElement : public UIFrame
{
public:
	UIElement();
	~UIElement();

//	virtual void Render();

};

class UIContainer : public UIFrame
{
public:
	UIContainer();
	~UIContainer();

	virtual void OnInit();
//	virtual void Render();
};

class UIFloatingContainer : public UIContainer
{
public:

	UIFloatingContainer();
	~UIFloatingContainer();

	virtual void OnInit();
	virtual void OnRender(float alphamul=1.0f);

	static int transitiontimer;
};

class UIButtonHelpFloatingContainer : public UIFloatingContainer
{
public:

	UIButtonHelpFloatingContainer();
	~UIButtonHelpFloatingContainer();

	static UIButtonHelpFloatingContainer * uniqueUIHFC;
	virtual void OnActive();
	virtual void OnUpdate();
};

class UIStatusFrame : public UIFrame
{
public:
	UIStatusFrame();
	~UIStatusFrame();
	
	virtual void OnInit();
	virtual void OnEnter();
	virtual void OnUpdate();
};

class UIHoverFrame : public UIStatusFrame
{
public:
	UIHoverFrame();
	~UIHoverFrame();
	
	virtual void OnInit();
	virtual void OnUpdate();
};



class UIButton : public UIFrame
{
public:
	UIButton();
	~UIButton();

	virtual void OnInit();
	virtual void OnUpdate();
	virtual void OnHover();
	virtual void OnHoverOff();
};


#endif