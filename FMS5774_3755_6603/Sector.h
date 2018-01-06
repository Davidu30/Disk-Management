#pragma once
using namespace std;
typedef unsigned int uint;

struct Sector
{
	uint sectorNr;
	char rawData[1020];
};
