LGlobal_MessageBoxCount	=	{}

_DEBUG_LGlobal_Jump	=	-1;
_DEBUG_MatchAndLog	=	0;

function LGlobal_CallMessageBoxOnce(content, title, indi)
	if indi == nil then
		indi = 1;
	end
	if LGlobal_MessageBoxCount[indi] == nil or hge.Input_GetDIKey(DIK_DELETE, DIKEY_DOWN) then
		LGlobal_MessageBoxCount[indi] = 0;
	end
	if LGlobal_MessageBoxCount[indi] > 0 then
		return 0;
	end
	LGlobal_MessageBoxCount[indi] = LGlobal_MessageBoxCount[indi] + 1;
	return LGlobal_CallMessageBox(content, title);
end

function LGlobal_CallMessageBox(content, title)
	content = tostring(content);
	title = tostring(title);
	return global.MessageBox(content, title);
end

MB	=	LGlobal_CallMessageBoxOnce;
MBA	=	LGlobal_CallMessageBox;
LOG	=	hge.System_Log;

RANDT	=	game.Random_Int;
RANDTF	=	game.Random_Float;