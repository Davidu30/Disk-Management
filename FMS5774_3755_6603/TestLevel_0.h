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
#include "FileHeader.h"
#include "RootDir.h"
#include "SectorDir.h"
using namespace std;

class TestLevel_0
{
public:
	static void printStructSize()
	{
		cout << "start" << endl;
		cout << "Size Of Disk -->" << sizeof(Disk) << endl;
		cout << "Size Of Sector -->" << sizeof(Sector) << endl;
		cout << "Size Of VolumeHeader -->" << sizeof(VolumeHeader) << endl;
		cout << "Size Of DAT -->" << sizeof(Dat) << endl;
		cout << "Size Of DirEntry -->" << sizeof(DirEntry) << endl;
		cout << "Size Of SectorDir -->" << sizeof(SectorDir) << endl;
		cout << "Size Of FileHeader -->" << sizeof(FileHeader) << endl;

		cout << "Size Of RootDir -->" << sizeof(RootDir) << endl;
	}

	static void printDiskInfo(Disk& d)
	{
		VolumeHeader* vh = &d.vhd;

		cout << "	disk name:        " << vh->diskName << endl;
		cout << "	Owner Name:       " << vh->diskOwner << endl;
		cout << "	prodDate:         " << vh->prodDate << endl;
		cout << "	formatDate:       " << vh->formatDate << endl;
		cout << "	isFormated:       " << vh->isFormatted << endl;
		cout << "	addrDataStart:    " << vh->addrDataStart << endl;

		cout << "	ClusQty:          " << vh->ClusQty << endl;
		cout << "	dataClusQty:      " << vh->dataClusQty << endl;

		cout << "	addrDAT:          " << vh->addrDAT << endl;
		cout << "	addrRootDir:      " << vh->addrRootDir << endl;
		cout << "	addrDATcpy:       " << vh->addrDATcpy << endl;
		cout << "	addrRootDirCpy:   " << vh->addrRootDirCpy << endl << endl;

	}

	static void test_create(string diskName, string ownerName)
	{
		Disk d;
		cout << "\npre createdisk: " << endl;
		printDiskInfo(d);
		cout << "post createdisk: " << endl;
		d.createdisk(diskName, ownerName);
		printDiskInfo(d);
	}

	static void test_mount(string diskName)
	{
		Disk d;
		cout << "\npre mountdisk: " << endl;
		printDiskInfo(d);
		d.MountDisk(diskName);
		cout << "post mountdisk: " << endl;
		printDiskInfo(d);
		d.UnmountDisk();
	}


	static void test_rwSector(string diskName)
	{
		Disk d;
		Sector sector;
		d.MountDisk(diskName);

		cout << "\nread sector: " << endl;
		d.readSector(8, &sector);
		strcpy_s(sector.rawData, "this is write temp sector");
		d.writeSector(8, &sector);
		d.UnmountDisk();

	}

public:
	static void test_0()
	{
		try
		{
			string diskName = "disk 1";
			string ownerName = "oshri";

			printStructSize();
			test_create(diskName, ownerName);
			test_mount(diskName);
		}
		catch (exception ex)
		{
			cout << ex.what() << endl;
		}
	}
};
