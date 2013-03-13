#ifndef _EXPORT_LUA_GAME_H
#define _EXPORT_LUA_GAME_H

#include "Export_Lua.h"

class Export_Lua_Game : Export_Lua
{
public:
	static bool _LuaRegistConst(LuaObject * obj);
	static bool _LuaRegistFunction(LuaObject * obj);

	static int LuaFn_Game_Random_Int(LuaState * ls);
	static int LuaFn_Game_Random_Float(LuaState * ls);

	static int LuaFn_Game_LoadTexture(LuaState * ls);
	static int LuaFn_Game_FreeTexture(LuaState * ls);
};

#endif