#ifndef _EXPORT_LUA_EXECUTE_H
#define _EXPORT_LUA_EXECUTE_H


#define SCRIPT_CTOFFSET	0xA000
enum{
	SCR_TYPEBEGIN	= 0xAFFFAA00,

	SCR_SCRIPTTAG	= 0xAFFFAB00,

	SCR_FILENAME	= 0xAFFFAC10,
	SCR_BLOCKCON	= 0xAFFFAC20,

	SCR_CONTROL		= 0xAFFFAD10,
	SCR_STAGE		= 0xAFFFAD20,
	SCR_EDEF		= 0xAFFFAD40,
	SCR_SCENE		= 0xAFFFAD80,
	SCR_FUNCTION	= 0xAFFFAE10,
	SCR_EVENT		= 0xAFFFAE20,

	SCR_CTCONTROL	= SCR_CONTROL - SCRIPT_CTOFFSET,
	SCR_CTSTAGE		= SCR_STAGE - SCRIPT_CTOFFSET,
	SCR_CTEDEF		= SCR_EDEF - SCRIPT_CTOFFSET,
	SCR_CTSCENE		= SCR_SCENE - SCRIPT_CTOFFSET,
	SCR_CTFUNCTION	= SCR_FUNCTION - SCRIPT_CTOFFSET,
	SCR_CTEVENT		= SCR_EVENT - SCRIPT_CTOFFSET,

	SCR_NULL		= 0xAFFFAF00,
	SCR_CONST		= 0xAFFFAF10,
	SCR_KEYSTATE	= 0xAFFFAF20,
};

#include "Export_Lua.h"

class Export_Lua_Execute : public Export_Lua
{
public:
	static bool _LuaRegistConst(LuaObject * obj);
	static bool _LuaRegistFunction(LuaObject * obj);

	static bool InitCallbacks();
	static bool Execute(DWORD typeflag, DWORD name, DWORD con);

public:
	static LuaFunction<bool> * controlExecute;
	static LuaFunction<bool> * stageExecute;
	static LuaFunction<bool> * edefExecute;
	static LuaFunction<bool> * sceneExecute;
	static LuaFunction<bool> * functionExecute;
	static LuaFunction<bool> * eventExecute;
};

#endif