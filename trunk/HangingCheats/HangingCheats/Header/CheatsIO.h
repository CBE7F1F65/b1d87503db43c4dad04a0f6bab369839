#include "MainDependency.h"

#define MAXCOMMAND 4
#define MAXBUILDERLETTER 13
#define MAXSCRAMBLELETTER 17

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
	void DoUpdateScramble(bool force=false);
	void DoClear();
	void ClearData();
	void ClearResult();

	char GetLetterScore(char letter);
	char GetLengthScore(char lenghth);

	void AppendLog(const char * logstr);

	void FillRenderPos();

	struct length16
	{
		char word[17];
	};
	char ScrambleNextAll(length16 *word, char * used, char index, char nowpos, char letterindex);

public:
	static CheatsIO cheatsio;

public:

	hgeFont * font;
	bool init;

	list<length16> l2words;
	list<length16> l3words;

	list<length16> l4words;
	list<length16> l5words;
	list<length16> l6words;
	list<length16> l7words;
	list<length16> l8words;

	list<length16> l9words;
	list<length16> l10words;
	list<length16> l11words;
	list<length16> l12words;
	list<length16> l13words;
	list<length16> l14words;
	list<length16> l15words;
	list<length16> l16words;

	length16 nowguess;
	char possiblech;
	list<char> striked;

	char commandlist[MAXCOMMAND];
	char wordlength;

	int possiblecount[26];
	float percentage[26];
	list<length16> resultwords;

	int logtimer;

#define GAMEMODE_HANGING	0
#define GAMEMODE_BUILDER	1
#define GAMEMODE_SCRAMBLE	2
	char mode;
	char builderletters[MAXBUILDERLETTER];

	char scrambleletters[MAXSCRAMBLELETTER];

	class BuilderWord
	{
	public:
		BuilderWord();
		~BuilderWord();

		length16 word;
		int score;
		char step[MAXSCRAMBLELETTER];
		bool operator < (const BuilderWord &right) const{return this->score < right.score;};
	};
	list<BuilderWord> builderwords;
	list<BuilderWord> scramblewords;
	char page;

#define MULST_DL	'%'
#define MULST_TL	'^'
#define MULST_DW	'&'
#define MULST_TW	'*'
char mulstate[MAXSCRAMBLELETTER];

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

		static TouchButton * binding[TOUCH_TOUCHMAX];
	};


#define RESULTLISTROWB	12
#define RESULTLISTCOLB	4
	struct TouchButtonList 
	{
		TouchButton az[27];

		TouchButton l8[8];
		TouchButton ll8[8];
		TouchButton guess;
		TouchButton results;

		TouchButton bline[2];
		TouchButton bresults;

		TouchButton sline[4];

		TouchButton changemode;
		TouchButton backspace;
		TouchButton clear;
		TouchButton enter;
		TouchButton pagedown;
		TouchButton pageup;

		TouchButton mul[4];

		TouchButton sdir[16];

		TouchButton sresults[RESULTLISTROWB*RESULTLISTCOLB];
	};

	TouchButtonList tbl;

	void _RenderFrame(RenderPos * rect, DWORD col=0xffffffff, float edge = 1.0f, int thick=2, float corner=2.0f);
	void _RenderLine(RenderPos * pos1, RenderPos * pos2, DWORD col=0xffffffff, float xoffset=0, float yoffset=0, int thick=2);

	bool mousedown;
	char nowpointingresult;

	char logstring[M_STRMAX];
	
	struct Touches {
		float x;
		float y;
		bool on;
	};
	Touches touches[TOUCH_TOUCHMAX];
};