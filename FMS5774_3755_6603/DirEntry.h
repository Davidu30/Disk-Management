#pragma once
typedef unsigned int uint;
typedef unsigned char uchar;
class DirEntry
{
public:
	char FileName[12];
	char fileOwner[12];
	uint fileAddr;
	char crDate[10];
	uint fileSize;
	uint eofRecNr;
	uint maxRecSize;
	uint actualRecSize;
	char recFormat[2];
	uint keyOffset;
	uint keySize;
	char keyType[2];
	uchar entryStatus;
};

