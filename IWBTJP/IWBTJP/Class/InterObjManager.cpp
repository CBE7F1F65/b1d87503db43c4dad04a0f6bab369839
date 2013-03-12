#include "../Header/InterObjManager.h"

InterObjManager::InterObjManager()
{

}

InterObjManager::~InterObjManager()
{
	ClearAll();
}

void InterObjManager::PushObj( InterObj * pobj )
{
	lstObj.push_back(pobj);
	lstObj.sort(InterObj::CompareLessThan);

	if (pobj->GetRealm() == REALMFLAG_PLAYER)
	{
		lstPlayers.push_back((Player *)pobj);
	}
}

void InterObjManager::ClearAll()
{
	for (list<InterObj *>::iterator it=lstObj.begin(); it!=lstObj.end(); ++it)
	{
		delete *it;
	}
	lstObj.clear();

	lstPlayers.clear();
}

void InterObjManager::Update()
{
	for (list<InterObj *>::iterator it=lstObj.begin(); it!=lstObj.end(); ++it)
	{
		(*it)->Update();
	}
	for (list<Player *>::iterator it=lstPlayers.begin(); it!=lstPlayers.end(); ++it)
	{
		(*it)->PlayerUpdate();
	}
}

void InterObjManager::Render()
{
	for (list<InterObj *>::iterator it=lstObj.begin(); it!=lstObj.end(); ++it)
	{
		(*it)->Render();
	}
}
