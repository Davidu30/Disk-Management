#pragma once
#include "Fcb.h"
#include "Disk.h"
#include <vector>

class DMS
{
private:
	vector<FCB*> fcbArray;
	unsigned int fcbArrSize;
	unsigned int fcbMaxSize;
public:
	_declspec(dllexport) DMS(unsigned int = 5);
	_declspec(dllexport) ~DMS();
	_declspec(dllexport) FCB* openfile(Disk*, string&, string&, string&);
	_declspec(dllexport) void closefile(string&);
	_declspec(dllexport) FCB* getFile(unsigned int);
};

