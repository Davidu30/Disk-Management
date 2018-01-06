#include "Disk.h"
#pragma once
struct Record
{
	unsigned int key;
	char firstname[100];
	char lastName[100];
	char Id[11];
	unsigned int grade;
};

class TestLevel_3
{
	Disk D;
	FCB *f;
	void write();
	void read();
	void update(Record);
	void deleteRec();
	void printAll();
	void updateCancel();

public:
	TestLevel_3(void);

	~TestLevel_3(void);
};