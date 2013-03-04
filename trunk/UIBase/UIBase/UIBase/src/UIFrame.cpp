#include "../include/UIFrame.h"
#include "../include/UIRnederManager.h"

#include "../../Header/Main.h"

float UIFrameNode::mx = 0;
float UIFrameNode::my = 0;
bool UIFrameNode::mdown = false;
UIFrameNode * UIFrameNode::mdownnode = NULL;

UIFrameNode UIFrameNode::basenode;

UIFrameRect::UIFrameRect()
	:
x(0),
y(0),
w(0),
h(0)
{
}

UIFrameRect::~UIFrameRect()
{

}

void UIFrameRect::SetXYWH( float _x, float _y, float _w, float _h )
{
	x = _x;
	y = _y;
	if (_w >= 0)
	{
		w = _w;
	}
	if (_h >= 0)
	{
		h = _h;
	}
}

int UIFrameNode::hoveronitemtimer = 0;
int UIFrameNode::hoveronitemtimermax = 240;

UIFrameNode::UIFrameNode()
	:
parent(0),
isUpdate(true),
isInRect(false),
isHover(false),
isRender(true),
isActive(true),
isClickon(false),
isClickable(false),
timer(0)
{
	OnInit();
}

void UIFrameNode::OnInit()
{
}

void UIFrameNode::SetParent( UIFrameNode * _parent )
{
	if (!parent)
	{
		parent = _parent;
		parent->AddChild(this);
	}
}

void UIFrameNode::AddChild( UIFrameNode * child )
{
	if (child)
	{
		children.push_back(child);
		child->SetParent(this);
		child->OnEnter();
	}
}

void UIFrameNode::SortChildren()
{
	children.sort();
}

bool UIFrameNode::operator<(const UIFrameNode &right) const
{
	if (x < right.x)
	{
		return true;
	}
	if (x == right.x)
	{
		if (y < right.y)
		{
			return true;
		}
	}
	return false;
}

UIFrameNode::~UIFrameNode()
{

}


void UIFrameNode::OnUpdate()
{
	if (isActive)
	{
		timer++;

		bool bwashover = isHover;

		SetHover(false);
		SetClickOn(false);

		if (mx > x && mx < x+w && my > y && my < y+h)
		{
			SetInRect(true);
			SetHover(true);
			if (mdown)
			{
				if (!mdownnode && isClickable)
				{
					mdownnode = this;
				}
				if (mdownnode == this && isClickable)
				{
					SetClickOn(true);
				}
			}
			else
			{
				if (mdownnode == this)
				{
					OnClick();
					mdownnode = NULL;
				}
			}
		
		}
		else
		{
			if (mdownnode == this)
			{
				SetHover(true);
			}
		}
	

		if (isClickon && mdownnode == this)
		{
			OnClickOn();
		}

		if (isHover)
		{
			OnHover();
		}
		if (bwashover && !isHover)
		{
			OnHoverOff();
		}
	}

	if (children.size())
	{
		for (list<UIFrameNode *>::iterator it=children.begin(); it!=children.end(); ++it)
		{
			if ((*it) && (*it)->isUpdate)
			{
				(*it)->OnUpdate();
			}
		}
	}
}

void UIFrameNode::OnRender(float alphamul)
{
	if (isRender)
	{
		UIColoredRect::OnRender(alphamul);
	}

	if (children.size())
	{
		for (list<UIFrameNode *>::iterator it=children.begin(); it!=children.end(); ++it)
		{
			if (*it && (*it)->isRender)
			{
				(*it)->OnRender(alphamul);
			}
		}
	}

	if (hoveronitemtimer < 0)
	{
		hoveronitemtimer++;
	}
}

void UIFrameNode::GlobalUpdate()
{
	if (hge->Input_GetKeyState(HGEK_LBUTTON))
	{
		mdown = true;
	}
	else
	{
		mdown = false;
	}
	hge->Input_GetMousePos(&mx, &my);
	basenode.OnUpdate();

	if (mdownnode && !hge->Input_GetKeyState(HGEK_LBUTTON))
	{
		mdownnode = NULL;
	}
}

void UIFrameNode::OnEnter()
{

}

void UIFrameNode::OnHover()
{

}

void UIFrameNode::OnHoverOff()
{

}

void UIFrameNode::OnClickOn()
{

}

void UIFrameNode::OnClick()
{

}

void UIFrameNode::OnRightClick()
{

}

void UIFrameNode::GlobalRender()
{
	basenode.OnRender();
}

void UIFrameNode::SetInRect( bool binrect )
{
	isInRect = binrect;
}

void UIFrameNode::SetActive(bool bactive)
{
	if (isActive != bactive)
	{
		isActive = bactive;
		if (isActive)
		{
			OnActive();
		}
		else
		{
			OnInActive();
		}
	}
}

void UIFrameNode::SetRender(bool brender)
{
	isRender = brender;
}

void UIFrameNode::SetHover(bool bhover)
{
	isHover = bhover;
}

void UIFrameNode::SetClickable(bool bclickable)
{
	isClickable = bclickable;
}

void UIFrameNode::SetClickOn(bool bclickon)
{
	isClickon = bclickon;
}

void UIFrameNode::SetUpdate( bool bupdate )
{
	isUpdate = bupdate;
}

void UIFrameNode::OnInActive()
{

}

void UIFrameNode::OnActive()
{

}
UIImage::UIImage()
	:
tex(0)
{

}

UIImage::~UIImage()
{

}

void UIImage::Render()
{
	UIRenderManager::getSingleton()->RenderIcon(this);
}
UIColoredRect::UIColoredRect()
{

}

UIColoredRect::~UIColoredRect()
{

}

void UIColoredRect::OnRender(float alphamul)
{
	UIRenderManager::getSingleton()->RenderColoredRect(this, alphamul);
}

void UIColoredRect::SetColor( DWORD col, int i/*=-1*/ )
{
	if (i < 0 || i > 3)
	{
		for (int i=0; i<4; i++)
		{
			SetColor(col, i);
		}
		return;
	}
	color[i] = col;
}

void UIColoredRect::SetColor( DWORD col0, DWORD col1, DWORD col2, DWORD col3 )
{
	SetColor(col0, 0);
	SetColor(col1, 1);
	SetColor(col2, 2);
	SetColor(col3, 3);
}

void UIColoredRect::SetBoundaryColor( DWORD col, int i/*=-1*/ )
{
	if (i < 0 || i > 3)
	{
		for (int i=0; i<4; i++)
		{
			SetBoundaryColor(col, i);
		}
		return;
	}
	boundarycolor[i] = col;
}

void UIColoredRect::SetBoundaryColor( DWORD col0, DWORD col1, DWORD col2, DWORD col3 )
{
	SetBoundaryColor(col0, 0);
	SetBoundaryColor(col1, 1);
	SetBoundaryColor(col2, 2);
	SetBoundaryColor(col3, 3);
}

void UIColoredRect::ApplyColorStyle( DWORD style )
{
#define _SETCOLOR(cu, cd)	SetColor(0xff##cu##cu##cu, 0xff##cu##cu##cu, 0xff##cd##cd##cd, 0xff##cd##cd##cd)
	switch (style)
	{
	case UICS_CONTAINER:
		_SETCOLOR(d5, 8f);
		SetBoundaryColor(0xffffffff);
		break;
	case UICS_FRAME:
		SetColor(0xfffefefe);
		SetBoundaryColor(0xffffffff);
		break;
	case UICS_BUTTON:
		_SETCOLOR(fe, ee);
		SetBoundaryColor(0xffcecfd1);
		break;
	case UICS_HOVER:
		SetColor(0x200261bf);
		SetBoundaryColor(0xff0261bf);
		break;
	case UICS_STATUS:
		SetColor(0x400261bf);
		SetBoundaryColor(0xff0261bf);
		break;
	default:
		break;
	}
}
UIElement::UIElement()
{
	OnInit();
}

UIElement::~UIElement()
{

}

UIFrame::UIFrame()
{
	OnInit();
}

UIFrame::~UIFrame()
{

}

void UIFrame::OnInit()
{
	ApplyColorStyle(UICS_FRAME);
}

UIContainer::UIContainer()
{
	OnInit();
}

UIContainer::~UIContainer()
{

}

void UIContainer::OnInit()
{
	ApplyColorStyle(UICS_CONTAINER);
}

UIButton::UIButton()
{
	OnInit();
}

UIButton::~UIButton()
{

}

void UIButton::OnUpdate()
{
	UIFrameNode::OnUpdate();
}

void UIButton::OnInit()
{
	SetClickable(true);
	ApplyColorStyle(UICS_BUTTON);
}


void UIButton::OnHover()
{
	if (hoveronitemtimer < hoveronitemtimermax)
	{
		hoveronitemtimer++;
	}
}

void UIButton::OnHoverOff()
{
	hoveronitemtimer = -hoveronitemtimermax/8;
}
void UIHoverFrame::OnUpdate()
{
	if (parent)
	{
		if (parent->isHover)
		{
			SetRender(true);
		}
		else
		{
			SetRender(false);
		}
	}
//	UIFrameNode::OnUpdate();
}

void UIStatusFrame::OnEnter()
{
	SetRender(false);
}

UIStatusFrame::UIStatusFrame()
{
	OnInit();
}
UIStatusFrame::~UIStatusFrame()
{

}

void UIStatusFrame::OnInit()
{
	ApplyColorStyle(UICS_STATUS);
}

void UIStatusFrame::OnUpdate()
{
	if (parent)
	{
		if (parent->isClickon)
		{
			SetRender(true);
		}
		else
		{
			SetRender(false);
		}
	}
	//	UIFrameNode::OnUpdate();
}
UIHoverFrame::UIHoverFrame()
{
	OnInit();
}

UIHoverFrame::~UIHoverFrame()
{

}

void UIHoverFrame::OnInit()
{
	ApplyColorStyle(UICS_HOVER);
}

UIFloatingContainer::UIFloatingContainer()
{
	OnInit();
}

UIFloatingContainer::~UIFloatingContainer()
{

}

int UIFloatingContainer::transitiontimer = 120;

void UIFloatingContainer::OnRender(float alphamul)
{
	float _alphamul = alphamul;
	if (timer >= 0 && timer < transitiontimer)
	{
		_alphamul = ((float)(timer))/transitiontimer*alphamul;
	}
	else if (timer < 0)
	{
		_alphamul = ((float)(-timer))/transitiontimer*alphamul;
	}
	UIRenderManager::getSingleton()->RenderShadow(this, _alphamul);
	UIFrameNode::OnRender(_alphamul);
}

void UIFloatingContainer::OnInit()
{
	UIContainer::OnInit();
	SetActive(false);
	SetRender(false);
}

UIButtonHelpFloatingContainer * UIButtonHelpFloatingContainer::uniqueUIHFC = NULL;

UIButtonHelpFloatingContainer::UIButtonHelpFloatingContainer()
{
	OnInit();
}

UIButtonHelpFloatingContainer::~UIButtonHelpFloatingContainer()
{

}

void UIButtonHelpFloatingContainer::OnUpdate()
{
	if (parent)
	{
		if (parent->isHover)
		{
			if ((hoveronitemtimer >= hoveronitemtimermax || hoveronitemtimer < 0))
			{
				if (!isActive)
				{
					if (uniqueUIHFC && uniqueUIHFC != this)
					{
						uniqueUIHFC->timer = 0;
						uniqueUIHFC->SetActive(false);
						uniqueUIHFC->SetRender(false);
					}
					uniqueUIHFC = this;
					if (hoveronitemtimer < 0)
					{
						hoveronitemtimer = hoveronitemtimermax;
					}
					SetActive(true);
					SetRender(true);
					timer = 0;
				}
			}
		}
		else
		{
			if (isActive)
			{
				if (timer > 0)
				{
					timer = -transitiontimer;
				}
				else if (!timer)
				{
					SetActive(false);
					SetRender(false);
					uniqueUIHFC = NULL;
				}
			}
		}
	}
	UIFloatingContainer::OnUpdate();
}

void UIButtonHelpFloatingContainer::OnActive()
{
#define _YOFFSET 10
	if (parent)
	{
		SetXYWH(mx, parent->y+parent->h+_YOFFSET);
	}
	else
	{
		SetXYWH(mx, my+_YOFFSET);
	}
}
