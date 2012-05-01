#include "MainDependency.h"

#define MAXCOMMAND 4
#define MAXBUILDERLETTER 13

class CheatsIO
{
public:
	CheatsIO();
	~CheatsIO();

	void Release();

	bool FrameFunc();
	bool RenderFunc();

	bool ReadWordsFile(const char * filename);

	bool TouchToCommand(bool * force);

	void UpdateInput();
	bool GetInputCommand();
	bool DispatchInput(bool force=false);

	void DoUpdate(bool force=false);
	void DoUpdateBuilder(bool force=false);
	void DoClear();
	void ClearData();
	void ClearResult();

	char GetLetterScore(char letter);

	void AppendLog(const char * logstr);

	void FillRenderPos();

	struct length8
	{
		char word[9];
	};

public:
	static CheatsIO cheatsio;

public:

	hgeFont * font;
	bool init;

	list<length8> l4words;
	list<length8> l5words;
	list<length8> l6words;
	list<length8> l7words;
	list<length8> l8words;

	length8 nowguess;
	char possiblech;
	list<char> striked;

	char commandlist[MAXCOMMAND];
	char wordlength;

	int possiblecount[26];
	float percentage[26];
	list<length8> resultwords;

	int logtimer;

#define GAMEMODE_HANGING	0
#define GAMEMODE_BUILDER	1
#define GAMEMODE_SCRAMBLE	2
	char mode;
	char builderletters[MAXBUILDERLETTER];

	class BuilderWord
	{
	public:
		BuilderWord();
		~BuilderWord();

		length8 word;
		char score;
		bool operator < (const BuilderWord &right) const{return this->score < right.score;};
	};
	list<BuilderWord> builderwords;
	char page;

	struct RenderPos
	{
		float x;
		float y;
		float w;
		float h;
	};


	class TouchButton
	{
	public:
		TouchButton();
		~TouchButton();

		bool IsInRect(float x, float y);

		RenderPos rect;
		bool active;
		bool touchdown;

		static TouchButton * binding[TOUCH_TOUCHMAX];
	};


	struct TouchButtonList 
	{
		TouchButton az[26];

		TouchButton l8[8];
		TouchButton guess;
		TouchButton results;

		TouchButton bline[2];
		TouchButton bresults;

		TouchButton changemode;
		TouchButton backspace;
		TouchButton clear;
		TouchButton enter;
		TouchButton pagedown;
		TouchButton pageup;
	};

	TouchButtonList tbl;

	void _RenderFrame(RenderPos * rect, float edge = 1.0f, int thick=2, float corner=2.0f);

	bool mousedown;

	char logstring[M_STRMAX];
};