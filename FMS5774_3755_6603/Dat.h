#pragma once
#pragma once
using namespace std;
#include <bitset>
typedef bitset<1600> DATtype;
typedef unsigned int uint;
class Dat
{public:
	uint sectorNr;
	DATtype data;
	char emptyArea[816];

//	Dat();
//	~Dat();
};

