#pragma once
#include "Disk.h"
class TestLevel1
{
	DATtype fat;
	Disk d;
public:
	void printDat();
	void alocations();
	TestLevel1();
	~TestLevel1();
	void extend();
};

