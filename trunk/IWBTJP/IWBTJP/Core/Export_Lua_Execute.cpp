#include "../Header/Export_Lua_Execute.h"
#include "../Header/LuaConstDefine.h"
#include "../Header/BResource.h"

LuaFunction<bool> * Export_Lua_Execute::controlExecute;
LuaFunction<bool> * Export_Lua_Execute::stageExecute;
LuaFunction<bool> * Export_Lua_Execute::edefExecute;
LuaFunction<bool> * Export_Lua_Execute::sceneExecute;
LuaFunction<bool> * Export_Lua_Execute::functionExecute;
LuaFunction<bool> * Export_Lua_Execute::eventExecute;


bool Export_Lua_Execute::_LuaRegistConst(LuaObject * obj)
{
	int i = 0;
	/*
	char str[M_STRMAX];
	for (; scrKeyTable[i].code != SCR_CONST || strcmp(scrKeyTable[i].word, SCR_CONST_STR); i++)
	{
		sprintf(str, "%s%s", HDSS_PREFIX, scrKeyTable[i].word);
		_ChangeSpecialChar(str);
		obj->SetInteger(str, scrKeyTable[i].code);
	}
	i++;
	i++;	//true
	i++;	//false
	for (; scrKeyTable[i].code != SCR_KEYSTATE || strcmp(scrKeyTable[i].word, SCR_KEYSTATE_STR); i++)
	{
		obj->SetInteger(scrKeyTable[i].word, scrKeyTable[i].code);
	}
	i++;
	for (; scrKeyTable[i].code != SCR_NULL || strcmp(scrKeyTable[i].word, SCR_NULL_STR); i++)
	{
		obj->SetNumber(scrKeyTable[i].word, CUINT(scrKeyTable[i].code));
	}
	*/
	//SI
	for (i=0; i<BResource::PIns()->spritenumber; i++)
	{
		if (strlen(BResource::PIns()->spritedata[i].spritename))
		{
			obj->SetInteger(BResource::PIns()->spritedata[i].spritename, i);
		}
	}
	return true;
}

bool Export_Lua_Execute::_LuaRegistFunction(LuaObject * obj)
{
	/*
	LuaObject _hdssobj = obj->CreateTable("hdss");
	_hdssobj.Register("Call", LuaFn_HDSS_Call);
	_hdssobj.Register("Get", LuaFn_HDSS_Get);
	*/
	return true;
}


bool Export_Lua_Execute::InitCallbacks()
{
	LuaState * ls = state;
	LuaObject _obj = ls->GetGlobal(LUAFN_CONTROLEXECUTE);
	if (!_obj.IsFunction())
	{
		ShowError(LUAERROR_NOTFUNCTION, LUAFN_CONTROLEXECUTE);
		return false;
	}
	static LuaFunction<bool> _fcontrol = _obj;
	_fcontrol = _obj;
	controlExecute = &_fcontrol;
	_obj = ls->GetGlobal(LUAFN_STAGEEXECUTE);
	if (!_obj.IsFunction())
	{
		ShowError(LUAERROR_NOTFUNCTION, LUAFN_STAGEEXECUTE);
		return false;
	}
	static LuaFunction<bool> _fstage = _obj;
	_fstage = _obj;
	stageExecute = &_fstage;
	_obj = ls->GetGlobal(LUAFN_EDEFEXECUTE);
	if (!_obj.IsFunction())
	{
		ShowError(LUAERROR_NOTFUNCTION, LUAFN_EDEFEXECUTE);
		return false;
	}
	static LuaFunction<bool> _fedef = _obj;
	_fedef = _obj;
	edefExecute = &_fedef;
	_obj = ls->GetGlobal(LUAFN_SCENEEXECUTE);
	if (!_obj.IsFunction())
	{
		ShowError(LUAERROR_NOTFUNCTION, LUAFN_SCENEEXECUTE);
		return false;
	}
	static LuaFunction<bool> _fscene = _obj;
	_fscene = _obj;
	sceneExecute = &_fscene;
	_obj = ls->GetGlobal(LUAFN_FUNCTIONEXECUTE);
	if (!_obj.IsFunction())
	{
		ShowError(LUAERROR_NOTFUNCTION, LUAFN_FUNCTIONEXECUTE);
		return false;
	}
	static LuaFunction<bool> _ffunction = _obj;
	_ffunction = _obj;
	functionExecute = &_ffunction;
	_obj = ls->GetGlobal(LUAFN_EVENTEXECUTE);
	if (!_obj.IsFunction())
	{
		ShowError(LUAERROR_NOTFUNCTION, LUAFN_EVENTEXECUTE);
		return false;
	}
	static LuaFunction<bool> _fevent = _obj;
	_fevent = _obj;
	eventExecute = &_fevent;
	return true;
}

bool Export_Lua_Execute::Execute(DWORD typeflag, DWORD name, DWORD con)
{
	LuaState * ls = state;
	LuaFunction<bool> *_f;
	switch (typeflag)
	{
	case SCR_CONTROL:
		_f = controlExecute;
		break;
	case SCR_STAGE:
		_f = stageExecute;
		break;
	case SCR_EDEF:
		_f = edefExecute;
		break;
	case SCR_SCENE:
		_f = sceneExecute;
		break;
	case SCR_FUNCTION:
		_f = functionExecute;
		break;
	case SCR_EVENT:
		_f = eventExecute;
		break;
	}
	bool bret = (*_f)(name, con);
	if (state->CheckError())
	{
		Export_Lua::ShowError(LUAERROR_LUAERROR, state->GetError());
	}
	return bret;
}