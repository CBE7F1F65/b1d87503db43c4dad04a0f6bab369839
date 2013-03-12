#include "../Header/InterObj.h"
#include "../Header/SpriteItemManager.h"
#include "../Header/Process.h"

InterObj::InterObj()
{
	x = 0;
	y = 0;
	angle = 0;
	hscale = 1.0f;
	vscale = 0.0f;

	boundingxoff = 0;
	boundingyoff = 0;
	boundingw = 0;
	boundingh = 0;

	alpha = 0xff;
	color = 0xffffff;

	basesiid = -1;
	cursiid = -1;
	timer = 0;

	animetimer = 0;
	bFlipX = false;

	sp = NULL;
}

InterObj::~InterObj()
{
	SpriteItemManager::PIns()->FreeSprite(&sp);
}

void InterObj::SetSIID( int siid )
{
	if (siid == cursiid)
	{
		return;
	}
	SpriteItemManager * psm = SpriteItemManager::PIns();
	if (!sp)
	{
		if (psm->CreateSprite(siid, &sp))
		{
			cursiid = siid;
		}
	}
	else
	{
		if (psm->ChangeSprite(siid, sp))
		{
			cursiid = siid;
		}
	}
}

void InterObj::SetPos( int xpos, int ypos )
{
	x = xpos;
	y = ypos;
}

void InterObj::SetRot( int _angle )
{
	angle = _angle;
}

void InterObj::SetScale( float hs, float vs/*=0.0f*/ )
{
	hscale = hs;
	vscale = vs;
}

void InterObj::SetRealm( int _realmflag )
{
	realmflag = _realmflag;
}

bool InterObj::AddInteractiveEvent( int opponentflag, int cltype, int a, int b, int xoff, int yoff, int angle, int eventid, bool bonce )
{
	int i=0;
	for (; i<INTERACTIVEEVENTMAX; i++)
	{
		if (!ievent[i].Registered())
		{
			break;
		}
	}
	if (i >= INTERACTIVEEVENTMAX)
	{
		return false;
	}

	return ievent[i].SetValue(opponentflag, cltype, a, b, xoff, yoff, angle, eventid, bonce);
}

void InterObj::Render()
{
	Process * pp = Process::PIns();
	float wxoff = pp->worldxoff;
	float wyoff = pp->worldyoff;
	
	float scrr = pp->screenwidth;
	float scrb = pp->screenheight;

	float xpos = x+wxoff;
	float ypos = y+wyoff;

	if (xpos+boundingxoff > scrr || xpos+boundingxoff+boundingw < 0 || ypos+boundingyoff > scrb || ypos+boundingyoff+boundingh < 0)
	{
		return;
	}

	sp->SetFlip(bFlipX, false);
	sp->SetColor((alpha<<24)|(color&0xffffff));
	SpriteItemManager::PIns()->RenderSpriteEx(sp, xpos*FLT_1_FMUL, ypos*FLT_1_FMUL, ARC(angle), hscale, vscale);
}

void InterObj::SetBoundingBox( int bxoff, int byoff, int bw, int bh )
{
	boundingxoff = bxoff;
	boundingyoff = byoff;
	boundingw = bw;
	boundingh = bh;
}

void InterObj::Update()
{
	++timer;
	DoAnimation();
	CalculateBound();
}

void InterObj::SetDepth( int _depth )
{
	depth = _depth;
}

bool InterObj::CompareLessThan( const InterObj * left, const InterObj * right )
{
	return left->depth < right->depth;
}

void InterObj::SetAlpha( int _alpha )
{
	alpha = _alpha;
}

void InterObj::SetColor( int col )
{
	color = col;
}

void InterObj::SetAnimationOffset( int index, int siidoffset, int duration )
{
	SetAnimation(index, basesiid+siidoffset, duration);
}

void InterObj::SetAnimation( InterObjAnimation * animes, int nanime )
{
	if (!animes || !nanime)
	{
		return;
	}
	nanime = min(nanime, ANIMATIONMAX);
	for (int i=0; i<nanime; i++)
	{
		SetAnimation(i, animes[i].siid, animes[i].duration);
	}
}

void InterObj::SetAnimation( int index, int siid, int duration )
{
	if (index < 0 || index >= ANIMATIONMAX)
	{
		return;
	}
	ianime[index].SetValue(siid, duration);
}

void InterObj::ClearAnimation()
{
	for (int i=0; i<ANIMATIONMAX; i++)
	{
		ianime[i].ClearSet();
	}
}

void InterObj::SetBaseSIID( int siid )
{
	basesiid = siid;
	SetSIID(siid);
}

void InterObj::DoAnimation()
{
	++animetimer;
	int totalduration = 0;
	int i=0;
	for (; i<ANIMATIONMAX; i++)
	{
		if (ianime[i].Registered())
		{
			totalduration += ianime[i].duration;
			if (animetimer < totalduration)
			{
				break;
			}
		}
		else
		{
			i = ANIMATIONMAX;
			break;
		}
	}
	if (i == ANIMATIONMAX)
	{
		i = 0;
		animetimer = 0;
	}
	SetSIID(ianime[i].siid);
}

void InterObj::CalculateBound()
{
	lBound = x+boundingxoff-boundingw;
	rBound = x+boundingxoff+boundingw;
	tBound = y+boundingyoff-boundingh;
	bBound = y+boundingyoff+boundingh;
}
