#include "../Header/BGItem.h"

BGItem::BGItem()
{
	SetRealm(REALMFLAG_EMPTYSIDE);
}

BGItem::~BGItem()
{

}

void BGItem::Update()
{
	++timer;
	DoAnimation();
}
