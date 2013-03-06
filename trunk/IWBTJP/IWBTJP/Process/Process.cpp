#include "../Header/Process.h"
#include "../Header/Export.h"
#include "../Header/GameInput.h"
#include "../Header/ConstResource.h"

Process::Process()
{
}

Process::~Process()
{
}

void Process::Init()
{
	state = STATE_INIT;
	gametime = 0;
	lasttime = 0;
	GameInput::InitInput(hge);
}

void Process::Release()
{
	GameInput::ReleaseInput();
}

int Process::frame()
{
	if(hge->Input_GetKeyState(HGEK_ALT) && hge->Input_GetKeyState(HGEK_ENTER)) 
	{
		bool bWindowed = hge->System_GetState(HGE_WINDOWED);
		hge->System_SetState(HGE_WINDOWED, !bWindowed);
		hge->System_SetState(HGE_HIDEMOUSE, !bWindowed);
		Export::clientAdjustWindow();
		return PSKIP;
	}
#ifdef __DEBUG
	if(hge->Input_GetKeyState(HGEK_BACKSPACE))
	{
//		Scripter::scr.LoadAll();
		state = STATE_TITLE;
		gametime = 0;
		return PTURN;
	}
#endif

	int frameskip = M_DEFAULT_FRAMESKIP;
	if (GameInput::GetKey(0, KSI_SKIP))
	{
		frameskip = M_FRAMESKIP_FASTSKIP;
	}
	else if(frameskip < M_DEFAULT_FRAMESKIP)
	{
		frameskip = M_DEFAULT_FRAMESKIP;
	}
	hge->System_SetState(HGE_FRAMESKIP, frameskip);


	getInput();
	lasttime = gametime;

	int rv = 0xffffffff;
	switch(state)
	{

	case STATE_START:
		rv = processStart();
		break;
	case STATE_DEAD:
		rv = processDead();
		break;
	case STATE_TITLE:
		rv = processTitle();
		break;
	case STATE_INIT:
		rv = processInit();
		break;
	}

	if(rv == 0xffffffff)
	{
		gametime = 0;
		state = STATE_TITLE;
		rv = PTURN;
	}

	if (rv == PTURN)
	{
		return PTURN;
	}

	if(rv == PQUIT)
		return PQUIT;

	frameEnd();

	return PGO;
}

int Process::processTitle()
{
	return PGO;
}

int Process::processStart()
{
	return PGO;
}

int Process::processDead()
{
	return PGO;
}


int Process::processInit()
{
	return PGO;
}

bool Process::reload()
{
	//TODO
	return true;
}

int Process::getInput()
{
	GameInput::UpdateInput(state==STATE_START);
	if (state != STATE_START)
	{
		GameInput::SyncForActiveInput();
	}
	return PGO;
}

char Process::getInputNowChar( bool wide )
{
	char nowchar = -1;
	if(hge->Input_GetDIKey(GameInput::KS_FIRE) && hge->Input_GetDIJoy(GameInput::JS_FIRE))
	{
		hge->Input_SetDIKey(GameInput::KS_FIRE, false);
	}
	if(hge->Input_GetDIKey(GameInput::KS_JUMP) && hge->Input_GetDIJoy(GameInput::JS_JUMP))
	{
		hge->Input_SetDIKey(GameInput::KS_JUMP, false);
	}
	if(hge->Input_GetDIKey(GameInput::KS_SUICIDE) && hge->Input_GetDIJoy(GameInput::KS_SUICIDE))
	{
		hge->Input_SetDIKey(GameInput::KS_SUICIDE, false);
	}
	if(hge->Input_GetDIKey(GameInput::KS_SPECIAL) && hge->Input_GetDIJoy(GameInput::KS_SPECIAL))
	{
		hge->Input_SetDIKey(GameInput::KS_SPECIAL, false);
	}
	if(hge->Input_GetDIKey(GameInput::KS_PAUSE) && hge->Input_GetDIJoy(GameInput::JS_PAUSE))
	{
		hge->Input_SetDIKey(GameInput::KS_PAUSE, false);
	}
#ifdef __DEBUG
	if(hge->Input_GetDIKey(GameInput::KS_SKIP) && hge->Input_GetDIJoy(GameInput::JS_DEBUG_SPEEDUP))
	{
		hge->Input_SetDIKey(GameInput::KS_SKIP, false);
	}
#endif

	if(hge->Input_GetDIKey(GameInput::KS_RETRY) && hge->Input_GetDIJoy(GameInput::KS_RETRY))
	{
		hge->Input_SetDIKey(GameInput::KS_RETRY, false);
	}

	if(hge->Input_GetDIKey(DIK_1, DIKEY_DOWN) || hge->Input_GetDIKey(DIK_NUMPAD1, DIKEY_DOWN))
	{
		nowchar = '1';
	}
	else if(hge->Input_GetDIKey(DIK_2, DIKEY_DOWN) || hge->Input_GetDIKey(DIK_NUMPAD2, DIKEY_DOWN))
	{
		nowchar = '2';
	}
	else if(hge->Input_GetDIKey(DIK_3, DIKEY_DOWN) || hge->Input_GetDIKey(DIK_NUMPAD3, DIKEY_DOWN))
	{
		nowchar = '3';
	}
	else if(hge->Input_GetDIKey(DIK_4, DIKEY_DOWN) || hge->Input_GetDIKey(DIK_NUMPAD4, DIKEY_DOWN))
	{
		nowchar = '4';
	}
	else if(hge->Input_GetDIKey(DIK_5, DIKEY_DOWN) || hge->Input_GetDIKey(DIK_NUMPAD5, DIKEY_DOWN))
	{
		nowchar = '5';
	}
	else if(hge->Input_GetDIKey(DIK_6, DIKEY_DOWN) || hge->Input_GetDIKey(DIK_NUMPAD6, DIKEY_DOWN))
	{
		nowchar = '6';
	}
	else if(hge->Input_GetDIKey(DIK_7, DIKEY_DOWN) || hge->Input_GetDIKey(DIK_NUMPAD7, DIKEY_DOWN))
	{
		nowchar = '7';
	}
	else if(hge->Input_GetDIKey(DIK_8, DIKEY_DOWN) || hge->Input_GetDIKey(DIK_NUMPAD8, DIKEY_DOWN))
	{
		nowchar = '8';
	}
	else if(hge->Input_GetDIKey(DIK_9, DIKEY_DOWN) || hge->Input_GetDIKey(DIK_NUMPAD9, DIKEY_DOWN))
	{
		nowchar = '9';
	}
	else if(hge->Input_GetDIKey(DIK_0, DIKEY_DOWN) || hge->Input_GetDIKey(DIK_NUMPAD0, DIKEY_DOWN))
	{
		nowchar = '0';
	}
	else if(hge->Input_GetDIKey(DIK_Q, DIKEY_DOWN))
	{
		nowchar = 'q';
	}
	else if(hge->Input_GetDIKey(DIK_W, DIKEY_DOWN))
	{
		nowchar = 'w';
	}
	else if(hge->Input_GetDIKey(DIK_E, DIKEY_DOWN))
	{
		nowchar = 'e';
	}
	else if(hge->Input_GetDIKey(DIK_R, DIKEY_DOWN))
	{
		nowchar = 'r';
	}
	else if(hge->Input_GetDIKey(DIK_T, DIKEY_DOWN))
	{
		nowchar = 't';
	}
	else if(hge->Input_GetDIKey(DIK_Y, DIKEY_DOWN))
	{
		nowchar = 'y';
	}
	else if(hge->Input_GetDIKey(DIK_U, DIKEY_DOWN))
	{
		nowchar = 'u';
	}
	else if(hge->Input_GetDIKey(DIK_I, DIKEY_DOWN))
	{
		nowchar = 'i';
	}
	else if(hge->Input_GetDIKey(DIK_O, DIKEY_DOWN))
	{
		nowchar = 'o';
	}
	else if(hge->Input_GetDIKey(DIK_P, DIKEY_DOWN))
	{
		nowchar = 'p';
	}
	else if(hge->Input_GetDIKey(DIK_A, DIKEY_DOWN))
	{
		nowchar = 'a';
	}
	else if(hge->Input_GetDIKey(DIK_S, DIKEY_DOWN))
	{
		nowchar = 's';
	}
	else if(hge->Input_GetDIKey(DIK_D, DIKEY_DOWN))
	{
		nowchar = 'd';
	}
	else if(hge->Input_GetDIKey(DIK_F, DIKEY_DOWN))
	{
		nowchar = 'f';
	}
	else if(hge->Input_GetDIKey(DIK_G, DIKEY_DOWN))
	{
		nowchar = 'g';
	}
	else if(hge->Input_GetDIKey(DIK_H, DIKEY_DOWN))
	{
		nowchar = 'h';
	}
	else if(hge->Input_GetDIKey(DIK_J, DIKEY_DOWN))
	{
		nowchar = 'j';
	}
	else if(hge->Input_GetDIKey(DIK_K, DIKEY_DOWN))
	{
		nowchar = 'k';
	}
	else if(hge->Input_GetDIKey(DIK_L, DIKEY_DOWN))
	{
		nowchar = 'l';
	}
	else if(hge->Input_GetDIKey(DIK_Z, DIKEY_DOWN))
	{
		nowchar = 'z';
	}
	else if(hge->Input_GetDIKey(DIK_X, DIKEY_DOWN))
	{
		nowchar = 'x';
	}
	else if(hge->Input_GetDIKey(DIK_C, DIKEY_DOWN))
	{
		nowchar = 'c';
	}
	else if(hge->Input_GetDIKey(DIK_V, DIKEY_DOWN))
	{
		nowchar = 'v';
	}
	else if(hge->Input_GetDIKey(DIK_B, DIKEY_DOWN))
	{
		nowchar = 'b';
	}
	else if(hge->Input_GetDIKey(DIK_N, DIKEY_DOWN))
	{
		nowchar = 'n';
	}
	else if(hge->Input_GetDIKey(DIK_M, DIKEY_DOWN))
	{
		nowchar = 'm';
	}
	else if(hge->Input_GetDIKey(DIK_MINUS, DIKEY_DOWN))
	{
		nowchar = '-';
	}

	if(wide)
	{
		if(hge->Input_GetDIKey(DIK_EQUALS, DIKEY_DOWN))
		{
			nowchar = '=';
		}
		else if(hge->Input_GetDIKey(DIK_LBRACKET, DIKEY_DOWN))
		{
			nowchar = '[';
		}
		else if(hge->Input_GetDIKey(DIK_RBRACKET, DIKEY_DOWN))
		{
			nowchar = ']';
		}
		else if(hge->Input_GetDIKey(DIK_SEMICOLON, DIKEY_DOWN))
		{
			nowchar = ';';
		}
		else if(hge->Input_GetDIKey(DIK_APOSTROPHE, DIKEY_DOWN))
		{
			nowchar = '\'';
		}
		else if(hge->Input_GetDIKey(DIK_GRAVE, DIKEY_DOWN))
		{
			nowchar = '`';
		}
		else if(hge->Input_GetDIKey(DIK_BACKSLASH, DIKEY_DOWN))
		{
			nowchar = '\\';
		}
		else if(hge->Input_GetDIKey(DIK_COMMA, DIKEY_DOWN))
		{
			nowchar = ',';
		}
		else if(hge->Input_GetDIKey(DIK_PERIOD, DIKEY_DOWN))
		{
			nowchar = '.';
		}
		else if(hge->Input_GetDIKey(DIK_SLASH, DIKEY_DOWN))
		{
			nowchar = '/';
		}
		else if(hge->Input_GetDIKey(DIK_SPACE, DIKEY_DOWN))
		{
			nowchar = ' ';
		}

		else if(hge->Input_GetDIKey(DIK_ADD, DIKEY_DOWN))
		{
			nowchar = '+';
		}
		else if(hge->Input_GetDIKey(DIK_SUBTRACT, DIKEY_DOWN))
		{
			nowchar = '-';
		}
		else if(hge->Input_GetDIKey(DIK_MULTIPLY, DIKEY_DOWN))
		{
			nowchar = '*';
		}
		else if(hge->Input_GetDIKey(DIK_DIVIDE, DIKEY_DOWN))
		{
			nowchar = '/';
		}
		else if(hge->Input_GetDIKey(DIK_DECIMAL, DIKEY_DOWN))
		{
			nowchar = '.';
		}
	}
	if(hge->Input_GetDIKey(DIK_LSHIFT) || hge->Input_GetDIKey(DIK_RSHIFT))
	{
		if(nowchar >= 'a' && nowchar <= 'z')
		{
			nowchar += 'A' - 'a';
		}
		else if(hge->Input_GetDIKey(DIK_MINUS, DIKEY_DOWN))
		{
			nowchar = '_';
		}

		if(wide)
		{
			if(nowchar == '1')
			{
				nowchar = '!';
			}
			else if(nowchar == '2')
			{
				nowchar = '@';
			}
			else if(nowchar == '3')
			{
				nowchar = '#';
			}
			else if(nowchar == '4')
			{
				nowchar = '$';
			}
			else if(nowchar == '5')
			{
				nowchar = '%';
			}
			else if(nowchar == '6')
			{
				nowchar = '^';
			}
			else if(nowchar == '7')
			{
				nowchar = '&';
			}
			else if(nowchar == '8')
			{
				nowchar = '*';
			}
			else if(nowchar == '9')
			{
				nowchar = '(';
			}
			else if(nowchar == '0')
			{
				nowchar = ')';
			}
			else if(nowchar == '=')
			{
				nowchar = '+';
			}
			else if(nowchar == '[')
			{
				nowchar = '{';
			}
			else if(nowchar == ']')
			{
				nowchar = '}';
			}
			else if(nowchar == ';')
			{
				nowchar = ':';
			}
			else if(nowchar == '\'')
			{
				nowchar = '\"';
			}
			else if(nowchar == '`')
			{
				nowchar = '~';
			}
			else if(nowchar == '\\')
			{
				nowchar = '|';
			}
			else if(nowchar == ',')
			{
				nowchar = '<';
			}
			else if(nowchar == '.')
			{
				nowchar = '>';
			}
			else if(nowchar == '/')
			{
				nowchar = '?';
			}
		}
	}
	return nowchar;

}

void Process::frameStart()
{
	gametime++;
	WORD nowInput = GameInput::GetNowInput();
}

void Process::frameEnd()
{
	//Action
}

void Process::_Render(BYTE renderflag/* =M_RENDER_NULL */)
{
	//Render
}

void Process::_RenderTar()
{
}

int Process::render()
{
	hge->Gfx_BeginScene();
	hge->Gfx_Clear(0x00000000);

	if (state == STATE_INIT)
	{
		int ret = renderInit();
		hge->Gfx_EndScene();
		return ret;
	}
	//BGLayer

	_Render();
	
	hge->Gfx_EndScene();
	return PGO;
}

int Process::renderInit()
{
	/*
	if (texInit.tex)
	{
		hgeQuad quad;
		quad.blend = BLEND_DEFAULT;
		quad.tex = texInit;
		quad.v[0].col = quad.v[1].col = quad.v[2].col = quad.v[3].col = 0xffffffff;
		quad.v[0].tx = 0;	quad.v[0].ty = 0;
		quad.v[1].tx = 1;	quad.v[1].ty = 0;
		quad.v[2].tx = 1;	quad.v[2].ty = 1;
		quad.v[3].tx = 0;	quad.v[3].ty = 1;
		quad.v[0].x = M_CLIENT_LEFT;	quad.v[0].y = M_CLIENT_TOP;	quad.v[0].z = 0;
		quad.v[1].x = M_CLIENT_RIGHT;	quad.v[1].y = M_CLIENT_TOP;	quad.v[1].z = 0;
		quad.v[2].x = M_CLIENT_RIGHT;	quad.v[2].y = M_CLIENT_BOTTOM;	quad.v[2].z = 0;
		quad.v[3].x = M_CLIENT_LEFT;	quad.v[3].y = M_CLIENT_BOTTOM;	quad.v[3].z = 0;
		SpriteItemManager::RenderQuad(&quad);
	}
	*/
	return PGO;
}
bool Process::SyncInputAndCheckEscSnap()
{
	GameInput::SyncControlInput();
	if (GameInput::GetKey(0, KSI_CAPTURE, DIKEY_DOWN))
	{
		SnapShot();
	}
	return GameInput::GetKey(0, KSI_ESCAPE);
}

void Process::SnapShot()
{
	WORD wYear, wMonth, wDay, wHour, wMinute, wSecond, wMilliseconds;
	hge->Timer_GetSystemTime(&wYear, &wMonth, NULL, &wDay, &wHour, &wMinute, &wSecond, &wMilliseconds);

	char snapshotfilename[M_PATHMAX];
	strcpy(snapshotfilename, "");
	sprintf(snapshotfilename, "%s%s_%04d_%02d_%02d_%02d_%02d_%02d_%04d.%s",
		hge->Resource_MakePath(SNAPSHOT_FOLDER),
		SNAPSHOT_PRIFIX,
		wYear, wMonth, wDay, wHour, wMinute, wSecond, wMilliseconds,
		SNAPSHOT_EXTENSION);
	hge->System_Snapshot(snapshotfilename);
}
