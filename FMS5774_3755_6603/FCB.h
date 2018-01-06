#pragma once
using namespace std;
#include "DirEntry.h"
#include <bitset>
#include "Sector.h"
#include "FileHeader.h"
typedef bitset<1600> DATtype;
class disk;
class FCB
{
	friend class DMS;
	friend class Disk;

	Disk* d;
	DirEntry fileDesc;
	DATtype FAT;
	Sector Buffer;
	uint currRecNr;
	uint currSecNr;
	uint currRecNrInBuff;
	bool isOpen;
	string format;
	bool lock;
	string lastErrorMessage;

public:
	FCB(void);
	FCB(Disk*);
	~FCB(void);
	void closefile();
	void flushfile();
	void read(char * record, bool readForUpdate);
	void write(char* record);
	void seek(uint, int );
	void updateCancel();
	void deleteRec();
	void updateRec(char* record);

	int findCurrnetSector();
	string& GetLastErrorMessage() { return this->lastErrorMessage; }
	void SetLastErrorMessage(string lastErrorMessage) { this->lastErrorMessage = lastErrorMessage; }

};