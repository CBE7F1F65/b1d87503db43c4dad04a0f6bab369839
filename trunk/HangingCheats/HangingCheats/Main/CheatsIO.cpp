#include "../Header/CheatsIO.h"
#include "../Header/Main.h"

CheatsIO CheatsIO::cheatsio;

#define WORDSFILENAME	"words.txt"
#define FONTFILENAME	"font.fnt"

CheatsIO::BuilderWord::BuilderWord()
{
	ZeroMemory(&word, sizeof(length8));
	score = 0;
}


CheatsIO::BuilderWord::~BuilderWord()
{

}

CheatsIO::TouchButton::TouchButton()
{
	ZeroMemory(&rect, sizeof(RenderPos));
	active = false;
	touchdown = false;
}

CheatsIO::TouchButton::~TouchButton()
{

}

CheatsIO::TouchButton * CheatsIO::TouchButton::binding[TOUCH_TOUCHMAX];

void CheatsIO::FillRenderPos()
{
	int xbegin = 0;
	int ybegin = 0;
	int xoffset = 0;
	int yoffset = 0;

	int aztz = M_CLIENT_WIDTH/13;
	ybegin = M_CLIENT_HEIGHT/4;
	for (int i=0; i<26; i++)
	{
		tbl.az[i].rect.x = (i%10+2) * aztz;
		tbl.az[i].rect.y = (i/10) * aztz + ybegin;
		tbl.az[i].rect.w = tbl.az[i].rect.h = aztz;
	}

	xoffset = aztz * 1.2f;
	xbegin = aztz*2.5f;
	ybegin = M_CLIENT_HEIGHT / 10;
	for (int i=0; i<8; i++)
	{
		tbl.l8[i].rect.x = xbegin + i*xoffset;
		tbl.l8[i].rect.y = ybegin;
		tbl.l8[i].rect.w = tbl.l8[i].rect.h = xoffset;
	}

	tbl.guess.rect.x = 20;
	tbl.guess.rect.y = M_CLIENT_HEIGHT / 2 + 30;

	tbl.results.rect.x = 40;
	tbl.results.rect.y = M_CLIENT_HEIGHT / 2 + 60;
	tbl.results.rect.h = 20;

	for (int i=0; i<2; i++)
	{
		tbl.bline[i].rect.x = M_CLIENT_WIDTH / 3;
		tbl.bline[i].rect.y = i * 30 + 5;
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
	tbl.enter.rect.w = 60;
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
	builderwords.clear();
	ZeroMemory(builderletters, sizeof(char)*MAXBUILDERLETTER);

	wordlength = 0;
	striked.clear();
	ZeroMemory(&nowguess, sizeof(length8));
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
				if (!(mode == GAMEMODE_BUILDER && builderwords.size()))
				{
					for (int j=0; j<26; j++)
					{
						if (tbl.az[j].IsInRect(x, y))
						{
							TouchButton::binding[i] = &(tbl.az[j]);
							return false;
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
				if (tbl.enter.IsInRect(x, y))
				{
					TouchButton::binding[i] = &(tbl.enter);
					return false;
				}
				if (tbl.changemode.IsInRect(x, y))
				{
					TouchButton::binding[i] = &(tbl.changemode);
					return false;
				}
				if (mode == GAMEMODE_BUILDER && tbl.backspace.IsInRect(x, y))
				{
					TouchButton::binding[i] = &(tbl.backspace);
					return false;
				}
				if (mode == GAMEMODE_BUILDER && builderwords.size())
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
				for (; j<26; j++)
				{
					if (tbinding == &(tbl.az[j]))
					{
						found = true;
						break;
					}
				}
				if (found)
				{
					if (mode == GAMEMODE_BUILDER)
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
					commandlist[0] = '7';
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
					if (page < 6)
					{
						page++;
					}
					return false;
				}
				if (tbinding == &(tbl.pagedown))
				{
					if (page > 0)
					{
						page--;
					}
					return false;
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
		if (commandlist[0] == '7')
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
		if (builderwords.size() && commandlist[0] >= '1' && commandlist[0] <= '6')
		{
			page = commandlist[0] - '1';
			ZeroMemory(&commandlist, sizeof(char)*MAXCOMMAND);
			return true;
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
	if (strlen(builderletters) == MAXBUILDERLETTER-1 || force)
	{
		builderwords.clear();
		page = 0;
		for (int i=8; i>=4; i--)
		{
			list<length8> * pwords;
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
			for (list<length8>::iterator it=pwords->begin(); it!=pwords->end(); it++)
			{
				ZeroMemory(used, sizeof(char)*MAXBUILDERLETTER);
				notfound = true;

				char score = 0;

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
					score += GetLetterScore(it->word[j]);
				}

				if (!notfound)
				{
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
		return 10;
	}
	return 0;
}


void CheatsIO::DoUpdate(bool force)
{
	ZeroMemory(commandlist, sizeof(char)*MAXCOMMAND);
	if (mode == GAMEMODE_BUILDER)
	{
		return DoUpdateBuilder(force);
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
		list<length8> * pwordlist;
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

		for (list<length8>::iterator it=pwordlist->begin(); it!=pwordlist->end(); ++it)
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
	hge->Gfx_Clear(0x0);

#define RESULTLISTROW	5
#define RESULTLISTCOL	8

#define RESULTLISTROWB	12
#define RESULTLISTCOLB	4

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
					tbuff[0] = nowguess.word[i];
					if (!tbuff[0])
					{
						tbuff[0] = '_';
					}
					font->RenderEx(tbl.l8[i].rect.x, tbl.l8[i].rect.y, HGETEXT_CENTER|HGETEXT_MIDDLE, tbuff, 1.5f);
				}

			}
			else
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

			}


			if (!(mode == GAMEMODE_BUILDER && builderwords.size()))
			{
				for (int i=0; i<26; i++)
				{
					char strbuff[2];
					strbuff[0] = i + 'a';
					strbuff[1] = 0;

					font->SetColor(0xffffffff);
					if (mode == GAMEMODE_HANGING)
					{
						for (list<char>::iterator it=striked.begin(); it!=striked.end(); ++it)
						{
							if (strbuff[0] == *it)
							{
								font->SetColor(0xffff0000);
							}
						}
						for (int j=0; j<wordlength; j++)
						{
							if (strbuff[0] == nowguess.word[j])
							{
								font->SetColor(0xff00ff00);
							}
						}
					}

					font->Render(tbl.az[i].rect.x, tbl.az[i].rect.y, HGETEXT_CENTER|HGETEXT_MIDDLE, strbuff);
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
				for (list<length8>::iterator it=resultwords.begin(); it!=resultwords.end(); ++it)
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
			if (!(mode == GAMEMODE_BUILDER && builderwords.size()))
			{
				for (int i=0; i<26; i++)
				{
					_RenderFrame(&tbl.az[i].rect);
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
			if (mode == GAMEMODE_BUILDER && builderwords.size())
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
			if (mode == GAMEMODE_HANGING)
			{
				for (int i=0; i<TOUCH_TOUCHMAX; i++)
				{
					if (TouchButton::binding[i] && hge->Input_IsTouchOn(i))
					{
						float x = 0;
						float y = 0;
						hge->Input_GetTouchPos(i, &x, &y);
						char tbuff[2];
						tbuff[1] = 0;

						bool found = false;
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
				}
			}
		}
		font->SetScale(1.0f);
	}

	hge->Gfx_EndScene();
	return false;
}

void CheatsIO::_RenderFrame(RenderPos * rect, float edge /* = 1.0f */, int thick/* =2 */, float corner/* =2.0f */)
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
		_RenderFrame(&trect, edge, thick-1, corner);
	}
	float corneredge = edge+thick+corner;
	if (rect->w - 2*(corneredge) < 0 || rect->h - 2*(corneredge) < 0)
	{
		return;
	}
	float noncorneredge = thick+edge;
	DWORD col = 0xffffffff;

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

	char strbuffer[12];

	length8 buff8;

	while(!feof(fwords))
	{
		fscanf(fwords, "%s", strbuffer);
		if (feof(fwords))
		{
			break;
		}
		strcpy(buff8.word, strbuffer);
		switch (strlen(strbuffer))
		{
		case 4:
			l4words.push_back(buff8);
			break;
		case 5:
			l5words.push_back(buff8);
			break;
		case 6:
			l6words.push_back(buff8);
			break;
		case 7:
			l7words.push_back(buff8);
			break;
		case 8:
			l8words.push_back(buff8);
			break;

		}
	}

	fclose(fwords);
	return true;
}