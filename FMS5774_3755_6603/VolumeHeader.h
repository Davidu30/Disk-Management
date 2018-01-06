#pragma once
using namespace std;
typedef unsigned int uint;
class VolumeHeader
{
public:
	uint sectorNr;
	char diskName[12];
	char diskOwner[12];
	char prodDate[11];
	uint ClusQty;
	uint dataClusQty;
	uint addrDAT;
	uint addrRootDir;
	uint addrDATcpy;
	uint addrRootDirCpy;
	uint addrDataStart;
	char formatDate[11];
	bool isFormatted;
	char emptyArea[942];

	VolumeHeader();
	~VolumeHeader();
};

