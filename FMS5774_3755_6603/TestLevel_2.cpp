#include "TestLevel_2.h"
#include "FileHeader.h"



TestLevel_2::TestLevel_2(void)
{
	try
	{
		d.createdisk("testlevel_2.txt", "David");
		d.MountDisk("testlevel_2.txt");
		d.format("David");
		this->addfile("students", "David");
		this->addfile("lecturs", "David");
		this->print();

		this->extendfile("students", "David");

		cout << "After 'students' was extended\n\n";
		this->print();
		this->deleteFile("students", "David");
		cout << "After students was deleted\n\n";
		this->print();
	}
	catch (char* error)
	{
		cout << error;
	}
}

void TestLevel_2::addfile(string fileName, string ownerName)
{
	d.createfile(fileName, ownerName, "F", 100, 80, "C", 10, 10, 1);
}
void TestLevel_2::print()
{
	FileHeader F;
	FileHeader* header = &F;

	for (int i = 0;i<14;i++)
	{
		if (d.rootdir.Part1.dirEntry[i].entryStatus == '1')
		{
			this->d.readSector(d.rootdir.Part1.dirEntry[i].fileAddr, (Sector*)header);
			cout << d.rootdir.Part1.dirEntry[i].crDate << endl;
			cout << d.rootdir.Part1.dirEntry[i].FileName << endl;
			cout << d.rootdir.Part1.dirEntry[i].fileOwner << endl;
			cout << "file size " << d.rootdir.Part1.dirEntry[i].fileSize << endl;
			cout << "File address " << d.rootdir.Part1.dirEntry[i].fileAddr << endl;

			cout << "******************************************************************************\n";

		}
	}
	for (int i = 0;i<14;i++)
	{
		if (d.rootdir.Part2.dirEntry[i].entryStatus == '1')
		{
			this->d.readSector(d.rootdir.Part2.dirEntry[i].fileAddr, (Sector*)header);
			cout << d.rootdir.Part2.dirEntry[i].crDate << endl;
			cout << d.rootdir.Part2.dirEntry[i].FileName << endl;
			cout << d.rootdir.Part2.dirEntry[i].fileOwner << endl;
			cout << "file size " << d.rootdir.Part2.dirEntry[i].fileSize << endl;
			cout << "File address " << d.rootdir.Part2.dirEntry[i].fileAddr << endl;

			cout << "******************************************************************************\n";

		}

	}
}
void TestLevel_2::extendfile(string nameOfFile, string ownerName)
{
	d.extendfile(nameOfFile, ownerName, 23, 1);
}
void TestLevel_2::deleteFile(string nameofFile, string ownerName)

{
	d.delfile(nameofFile, ownerName);
}