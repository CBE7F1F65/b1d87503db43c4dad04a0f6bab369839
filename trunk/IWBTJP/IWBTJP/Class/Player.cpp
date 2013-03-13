#include "../Header/Player.h"
#include "../Header/BResource.h"
#include "../Header/GameInput.h"

Player::Player(int id/*=0*/)
{
	playerID = id;
	ClearSet();
}

Player::~Player()
{

}

void Player::ClearSet()
{
	ZeroMemory(&nowstate, sizeof(nowstate));
	laststate = nowstate;

	blockdisl = BLOCKDISTMAX;
	blockdisr = BLOCKDISTMAX;
	blockdist = BLOCKDISTMAX;
	blockdisb = BLOCKDISTMAX;

	baseVal.lSpeed = 200;
	baseVal.rSpeed = 200;
	baseVal.fjSpeed = -720;
	baseVal.sjSpeed = -600;
	baseVal.fSpeedAcc = 30;
	baseVal.fSpeedMax = 600;
	baseVal.fjJumpTimerMax = 24;
	baseVal.sjJumpTimerMax = 20;
	baseVal.fjJumpTimerMin = 10;
	baseVal.sjJumpTimerMin = 8;
	curVal = baseVal;
	vSpeed = 0;

	jumptimer = 0;

	EnterMotion(PLAYERMOTION_IDLE);

	SetRealm(REALMFLAG_PLAYER);
	SetDepth(OBJLAYER_PLAYER);
	CalculateBound();
}

void Player::PlayerUpdate()
{
	DispatchInput();
	curVal = baseVal;

	laststate = nowstate;

	if (nowstate.facinglrstate == PLAYERSTATE_FACINGLEFT)
	{
		bFlipX = true;
	}
	else if (nowstate.facinglrstate == PLAYERSTATE_FACINGRIGHT)
	{
		bFlipX = false;
	}

	if (vSpeed > curVal.fSpeedMax)
	{
		vSpeed = curVal.fSpeedMax;
	}
	if (blockdisb)
	{
		ToFall();
	}

	blockdisl = BLOCKDISTMAX;
	blockdisr = BLOCKDISTMAX;
	blockdist = BLOCKDISTMAX;
	blockdisb = BLOCKDISTMAX;
	CalculateBound();
}

void Player::DispatchInput()
{
	bool bkdleft = GameInput::GetKey(playerID, KSI_LEFT);
	bool bkdright = GameInput::GetKey(playerID, KSI_RIGHT);
	bool bkdup = GameInput::GetKey(playerID, KSI_UP);
	bool bkddown = GameInput::GetKey(playerID, KSI_DOWN);
	bool bkdjump = GameInput::GetKey(playerID, KSI_JUMP, DIKEY_DOWN);
	bool bkdshoot = GameInput::GetKey(playerID, KSI_SHOOT, DIKEY_DOWN);
	bool bkdsuicide = GameInput::GetKey(playerID, KSI_SUICIDE, DIKEY_DOWN);
	bool bkdspecial = GameInput::GetKey(playerID, KSI_SPECIAL, DIKEY_DOWN);

	if (bkdsuicide)
	{
		Die();
	}
	if (bkdjump)
	{
		Jump(bkdup, bkddown);
	}

	if (nowstate.motionstate == PLAYERSTATE_FIRSTJUMPUP)
	{
		if (!GameInput::GetKey(playerID, KSI_JUMP)&&jumptimer>=curVal.fjJumpTimerMin || jumptimer >= curVal.fjJumpTimerMax)
		{
			SetMotionState(PLAYERSTATE_FIRSTJUMPFALL);
			EnterMotion(PLAYERMOTION_FALL);
			jumptimer = 0;
			if (vSpeed < 0)
			{
				vSpeed = 0;
			}
		}
		else
		{
			Jumping();
		}
	}
	else if (nowstate.motionstate == PLAYERSTATE_SECONDJUMPUP)
	{
		if (!GameInput::GetKey(playerID, KSI_JUMP)&&jumptimer>=curVal.sjJumpTimerMin || jumptimer >= curVal.sjJumpTimerMax)
		{
			SetMotionState(PLAYERSTATE_SECONDJUMPFALL);
			EnterMotion(PLAYERMOTION_FALL);
			jumptimer = 0;
			if (vSpeed < 0)
			{
				vSpeed = 0;
			}
		}
		else
		{
			Jumping();
		}
	}
	if (nowstate.motionstate == PLAYERSTATE_FIRSTJUMPFALL || nowstate.motionstate == PLAYERSTATE_SECONDJUMPFALL)
	{
		Falling();
	}

	if (bkdshoot)
	{
		Shoot();
	}
	if (bkdleft && !bkdright)
	{
		MoveLeft();
	}
	else if (bkdright && !bkdleft)
	{
		MoveRight();
	}
	else
	{
		if (nowstate.motionstate == PLAYERSTATE_LANDMOVING)
		{
			SetMotionState(PLAYERSTATE_IDLE);
			EnterMotion(PLAYERMOTION_IDLE);
		}
	}

}

void Player::Jump( bool bHoldUp, bool bHoldDown )
{
	if (nowstate.motionstate == PLAYERSTATE_SECONDJUMPUP || nowstate.motionstate == PLAYERSTATE_SECONDJUMPFALL)
	{
		return;
	}
	jumptimer = 0;
	if (nowstate.motionstate == PLAYERSTATE_IDLE || nowstate.motionstate == PLAYERSTATE_LANDMOVING)
	{
		vSpeed = curVal.fjSpeed;
		SetMotionState(PLAYERSTATE_FIRSTJUMPUP);
		EnterMotion(PLAYERMOTION_JUMP);
	}
	else if (nowstate.motionstate == PLAYERSTATE_FIRSTJUMPUP || nowstate.motionstate == PLAYERSTATE_FIRSTJUMPFALL)
	{
		vSpeed = curVal.sjSpeed;
		SetMotionState(PLAYERSTATE_SECONDJUMPUP);
		EnterMotion(PLAYERMOTION_JUMP);
	}
}

void Player::MoveLeft()
{
	DoXMove(-curVal.lSpeed);

	if (nowstate.motionstate == PLAYERSTATE_IDLE)
	{
		EnterMotion(PLAYERMOTION_WALK);
		SetMotionState(PLAYERSTATE_LANDMOVING);
	}
	if (nowstate.movinglrstate != PLAYERSTATE_LSLIDE)
	{
		SetLRMovingState(PLAYERSTATE_LMOVING);
	}
}

void Player::MoveRight()
{
	DoXMove(curVal.rSpeed);

	if (nowstate.motionstate == PLAYERSTATE_IDLE)
	{
		EnterMotion(PLAYERMOTION_WALK);
		SetMotionState(PLAYERSTATE_LANDMOVING);
	}
	if (nowstate.movinglrstate != PLAYERSTATE_RSLIDE)
	{
		SetLRMovingState(PLAYERSTATE_RMOVING);
	}
}

void Player::Jumping()
{
	++jumptimer;

	vSpeed += curVal.fSpeedAcc;
	float ymove = vSpeed;
	/*
	if (-ymove > blockdist)
	{
		ymove = -blockdist;
	}
	y += ymove;

	blockdisb -= ymove;
	blockdist += ymove;
	*/
	DoYMove(ymove);
	if (blockdist <= 0)
	{
		if (nowstate.motionstate == PLAYERSTATE_FIRSTJUMPUP)
		{
			jumptimer = curVal.fjJumpTimerMax;
		}
		else
		{
			jumptimer = curVal.sjJumpTimerMax;
		}
		if (vSpeed < 0)
		{
			vSpeed = 0;
		}
	}
}

void Player::Falling()
{
	float fSpeedAcc = curVal.fSpeedAcc;
	vSpeed += fSpeedAcc;
	if (vSpeed > curVal.fSpeedMax)
	{
		vSpeed = curVal.fSpeedMax;
	}
	float ymove = vSpeed;
	if (ymove >= blockdisb)
	{
		ymove = blockdisb;
		vSpeed = 0;
		SetMotionState(PLAYERSTATE_IDLE);
		EnterMotion(PLAYERMOTION_IDLE);
	}
	/*
	y += ymove;

	blockdisb -= ymove;
	blockdist += ymove;
	*/
	DoYMove(ymove);
}

void Player::Shoot()
{

}

void Player::Die()
{

}

void Player::SetMotionState( int state )
{
	nowstate.motionstate = state;
}

void Player::SetLRMovingState( int state )
{
	nowstate.movinglrstate = state;

	if (state == PLAYERSTATE_LMOVING || state == PLAYERSTATE_LSLIDE)
	{
		SetLRFacingState(PLAYERSTATE_FACINGLEFT);
	}
	else if (state == PLAYERSTATE_RMOVING || state == PLAYERSTATE_RSLIDE)
	{
		SetLRFacingState(PLAYERSTATE_FACINGRIGHT);
	}
}

void Player::SetLRFacingState( int state )
{
	nowstate.facinglrstate = state;
}

void Player::SetShootState( int state )
{
	nowstate.shootstate = state;
}

bool Player::IsFacingLeft()
{
	return nowstate.facinglrstate == PLAYERSTATE_FACINGLEFT;
}

void Player::EnterMotion( int motion )
{
	if (motion < 0 || motion >= PLAYERMOTIONSETMAX)
	{
		return;
	}
	playerMotionData * pmd = &BResource::PIns()->playermotiondata[motion];
	SetBaseSIID(pmd->basesiid);
	ClearAnimation();
	SetAnimation(0, pmd->basesiid, pmd->duration[0]);
	for (int i=1; i<ANIMATIONMAX; i++)
	{
		if (!pmd->duration[i])
		{
			break;
		}
		SetAnimation(i, pmd->basesiid+pmd->siidoffset[i-1], pmd->duration[i]);
	}
	SetBoundingBox(pmd->bbxoff, pmd->bbyoff, pmd->bbw, pmd->bbh);
}

bool Player::CheckBlock( int l, int r, int t, int b )
{
	if (tBound < b && bBound > t)
	{
		if (lBound <= l)
		{
			int rdis = l-rBound;
			if (rdis < blockdisr)
			{
				if (rdis < 0)
				{
					if (IsOnLand())
					{
						DoYMove(t-bBound);
						blockdisb = 0;
					}
					else
					{
						DoXMove(rdis);
						blockdisr = 0;
					}
				}
				else
				{
					blockdisr = rdis;
				}
			}
			if (rBound == l)
			{
				return true;
			}
		}
		if (rBound >= r)
		{
			int ldis = lBound-r;
			if (ldis < blockdisl)
			{
				if (ldis < 0)
				{
					if (IsOnLand())
					{
						DoYMove(t-bBound);
						blockdisb = 0;
					}
					else
					{
						DoXMove(-ldis);
						blockdisl = 0;
					}
				}
				else
				{
					blockdisl = ldis;
				}
			}
			if (lBound == r)
			{
				return true;
			}
		}
	}
	if (lBound < r && rBound > l)
	{
		if (tBound <= t)
		{
			int bdis = t-bBound;
			if (bdis < blockdisb)
			{
				if (bdis < 0)
				{
					DoYMove(bdis);
					bdis = 0;
				}
				blockdisb = bdis;
			}
			if (bBound == t)
			{
				return true;
			}
		}
		if (bBound >= b)
		{
			int tdis = tBound-b;
			if (tdis < blockdist)
			{
				if (tdis < 0)
				{
					DoYMove(-tdis);
					tdis = 0;
				}
				blockdist = tdis;
			}
			if (tBound == b)
			{
				return true;
			}
		}
	}
	return false;
}

void Player::ToFall()
{
	if (IsOnLand())
	{
		SetMotionState(PLAYERSTATE_FIRSTJUMPFALL);
		EnterMotion(PLAYERMOTION_FALL);
	}
}

bool Player::IsOnLand()
{
	if (nowstate.motionstate == PLAYERSTATE_LANDMOVING || nowstate.motionstate == PLAYERSTATE_IDLE || nowstate.motionstate == PLAYERSTATE_SLIDE)
	{
		return true;
	}
	return false;
}

void Player::DoXMove( int xoff )
{
	if (xoff > 0)
	{
		if (blockdisr < xoff)
		{
			xoff = blockdisr;
		}
	}
	else if (xoff < 0)
	{
		if (blockdisl < -xoff)
		{
			xoff = -blockdisl;
		}
	}

	x += xoff;

	blockdisl += xoff;
	blockdisr -= xoff;

	CalculateBound();
}
void Player::DoYMove( int yoff )
{
	if (yoff > 0)
	{
		if (blockdisb < yoff)
		{
			yoff = blockdisb;
		}
	}
	else if (yoff < 0)
	{
		if (blockdist < -yoff)
		{
			yoff = -blockdist;
		}
	}

	y += yoff;

	blockdist += yoff;
	blockdisb -= yoff;

	CalculateBound();

	if (y>48000)
	{
		y=0;
	}
}
