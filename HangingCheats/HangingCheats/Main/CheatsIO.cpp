#include "../Header/CheatsIO.h"
#include "../Header/Main.h"

CheatsIO CheatsIO::cheatsio;

#define WORDSFILENAME	"words.txt"
#define FONTFILENAME	"font.fnt"

CheatsIO::BuilderWord::BuilderWord()
{
	ZeroMemory(&word, sizeof(length16));
	ZeroMemory(step, sizeof(char)*MAXSCRAMBLELETTER);
	score = 0;
}


CheatsIO::BuilderWord::~BuilderWord()
{

}

CheatsIO::TouchButton::TouchButton()
{
	ZeroMemory(&rect, sizeof(RenderPos));
}

CheatsIO::TouchButton::~TouchButton()
{

}

CheatsIO::TouchButton * CheatsIO::TouchButton::binding[TOUCH_TOUCHMAX];

void CheatsIO::FillRenderPos()
{
	float xbegin = 0;
	float ybegin = 0;
	float xoffset = 0;
	float yoffset = 0;

	float aztz = M_CLIENT_WIDTH/13;
	ybegin = M_CLIENT_HEIGHT/4;
	for (int i=0; i<27; i++)
	{
		tbl.az[i].rect.x = (i%10+2) * aztz;
		tbl.az[i].rect.y = (i/10) * aztz + ybegin;
		tbl.az[i].rect.w = tbl.az[i].rect.h = aztz;
	}

	for (int i=0; i<4; i++)
	{
		tbl.mul[i].rect.x = (i+2) * (aztz+30);
		tbl.mul[i].rect.y = ybegin + 3 * aztz + 10;
		tbl.mul[i].rect.w = aztz + 30;
		tbl.mul[i].rect.h = aztz+10;
	}

	xoffset = aztz * 1.2f;
	xbegin = aztz*2.5f;
	ybegin = M_CLIENT_HEIGHT / 10;
	for (int i=0; i<8; i++)
	{
		tbl.l8[i].rect.x = xbegin + i*xoffset;
		tbl.l8[i].rect.y = ybegin;
		tbl.l8[i].rect.w = tbl.l8[i].rect.h = xoffset;

		tbl.ll8[i].rect.x = (i+2)*xoffset;
		tbl.ll8[i].rect.y = M_CLIENT_HEIGHT * 3 / 4 + 8;
		tbl.ll8[i].rect.w = tbl.ll8[i].rect.h = xoffset;
	}

	tbl.guess.rect.x = 20;
	tbl.guess.rect.y = M_CLIENT_HEIGHT / 2 + 30;

	tbl.results.rect.x = 40;
	tbl.results.rect.y = M_CLIENT_HEIGHT / 2 + 60;
	tbl.results.rect.h = 20;

	for (int i=0; i<2; i++)
	{
		tbl.bline[i].rect.x = M_CLIENT_WIDTH / 3;
		tbl.bline[i].rect.y = i * 32 + 2;
	}

	for (int i=0; i<4; i++)
	{
		tbl.sline[i].rect.x = M_CLIENT_WIDTH / 3;
		tbl.sline[i].rect.y = i * 17 + 2;

		for (int j=0; j<4; j++)
		{
			tbl.sdir[i*4+j].rect.x = M_CLIENT_WIDTH/2 + j*17;
			tbl.sdir[i*4+j].rect.y = i*17 + 2;
			tbl.sdir[i*4+j].rect.w = tbl.sdir[i*4+j].rect.h = 24;
		}

	}
	for (int i=0; i<RESULTLISTROWB; i++)
	{
		for(int j=0; j<RESULTLISTCOLB; j++)
		{
			tbl.sresults[i*4+j].rect.x = 10+tbl.results.rect.h*6*(j+0.5f);
			tbl.sresults[i*4+j].rect.y = M_CLIENT_HEIGHT/4 + i*tbl.results.rect.h;
			tbl.sresults[i*4+j].rect.w = tbl.results.rect.h*6;
			tbl.sresults[i*4+j].rect.h = tbl.results.rect.h;
		}
	}

	tbl.bresults.rect.x = 10;
	tbl.bresults.rect.y = M_CLIENT_HEIGHT / 4;
	tbl.bresults.rect.h = tbl.results.rect.h;

	// Button
	tbl.changemode.rect.x = 35;
	tbl.changemode.rect.y = 20;
	tbl.changemode.rect.w = 60;
	tbl.changemode.rect.h = 40;

	tbl.clear.rect.x = M_CLIENT_WIDTH - 35;
	tbl.clear.rect.y = 5;
	tbl.clear.rect.w = 60;
	tbl.clear.rect.h = 38;

	tbl.backspace.rect.x = M_CLIENT_WIDTH - 35;
	tbl.backspace.rect.y = 44;
	tbl.backspace.rect.w = 60;
	tbl.backspace.rect.h = 38;

	tbl.enter.rect.x = M_CLIENT_WIDTH - 35;
	tbl.enter.rect.y = 84;
	tbl.enter.rect.w = 45;
	tbl.enter.rect.h = 38;

	tbl.pageup.rect.x = M_CLIENT_WIDTH - 100;
	tbl.pageup.rect.y = 5;
	tbl.pageup.rect.w = 60;
	tbl.pageup.rect.h = 38;

	tbl.pagedown.rect.x = M_CLIENT_WIDTH - 100;
	tbl.pagedown.rect.y = 44;
	tbl.pagedown.rect.w = 60;
	tbl.pagedown.rect.h = 38;

}

struct DIKConvert
{
	unsigned char dik;
	char ch;
};

#define CH_BACK	0x08

const DIKConvert dikconvert[] = 
{
	{	DIK_1	,	'1'	},
	{	DIK_2	,	'2'	},
	{	DIK_3	,	'3'	},
	{	DIK_4	,	'4'	},
	{	DIK_5	,	'5'	},
	{	DIK_6	,	'6'	},
	{	DIK_7	,	'7'	},
	{	DIK_8	,	'8'	},
	{	DIK_9	,	'9'	},
	{	DIK_0	,	'0'	},
	{	DIK_MINUS	,	'-'	},
	{	DIK_EQUALS	,	'='	},
	{	DIK_Q	,	'q'	},
	{	DIK_W	,	'w'	},
	{	DIK_E	,	'e'	},
	{	DIK_R	,	'r'	},
	{	DIK_T	,	't'	},
	{	DIK_Y	,	'y'	},
	{	DIK_U	,	'u'	},
	{	DIK_I	,	'i'	},
	{	DIK_O	,	'o'	},
	{	DIK_P	,	'p'	},
	{	DIK_LBRACKET	,	'['	},
	{	DIK_RBRACKET	,	']'	},
	{	DIK_A	,	'a'	},
	{	DIK_S	,	's'	},
	{	DIK_D	,	'd'	},
	{	DIK_F	,	'f'	},
	{	DIK_G	,	'g'	},
	{	DIK_H	,	'h'	},
	{	DIK_J	,	'j'	},
	{	DIK_K	,	'k'	},
	{	DIK_L	,	'l'	},
	{	DIK_SEMICOLON	,	';'	},
	{	DIK_APOSTROPHE	,	'\''	},
	{	DIK_GRAVE	,	'`'	},
	{	DIK_BACKSLASH	,	'\\'	},
	{	DIK_Z	,	'z'	},
	{	DIK_X	,	'x'	},
	{	DIK_C	,	'c'	},
	{	DIK_V	,	'v'	},
	{	DIK_B	,	'b'	},
	{	DIK_N	,	'n'	},
	{	DIK_M	,	'm'	},
	{	DIK_COMMA	,	','	},
	{	DIK_PERIOD	,	'.'	},
	{	DIK_SLASH	,	'/'	},
	{	DIK_MULTIPLY	,	'*'	},
	{	DIK_SPACE	,	' '	},
	{	DIK_NUMPAD7	,	'7'	},
	{	DIK_NUMPAD8	,	'8'	},
	{	DIK_NUMPAD9	,	'9'	},
	{	DIK_SUBTRACT	,	'-'	},
	{	DIK_NUMPAD4	,	'4'	},
	{	DIK_NUMPAD5	,	'5'	},
	{	DIK_NUMPAD6	,	'6'	},
	{	DIK_ADD	,	'+'	},
	{	DIK_NUMPAD1	,	'1'	},
	{	DIK_NUMPAD2	,	'2'	},
	{	DIK_NUMPAD3	,	'3'	},
	{	DIK_NUMPAD0	,	'0'	},
	{	DIK_DECIMAL	,	'.'	},
	{	DIK_DIVIDE	,	'/'	},

	{	DIK_F2	,	'z'+1	},

	{	DIK_F5	,	MULST_DL	},
	{	DIK_F6	,	MULST_TL	},
	{	DIK_F7	,	MULST_DW	},
	{	DIK_F8	,	MULST_TW	},

	{	DIK_BACK,	CH_BACK	},

	{0xff, 0xff},
};

CheatsIO::CheatsIO()
{
	Release();
}

CheatsIO::~CheatsIO()
{
	Release();
}

void CheatsIO::Release()
{
	init = false;
	mode = GAMEMODE_HANGING;
	l4words.clear();
	l5words.clear();
	l6words.clear();
	l7words.clear();
	l8words.clear();

	if (font)
	{
		delete font;
	}
	font = NULL;

	strcpy(logstring, "");

	ZeroMemory(commandlist, sizeof(char)*MAXCOMMAND);

	logtimer = 0;
	ClearData();

	mousedown = false;

	ZeroMemory(TouchButton::binding, sizeof(TouchButton *)*TOUCH_TOUCHMAX);
}

void CheatsIO::AppendLog(const char * logstr)
{
	logtimer = 0x7f;
	strcpy(logstring, logstr);
}

void CheatsIO::ClearData()
{
	page = 0;
	nowpointingresult = 0;
	builderwords.clear();
	scramblewords.clear();
	ZeroMemory(builderletters, sizeof(char)*MAXBUILDERLETTER);
	ZeroMemory(scrambleletters, sizeof(char)*MAXSCRAMBLELETTER);

	ZeroMemory(mulstate, sizeof(char)*MAXSCRAMBLELETTER);

	wordlength = 0;
	striked.clear();
	ZeroMemory(&nowguess, sizeof(length16));
	ClearResult();
}

void CheatsIO::ClearResult()
{
	possiblech = 0;
	resultwords.clear();
	ZeroMemory(possiblecount, sizeof(int)*26);
	ZeroMemory(percentage, sizeof(float)*26);
}

bool CheatsIO::FrameFunc()
{
	if (!init)
	{
		if (!ReadWordsFile(WORDSFILENAME))
		{
			return true;
		}
		font = new hgeFont(FONTFILENAME);
		if (!font)
		{
			return true;
		}
		FillRenderPos();
		init = true;
	}
	UpdateInput();
	return GetInputCommand();
}

void CheatsIO::UpdateInput()
{
	if (hge->Input_KeyDown(HGEK_LBUTTON) || hge->Input_KeyDown(HGEK_RBUTTON))
	{
		mousedown = true;
	}
	else if (hge->Input_KeyUp(HGEK_LBUTTON) || hge->Input_KeyUp(HGEK_RBUTTON))
	{
		mousedown = false;
	}

	if (mousedown)
	{
		float x = 0;
		float y = 0;
		hge->Input_GetMousePos(&x, &y);
		hge->Input_SetTouchPos(0, x, y);
		char buffer[M_STRMAX];
		sprintf(buffer, "%.2f, %.2f", x, y);
		AppendLog(buffer);
	}
}

bool CheatsIO::TouchButton::IsInRect(float x, float y)
{
	return x >= rect.x-rect.w/2 && x < rect.x+rect.w/2 && y >= rect.y && y <= rect.y+rect.h;
}

bool CheatsIO::TouchToCommand(bool * force)
{
	if (!force)
	{
		return false;
	}
	for (int i=0; i<TOUCH_TOUCHMAX; i++)
	{
		float firstx=0;
		float firsty=0;
		float x = 0;
		float y = 0;
		int dur = 0;

#define TB_ON	1
#define TB_DOWN	2
#define TB_UP	4
#define TB_DUROVER	30

		char touchstate = 0;
		if (hge->Input_IsTouchOn(i))
		{
			touchstate |= TB_ON;
		}
		if (hge->Input_IsTouchDown(i))
		{
			touchstate |= TB_DOWN;
		}
		if (hge->Input_IsTouchUp(i))
		{
			touchstate |= TB_UP;
		}

		if (touchstate)
		{
			hge->Input_GetFirstTouchPos(i, &firstx, &firsty);
			hge->Input_GetTouchPos(i, &x, &y);
			dur = hge->Input_GetTouchDuration(i);

			if (touchstate & TB_DOWN)
			{
				if (!(mode == GAMEMODE_BUILDER && builderwords.size() || mode == GAMEMODE_SCRAMBLE && scramblewords.size()))
				{
					for (int j=0; j<27; j++)
					{
						if (i == 26 && mode != GAMEMODE_SCRAMBLE)
						{
							break;
						}
						if (tbl.az[j].IsInRect(x, y))
						{
							TouchButton::binding[i] = &(tbl.az[j]);
							return false;
						}
					}
					if (mode != GAMEMODE_HANGING)
					{
						for (int j=0; j<4; j++)
						{
							if (tbl.mul[j].IsInRect(x, y))
							{
								TouchButton::binding[i] = &(tbl.mul[j]);
								return false;
							}
						}
						if (mode == GAMEMODE_BUILDER)
						{
							for (int j=0; j<8; j++)
							{
								if (tbl.ll8[j].IsInRect(x, y))
								{
									TouchButton::binding[i] = &(tbl.ll8[j]);
									return false;
								}
							}
						}
					}
				}
				if (mode == GAMEMODE_HANGING)
				{
					int twordlength = wordlength ? wordlength : 8;
					for (int k=0; k<twordlength; k++)
					{
						if (tbl.l8[k].IsInRect(x, y))
						{
							TouchButton::binding[i] = &(tbl.l8[k]);
						}
					}
				}
				if (tbl.clear.IsInRect(x, y))
				{
					TouchButton::binding[i] = &(tbl.clear);
					return false;
				}
				if (tbl.changemode.IsInRect(x, y))
				{
					TouchButton::binding[i] = &(tbl.changemode);
					return false;
				}
				if ((mode == GAMEMODE_BUILDER || mode == GAMEMODE_SCRAMBLE) && tbl.backspace.IsInRect(x, y))
				{
					TouchButton::binding[i] = &(tbl.backspace);
					return false;
				}
				if (mode == GAMEMODE_BUILDER && builderwords.size() || mode == GAMEMODE_SCRAMBLE && scramblewords.size())
				{
					if (tbl.pageup.IsInRect(x, y))
					{
						TouchButton::binding[i] = &(tbl.pageup);
						return false;
					}
					if (tbl.pagedown.IsInRect(x, y))
					{
						TouchButton::binding[i] = &(tbl.pagedown);
						return false;
					}
					if (mode == GAMEMODE_SCRAMBLE)
					{
						for (int j=0; j<RESULTLISTROWB*RESULTLISTCOLB; j++)
						{
							if (tbl.sresults[j].IsInRect(x, y))
							{
								TouchButton::binding[i] = &(tbl.sresults[j]);
								return false;
							}
						}
					}
				}
				else
				{
					if (tbl.enter.IsInRect(x, y))
					{
						TouchButton::binding[i] = &(tbl.enter);
						return false;
					}
				}
			}

			else if (touchstate & TB_UP)
			{
				TouchButton * tbinding = TouchButton::binding[i];
				TouchButton::binding[i] = NULL;
				bool ret = false;
				bool found = false;
				// from letters
				int j=0;
				for (; j<27; j++)
				{
					if (tbinding == &(tbl.az[j]))
					{
						found = true;
						break;
					}
				}
				if (found)
				{
					if (mode == GAMEMODE_BUILDER || mode == GAMEMODE_SCRAMBLE)
					{
						if (tbinding->IsInRect(x, y))
						{
							commandlist[0] = 'a' + j;
							tbinding = NULL;
							return true;
						}
						return false;
					}
					else if (mode == GAMEMODE_HANGING)
					{
						if (dur <= TB_DUROVER && tbinding->IsInRect(x, y))
						{
							commandlist[0] = 'a' + j;
							return true;
						}
						else
						{
							for (int k=0; k<wordlength; k++)
							{
								if (tbl.l8[k].IsInRect(x, y))
								{
									commandlist[0] = k + '1';
									commandlist[1] = j + 'a';
									return true;
								}
							}
						}
						return false;
					}
					return false;
				}
				// from l8
				if (mode == GAMEMODE_HANGING)
				{
					int k=0;
					for (; k<8; k++)
					{
						if (tbinding == &(tbl.l8[k]))
						{
							found = true;
							break;
						}
					}
					if (found)
					{
						if (!wordlength)
						{
							if (k < 5)
							{
								commandlist[0] = '0';
								commandlist[1] = k + '4';
								return true;
							}
							return false;
						}
						for (int j=0; j<wordlength; j++)
						{
							if (j != k)
							{
								if (tbl.l8[j].IsInRect(x, y))
								{
									// swap
									commandlist[0] = k + '1';
									commandlist[1] = j + '1';
									return true;
								}
							}
						}
						commandlist[0] = k + '1';
						commandlist[1] = '0';
						return true;
					}
					// Drop

				}
				// from button
				if (tbinding == &(tbl.backspace) && mode == GAMEMODE_BUILDER)
				{
					commandlist[0] = CH_BACK;
					return true;
				}
				if (tbinding == &(tbl.changemode))
				{
					commandlist[0] = '9';
					return true;
				}
				if (tbinding == &(tbl.clear))
				{
					commandlist[0] = '0';
					commandlist[1] = '0';
					return true;
				}
				if (tbinding == &(tbl.enter))
				{
					*force = true;
					return true;
				}
				if (tbinding == &(tbl.pageup))
				{
					if (page > 0)
					{
						page--;
					}
					return false;
				}
				if (tbinding == &(tbl.pagedown))
				{
					if (page < 8)
					{
						page++;
					}
					return false;
				}

				// from results
				for (int j=0; j<RESULTLISTROWB*RESULTLISTCOLB; j++)
				{
					if (tbinding == &(tbl.sresults[j]))
					{
						nowpointingresult = j;
						return false;
					}
				}

				// from mul
				bool frommul = false;
				if (tbinding == &(tbl.mul[0]))
				{
					commandlist[0] = MULST_DL;
					frommul = true;
				}
				else if (tbinding == &(tbl.mul[1]))
				{
					commandlist[0] = MULST_TL;
					frommul = true;
				}
				else if (tbinding == &(tbl.mul[2]))
				{
					commandlist[0] = MULST_DW;
					frommul = true;
				}
				else if (tbinding == &(tbl.mul[3]))
				{
					commandlist[0] = MULST_TW;
					frommul = true;
				}

				if (frommul)
				{
					if (mode == GAMEMODE_SCRAMBLE)
					{
						return false;
					}
					if (mode == GAMEMODE_BUILDER)
					{
						for (int j=0; j<8; j++)
						{
							if (tbl.ll8[j].IsInRect(x, y))
							{
								commandlist[1] = j + '1';
								return false;
							}
						}
					}
					return false;
				}

				// from ll8
				for (int j=0; j<8; j++)
				{
					if (tbinding == &tbl.ll8[j])
					{
						commandlist[0] = '1' + j;
						for (int k=0; k<8; k++)
						{
							if (k == j)
							{
								continue;
							}
							if (tbl.ll8[k].IsInRect(x, y))
							{
								commandlist[1] = '1' + k;
								return false;
							}
						}
						commandlist[1] = '0';
						return false;
					}
				}
			}
		}

	}
	return false;
}

bool CheatsIO::GetInputCommand()
{
	if (hge->Input_GetDIKey(DIK_ESCAPE))
	{
		return true;
	}

	bool force = false;

	if (TouchToCommand(&force))
	{
		DispatchInput(force);
		return false;
	}

	// for PC
	if (mode == GAMEMODE_SCRAMBLE && scramblewords.size())
	{
		bool toret = false;
		if (hge->Input_GetDIKey(DIK_LEFT, DIKEY_DOWN))
		{
			nowpointingresult--;
			toret = true;
		}
		if (hge->Input_GetDIKey(DIK_RIGHT, DIKEY_DOWN))
		{
			nowpointingresult++;
			toret = true;
		}
		if (hge->Input_GetDIKey(DIK_UP, DIKEY_DOWN))
		{
			nowpointingresult -= RESULTLISTCOLB;
			toret = true;
		}
		if (hge->Input_GetDIKey(DIK_DOWN, DIKEY_DOWN))
		{
			nowpointingresult += RESULTLISTCOLB;
			toret = true;
		}

		if (toret)
		{
			if (nowpointingresult >= RESULTLISTROWB*RESULTLISTCOLB)
			{
				nowpointingresult = RESULTLISTROWB*RESULTLISTCOLB-1;
			}
			if (nowpointingresult < 0)
			{
				nowpointingresult = 0;
			}
			return false;
		}
	}
	char chcode = 0xff;
	for (int i=1; i<256; i++)
	{
		if (hge->Input_GetDIKey(i, DIKEY_DOWN))
		{
			if (i != DIK_RETURN && i != DIK_NUMPADENTER)
			{
				int k = 0;
				while (true)
				{
					if (dikconvert[k].dik == i)
					{
						chcode = dikconvert[k].ch;
						break;
					}
					++k;
					if (dikconvert[k].dik == 0xff)
					{
						break;
					}
				}

				for (int j=0; j<MAXCOMMAND; j++)
				{
					if (!commandlist[j])
					{
						commandlist[j] = chcode;
						break;
					}
				}
			}
		}
	}

	force = false;
	if (hge->Input_GetDIKey(DIK_RETURN, DIKEY_DOWN) || hge->Input_GetDIKey(DIK_NUMPADENTER, DIKEY_DOWN))
	{
		force = true;
	}
	DispatchInput(force);


	return false;
}

void CheatsIO::DoClear()
{
	ClearData();

	AppendLog("Cleared");
}

bool CheatsIO::DispatchInput(bool force)
{
	if (commandlist[0] == '0' && commandlist[1] == '0')
	{
		DoClear();
		DoUpdate();
		return true;
	}

	if (commandlist[0] == '9')
	{
		DoClear();
		if (mode == GAMEMODE_HANGING)
		{
			mode = GAMEMODE_BUILDER;
		}
		else if (mode == GAMEMODE_BUILDER)
		{
			mode = GAMEMODE_SCRAMBLE;
		}
		else
		{
			mode = GAMEMODE_HANGING;
		}
		DoUpdate();
		return true;
	}

	if (mode == GAMEMODE_BUILDER)
	{
		if (force)
		{
			DoUpdate(true);
			return true;
		}
		if (commandlist[0] == CH_BACK)
		{
			if (strlen(builderletters))
			{
				builderletters[strlen(builderletters)-1] = 0;
				builderwords.clear();
				page = 0;
				DoUpdate();
				return true;
			}
		}
		if (commandlist[0] >= 'a' && commandlist[0] <= 'z')
		{
			char buff[2];
			buff[0] = commandlist[0];
			buff[1] = 0;
			if (strlen(builderletters) < MAXBUILDERLETTER-1)
			{
				strcat(builderletters, buff);
				DoUpdate();
				return true;
			}
		}

		if (commandlist[0] >= '1' && commandlist[0] <= '8')
		{
			if (builderwords.size())
			{
				page = commandlist[0] - '1';
				ZeroMemory(&commandlist, sizeof(char)*MAXCOMMAND);
				return true;
			}
			else
			{
				char pos = commandlist[0] - '1';
				if (commandlist[1] == '0')
				{
					mulstate[pos] = 0;
					DoUpdate();
					return true;
				}
				else if (commandlist[1] >= '1' && commandlist[1] <= '8')
				{
					char pos2 = commandlist[1] - '1';
					char tmul = mulstate[pos];
					mulstate[pos] = mulstate[pos2];
					mulstate[pos2] = tmul;
					DoUpdate();
					return true;
				}
			}
		}

		if (commandlist[1] >= '1' && commandlist[1] <= '8')
		{
			char pos = commandlist[1] - '1';
			if (commandlist[0] == MULST_DL || commandlist[0] == MULST_TL || commandlist[0] == MULST_DW || commandlist[0] == MULST_TW)
			{
				ZeroMemory(mulstate, sizeof(char)*MAXSCRAMBLELETTER);
				mulstate[pos] = commandlist[0];
				DoUpdate();
				return true;
			}
		}
		return true;
	}

	else if (mode == GAMEMODE_SCRAMBLE)
	{
		if (force)
		{
			DoUpdate(true);
			return true;
		}
		if (commandlist[0] == CH_BACK)
		{
			if (strlen(scrambleletters))
			{
				mulstate[strlen(scrambleletters)-1] = 0;
				scrambleletters[strlen(scrambleletters)-1] = 0;
				scramblewords.clear();
				page = 0;
				nowpointingresult = 0;
				DoUpdate();
				return true;
			}
		}
		if (commandlist[0] >= 'a' && commandlist[0] <= 'z'+1)
		{
			char buff[2];
			buff[0] = commandlist[0];
			buff[1] = 0;
			if (strlen(scrambleletters) < MAXSCRAMBLELETTER-1)
			{
				strcat(scrambleletters, buff);
				DoUpdate();
				return true;
			}
		}
		if (scramblewords.size() && commandlist[0] >= '1' && commandlist[0] <= '8')
		{
			page = commandlist[0] - '1';
			ZeroMemory(&commandlist, sizeof(char)*MAXCOMMAND);
			return true;
		}

		char nowindex = strlen(scrambleletters)-1;
		if (nowindex >= 0)
		{
			if (commandlist[0] == MULST_DL || commandlist[0] == MULST_TL || commandlist[0] == MULST_DW || commandlist[0] == MULST_TW)
			{
				if (mulstate[nowindex] == commandlist[0])
				{
					mulstate[nowindex] = 0;
				}
				else
				{
					mulstate[nowindex] = commandlist[0];
				}
				DoUpdate();
				return true;
			}
		}

		return true;
	}

	if (commandlist[0] == '0' && commandlist[1] >= '4' && commandlist[1] <= '8')
	{
		DoClear();
		wordlength = commandlist[1] - '0';
		DoUpdate();
		return true;
	}
	if (!wordlength && commandlist[0] >= '4' && commandlist[1] <= '8')
	{
		DoClear();
		wordlength = commandlist[0] - '0';
		DoUpdate();
		return true;
	}


	if (commandlist[0] >= 'a' && commandlist[0] <= 'z' || force && possiblech)
	{
		char strikedch = commandlist[0];
		if (!strikedch)
		{
			strikedch = possiblech;
		}
		bool turnoff = false;
		for (list<char>::iterator it=striked.begin(); it!=striked.end();)
		{
			if (*it == strikedch)
			{
				it = striked.erase(it);
				turnoff = true;
			}
			else
			{
				++it;
			}
		}
		if (!turnoff)
		{
			striked.push_back(strikedch);
			bool toclear = true;
			for (int i=0; i<wordlength; i++)
			{
				if (nowguess.word[i] == strikedch)
				{
					nowguess.word[i] = 0;
				}
				if (nowguess.word[i])
				{
					toclear = false;
				}
			}
			if (toclear)
			{
				char twordlength = wordlength;
				DoClear();
				wordlength = twordlength;
			}
		}

		DoUpdate();
		return true;
	}

	if (commandlist[0] > '0' && commandlist[0] <= wordlength+'0')
	{
		char position = commandlist[0] - '0'-1;
		if (commandlist[1] > '0' && commandlist[1] <= wordlength+'0')
		{
			char pos2 = commandlist[1] - '0' -1;
			char ch = nowguess.word[position];
			nowguess.word[position] = nowguess.word[pos2];
			nowguess.word[pos2] = ch;
			DoUpdate();
			return true;
		}
		if (commandlist[1] == '0')
		{
			nowguess.word[position] = 0;
			bool toclear = true;
			for (int i=0; i<wordlength; i++)
			{
				if (nowguess.word[i])
				{
					toclear = false;
					break;
				}
			}
			if (toclear)
			{
				char twordlength = wordlength;
				DoClear();
				wordlength = twordlength;
			}
			DoUpdate();
			return true;
		}
		if (commandlist[1] >= 'a' && commandlist[1] <= 'z')
		{
			nowguess.word[position] = commandlist[1];

			for (list<char>::iterator it=striked.begin(); it!=striked.end();)
			{
				if (nowguess.word[position] == *it)
				{
					it = striked.erase(it);
				}
				else
				{
					++it;
				}
			}
			DoUpdate();
			return true;
		}
	}

	if (force)
	{
		ZeroMemory(&commandlist, sizeof(char)*MAXCOMMAND);
		return false;
	}


	return true;
}

void CheatsIO::DoUpdateBuilder(bool force)
{
	if (strlen(builderletters) >= MAXBUILDERLETTER-1 || force)
	{
		if (!force)
		{
			bool toret = true;
			for (int i=0; i<8; i++)
			{
				if (mulstate[i])
				{
					toret = false;
					break;
				}
			}
			if (toret)
			{
				return;
			}
		}
		builderwords.clear();
		page = 0;
		for (int i=8; i>=4; i--)
		{
			list<length16> * pwords;
			switch (i)
			{
			case 4:
				pwords = &l4words;
				break;;
			case 5:
				pwords = &l5words;
				break;
			case 6:
				pwords = &l6words;
				break;
			case 7:
				pwords = &l7words;
				break;
			case 8:
				pwords = &l8words;
				break;
			}
			char used[MAXBUILDERLETTER];
			int letternum = strlen(builderletters);
			bool notfound = true;
			int score = 0;
			for (list<length16>::iterator it=pwords->begin(); it!=pwords->end(); ++it)
			{
				ZeroMemory(used, sizeof(char)*MAXBUILDERLETTER);
				notfound = true;

				score = 0;
				int mul = 1;
				int chscore = 0;

				for (int j=0; j<i; j++)
				{
					notfound = true;
					for (int k=0; k<letternum; k++)
					{
						if (builderletters[k] == it->word[j] && !used[k])
						{
							used[k] = 1;
							notfound = false;
							break;
						}
					}
					if (notfound)
					{
						break;
					}
					chscore = GetLetterScore(it->word[j]);
					switch (mulstate[j])
					{
					case 0:
						break;
					case MULST_DL:
						chscore *= 2;
						break;
					case MULST_TL:
						chscore *= 3;
						break;
					case MULST_DW:
						mul *= 2;
						break;
					case MULST_TW:
						mul *= 3;
						break;
					}
					score += chscore;
				}

				if (!notfound)
				{
					score *= mul;

					BuilderWord _bw;
					strcpy(_bw.word.word, it->word);
					_bw.score = score;
					builderwords.push_back(_bw);
				}
			}
		}
		builderwords.sort();
		builderwords.reverse();
	}
}

void CheatsIO::DoUpdateScramble(bool force/* =false */)
{
	if (strlen(scrambleletters) >= MAXSCRAMBLELETTER-1 && force)
	{
		scramblewords.clear();
		page = 0;
		for (int j=16; j>=2; j--)
		{
			list<length16> * pwords;
			switch (j)
			{
			case 2:
				pwords = &l2words;
				break;;
			case 3:
				pwords = &l3words;
				break;
			case 4:
				pwords = &l4words;
				break;;
			case 5:
				pwords = &l5words;
				break;
			case 6:
				pwords = &l6words;
				break;
			case 7:
				pwords = &l7words;
				break;
			case 8:
				pwords = &l8words;
				break;
			case 9:
				pwords = &l9words;
				break;
			case 10:
				pwords = &l10words;
				break;
			case 11:
				pwords = &l11words;
				break;
			case 12:
				pwords = &l12words;
				break;
			case 13:
				pwords = &l13words;
				break;
			case 14:
				pwords = &l14words;
				break;
			case 15:
				pwords = &l15words;
				break;
			case 16:
				pwords = &l16words;
				break;
			}
			char bused[MAXSCRAMBLELETTER];
			bool notfound = true;
			int score = 0;
			for (list<length16>::iterator it=pwords->begin(); it!=pwords->end(); ++it)
			{
				ZeroMemory(bused, sizeof(char) * MAXSCRAMBLELETTER);
				notfound = true;
				score = 0;
				char ret = 0;

				for (int i=0; i<16; i++)
				{
					bool qu = (scrambleletters[i] == 'a'+26);
					if (it->word[0] == scrambleletters[i] || qu && it->word[0] == 'q' && it->word[1] == 'u')
					{
						bused[i] = 1;
						ret = ScrambleNextAll(&(*it), bused, qu?2:1, i, 2);
						if (ret)
						{
							notfound = false;
							break;
						}
						bused[i] = 0;
					}
				}

				if (!notfound)
				{
					int mul = 1;
					for (int i=0; i<16; i++)
					{
						if (bused[i])
						{
							int chscore = GetLetterScore(scrambleletters[i]);
							switch (mulstate[i])
							{
							case 0:
								break;
							case MULST_DL:
								chscore *= 2;
								break;
							case MULST_TL:
								chscore *= 3;
								break;
							case MULST_DW:
								mul *= 2;
								break;
							case MULST_TW:
								mul *= 3;
								break;
							}
							score += chscore;
						}
					}
					if (strlen(it->word) <= 2)
					{
						score = 1;
					}
					score *= mul;
					score += GetLengthScore(strlen(it->word));
					BuilderWord _bw;
					strcpy(_bw.word.word, it->word);
					_bw.score = score;
					memcpy(_bw.step, bused, sizeof(char)*MAXSCRAMBLELETTER);
					scramblewords.push_back(_bw);
				}
			}
		}
		scramblewords.sort();
		scramblewords.reverse();
	}
}

char CheatsIO::ScrambleNextAll(length16 *word, char * bused, char index, char nowpos, char letterindex)
{
	if (!word || !bused)
	{
		return 0;
	}

	if (index >= strlen(word->word))
	{
		return 0;
	}

	char tocheckch = word->word[index];
	char tocheckch2 = word->word[index+1];
	/************************************************************************/
	/*          0123                                                        */
	/*          4567                                                        */
	/*          89ab                                                        */
	/*          cdef                                                        */
	/*                                                                      */
	/*                                                                      */
	/************************************************************************/
	char checkpos = 0;
	char ret = 0;

#define _CHECKPROCESS	\
	bool qu = (scrambleletters[checkpos] == 'a'+26);	\
	if (!bused[checkpos] && (scrambleletters[checkpos] == tocheckch || qu && tocheckch == 'q' && tocheckch2 == 'u'))	\
	{	\
		bused[checkpos] = letterindex;	\
		if (index+(qu?2:1) == strlen(word->word))	\
		{	\
			return letterindex+1;	\
		}	\
		ret = ScrambleNextAll(word, bused, index+(qu?2:1), checkpos, letterindex+1);	\
		if (!ret)	\
		{	\
			bused[checkpos] = 0;	\
		}	\
		else	\
		{	\
			return ret;	\
		}	\
	}


	if (nowpos % 4 < 3)
	{
		checkpos = nowpos+1;
		_CHECKPROCESS;
/*
		if (!bused[checkpos] && (scrambleletters[checkpos] == tocheckch || qu && tocheckch == 'q' && tocheckch2 == 'u'))	
		{	
			bused[checkpos] = letterindex;	
			ret = ScrambleNextAll(word, bused, index+(qu?2:1), checkpos, letterindex+1);	
			if (!ret)	
			{	
				bused[checkpos] = 0;	
			}	
			else	
			{	
				return ret;	
			}	
		}*/
	}
	if (nowpos % 4)
	{
		checkpos = nowpos-1;
		_CHECKPROCESS;
	}
	if (nowpos > 3)
	{
		checkpos = nowpos-4;
		_CHECKPROCESS;
	}
	if (nowpos < 12)
	{
		checkpos = nowpos+4;
		_CHECKPROCESS;
	}
	if (nowpos < 12 && nowpos % 4 < 3)
	{
		checkpos = nowpos+5;
		_CHECKPROCESS;
	}
	if (nowpos < 12 && nowpos % 4)
	{
		checkpos = nowpos+3;
		_CHECKPROCESS;
	}
	if (nowpos > 3 && nowpos % 4 < 3)
	{
		checkpos = nowpos-3;
		_CHECKPROCESS;
	}
	if (nowpos > 3 && nowpos % 4)
	{
		checkpos = nowpos-5;
		_CHECKPROCESS;
	}

	return 0;
}

char CheatsIO::GetLetterScore(char letter)
{
	switch (letter)
	{
	case 'a':
	case 'e':
	case 'i':
	case 'o':
	case 'r':
	case 's':
	case 't':
		return 1;

	case 'l':
	case 'n':
	case 'd':
	case 'u':
		return 2;

	case 'g':
	case 'h':
	case 'y':
		return 3;

	case 'p':
	case 'b':
	case 'c':
	case 'f':
	case 'm':
	case 'w':
		return 4;

	case 'k':
	case 'v':
		return 5;

	case 'x':
		return 8;

	case 'j':
	case 'q':
	case 'z':
	case 'z'+1:
		return 10;
	}
	return 0;
}

char CheatsIO::GetLengthScore(char lenghth)
{
	switch (lenghth)
	{
	case 2:
	case 3:
	case 4:
		return 0;
	case 5:
		return 3;
	case 6:
		return 6;
	case 7:
		return 10;
	case 8:
		return 15;
	case 9:
		return 20;
	case 10:
		return 25;
	case 11:
		return 30;
	case 12:
		return 35;
	case 13:
		return 40;
	case 14:
		return 45;
	case 15:
		return 50;
	case 16:
		return 55;
	}
}


void CheatsIO::DoUpdate(bool force)
{
	ZeroMemory(commandlist, sizeof(char)*MAXCOMMAND);
	if (mode == GAMEMODE_BUILDER)
	{
		DoUpdateBuilder(force);
		return;
	}
	if (mode == GAMEMODE_SCRAMBLE)
	{
		DoUpdateScramble(force);
		return;
	}
	bool update = false;
	for (int i=0; i<8; i++)
	{
		if (nowguess.word[i])
		{
			update = true;
			break;
		}
	}

	if (!update)
	{
		return;
	}

	if (wordlength)
	{

		int strikedlength = striked.size();
		list<length16> * pwordlist;
		switch (wordlength)
		{
		case 4:
			pwordlist = &l4words;
			break;
		case 5:
			pwordlist = &l5words;
			break;
		case 6:
			pwordlist = &l6words;
			break;
		case 7:
			pwordlist = &l7words;
			break;
		case 8:
			pwordlist = &l8words;
			break;
		default:
			return;
		}

		ClearResult();

		list<char>nocountletter;
		for (list<char>::iterator it=striked.begin(); it!=striked.end(); ++it)
		{
			nocountletter.push_back(*it);
		}
		for (int i=0; i<wordlength; i++)
		{
			if (nowguess.word[i])
			{
				nocountletter.push_back(nowguess.word[i]);
			}
		}

		for (list<length16>::iterator it=pwordlist->begin(); it!=pwordlist->end(); ++it)
		{
			bool skip = false;
			for (int i=0; i<wordlength; i++)
			{
				if (nowguess.word[i])
				{
					if (nowguess.word[i]!=it->word[i])
					{
						skip = true;
						break;
					}
					for (int j=0; j<wordlength; j++)
					{
						if (j == i)
						{
							continue;
						}
						if (nowguess.word[i] == it->word[j] && nowguess.word[j] != it->word[j])
						{
							skip = true;
							break;
						}
					}
				}
				if (skip)
				{
					break;
				}
			}

			if (skip)
			{
				continue;
			}

			// All Guess Matched

			if (striked.size())
			{
				for (int i=0; i<wordlength; i++)
				{
					if (skip)
					{
						break;
					}
					for (list<char>::iterator jt=striked.begin(); jt!=striked.end(); jt++)
					{
						if (it->word[i] == *jt)
						{
							skip = true;
							break;
						}
					}
				}

				if (skip)
				{
					continue;
				}
			}

			// All Strikes

			resultwords.push_back(*it);

			for (int i=0; i<wordlength; i++)
			{
				bool skipletter = false;
				for (int j=0; j<i; j++)
				{
					if (it->word[j] == it->word[i])
					{
						skipletter = true;
						break;
					}
				}
				if (!skipletter)
				{
					for (list<char>::iterator jt=nocountletter.begin(); jt!=nocountletter.end(); ++jt)
					{
						if (it->word[i] == *jt)
						{
							skipletter = true;
							break;
						}
					}
					if (!skipletter)
					{
						possiblecount[it->word[i]-'a']++;
					}
				}
			}
		}

		int maxcount = 0;
		for (int i=0; i<26; i++)
		{
			if (possiblecount[i] > maxcount)
			{
				possiblech = i+'a';
				maxcount = possiblecount[i];
			}
		}
		if (resultwords.size())
		{
			for (int i=0; i<26; i++)
			{
				if (possiblecount[i])
				{
					percentage[i] = (float)possiblecount[i]/(float)resultwords.size();
				}
			}
		}
		AppendLog("Updated");
	}
}

bool CheatsIO::RenderFunc()
{
	hge->Gfx_BeginScene();
	hge->Gfx_Clear(0xff303030);

#define RESULTLISTROW	5
#define RESULTLISTCOL	8


	if (init)
	{
		if (font)
		{

			commandlist[MAXCOMMAND-1] = 0;
			font->Render(0, 0, 0, commandlist);

			if (logtimer)
			{
				logtimer--;
				unsigned char alpha = logtimer*2;
				font->SetScale(0.5f);
				font->SetColor(ARGB(alpha, 0xc0, 0xc0, 0xc0));
				font->Render(0, 0, HGETEXT_LEFT|HGETEXT_TOP, logstring);
			}
			font->SetScale(1.0f);
			font->SetColor(0xffffffff);

			if (mode == GAMEMODE_HANGING)
			{
				char tbuff[2];
				tbuff[1] = 0;
				if (!wordlength)
				{
					for (int i=0; i<5; i++)
					{
						tbuff[0] = '4' + i;
						font->RenderEx(tbl.l8[i].rect.x, tbl.l8[i].rect.y, HGETEXT_CENTER|HGETEXT_MIDDLE, tbuff, 1.5f);
					}
				}
				for (int i=0; i<wordlength; i++)
				{
					tbuff[0] = nowguess.word[i]+'A'-'a';
					if (!tbuff[0])
					{
						tbuff[0] = '_';
					}
					font->RenderEx(tbl.l8[i].rect.x, tbl.l8[i].rect.y, HGETEXT_CENTER|HGETEXT_MIDDLE, tbuff, 1.5f);
				}

			}
			else if (mode == GAMEMODE_BUILDER)
			{
				char linebuffer[2][7];
				ZeroMemory(linebuffer, sizeof(char)*2*7);

				if (strlen(builderletters))
				{
					strncpy(linebuffer[0], builderletters, 6);
					linebuffer[0][6] = 0;
					if (strlen(builderletters) > 6)
					{
						strncpy(linebuffer[1], &(builderletters[6]), 6);
						linebuffer[1][6] = 0;
					}
				}

				for (int i=0; i<2; i++)
				{
					for (int j=0; j<6; j++)
					{
						if (!linebuffer[i][j])
						{
							linebuffer[i][j] = '_';
						}
						else
						{
							linebuffer[i][j] += 'A' - 'a';
						}
					}
				}

				for (int i=0; i<2; i++)
				{
					font->RenderEx(tbl.bline[i].rect.x, tbl.bline[i].rect.y, HGETEXT_CENTER|HGETEXT_MIDDLE, linebuffer[i], 1.2f);
				}


				if (builderwords.size())
				{
					char strbuffer[M_STRMAX];
					list<BuilderWord>::iterator it = builderwords.begin();

					char maxpage = builderwords.size()/(RESULTLISTROWB*RESULTLISTCOLB);
					if (page > maxpage)
					{
						page = maxpage;
					}

					for (int i=0; i<page*RESULTLISTROWB*RESULTLISTCOLB; i++)
					{
						++it;
					}
					strcpy(strbuffer, "");
					bool wordover=false;
					for (int i=0; i<RESULTLISTROWB; i++)
					{
						for (int j=0; j<RESULTLISTCOLB; j++)
						{
							if (it == builderwords.end())
							{
								wordover = true;
								break;
							}
							sprintf(strbuffer, "%s%8s %02d,", strbuffer, it->word.word, it->score);
							++it;

						}
						font->RenderEx(tbl.bresults.rect.x, tbl.bresults.rect.y+i*tbl.bresults.rect.h, HGETEXT_LEFT|HGETEXT_MIDDLE, strbuffer, 0.6f);
						strcpy(strbuffer, "");
						if (wordover)
						{
							break;
						}
					}
				}
				else
				{
					char blbuffer[3];
					for (int i=0; i<8; i++)
					{
						if (mulstate[i])
						{
							switch (mulstate[i])
							{
							case MULST_DL:
								strcpy(blbuffer, "DL");
								break;
							case MULST_TL:
								strcpy(blbuffer, "TL");
								break;
							case MULST_DW:
								strcpy(blbuffer, "DW");
								break;
							case MULST_TW:
								strcpy(blbuffer, "TW");
								break;
							}
						}
						else
						{
							sprintf(blbuffer, "%d", i+1);
						}
						font->Render(tbl.ll8[i].rect.x, tbl.ll8[i].rect.y+5, HGETEXT_CENTER|HGETEXT_MIDDLE, blbuffer);
					}
				}

			}
			else if (mode == GAMEMODE_SCRAMBLE)
			{
				char linebuffer[4][17];
				ZeroMemory(linebuffer, sizeof(char)*4*17);

				char nowrow;
				char nowcol;
				for (int i=0; i<strlen(scrambleletters); i++)
				{
					nowrow = i/4;
					nowcol = (i%4)*4+1;
					linebuffer[nowrow][nowcol] = scrambleletters[i] + 'A' - 'a';
					if (scrambleletters[i] == 'a' + 26)
					{
						linebuffer[nowrow][nowcol] = 'Q';
						linebuffer[nowrow][nowcol+1] = 'u';
					}
				}

				for (int i=0; i<4; i++)
				{
					for (int j=0; j<4; j++)
					{
						if (!linebuffer[i][j*4+1])
						{
							linebuffer[i][j*4+1] = '_';
						}
						if (!linebuffer[i][j*4+2])
						{
							linebuffer[i][j*4+2] = ' ';
						}
						if (!linebuffer[i][j*4+3])
						{
							linebuffer[i][j*4+3] = ' ';
						}
						if (!linebuffer[i][j*4])
						{
							if (mulstate[i*4+j])
							{
								linebuffer[i][j*4] = mulstate[i*4+j];
							}
							else
							{
								linebuffer[i][j*4] = ' ';
							}
						}
					}
				}

				for (int i=0; i<4; i++)
				{
					font->RenderEx(tbl.sline[i].rect.x, tbl.sline[i].rect.y, HGETEXT_CENTER|HGETEXT_MIDDLE, linebuffer[i], 0.6f);
				}

				if (scramblewords.size())
				{
					char strbuffer[M_STRMAX];
					list<BuilderWord>::iterator it = scramblewords.begin();
					BuilderWord * dispit = NULL;

					char maxpage = scramblewords.size()/(RESULTLISTROWB*RESULTLISTCOLB);
					if (page > maxpage)
					{
						page = maxpage;
					}

					for (int i=0; i<page*RESULTLISTROWB*RESULTLISTCOLB; i++)
					{
						++it;
					}

					char nowindex = 0;

					strcpy(strbuffer, "");
					bool wordover=false;
					for (int i=0; i<RESULTLISTROWB; i++)
					{
						for (int j=0; j<RESULTLISTCOLB; j++)
						{
							if (it == scramblewords.end())
							{
								wordover = true;
								break;
							}
							if (nowindex == nowpointingresult)
							{
								dispit = &(*it);
								font->SetColor(0xffffff00);
							}
							sprintf(strbuffer, "%8s %02d,", it->word.word, it->score);
							font->RenderEx(tbl.sresults[i*RESULTLISTCOLB+j].rect.x-tbl.sresults[i*RESULTLISTCOLB+j].rect.w/2, tbl.sresults[i*RESULTLISTCOLB+j].rect.y, HGETEXT_LEFT|HGETEXT_MIDDLE, strbuffer, 0.6f);
							font->SetColor(0xffffffff);
							//
//							_RenderFrame(&(tbl.sresults[i*RESULTLISTCOLB+j].rect));
							//
							++it;
							nowindex++;

						}
						strcpy(strbuffer, "");
						if (wordover)
						{
							break;
						}
					}

					if (dispit)
					{
						char tbuff[3];
						char maxstep = 0;
						for (int i=0; i<16; i++)
						{
							if (dispit->step[i])
							{
								sprintf(tbuff, "%d", dispit->step[i]);
								if (dispit->step[i] > maxstep)
								{
									maxstep = dispit->step[i];
								}
								font->RenderEx(tbl.sdir[i].rect.x, tbl.sdir[i].rect.y, HGETEXT_CENTER|HGETEXT_MIDDLE, tbuff, 0.75f);
							}
						}

						if (maxstep)
						{
							hgeColorHSV hsv(0, 1, 1, 1);
							for (int i=0; i<16; i++)
							{
								if (dispit->step[i])
								{
									hsv.h = (float)dispit->step[i]/(float)maxstep/3;
									_RenderFrame(&(tbl.sdir[i].rect), hsv.GetHWColor());
								}
								else
								{
									_RenderFrame(&(tbl.sdir[i].rect), 0x40ffffff);
								}
								/*
								if (i < maxstep-1)
								{
									for (int j=0; j<16; j++)
									{
										if (dispit->step[j] == i+1)
										{
											for (int k=0; k<16; k++)
											{
												if (dispit->step[k] == i+2)
												{
													_RenderLine(&(tbl.sres[j].rect), &(tbl.sres[k].rect), 0xffffff00, -4, -4);
													break;
												}
											}
											break;
										}
									}
								}*/
							}
						}
					}
				}

			}


			if (!(mode == GAMEMODE_BUILDER && builderwords.size() || mode == GAMEMODE_SCRAMBLE && scramblewords.size()))
			{
				char strbuff[4];
				strbuff[2] = 0;
				for (int i=0; i<27; i++)
				{
					strbuff[0] = i + 'A';
					strbuff[1] = 0;

					if (i == 26)
					{
						if (mode == GAMEMODE_SCRAMBLE)
						{
							strbuff[0] = 'Q';
							strbuff[1] = 'u';
						}
						else
						{
							break;
						}
					}


					font->SetColor(0xffffffff);
					if (mode == GAMEMODE_HANGING)
					{
						for (list<char>::iterator it=striked.begin(); it!=striked.end(); ++it)
						{
							if (strbuff[0] == (*it)+'A'-'a')
							{
								font->SetColor(0xffff0000);
							}
						}
						for (int j=0; j<wordlength; j++)
						{
							if (strbuff[0] == nowguess.word[j]+'A'-'a')
							{
								font->SetColor(0xff00ff00);
							}
						}
					}

					font->Render(tbl.az[i].rect.x, tbl.az[i].rect.y+2, HGETEXT_CENTER|HGETEXT_MIDDLE, strbuff);
				}
				font->SetColor(0xffffffff);

				if (mode != GAMEMODE_HANGING)
				{
					font->RenderEx(tbl.mul[0].rect.x, tbl.mul[0].rect.y+10, HGETEXT_CENTER|HGETEXT_MIDDLE, "DL%", 0.75f);
					font->RenderEx(tbl.mul[1].rect.x, tbl.mul[1].rect.y+10, HGETEXT_CENTER|HGETEXT_MIDDLE, "TL^", 0.75f);
					font->RenderEx(tbl.mul[2].rect.x, tbl.mul[2].rect.y+10, HGETEXT_CENTER|HGETEXT_MIDDLE, "DW&", 0.75f);
					font->RenderEx(tbl.mul[3].rect.x, tbl.mul[3].rect.y+10, HGETEXT_CENTER|HGETEXT_MIDDLE, "TW*", 0.75f);
				}
			}

			if (mode == GAMEMODE_HANGING && possiblech)
			{
				font->SetScale(0.6f);
				char strbuffer[M_STRMAX];

				sprintf(strbuffer, "%c", possiblech+'A'-'a');
				font->SetColor(0xffffff00);
				font->RenderEx(tbl.guess.rect.x, tbl.guess.rect.y, HGETEXT_CENTER|HGETEXT_MIDDLE, strbuffer, 1.5f);

				sprintf(strbuffer, "  %.3f%%  Word Count:%d", percentage[possiblech-'a']*100, resultwords.size());
				font->SetColor(0xffffffc0);
				font->Render(tbl.guess.rect.x, tbl.guess.rect.y, HGETEXT_LEFT|HGETEXT_MIDDLE, strbuffer);

				font->SetColor(0xffffffff);

				
				char resultliststr[RESULTLISTROW][M_STRMAX];
				ZeroMemory(resultliststr, sizeof(char)*M_STRMAX*RESULTLISTROW);

				int i=0;
				int j=0;
				for (list<length16>::iterator it=resultwords.begin(); it!=resultwords.end(); ++it)
				{
					strcat(resultliststr[i], it->word);
					strcat(resultliststr[i], " ");
					j++;
					if (wordlength != 8 && j == RESULTLISTCOL-wordlength+4 || wordlength == 8 && j == 5)
					{
						j = 0;
						i++;
						if (i == RESULTLISTROW)
						{
							break;
						}
					}
				}

				for (int k=0; k<RESULTLISTROW; k++)
				{
					font->Render(tbl.results.rect.x, tbl.results.rect.y+k*tbl.results.rect.h, HGETEXT_LEFT|HGETEXT_MIDDLE, resultliststr[k]);
				}
			}

			// button frame
			if (!(mode == GAMEMODE_BUILDER && builderwords.size() || mode == GAMEMODE_SCRAMBLE && scramblewords.size()))
			{
				for (int i=0; i<27; i++)
				{
					if (i == 26 && mode != GAMEMODE_SCRAMBLE)
					{
						break;
					}
					_RenderFrame(&tbl.az[i].rect);
				}
				if (mode != GAMEMODE_HANGING)
				{
					for (int i=0; i<4; i++)
					{
						_RenderFrame(&tbl.mul[i].rect);
					}
					if (mode == GAMEMODE_BUILDER)
					{
						for (int i=0; i<8; i++)
						{
							_RenderFrame(&tbl.ll8[i].rect);
						}
					}
				}
			}
			if (mode == GAMEMODE_HANGING)
			{
				char twordlength = wordlength ? wordlength : 5;
				for (int i=0; i<twordlength; i++)
				{
					_RenderFrame(&tbl.l8[i].rect);
				}
			}

			// buttons

			float scale = 0.6f;
			float yoffset = 10;
			font->RenderEx(tbl.clear.rect.x, tbl.clear.rect.y+yoffset, HGETEXT_CENTER|HGETEXT_MIDDLE, "Clear", scale);
			font->RenderEx(tbl.backspace.rect.x, tbl.backspace.rect.y+yoffset, HGETEXT_CENTER|HGETEXT_MIDDLE, "BS", scale);
			font->RenderEx(tbl.changemode.rect.x, tbl.changemode.rect.y+yoffset, HGETEXT_CENTER|HGETEXT_MIDDLE, "Mode", scale);

			_RenderFrame(&tbl.clear.rect);
			_RenderFrame(&tbl.backspace.rect);
			_RenderFrame(&tbl.changemode.rect);
			if (mode == GAMEMODE_BUILDER && builderwords.size() || mode == GAMEMODE_SCRAMBLE && scramblewords.size())
			{
				_RenderFrame(&tbl.pageup.rect);
				_RenderFrame(&tbl.pagedown.rect);
				font->RenderEx(tbl.pageup.rect.x, tbl.pageup.rect.y+yoffset, HGETEXT_CENTER|HGETEXT_MIDDLE, "PgUp", scale);
				font->RenderEx(tbl.pagedown.rect.x, tbl.pagedown.rect.y+yoffset, HGETEXT_CENTER|HGETEXT_MIDDLE, "PgDn", scale);
			}
			else
			{
				_RenderFrame(&tbl.enter.rect);
				font->RenderEx(tbl.enter.rect.x, tbl.enter.rect.y+yoffset, HGETEXT_CENTER|HGETEXT_MIDDLE, "Go", scale);
			}

			// floating
			if (mode == GAMEMODE_HANGING || mode == GAMEMODE_BUILDER && !builderwords.size())
			{
				for (int i=0; i<TOUCH_TOUCHMAX; i++)
				{
					if (TouchButton::binding[i] && hge->Input_IsTouchOn(i))
					{
						float x = 0;
						float y = 0;
						hge->Input_GetTouchPos(i, &x, &y);
						char tbuff[3];
						tbuff[1] = 0;
						tbuff[2] = 0;

						bool found = false;
						if (mode == GAMEMODE_HANGING)
						{
							for (int j=0; j<26; j++)
							{
								if (TouchButton::binding[i] == &(tbl.az[j]))
								{
									tbuff[0] = j+'a';
									font->RenderEx(x, y-20, HGETEXT_CENTER|HGETEXT_BOTTOM, tbuff, 1.5f);
									RenderPos trect;
									trect.x = x;
									trect.y = y-20;
									trect.w = 50;
									trect.h = 50;
									_RenderFrame(&trect);
									found = true;
									break;
								}
							}
							if (!found && wordlength)
							{
								for (int k=0; k<wordlength; k++)
								{
									if (TouchButton::binding[i] == &(tbl.l8[k]))
									{
										tbuff[0] = nowguess.word[k];
										if (!tbuff[0])
										{
											tbuff[0] = '_';
										}
										font->RenderEx(x, y-20, HGETEXT_CENTER|HGETEXT_BOTTOM, tbuff, 1.5f);
										RenderPos trect;
										trect.x = x;
										trect.y = y-20;
										trect.w = 50;
										trect.h = 50;
										_RenderFrame(&trect);
										found = true;
										break;
									}
								}
							}
						}
						else
						{
							for (int j=0; j<8; j++)
							{
								if (TouchButton::binding[i] == &(tbl.ll8[j]))
								{
									if (!mulstate[j])
									{
										sprintf(tbuff, "%d", j+1);
									}
									else
									{
										switch (mulstate[j])
										{
										case MULST_DL:
											strcpy(tbuff, "DL");
											break;
										case MULST_TL:
											strcpy(tbuff, "TL");
											break;
										case MULST_DW:
											strcpy(tbuff, "DW");
											break;
										case MULST_TW:
											strcpy(tbuff, "TW");
											break;
										}
									}
									font->RenderEx(x, y-20, HGETEXT_CENTER|HGETEXT_BOTTOM, tbuff, 1.5f);
									RenderPos trect;
									trect.x = x;
									trect.y = y-20;
									trect.w = 50;
									trect.h = 50;
									_RenderFrame(&trect);
									found = true;
									break;
								}
							}
							if (!found)
							{
								for (int j=0; j<4; j++)
								{
									if (TouchButton::binding[i] == &(tbl.mul[j]))
									{
										switch (j)
										{
										case 0:
											strcpy(tbuff, "DL");
											break;
										case 1:
											strcpy(tbuff, "TL");
											break;
										case 2:
											strcpy(tbuff, "DW");
											break;
										case 3:
											strcpy(tbuff, "TW");
											break;
										}
										font->RenderEx(x, y-15, HGETEXT_CENTER|HGETEXT_BOTTOM, tbuff, 1.2f);
										RenderPos trect;
										trect.x = x;
										trect.y = y-20;
										trect.w = 50;
										trect.h = 50;
										_RenderFrame(&trect);
										found = true;
										break;
									}
								}
							}
						}
					}
				}
			}
		}
		font->SetScale(1.0f);
	}

	hge->Gfx_EndScene();
	return false;
}

void CheatsIO::_RenderLine(RenderPos * pos1, RenderPos * pos2, DWORD col/* =0xffffffff */, float xoffset, float yoffset, int thick)
{
	if (!pos1 || !pos2)
	{
		return;
	}
	if (thick > 1)
	{
		_RenderLine(pos1, pos2, col, xoffset, yoffset, thick-1);
	}
	if (thick <= 1)
	{
		hge->Gfx_RenderLine(pos1->x+xoffset, pos1->y+pos1->h/2+yoffset, pos2->x+xoffset, pos2->y+pos2->h/2+yoffset, col);
	}
	else
	{
		float offset = 0.4f * (thick-1);
		hge->Gfx_RenderLine(pos1->x+offset+xoffset, pos1->y+pos1->h/2+offset+yoffset, pos2->x+offset+xoffset, pos2->y+pos2->h/2+offset+yoffset, col);
		hge->Gfx_RenderLine(pos1->x-offset+xoffset, pos1->y+pos1->h/2-offset+yoffset, pos2->x-offset+xoffset, pos2->y+pos2->h/2-offset+yoffset, col);
		hge->Gfx_RenderLine(pos1->x+offset+xoffset, pos1->y+pos1->h/2+offset+yoffset, pos2->x-offset+xoffset, pos2->y+pos2->h/2-offset+yoffset, col);
		hge->Gfx_RenderLine(pos1->x-offset+xoffset, pos1->y+pos1->h/2-offset+yoffset, pos2->x+offset+xoffset, pos2->y+pos2->h/2+offset+yoffset, col);
	}
}

void CheatsIO::_RenderFrame(RenderPos * rect, DWORD col, float edge /* = 1.0f */, int thick/* =2 */, float corner/* =2.0f */)
{
	if (!rect)
	{
		return;
	}

	if (thick)
	{
		RenderPos trect;
		trect.x = rect->x+1;
		trect.y = rect->y+1;
		trect.w = rect->w-2;
		trect.h = rect->h-2;
		_RenderFrame(&trect, col, edge, thick-1, corner);
	}
	float corneredge = edge+thick+corner;
	if (rect->w - 2*(corneredge) < 0 || rect->h - 2*(corneredge) < 0)
	{
		return;
	}
	float noncorneredge = thick+edge;

	/************************************************************************/
	/* -0---1-
	/* 7-----2
	/* 6-----3
	/* -5---4-
	*/
	/************************************************************************/
	float x[8];
	float y[8];
	x[0] = x[5] = rect->x-rect->w/2+corneredge;
	x[1] = x[4] = rect->x+rect->w/2-corneredge;
	x[2] = x[3] = rect->x+rect->w/2-noncorneredge;
	x[6] = x[7] = rect->x-rect->w/2+noncorneredge;

	y[0] = y[1] = rect->y+noncorneredge;
	y[2] = y[7] = rect->y+corneredge;
	y[4] = y[5] = rect->y+rect->h-noncorneredge;
	y[3] = y[6] = rect->y+rect->h-corneredge;

	hge->Gfx_RenderLine(x[0], y[0], x[1], y[1], col);
	hge->Gfx_RenderLine(x[4], y[4], x[5], y[5], col);
	hge->Gfx_RenderLine(x[2], y[2], x[3], y[3], col);
	hge->Gfx_RenderLine(x[6], y[6], x[7], y[7], col);
	hge->Gfx_RenderLine(x[1], y[1], x[2], y[2], col);
	hge->Gfx_RenderLine(x[3], y[3], x[4], y[4], col);
	hge->Gfx_RenderLine(x[5], y[5], x[6], y[6], col);
	hge->Gfx_RenderLine(x[7], y[7], x[0], y[0], col);
}

bool CheatsIO::ReadWordsFile(const char * filename)
{
	if (!hge->Resource_AccessFile(filename))
	{
		return false;
	}
	FILE * fwords = fopen(hge->Resource_MakePath(filename), "rb");
	if (!fwords)
	{
		return false;
	}

	char strbuffer[40];

	length16 buff16;

	while(!feof(fwords))
	{
		fscanf(fwords, "%s", strbuffer);
		if (feof(fwords))
		{
			break;
		}
		if (strlen(strbuffer) > MAXSCRAMBLELETTER-1)
		{
			continue;
		}
		strcpy(buff16.word, strbuffer);
		switch (strlen(strbuffer))
		{
		case 2:
			l2words.push_back(buff16);
			break;
		case 3:
			l2words.push_back(buff16);
			break;

		case 4:
			l4words.push_back(buff16);
			break;
		case 5:
			l5words.push_back(buff16);
			break;
		case 6:
			l6words.push_back(buff16);
			break;
		case 7:
			l7words.push_back(buff16);
			break;
		case 8:
			l8words.push_back(buff16);
			break;

		case 9:
			l9words.push_back(buff16);
			break;
		case 10:
			l10words.push_back(buff16);
			break;
		case 11:
			l11words.push_back(buff16);
			break;
		case 12:
			l12words.push_back(buff16);
			break;
		case 13:
			l13words.push_back(buff16);
			break;
		case 14:
			l14words.push_back(buff16);
			break;
		case 15:
			l15words.push_back(buff16);
			break;
		case 16:
			l16words.push_back(buff16);
			break;
		}
	}

	fclose(fwords);
	return true;
}