#include "../Header/BlockItem.h"
#include "../Header/InterObjManager.h"

BlockItem::BlockItem()
{
	SetRealm(REALMFLAG_BLOCKSIDE);
}

BlockItem::~BlockItem()
{

}
#include "../Header/Process.h"
void BlockItem::Update()
{
	__super::Update();
	
	InterObjManager * pim = InterObjManager::PIns();
	for (list<Player *>::iterator it=pim->lstPlayers.begin(); it!=pim->lstPlayers.end(); ++it)
	{
		Player * pplayer = *it;

		pplayer->CheckBlock(lBound, rBound, tBound, bBound);
	}
}

