#pragma once

#include "MainDependency.h"
#include "Const.h"

enum {
	OBJLAYER_BG_DEEP = 1000,
	OBJLAYER_BG_MIDDLE = 2000,
	OBJLAYER_BG_SHALLOW = 3000,
	OBJLAYER_PLATFORM = 4000,
	OBJLAYER_PLAYER = 5000,
	OBJLAYER_KILLER_HIDE = 6000,
	OBJLAYER_BLOCK = 7000,
	OBJLAYER_KILLER = 8000,
	OBJLAYER_FG_DEEP = 9000,
	OBJLAYER_FG_MIDDLE = 10000,
	OBJLAYER_FG_SHALLOW = 11000,
};

enum{
	COLLISIONTYPE_BOUNDINGBOX,
	COLLISIONTYPE_RECT,
	COLLISIONTYPE_SURFACE,
	COLLISIONTYPE_TRIANGLE,
	COLLISIONTYPE_CIRCLE,
	COLLISIONTYPE_EVENT,

	COLLISIONTYPE_ALWAYS,
	COLLISIONTYPE_NEVER,
};

class InteractiveEvent
{
public:
	InteractiveEvent()
	{
		opponentrealmflag = 0;
	};
	~InteractiveEvent(){};

	bool Registered(){return opponentrealmflag;};
	bool SetValue(int _opponentflag, int _cltype, int _a, int _b, int _xoff, int _yoff, int _angle, int _eventid, bool _bonce)
	{
		if (_opponentflag)
		{
			opponentrealmflag = _opponentflag;
			cltype = _cltype;
			a = _a;
			b = _b;
			xoff = _xoff;
			yoff = _yoff;
			angle = _angle;
			eventid = _eventid;
			bonce = _bonce;
			return true;
		}
		return false;
	};

	int opponentrealmflag;
	int cltype;
	int a;
	int b;
	int xoff;
	int yoff;
	int angle;
	int eventid;
	bool bonce;
};

enum
{
	COLLISIONEVENTID_KILLPLAYER,
	COLLISIONEVENTID_BLOCKPLAYER,

	COLLISIONEVENTID_SYSTEMEND	= 1000,
	COLLISIONEVENTID_SCRIPTBEGIN = 1000,
};

#define INTERACTIVEEVENTMAX	8

#define REALMFLAG_PLAYERSIDE	0x0010
#define REALMFLAG_PLAYER		0x0011
#define REALMFLAG_PLAYERBULLET	0x0012
#define REALMFLAG_BLOCKSIDE		0x0100
#define REALMFLAG_ENEMYSIDE		0x1000
#define REALMFLAG_EMPTYSIDE		0x8000

#define ANIMATIONMAX	4

class InterObjAnimation 
{
public:
	InterObjAnimation(){siid = -1;};
	~InterObjAnimation(){};

	void SetValue(int _siid, int _duration)
	{
		siid = _siid;
		duration = _duration;
	};
	bool Registered(){return siid >= 0;};
	void ClearSet(){siid = -1;};

	int siid;
	int duration;
};

class InterObj
{
public:
	InterObj();
	~InterObj();

	static bool CompareLessThan(const InterObj * left, const InterObj * right);

	void SetBaseSIID(int siid);
	void SetSIID(int siid);
	void SetPos(int xpos, int ypos);
	void SetRot(int _angle);
	void SetScale(float hs, float vs=0.0f);
	void SetRealm(int _realmflag);
	int GetRealm(){return realmflag;};
	void SetDepth(int _depth);

	void SetAlpha(int alpha);
	void SetColor(int col);

	void SetBoundingBox(int bxoff, int byoff, int bw, int bh);

	bool AddInteractiveEvent(int opponentflag, int cltype, int a, int b, int xoff, int yoff, int angle, int eventid, bool bonce);
	
	void SetAnimation(int index, int siid, int duration);
	void SetAnimationOffset(int index, int siidoffset, int duration);
	void SetAnimation(InterObjAnimation * animes, int nanime);
	void ClearAnimation();

	void CalculateBound();

	void DoAnimation();

	virtual void Update();
	virtual void Render();

protected:

	int basesiid;
	int cursiid;
	hgeSprite * sp;
	bool bFlipX;
	int x;
	int y;
	int angle;
	int realmflag;
	float hscale;
	float vscale;

	int depth;

	int alpha;
	int color;

	int boundingw;
	int boundingh;
	int boundingxoff;
	int boundingyoff;

	int lBound;
	int rBound;
	int tBound;
	int bBound;

	int timer;
	int animetimer;

	InteractiveEvent ievent[INTERACTIVEEVENTMAX];
	InterObjAnimation ianime[ANIMATIONMAX];
};