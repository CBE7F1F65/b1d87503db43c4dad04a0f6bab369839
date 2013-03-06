#ifndef _GAMEINPUT_H
#define _GAMEINPUT_H

#include "MainDependency.h"

#define GAMEINPUTKEYMAX	14
#define GAMEINPUTJOYMAX	6
#define GAMEACTIVEINPUTMAX	8

#define KSI_UP		0
#define KSI_DOWN	1
#define KSI_LEFT	2
#define KSI_RIGHT	3
#define KSI_FIRE	4
#define KSI_JUMP	5
#define KSI_SUICIDE	6
#define KSI_SPECIAL	7
#define KSI_PAUSE	8
#define KSI_SKIP	9
#define KSI_RETRY	10
#define KSI_ENTER	11
#define KSI_ESCAPE	12
#define KSI_CAPTURE	13

#define KS_UP_(X)		gameinput[(X)].keyKS.keyUp
#define KS_DOWN_(X)		gameinput[(X)].keyKS.keyDown
#define KS_LEFT_(X)		gameinput[(X)].keyKS.keyLeft
#define KS_RIGHT_(X)	gameinput[(X)].keyKS.keyRight
#define KS_FIRE_(X)		gameinput[(X)].keyKS.keyFire
#define KS_JUMP_(X)		gameinput[(X)].keyKS.keyJump
#define KS_SUICIDE_(X)	gameinput[(X)].keyKS.keySuicide
#define KS_SPECIAL_(X)	gameinput[(X)].keyKS.keySpecial
#define KS_PAUSE_(X)	gameinput[(X)].keyKS.keyPause
#define KS_SKIP_(X)		gameinput[(X)].keyKS.keySkip
#define KS_RETRY_(X)	gameinput[(X)].keyKS.keyRetry
#define KS_ENTER_(X)	gameinput[(X)].keyKS.keyEnter
#define KS_ESCAPE_(X)	gameinput[(X)].keyKS.keyEscape
#define KS_CAPTURE_(X)	gameinput[(X)].keyKS.keyCapture

#define KS_UP		KS_UP_(0)
#define KS_DOWN		KS_DOWN_(0)
#define KS_LEFT		KS_LEFT_(0)
#define KS_RIGHT	KS_RIGHT_(0)
#define KS_FIRE		KS_FIRE_(0)
#define KS_JUMP		KS_JUMP_(0)
#define KS_SUICIDE	KS_SUICIDE_(0)
#define KS_SPECIAL	KS_SPECIAL_(0)
#define KS_RETRY	KS_RETRY_(0)
#define KS_PAUSE	KS_PAUSE_(0)
#define KS_SKIP		KS_SKIP_(0)
#define KS_ENTER	KS_ENTER_(0)
#define KS_ESCAPE	KS_ESCAPE_(0)
#define KS_CAPTURE	KS_CAPTURE_(0)

#define JS_FIRE_(X)				gameinput[(X)].keyJS.joyFire
#define JS_JUMP_(X)				gameinput[(X)].keyJS.joyJump
#define JS_SUICIDE_(X)			gameinput[(X)].keyJS.joySuicide
#define JS_SPECIAL_(X)			gameinput[(X)].keyJS.joySpecial
#define JS_PAUSE_(X)			gameinput[(X)].keyJS.joyPause
#define JS_RETRY_(X)			gameinput[(X)].keyJS.joyRetry
#define JS_DEBUG_SPEEDUP_(X)	gameinput[(X)].keyJS.debug_joySpeedUp

#define JS_FIRE		JS_FIRE_(0)
#define JS_JUMP		JS_JUMP_(0)
#define JS_SUICIDE	JS_SUICIDE_(0)
#define JS_SPECIAL	JS_SPECIAL_(0)
#define JS_PAUSE	JS_PAUSE_(0)
#define JS_RETRY	JS_RETRY_(0)
#define JS_DEBUG_SPEEDUP	JS_DEBUG_SPEEDUP_(0)

class GameInput
{
public:
	GameInput();
	~GameInput();
	static bool InitInput(HGE * hge);
	static bool ReleaseInput();
	static bool UpdateInput(bool startstate=false);
	WORD updateActiveInput(bool copylast=false);
	static void SyncControlInput();
	static void SyncControlInputSelf();
	static void SyncForActiveInput();
	static void SwapInput(bool setswap);
private:
	bool getKey(int ksi, int type=DIKEY_PRESSED);
	void setKey(int ksi, bool set=true);
public:
	static bool GetKey(BYTE playerindex, int ksi, int type=DIKEY_PRESSED);
	static void SetKey(BYTE playerindex, int ksi, bool set=true);

	static WORD GetNowInput();
	static void SetNowInput(WORD nowinput);
public:

	union{
		struct{
			int keyUp;
			int keyDown;
			int keyLeft;
			int keyRight;
			int keyFire;
			int keyJump;
			int keySuicide;
			int keySpecial;
			int keyPause;
			int keySkip;
			int keyRetry;
			int keyEnter;
			int keyEscape;
			int keyCapture;
		}		keyKS;
		int		keyKey[GAMEINPUTKEYMAX];
	};
	union{
		struct{
			int	joyFire;
			int	joyJump;
			int	joySuicide;
			int	joySpecial;
			int	joyPause;
			int	joyRetry;
			int debug_joySpeedUp;
		}		keyJS;
		int		joyKey[GAMEINPUTJOYMAX];
	};

	WORD activeInput;
	WORD lastActiveInput;
	WORD input;
	WORD lastInput;

	static HGE * hge;
	static GameInput gameinput[M_PL_MATCHMAXPLAYER];
	static bool swapinput;
};

#endif