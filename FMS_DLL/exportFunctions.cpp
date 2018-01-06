#pragma once
#include "Disk.h"
#include "FCB.h"
#include <string>       
#include <iostream>     
#include <sstream>     
#include<fstream>

extern "C"
{


	__declspec(dllexport) Disk*  makeDiskObject()
	{
		return new Disk;
	}
	__declspec(dllexport) void  deleteDiskObject(Disk*& THIS)
	{
		if (THIS != NULL)
			delete  THIS;
		THIS = NULL;
	}
	__declspec(dllexport) const  char*  getLastDiskErrorMessage(Disk* THIS)
	{ 
		const char* str = THIS->GetLastErrorMessage().c_str();
		return  str;
		
	}

	__declspec(dllexport) void  deleteFcbObject(FCB*& THIS)
	{
		if (THIS != NULL)
			delete  THIS;
		THIS = NULL;
	}
	__declspec(dllexport) const  char*  getLastFcbErrorMessage(FCB* THIS)
	{
		const char* str = THIS->GetLastErrorMessage().c_str();
		return str;
	}

	// Level 0
	__declspec(dllexport) void  createdisk(Disk* THIS, char* diskName, char* diskOwner)
	{
		try
		{
			
			THIS->createdisk(diskName, diskOwner);
		}
		catch (exception ex)
		{
			THIS->SetLastErrorMessage(ex.what());
			throw ex;
		}
	}
	__declspec(dllexport) void  mountdisk(Disk* THIS, char* diskName)
	{
		try
		{
			THIS->MountDisk(diskName);
		}
		catch (exception ex)
		{
			THIS->SetLastErrorMessage(ex.what());
			throw ex;
		}
	}
	__declspec(dllexport) void  unmountdisk(Disk* THIS)
	{
		try
		{
			THIS->UnmountDisk();
		}
		catch (exception ex)
		{
			THIS->SetLastErrorMessage(ex.what());
			throw ex;
		}
	}
	__declspec(dllexport) void  recreatedisk(Disk* THIS, char* diskOwner)
	{
		try
		{
			THIS->recreatedisk(diskOwner);
		}
		catch (exception ex)
		{
			THIS->SetLastErrorMessage(ex.what());
			throw ex;
		}
	}

	// Level 1
	__declspec(dllexport) void  format(Disk* THIS, char* diskOwner)
	{
		try
		{
			THIS->format(diskOwner);
		}
		catch (exception ex)
		{
			THIS->SetLastErrorMessage(ex.what());
			throw ex;
		}
	}
	__declspec(dllexport) int   howmuchempty(Disk* THIS)
	{
		try
		{
			return THIS->HowMuchEmpty();
		}
		catch (exception ex)
		{
			THIS->SetLastErrorMessage(ex.what());
			throw ex;
		}
	}

	//Level 2
	__declspec(dllexport) void  createfile(Disk* THIS, char* fileName, char* fileOwner, char* FinalOrVar,
		unsigned int recSize, unsigned int fileSize,
		char* keyType, unsigned int keyOffset, unsigned int keySize, unsigned int algoType)
	{
		try
		{
			THIS->createfile(fileName, fileOwner, FinalOrVar,
				recSize, fileSize,
				keyType, keyOffset, keySize, algoType);
		}
		catch (exception ex)
		{
			THIS->SetLastErrorMessage(ex.what());
			throw ex;
		}
	}

	__declspec(dllexport) void  delfile(Disk* THIS, char* fileName, char* fileOwner)
	{
		try
		{
			THIS->delfile(fileName, fileOwner);
		}
		catch (exception ex)
		{
			THIS->SetLastErrorMessage(ex.what());
			throw ex;
		}
	}
	__declspec(dllexport) void  extendfile(Disk* THIS, char* fileName, char* fileOwner, unsigned int size, unsigned int AlgoType)
	{
		try
		{
			THIS->extendfile(fileName, fileOwner, size, AlgoType);
		}
		catch (exception ex)
		{
			THIS->SetLastErrorMessage(ex.what());
			throw ex;
		}
	}


	// Level 3
	__declspec(dllexport)  FCB *  openfile(Disk* THIS, char* fileName, char* fileOwner, char* openMode)
	{
		try
		{
			return THIS->openfile(fileName, fileOwner, openMode);
		}
		catch (exception ex)
		{
			THIS->SetLastErrorMessage(ex.what());
			throw ex;
		}
	}


	// FCB
	__declspec(dllexport) void  closefile(FCB* THIS)
	{
		try
		{
			THIS->closefile();
		}
		catch (exception ex)
		{
			THIS->SetLastErrorMessage(ex.what());
			throw ex;
		}
	}
	__declspec(dllexport) void  readRec(FCB* THIS, char * dest, bool readForUpdate)
	{
		try
		{
			THIS->read(dest, readForUpdate);
		}
		catch (exception ex)
		{
			THIS->SetLastErrorMessage(ex.what());
			throw ex;
		}
	}
	__declspec(dllexport) void  writeRec(FCB* THIS, char * source)
	{
		try
		{
			THIS->write(source);
		}
		catch (exception ex)
		{
			THIS->SetLastErrorMessage(ex.what());
			throw ex;
		}
	}
	__declspec(dllexport) void  seekRec(FCB* THIS, unsigned int from, int pos)
	{
		try
		{
			THIS->seek(from, pos);
		}
		catch (exception ex)
		{
			THIS->SetLastErrorMessage(ex.what());
			throw ex;
		}
	}

	__declspec(dllexport) void  updateRecCancel(FCB* THIS)
	{
		try
		{
			THIS->updateCancel();
		}
		catch (exception ex)
		{
			THIS->SetLastErrorMessage(ex.what());
			throw ex;
		}
	}
	__declspec(dllexport) void  deleteRec(FCB* THIS)
	{
		try
		{
			THIS->deleteRec();
		}
		catch (exception ex)
		{
			THIS->SetLastErrorMessage(ex.what());
			throw ex;
		}
	}
	__declspec(dllexport) void  updateRec(FCB* THIS, char * source)
	{
		try
		{
			THIS->updateRec(source);
		}
		catch (exception ex)
		{
			THIS->SetLastErrorMessage(ex.what());
			throw ex;
		}
	}

	__declspec(dllexport)   void  getVolumeHeader(Disk* THIS, VolumeHeader* buffer)
	{
		memcpy_s(buffer, sizeof(VolumeHeader), &THIS->getVolumeHeader(), sizeof(VolumeHeader));
	}

	__declspec(dllexport) void GetEntry(Disk* THIS, DirEntry* buffer, bool part, int index)
	{
		try
		{
			memcpy_s(buffer, sizeof(DirEntry), &THIS->GetEntry(part, index), sizeof(DirEntry));
		}
		catch (exception ex)
		{
			THIS->SetLastErrorMessage(ex.what());
			throw ex;
		}
	}

}