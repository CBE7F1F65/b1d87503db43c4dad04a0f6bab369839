#include "../Header/Process.h"

#include "../Header/BlockItem.h"
#include "../Header/InterObjManager.h"
#include "../Header/InterObj.h"
#include "../Header/BGItem.h"

#include "../Header/Player.h"

void Process::Debug_Test()
{

	BGItem * pbgi = new BGItem();
	pbgi->SetBaseSIID(1);
	pbgi->SetPos(0, 0);
	pbgi->SetScale(screenwidth, screenheight);
	pbgi->SetDepth(OBJLAYER_BG_DEEP);
	pbgi->SetColor(0xc3d7f7);
	InterObjManager::PIns()->PushObj(pbgi);

	Player * pplayer = new Player();
	pplayer->SetPos(10000, 30000);
	InterObjManager::PIns()->PushObj(pplayer);

	BlockItem * pbi;

	for (int i=0; i<10; i++)
	{
		pbi = new BlockItem();
		pbi->SetBaseSIID(50);
		pbi->SetPos(10000+i*3200, 40000);
		pbi->SetBoundingBox(0, 0, 1600, 1600);
		pbi->SetDepth(OBJLAYER_BLOCK);
		InterObjManager::PIns()->PushObj(pbi);

		pbi = new BlockItem();
		pbi->SetBaseSIID(50);
		pbi->SetPos(15000+i*3200, 27200);
		pbi->SetBoundingBox(0, 0, 1600, 1600);
		pbi->SetDepth(OBJLAYER_BLOCK);
		InterObjManager::PIns()->PushObj(pbi);
	}
	pbgi = new BGItem();
	pbgi->SetBaseSIID(100);
	pbgi->SetPos(15000, 23200);
	pbgi->SetDepth(OBJLAYER_BG_SHALLOW);
	InterObjManager::PIns()->PushObj(pbgi);
}