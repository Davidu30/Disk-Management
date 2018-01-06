#pragma once
#include "DirEntry.h"

class SectorDir
{
public:
	int sectorNr;
	DirEntry dirEntry[14];
	char unUse[12];

};