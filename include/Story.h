#ifndef STORY_H
#define STORY_H

#include "Common.h"
#include "ClassUtilities.h"

class Story: public Inputable
{
private:

public:
	Story();

	
	virtual bool loadFromFile();
	virtual bool saveTofile();
};

#endif