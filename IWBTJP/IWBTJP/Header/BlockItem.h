#pragma once

#include "InterObj.h"

class BlockItem : public InterObj
{
public:
	BlockItem();
	~BlockItem();

	virtual void Update();
};