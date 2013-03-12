#pragma once

#include "InterObj.h"
#include "Player.h"

class InterObjManager
{
public:
	static InterObjManager * PIns() { static InterObjManager instance; return &instance; }

private:
	InterObjManager();
	~InterObjManager();
	InterObjManager(InterObjManager const&);
	void operator=(InterObjManager const&);


public:
	list<InterObj *> lstObj;

	list<Player *> lstPlayers;

	void PushObj(InterObj * pobj);
	void ClearAll();

	void Update();
	void Render();
};