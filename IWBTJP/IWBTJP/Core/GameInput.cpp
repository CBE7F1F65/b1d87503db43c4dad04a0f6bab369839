#include "../Header/GameInput.h"
#include "../Header/ConstResource.h"
#include "../Header/Process.h"

GameInput GameInput::gameinput[M_PL_MATCHMAXPLAYER];
HGE * GameInput::hge = NULL;
bool GameInput::swapinput = false;

GameInput::GameInput()
{
	KS_UP_(0)		= RESCONFIGDEFAULT_KEYUP_1;
	KS_DOWN_(0)		= RESCONFIGDEFAULT_KEYDOWN_1;
	KS_LEFT_(0)		= RESCONFIGDEFAULT_KEYLEFT_1;
	KS_RIGHT_(0)	= RESCONFIGDEFAULT_KEYRIGHT_1;
	KS_SHOOT_(0)		= RESCONFIGDEFAULT_KEYSHOOT_1;
	KS_JUMP_(0)	= RESCONFIGDEFAULT_KEYJUMP_1;
	KS_SUICIDE_(0)		= RESCONFIGDEFAULT_KEYSUICIDE_1;
	KS_SPECIAL_(0)	= RESCONFIGDEFAULT_KEYSPECIAL_1;
	KS_PAUSE_(0)	= RESCONFIGDEFAULT_KEYPAUSE;
	KS_SKIP_(0)		= RESCONFIGDEFAULT_KEYSKIP;
	KS_RETRY_(0)		= RESCONFIGDEFAULT_KEYRETRY;
	KS_ENTER_(0)	= RESCONFIGDEFAULT_KEYENTER;
	KS_ESCAPE_(0)	= RESCONFIGDEFAULT_KEYESCAPE;
	KS_CAPTURE_(0)	= RESCONFIGDEFAULT_KEYCAPTURE;

	KS_UP_(1)		= RESCONFIGDEFAULT_KEYUP_2;
	KS_DOWN_(1)		= RESCONFIGDEFAULT_KEYDOWN_2;
	KS_LEFT_(1)		= RESCONFIGDEFAULT_KEYLEFT_2;
	KS_RIGHT_(1)	= RESCONFIGDEFAULT_KEYRIGHT_2;
	KS_SHOOT_(1)		= RESCONFIGDEFAULT_KEYSHOOT_2;
	KS_JUMP_(1)	= RESCONFIGDEFAULT_KEYJUMP_2;
	KS_SUICIDE_(1)		= RESCONFIGDEFAULT_KEYSUICIDE_2;
	KS_SPECIAL_(1)	= RESCONFIGDEFAULT_KEYSPECIAL_2;
	KS_PAUSE_(1)	= RESCONFIGDEFAULT_KEYPAUSE;
	KS_SKIP_(1)		= RESCONFIGDEFAULT_KEYSKIP;
	KS_RETRY_(1)		= RESCONFIGDEFAULT_KEYRETRY;
	KS_ENTER_(1)	= RESCONFIGDEFAULT_KEYENTER;
	KS_ESCAPE_(1)	= RESCONFIGDEFAULT_KEYESCAPE;
	KS_CAPTURE_(1)	= RESCONFIGDEFAULT_KEYCAPTURE;
}

GameInput::~GameInput()
{

}

bool GameInput::InitInput(HGE * _hge)
{
	hge = _hge;

	KS_UP_(0)		= hge->Ini_GetInt(RESCONFIGS_KEYSETTING_1, RESCONFIGN_KEYUP, RESCONFIGDEFAULT_KEYUP_1);
	KS_DOWN_(0)		= hge->Ini_GetInt(RESCONFIGS_KEYSETTING_1, RESCONFIGN_KEYDOWN, RESCONFIGDEFAULT_KEYDOWN_1);
	KS_LEFT_(0)		= hge->Ini_GetInt(RESCONFIGS_KEYSETTING_1, RESCONFIGN_KEYLEFT, RESCONFIGDEFAULT_KEYLEFT_1);
	KS_RIGHT_(0)	= hge->Ini_GetInt(RESCONFIGS_KEYSETTING_1, RESCONFIGN_KEYRIGHT, RESCONFIGDEFAULT_KEYRIGHT_1);
	KS_SHOOT_(0)		= hge->Ini_GetInt(RESCONFIGS_KEYSETTING_1, RESCONFIGN_KEYSHOOT, RESCONFIGDEFAULT_KEYSHOOT_1);
	KS_JUMP_(0)		= hge->Ini_GetInt(RESCONFIGS_KEYSETTING_1, RESCONFIGN_KEYJUMP, RESCONFIGDEFAULT_KEYJUMP_1);
	KS_SUICIDE_(0)	= hge->Ini_GetInt(RESCONFIGS_KEYSETTING_1, RESCONFIGN_KEYSUICIDE, RESCONFIGDEFAULT_KEYSUICIDE_1);
	KS_SPECIAL_(0)	= hge->Ini_GetInt(RESCONFIGS_KEYSETTING_1, RESCONFIGN_KEYSPECIAL, RESCONFIGDEFAULT_KEYSPECIAL_1);
	KS_PAUSE_(0)	= hge->Ini_GetInt(RESCONFIGS_KEYSETTING_1, RESCONFIGN_KEYPAUSE, RESCONFIGDEFAULT_KEYPAUSE);
	KS_SKIP_(0)		= hge->Ini_GetInt(RESCONFIGS_KEYSETTING_1, RESCONFIGN_KEYSKIP, RESCONFIGDEFAULT_KEYSKIP);
	KS_RETRY_(0)	= hge->Ini_GetInt(RESCONFIGS_KEYSETTING_1, RESCONFIGN_KEYRETRY, RESCONFIGDEFAULT_KEYRETRY);
	KS_ENTER_(0)	= hge->Ini_GetInt(RESCONFIGS_KEYSETTING_1, RESCONFIGN_KEYENTER, RESCONFIGDEFAULT_KEYENTER);
	KS_ESCAPE_(0)	= hge->Ini_GetInt(RESCONFIGS_KEYSETTING_1, RESCONFIGN_KEYESCAPE, RESCONFIGDEFAULT_KEYESCAPE);
	KS_CAPTURE_(0)	= hge->Ini_GetInt(RESCONFIGS_KEYSETTING_1, RESCONFIGN_KEYCAPTURE, RESCONFIGDEFAULT_KEYCAPTURE);

	KS_UP_(1)		= hge->Ini_GetInt(RESCONFIGS_KEYSETTING_2, RESCONFIGN_KEYUP, RESCONFIGDEFAULT_KEYUP_2);
	KS_DOWN_(1)		= hge->Ini_GetInt(RESCONFIGS_KEYSETTING_2, RESCONFIGN_KEYDOWN, RESCONFIGDEFAULT_KEYDOWN_2);
	KS_LEFT_(1)		= hge->Ini_GetInt(RESCONFIGS_KEYSETTING_2, RESCONFIGN_KEYLEFT, RESCONFIGDEFAULT_KEYLEFT_2);
	KS_RIGHT_(1)	= hge->Ini_GetInt(RESCONFIGS_KEYSETTING_2, RESCONFIGN_KEYRIGHT, RESCONFIGDEFAULT_KEYRIGHT_2);
	KS_SHOOT_(1)		= hge->Ini_GetInt(RESCONFIGS_KEYSETTING_2, RESCONFIGN_KEYSHOOT, RESCONFIGDEFAULT_KEYSHOOT_2);
	KS_JUMP_(1)	= hge->Ini_GetInt(RESCONFIGS_KEYSETTING_2, RESCONFIGN_KEYJUMP, RESCONFIGDEFAULT_KEYJUMP_2);
	KS_SUICIDE_(1)		= hge->Ini_GetInt(RESCONFIGS_KEYSETTING_2, RESCONFIGN_KEYSUICIDE, RESCONFIGDEFAULT_KEYSUICIDE_2);
	KS_SPECIAL_(1)	= hge->Ini_GetInt(RESCONFIGS_KEYSETTING_2, RESCONFIGN_KEYSPECIAL, RESCONFIGDEFAULT_KEYSPECIAL_2);
	KS_PAUSE_(1)	= hge->Ini_GetInt(RESCONFIGS_KEYSETTING_2, RESCONFIGN_KEYPAUSE, RESCONFIGDEFAULT_KEYPAUSE);
	KS_SKIP_(1)		= hge->Ini_GetInt(RESCONFIGS_KEYSETTING_2, RESCONFIGN_KEYSKIP, RESCONFIGDEFAULT_KEYSKIP);
	KS_RETRY_(1)	= hge->Ini_GetInt(RESCONFIGS_KEYSETTING_2, RESCONFIGN_KEYRETRY, RESCONFIGDEFAULT_KEYRETRY);
	KS_ENTER_(1)	= hge->Ini_GetInt(RESCONFIGS_KEYSETTING_2, RESCONFIGN_KEYENTER, RESCONFIGDEFAULT_KEYENTER);
	KS_ESCAPE_(1)	= hge->Ini_GetInt(RESCONFIGS_KEYSETTING_2, RESCONFIGN_KEYESCAPE, RESCONFIGDEFAULT_KEYESCAPE);
	KS_CAPTURE_(1)	= hge->Ini_GetInt(RESCONFIGS_KEYSETTING_2, RESCONFIGN_KEYCAPTURE, RESCONFIGDEFAULT_KEYCAPTURE);

	JS_SHOOT_(0)		= hge->Ini_GetInt(RESCONFIGS_KEYSETTING_1, RESCONFIGN_JOYSHOOT, RESCONFIGDEFAULT_JOYSHOOT);
	JS_JUMP_(0)	= hge->Ini_GetInt(RESCONFIGS_KEYSETTING_1, RESCONFIGN_JOYJUMP, RESCONFIGDEFAULT_JOYJUMP);
	JS_SUICIDE_(0)		= hge->Ini_GetInt(RESCONFIGS_KEYSETTING_1, RESCONFIGN_JOYSUICIDE, RESCONFIGDEFAULT_JOYSUICIDE);
	JS_SPECIAL_(0)	= hge->Ini_GetInt(RESCONFIGS_KEYSETTING_1, RESCONFIGN_JOYSPECIAL, RESCONFIGDEFAULT_JOYSPECIAL);
	JS_PAUSE_(0)	= hge->Ini_GetInt(RESCONFIGS_KEYSETTING_1, RESCONFIGN_JOYPAUSE, RESCONFIGDEFAULT_JOYPAUSE);
	JS_RETRY_(0)	= hge->Ini_GetInt(RESCONFIGS_KEYSETTING_1, RESCONFIGN_JOYRETRY, RESCONFIGDEFAULT_JOYRETRY);

	JS_SHOOT_(1)		= hge->Ini_GetInt(RESCONFIGS_KEYSETTING_2, RESCONFIGN_JOYSHOOT, RESCONFIGDEFAULT_JOYSHOOT);
	JS_JUMP_(1)	= hge->Ini_GetInt(RESCONFIGS_KEYSETTING_2, RESCONFIGN_JOYJUMP, RESCONFIGDEFAULT_JOYJUMP);
	JS_SUICIDE_(1)		= hge->Ini_GetInt(RESCONFIGS_KEYSETTING_2, RESCONFIGN_JOYSUICIDE, RESCONFIGDEFAULT_JOYSUICIDE);
	JS_SPECIAL_(1)	= hge->Ini_GetInt(RESCONFIGS_KEYSETTING_2, RESCONFIGN_JOYSPECIAL, RESCONFIGDEFAULT_JOYSPECIAL);
	JS_PAUSE_(1)	= hge->Ini_GetInt(RESCONFIGS_KEYSETTING_2, RESCONFIGN_JOYPAUSE, RESCONFIGDEFAULT_JOYPAUSE);
	JS_RETRY_(1)	= hge->Ini_GetInt(RESCONFIGS_KEYSETTING_2, RESCONFIGN_JOYRETRY, RESCONFIGDEFAULT_JOYRETRY);

#ifdef __DEBUG
	JS_DEBUG_SPEEDUP_(0) = hge->Ini_GetInt(RESCONFIGS_KEYSETTING_1, RESCONFIGN_DEBUG_JOYSPEEDUP, RESCONFIGDEFAULT_DEBUG_JOYSPEEDUP);
	JS_DEBUG_SPEEDUP_(1) = hge->Ini_GetInt(RESCONFIGS_KEYSETTING_2, RESCONFIGN_DEBUG_JOYSPEEDUP, RESCONFIGDEFAULT_DEBUG_JOYSPEEDUP);
#endif
	for (int j=0; j<M_PL_MATCHMAXPLAYER; j++)
	{
		for (int i=0; i<GAMEINPUTKEYMAX; i++)
		{
			if (gameinput[j].keyKey[i] < 0 || gameinput[j].keyKey[i] >= M_KEYKEYMAX)
			{
				return false;
			}
		}
		for (int i=0; i<GAMEINPUTJOYMAX; i++)
		{
			if(gameinput[j].joyKey[i] < 0 || gameinput[j].joyKey[i] >= M_JOYKEYMAX)
			{
				return false;
			}
		}
	}
#ifdef __DEBUG
	if(JS_DEBUG_SPEEDUP_(0) < 0 || JS_DEBUG_SPEEDUP_(0) >= M_JOYKEYMAX ||
		JS_DEBUG_SPEEDUP_(1) < 0 || JS_DEBUG_SPEEDUP_(1) >= M_JOYKEYMAX)
		return false;
#endif
	return true;
}

bool GameInput::ReleaseInput()
{
	hge->	Ini_SetInt(RESCONFIGS_KEYSETTING_1, RESCONFIGN_KEYUP, KS_UP_(0));
	hge->	Ini_SetInt(RESCONFIGS_KEYSETTING_1, RESCONFIGN_KEYDOWN, KS_DOWN_(0));
	hge->	Ini_SetInt(RESCONFIGS_KEYSETTING_1, RESCONFIGN_KEYLEFT, KS_LEFT_(0));
	hge->	Ini_SetInt(RESCONFIGS_KEYSETTING_1, RESCONFIGN_KEYRIGHT, KS_RIGHT_(0));
	hge->	Ini_SetInt(RESCONFIGS_KEYSETTING_1, RESCONFIGN_KEYSHOOT, KS_SHOOT_(0));
	hge->	Ini_SetInt(RESCONFIGS_KEYSETTING_1, RESCONFIGN_KEYJUMP, KS_JUMP_(0));
	hge->	Ini_SetInt(RESCONFIGS_KEYSETTING_1, RESCONFIGN_KEYSUICIDE, KS_SUICIDE_(0));
	hge->	Ini_SetInt(RESCONFIGS_KEYSETTING_1, RESCONFIGN_KEYSPECIAL, KS_SPECIAL_(0));
	hge->	Ini_SetInt(RESCONFIGS_KEYSETTING_1, RESCONFIGN_KEYPAUSE, KS_PAUSE_(0));
	hge->	Ini_SetInt(RESCONFIGS_KEYSETTING_1, RESCONFIGN_KEYSKIP, KS_SKIP_(0));
	hge->	Ini_SetInt(RESCONFIGS_KEYSETTING_1, RESCONFIGN_KEYRETRY, KS_RETRY_(0));
	hge->	Ini_SetInt(RESCONFIGS_KEYSETTING_1, RESCONFIGN_KEYENTER, KS_ENTER_(0));
	hge->	Ini_SetInt(RESCONFIGS_KEYSETTING_1, RESCONFIGN_KEYESCAPE, KS_ESCAPE_(0));
	hge->	Ini_SetInt(RESCONFIGS_KEYSETTING_1, RESCONFIGN_KEYCAPTURE, KS_CAPTURE_(0));

	hge->	Ini_SetInt(RESCONFIGS_KEYSETTING_1, RESCONFIGN_JOYSHOOT, JS_SHOOT_(0));
	hge->	Ini_SetInt(RESCONFIGS_KEYSETTING_1, RESCONFIGN_JOYJUMP, JS_JUMP_(0));
	hge->	Ini_SetInt(RESCONFIGS_KEYSETTING_1, RESCONFIGN_JOYSUICIDE, JS_SUICIDE_(0));
	hge->	Ini_SetInt(RESCONFIGS_KEYSETTING_1, RESCONFIGN_JOYSPECIAL, JS_SPECIAL_(0));
	hge->	Ini_SetInt(RESCONFIGS_KEYSETTING_1, RESCONFIGN_JOYPAUSE, JS_PAUSE_(0));
	hge->	Ini_SetInt(RESCONFIGS_KEYSETTING_1, RESCONFIGN_JOYRETRY, JS_RETRY_(0));

	hge->	Ini_SetInt(RESCONFIGS_KEYSETTING_2, RESCONFIGN_KEYUP, KS_UP_(1));
	hge->	Ini_SetInt(RESCONFIGS_KEYSETTING_2, RESCONFIGN_KEYDOWN, KS_DOWN_(1));
	hge->	Ini_SetInt(RESCONFIGS_KEYSETTING_2, RESCONFIGN_KEYLEFT, KS_LEFT_(1));
	hge->	Ini_SetInt(RESCONFIGS_KEYSETTING_2, RESCONFIGN_KEYRIGHT, KS_RIGHT_(1));
	hge->	Ini_SetInt(RESCONFIGS_KEYSETTING_2, RESCONFIGN_KEYSHOOT, KS_SHOOT_(1));
	hge->	Ini_SetInt(RESCONFIGS_KEYSETTING_2, RESCONFIGN_KEYJUMP, KS_JUMP_(1));
	hge->	Ini_SetInt(RESCONFIGS_KEYSETTING_2, RESCONFIGN_KEYSUICIDE, KS_SUICIDE_(1));
	hge->	Ini_SetInt(RESCONFIGS_KEYSETTING_2, RESCONFIGN_KEYSPECIAL, KS_SPECIAL_(1));
	hge->	Ini_SetInt(RESCONFIGS_KEYSETTING_2, RESCONFIGN_KEYPAUSE, KS_PAUSE_(1));
	hge->	Ini_SetInt(RESCONFIGS_KEYSETTING_2, RESCONFIGN_KEYSKIP, KS_SKIP_(1));
	hge->	Ini_SetInt(RESCONFIGS_KEYSETTING_2, RESCONFIGN_KEYRETRY, KS_RETRY_(1));
	hge->	Ini_SetInt(RESCONFIGS_KEYSETTING_2, RESCONFIGN_KEYENTER, KS_ENTER_(1));
	hge->	Ini_SetInt(RESCONFIGS_KEYSETTING_2, RESCONFIGN_KEYESCAPE, KS_ESCAPE_(1));
	hge->	Ini_SetInt(RESCONFIGS_KEYSETTING_2, RESCONFIGN_KEYCAPTURE, KS_CAPTURE_(1));

	hge->	Ini_SetInt(RESCONFIGS_KEYSETTING_2, RESCONFIGN_JOYSHOOT, JS_SHOOT_(1));
	hge->	Ini_SetInt(RESCONFIGS_KEYSETTING_2, RESCONFIGN_JOYJUMP, JS_JUMP_(1));
	hge->	Ini_SetInt(RESCONFIGS_KEYSETTING_2, RESCONFIGN_JOYSUICIDE, JS_SUICIDE_(1));
	hge->	Ini_SetInt(RESCONFIGS_KEYSETTING_2, RESCONFIGN_JOYSPECIAL, JS_SPECIAL_(1));
	hge->	Ini_SetInt(RESCONFIGS_KEYSETTING_2, RESCONFIGN_JOYPAUSE, JS_PAUSE_(1));
	hge->	Ini_SetInt(RESCONFIGS_KEYSETTING_2, RESCONFIGN_JOYRETRY, JS_RETRY_(1));

#ifdef __DEBUG
	hge->	Ini_SetInt(RESCONFIGS_KEYSETTING_1, RESCONFIGN_DEBUG_JOYSPEEDUP, JS_DEBUG_SPEEDUP_(0));
	hge->	Ini_SetInt(RESCONFIGS_KEYSETTING_2, RESCONFIGN_DEBUG_JOYSPEEDUP, JS_DEBUG_SPEEDUP_(1));
#endif
	return true;
}

bool GameInput::UpdateInput(bool startstate)
{
	if (!hge)
	{
		return false;
	}
	for (int j=0; j<M_PL_MATCHMAXPLAYER; j++)
	{
		gameinput[j].lastInput = gameinput[j].input;
		gameinput[j].input = 0;
	}
	for (int j=0; j<M_PL_MATCHMAXPLAYER; j++)
	{
		for (int i=0; i<GAMEINPUTKEYMAX; i++)
		{
			gameinput[j].input |= (hge->Input_GetDIKey(gameinput[j].keyKey[i])?1:0)<<i;
		}
		if (hge->Input_GetDIJoy(JOY_UP, DIKEY_PRESSED, j))
		{
			gameinput[j].input |= 1<<KSI_UP;
		}
		if (hge->Input_GetDIJoy(JOY_DOWN, DIKEY_PRESSED, j))
		{
			gameinput[j].input |= 1<<KSI_DOWN;
		}
		if (hge->Input_GetDIJoy(JOY_LEFT, DIKEY_PRESSED, j))
		{
			gameinput[j].input |= 1<<KSI_LEFT;
		}
		if (hge->Input_GetDIJoy(JOY_RIGHT, DIKEY_PRESSED, j))
		{
			gameinput[j].input |= 1<<KSI_RIGHT;
		}
		if (hge->Input_GetDIJoy(JS_SHOOT_(j), DIKEY_PRESSED, j))
		{
			gameinput[j].input |= 1<<KSI_SHOOT;
		}
		if (hge->Input_GetDIJoy(JS_JUMP_(j), DIKEY_PRESSED, j))
		{
			gameinput[j].input |= 1<<KSI_JUMP;
		}
		if (hge->Input_GetDIJoy(JS_SUICIDE_(j), DIKEY_PRESSED, j))
		{
			gameinput[j].input |= 1<<KSI_SUICIDE;
		}
		if (hge->Input_GetDIJoy(JS_SPECIAL_(j), DIKEY_PRESSED, j))
		{
			gameinput[j].input |= 1<<KSI_SPECIAL;
		}
		if (hge->Input_GetDIJoy(JS_PAUSE_(j), DIKEY_PRESSED, j))
		{
			gameinput[j].input |= 1<<KSI_PAUSE;
		}
		if (hge->Input_GetDIJoy(JS_RETRY_(j), DIKEY_PRESSED, j))
		{
			gameinput[j].input |= 1<<KSI_RETRY;
		}
		if (hge->Input_GetDIJoy(JS_DEBUG_SPEEDUP_(j), DIKEY_PRESSED, j))
		{
			gameinput[j].input |= 1<<KSI_SKIP;
		}
#ifdef __PSP
		break;
#endif // __PSP
	}

	//
	SyncControlInputSelf();
	//

	return true;
}

void GameInput::SyncControlInputSelf()
{
	if (GetKey(0, KSI_PAUSE) || GetKey(1, KSI_PAUSE))
	{
		SetKey(0, KSI_PAUSE);
		SetKey(1, KSI_PAUSE);
	}
	if (GetKey(0, KSI_SKIP) || GetKey(1, KSI_SKIP))
	{
		SetKey(0, KSI_SKIP);
		SetKey(1, KSI_SKIP);
	}
	if (GetKey(0, KSI_RETRY) || GetKey(1, KSI_RETRY))
	{
		SetKey(0, KSI_RETRY);
		SetKey(1, KSI_RETRY);
	}
	if (GetKey(0, KSI_ENTER) || GetKey(1, KSI_ENTER))
	{
		SetKey(0, KSI_ENTER);
		SetKey(1, KSI_ENTER);
	}
	if (GetKey(0, KSI_ESCAPE) || GetKey(1, KSI_ESCAPE))
	{
		SetKey(0, KSI_ESCAPE);
		SetKey(1, KSI_ESCAPE);
	}
	if (GetKey(0, KSI_CAPTURE) || GetKey(1, KSI_CAPTURE))
	{
		SetKey(0, KSI_CAPTURE);
		SetKey(1, KSI_CAPTURE);
	}
}

void GameInput::SyncControlInput()
{
	if (hge)
	{
		if (hge->Input_GetDIKey(KS_PAUSE_(0)) || hge->Input_GetDIKey(KS_PAUSE_(1)) || hge->Input_GetDIJoy(JS_PAUSE_(0), DIKEY_PRESSED, 0) || hge->Input_GetDIJoy(JS_PAUSE_(1), DIKEY_PRESSED, 1))
		{
			hge->Input_SetDIKey(KS_PAUSE_(0));
			hge->Input_SetDIKey(KS_PAUSE_(1));
		}
		if (hge->Input_GetDIKey(KS_SKIP_(0)) || hge->Input_GetDIKey(KS_SKIP_(1)) || hge->Input_GetDIJoy(JS_DEBUG_SPEEDUP_(0), DIKEY_PRESSED, 0) || hge->Input_GetDIJoy(JS_DEBUG_SPEEDUP_(1), DIKEY_PRESSED, 1))
		{
			hge->Input_SetDIKey(KS_SKIP_(0));
			hge->Input_SetDIKey(KS_SKIP_(1));
		}
		if (hge->Input_GetDIKey(KS_RETRY_(0)) || hge->Input_GetDIKey(KS_RETRY_(1)) || hge->Input_GetDIJoy(JS_RETRY_(0), DIKEY_PRESSED, 0) || hge->Input_GetDIJoy(JS_RETRY_(1), DIKEY_PRESSED, 1))
		{
			hge->Input_SetDIKey(KS_RETRY_(0));
			hge->Input_SetDIKey(KS_RETRY_(1));
		}
		if (hge->Input_GetDIKey(KS_ENTER_(0)) || hge->Input_GetDIKey(KS_ENTER_(1)))
		{
			hge->Input_SetDIKey(KS_ENTER_(0));
			hge->Input_SetDIKey(KS_ENTER_(1));
		}
		if (hge->Input_GetDIKey(KS_ESCAPE_(0)) || hge->Input_GetDIKey(KS_ESCAPE_(1)))
		{
			hge->Input_SetDIKey(KS_ESCAPE_(0));
			hge->Input_SetDIKey(KS_ESCAPE_(1));
		}
		if (hge->Input_GetDIKey(KS_CAPTURE_(0)) || hge->Input_GetDIKey(KS_CAPTURE_(1)))
		{
			hge->Input_SetDIKey(KS_CAPTURE_(0));
			hge->Input_SetDIKey(KS_CAPTURE_(1));
		}
	}
}

void GameInput::SyncForActiveInput()
{
	for (int i=0; i<GAMEACTIVEINPUTMAX; i++)
	{
		WORD testi = 1<<i;
		if (gameinput[0].input & testi || gameinput[1].input & testi)
		{
			gameinput[0].input |= testi;
			gameinput[1].input |= testi;
		}
	}
}

void GameInput::SwapInput(bool setswap)
{
	swapinput = setswap;
}

WORD GameInput::updateActiveInput(bool copylast/* =false */)
{
	if (copylast)
	{
		activeInput = lastActiveInput;
		for (int i=0; i<GAMEACTIVEINPUTMAX; i++)
		{
			BYTE seti = 1<<i;
			input &= ~seti;
			input |= activeInput & seti;
		}
	}
	else
	{
		lastActiveInput = activeInput;
		activeInput = 0;
		for (int i=0; i<GAMEACTIVEINPUTMAX; i++)
		{
			activeInput |= (input&(1<<i));
		}
	}
	return activeInput;
}

bool GameInput::GetKey(BYTE playerindex, int ksi, int type/* =DIKEY_PRESSED */)
{
	if (playerindex != 1)
	{
		playerindex = 0;
	}
	if (swapinput)
	{
		playerindex = 1-playerindex;
	}
	return gameinput[playerindex].getKey(ksi, type);
}

void GameInput::SetKey(BYTE playerindex, int ksi, bool set/* =true */)
{
	if (playerindex != 1)
	{
		playerindex = 0;
	}
	if (swapinput)
	{
		playerindex = 1-playerindex;
	}
	gameinput[playerindex].setKey(ksi, set);
}

bool GameInput::getKey(int ksi, int type/* =DIKEY_PRESSED */)
{
	bool bnow = input & (1<<ksi);
	bool blast = lastInput & (1<<ksi);
	switch (type)
	{
	case DIKEY_DOWN:
		if (bnow && !blast)
		{
			return true;
		}
		break;
	case DIKEY_UP:
		if (!bnow && blast)
		{
			return true;
		}
		break;
	default:
		if (bnow)
		{
			return true;
		}
		break;
	}
	return false;
}

void GameInput::setKey(int ksi, bool set/* =true */)
{
	if (set)
	{
		input |= 1<<ksi;
	}
	else
	{
		input &= ~(1<<ksi);
	}
}

WORD GameInput::GetNowInput()
{
	WORD wret = 0;
	for (int j=0; j<M_PL_MATCHMAXPLAYER; j++)
	{
		for (int i=0; i<GAMEACTIVEINPUTMAX; i++)
		{
			wret |= (GetKey(j, i)<<i)<<(j*8);
		}
	}
	return wret;
}

void GameInput::SetNowInput(WORD nowinput)
{
	WORD seti = 0;
	for (int j=0; j<M_PL_MATCHMAXPLAYER; j++)
	{
		int usingindex = j;
		if (swapinput)
		{
			usingindex = 1-j;
		}
		for (int i=0; i<GAMEACTIVEINPUTMAX; i++)
		{
			seti = ((1<<i)<<(usingindex*8));
			gameinput[j].input &= ~seti;
			gameinput[j].input |= (nowinput & seti)>>(usingindex*8);
		}
	}
}