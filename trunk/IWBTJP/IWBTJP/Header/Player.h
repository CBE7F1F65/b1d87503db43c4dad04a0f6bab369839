#pragma once

#include "InterObj.h"

enum {
	PLAYERSTATE_IDLE,
	PLAYERSTATE_LANDMOVING,
	PLAYERSTATE_FIRSTJUMPUP,
	PLAYERSTATE_SECONDJUMPUP,
	PLAYERSTATE_FIRSTJUMPFALL,
	PLAYERSTATE_SECONDJUMPFALL,
	PLAYERSTATE_SLIDE,
};

enum{
	PLAYERSTATE_RMOVING,
	PLAYERSTATE_LMOVING,
	PLAYERSTATE_RSLIDE,
	PLAYERSTATE_LSLIDE,
};

enum{
	PLAYERSTATE_FACINGRIGHT,
	PLAYERSTATE_FACINGLEFT,
};

enum{
	PLAYERSTATE_SHOOTING,
	PLAYERSTATE_SHOOTCD,
};

#define BLOCKDISTMAX	10000000

enum{
	PLAYERMOTION_IDLE,
	PLAYERMOTION_WALK,
	PLAYERMOTION_JUMP,
	PLAYERMOTION_FALL,
	PLAYERMOTION_SLIDE,

	PLAYERMOTIONSETMAX,
};

class Player : public InterObj
{
public:
	Player(int id=0);
	~Player();

	void PlayerUpdate();

	void DispatchInput();


	void Jump(bool bHoldUp, bool bHoldDown);
	void MoveLeft();
	void MoveRight();
	void Shoot();

	void Jumping();
	void Falling();

	void ToFall();

	void Die();

	void ClearSet();

	bool IsFacingLeft();
	bool IsOnLand();

	void DoXMove(int xoff);
	void DoYMove(int xoff);
	void DoMove(int xoff, int yoff){DoXMove(xoff); DoYMove(yoff);};

	void SetMotionState(int state);
	void SetLRMovingState(int state);
	void SetLRFacingState(int state);
	void SetShootState(int state);

	void EnterMotion(int motion);


	bool CheckBlock(int l, int r, int t, int b);

public:

	int playerID;

	struct  
	{
		int motionstate;
		int movinglrstate;
		int facinglrstate;
		int shootstate;
	}nowstate, laststate;

	int jumptimer;

	int blockdisl;
	int blockdisr;
	int blockdist;
	int blockdisb;

	struct  
	{
		int lSpeed;
		int rSpeed;
		int fjSpeed;
		int sjSpeed;
		int fSpeedAcc;
		int fSpeedMax;
		int fjJumpTimerMax;
		int sjJumpTimerMax;
	}baseVal, curVal;

	int vSpeed;
};