#pragma once
#include<fstream>
#include <iostream>
#include <ctime>
#include <string>
#include <sstream>
#include "VolumeHeader.h"
#include "Dat.h"
#include "Sector.h"
#include "FCB.h"
#include "DirEntry.h"
using namespace std;
typedef unsigned int uint;
class FileHeader
{

public:
	uint sectorNr;
	DirEntry fileDesc;
	DATtype FAT;
	char emptyArea[744];
};

