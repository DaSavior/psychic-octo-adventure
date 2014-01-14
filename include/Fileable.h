#ifndef FILEABLE_H
#define FILEABLE_H

#include "Common.h"

class Fileable
{
public:
	virtual bool loadFromFile() =0;
	virtual bool saveTofile() =0;
};

#endif