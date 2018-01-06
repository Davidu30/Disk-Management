#include "DMS.h"



DMS::DMS(unsigned int size)
{
	fcbArray = vector<FCB*>();
	fcbMaxSize = size;
	fcbArrSize = 0;
}


DMS::~DMS()
{
	for (vector<FCB*>::iterator it = fcbArray.begin(); it != fcbArray.end(); ++it)
		if (*it != NULL)
			delete *it;

}

FCB * DMS::openfile(Disk * d, string& fileName, string & userName, string & openType)
{
	if (fcbArrSize < fcbMaxSize)
	{
		for (vector<FCB*>::iterator it = fcbArray.begin(); it != fcbArray.end(); ++it)
		{
			if (*it != NULL && (*it)->fileDesc.FileName == fileName)
				throw "File already opened";
		}
		fcbArray.push_back(d->openfile(fileName, userName, openType));
		return fcbArray[fcbArrSize++];
	}
	else
		throw "Too much files open";
}

void DMS::closefile(string & fileName)
{
	vector<FCB*>::iterator it;
	bool Found = false;
	for (it = fcbArray.begin(); it != fcbArray.end(); ++it)
	{
		if (*it != NULL && (*it)->fileDesc.FileName == fileName)
		{
			Found = true;
			break;
		}
	}
	if (!Found)
		throw "File does'nt exsist";

	(*it)->closefile();
	fcbArray.erase(it);
	fcbArrSize--;
}

FCB * DMS::getFile(unsigned int num)
{
	if (num < 0 || num > fcbArrSize - 1)
		return nullptr;
	return fcbArray[num];
}
