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
#include "Disk.h"
#include"RootDir.h"
#include "Dat.h"
using namespace std;
class Disk
{   
public:
	VolumeHeader vhd;
	RootDir rootdir;
	Dat dat;
	bool mounted;
	fstream dskfl;
	uint currDiskSectorNr;
	string lastErrorMessage;
	char buffer[sizeof(Sector)];
	
public:
	Disk(void);
	

	Disk(string & Disk_Name, string & Disk_Owner_Name, char Choice);

	~Disk(void);

	void createdisk(string DiskName, string OwnerName);
	string getCurrnetDate();

	void MountDisk(string );
	void seekToSector(uint SectorNumber);
	
	void readSector(Sector *s);

	void readSector(uint sectorNumber, Sector *s);
	
	void writeSector(Sector *s);
	
	void writeSector(uint SectorNumber,Sector * s);
	
	void UnmountDisk();
	
	void recreatedisk(string);
	
	fstream* getdskfl();
	
	
	
	//level 1
	void format(string  diskOwner);

	int HowMuchEmpty();

	void alloc(DATtype & Fat, uint SectorsNumber, uint algoType, int start);

	void allocextend(DATtype & Fat, uint SectorsNumber, uint algoType);

	void dealloc(DATtype &FAT);


protected:
	
public:
	virtual void createfile(string, string, string, uint, uint, string, uint, uint = 0, int = 0);
	void delfile(string, string);
	void extendfile(string, string, uint, uint);

	FCB* openfile(string, string, string);
	VolumeHeader getVolumeHeader();

	int findEOFSectorNr(FileHeader fhd);
	int findEntry(string fileName, bool& part1, bool& part2);
	string& GetLastErrorMessage() { return this->lastErrorMessage; }
	void SetLastErrorMessage(string lastErrorMessage) { this->lastErrorMessage = lastErrorMessage; }
	

	DirEntry GetEntry(bool part, int index);

	
};

