#pragma once
#include "Disk.h"
class TestLevel_2
{
	Disk d;
	void print();
	void addfile(string nameFile, string nameOwner);
	void extendfile(string nameFile, string nameOwner);
	void deleteFile(string fileName, string owner);
public:
	TestLevel_2();

	
};

