#pragma once
#include "Disk.h"
#include"RootDir.h"
#include "FileHeader.h"

#pragma region level 0
/// <name>
/// constructor with out parameters
/// </name>
/// <summary>
/// constructor with out parameters-Update fields of disk
/// </summary>
Disk::Disk()
{
	//update all the fields
	string a = "";
	strncpy_s((this->vhd).diskName, "", sizeof(vhd.diskName));
	strncpy_s((this->vhd).diskOwner, "", sizeof(vhd.diskOwner));
	strncpy_s((this->vhd).formatDate, "", sizeof(vhd.formatDate));
	strncpy_s((this->vhd).prodDate, "", sizeof(vhd.prodDate));
	vhd.isFormatted = false;
	vhd.addrDataStart = 0;
	vhd.addrDATcpy = 0;
	vhd.ClusQty = 0;
	vhd.dataClusQty = 0;
	vhd.addrDAT = 0;
	vhd.addrRootDir = 0;
	vhd.addrRootDirCpy = 0;
	this->mounted = false;
	currDiskSectorNr = 0;
}

/// <name>
/// constructor with 3 parameters
/// </name>
/// <summary>
/// constructor with 3 parameters-The role of this constructor to initialize an object of type disk
/// </summary>
/// <param name="DiskName">Name of disk</param>
/// <param name="OwnerName">The name of the owner</param>
/// <param name="C">Variable to choose whether to createdisk and mountdisk or mountdisk only</param>
Disk::Disk(string & Disk_Name, string & Disk_Owner_Name, char Choice) {
	switch (Choice)
	{
	case 'c':
		createdisk(Disk_Name, Disk_Owner_Name);
		MountDisk(Disk_Name);
		break;
	case 'm':
		MountDisk(Disk_Name);
		break;
	default:
		if (Choice != 'c'&& Choice != 'm')
		{
			throw exception("invalid choice");	
		}
		break;
	}
}
/// <name>
/// createdisk-2 parameters
/// </name>
/// <summary>
/// The role of this function is to create a virtual disk(unmounted)
/// </summary>
/// <param name="DiskName">Name of disk</param>
/// <param name="OwnerName">The name of the owner</param>
void Disk:: createdisk(string Disk_Name, string Owner_Name)
{
# pragma region update of sector

	memcpy((this->vhd).diskName, Disk_Name.c_str(), sizeof(vhd.diskName));
	vhd.diskName[sizeof(vhd.diskName) - 1] = NULL;
	strncpy_s((this->vhd).diskOwner, Owner_Name.c_str(), sizeof(vhd.diskOwner));
	vhd.diskOwner[sizeof(vhd.diskOwner) - 1] = NULL;
	strncpy_s( vhd.prodDate, getCurrnetDate().c_str(),sizeof(vhd.formatDate));
	strncpy_s((this->vhd).prodDate, getCurrnetDate().c_str(), sizeof(vhd.prodDate));
	vhd.prodDate[sizeof(vhd.prodDate) - 1] = NULL;
	vhd.isFormatted = false;
	vhd.addrDataStart =4;
	vhd.addrDATcpy = 3198;
	vhd.ClusQty = 1600;
	vhd.dataClusQty =1596;
	vhd.addrDAT = 1;
	vhd.addrRootDir = 2;
	vhd.addrRootDirCpy = 3196;
	currDiskSectorNr = 0;
#pragma endregion
#pragma region check if the file exist
	
	
	if (ifstream(Disk_Name.c_str()))
	{
		throw exception("File already exist! \n");
	}
	
#pragma endregion
#pragma region 
	fstream toFile;
	toFile.open(Disk_Name.c_str(),ios::trunc | ios::out | ios::binary);
	toFile.seekp(0);
	toFile.write((char*)&vhd, sizeof(Sector));
	Sector S;
	for (int i = 1; i < 3200; i++)
	{
		S.sectorNr = i;
		toFile.write((char*)&S, sizeof(Sector));
	}
	toFile.close();


#pragma endregion
}
/// <name>
/// getCurrnetDate-0 parameters
/// </name>
/// <summary>
/// The role of this function is to find the current date
/// </summary>
/// <return>current date</return>
string Disk::getCurrnetDate()//îöéàú úàøéê ðåëçé
{
	string s1 = "", s2 = "";
	time_t curr = time(0);
	tm local;
	localtime_s(&local, &curr);
	stringstream temp;
	/*if (local.tm_mday <10)
		s1 = "0";
	if (local.tm_mon + 1 <10)
		s2 = "0";*/
	temp << s1 << local.tm_mday << "/" << s2 << local.tm_mon + 1 << "/" << local.tm_year + 1900;
	return temp.str();
}
/// <name>
/// mountdisk-1 parameters
/// </name>
/// <summary>
/// The role of this function-open the file who exercises the virtual disk
/// </summary>
/// <param name="diskName">Name of disk</param>
void Disk::MountDisk(string  diskName)//mount data to virtual disk
{
	dskfl.open(diskName, ios::in | ios::out | ios::binary);//ôúçú ä÷åáõ
	if (dskfl) {
		mounted = true;
		readSector(0, (Sector*)&vhd);
		readSector((Sector*)&dat);
		
	}
	else
	{
		throw exception("can not open file \n");
	}
}
/// <name>
/// unmountdisk-0 parameters
/// </name>
/// <summary>
/// The role of this function is to update all the sectors that contain structural information of the virtual disk,
/// close the file of the virtual disk and to compare field mounted the value false
/// </summary>
void Disk::UnmountDisk() {
	if (mounted)
	{
		if (!dskfl)
			throw exception("cannot open file \n");
# pragma region 
		writeSector(0, (Sector*)&vhd);
		writeSector((Sector*)&dat);


		writeSector(3198, (Sector*)&dat); //âéáåé
		dskfl.close();
#pragma endregion

		mounted = false;
	}
	else //if the file is unmounted before
	{
		throw exception("the file is unmounted before \n");
	}
}

/// <name>
/// seekToSector-1 parameters
/// </name>
/// <summary>
/// The role of this function to locate specific sector
/// </summary>
/// <param name="SectorNumber">The serial number of the virtual disk specific sector</param>
void Disk::seekToSector(uint SectorNumber)
{
	dskfl.seekp(SectorNumber*sizeof(Sector));
}

/// <name>
/// readSector-1 parameters
/// </name>
/// <summary>
/// The role of this function is to read the current sector from the virtual disk into the buffer pointed to the parameter
/// </summary>
/// <param name="s">pointer to buffer(length of sector)</param>
void Disk::readSector(Sector *s) {
	if (!dskfl)
	{
		throw exception("file not found \n");
	}
	dskfl.read((char*)s, sizeof(Sector));
	currDiskSectorNr++;
}

/// <name>
/// readSector-2 parameters
/// </name>
/// <summary>
/// The role of this function is to read the sector requested from the virtual disk into the buffer pointed to the second parameter
/// </summary>
/// <param name="SectorNumber">The serial number of the virtual disk specific sector</param>
/// <param name="s">pointer to buffer(length of sector)</param>
void Disk::readSector(uint sectorNumber, Sector *s) {
	if (sectorNumber < 0 || sectorNumber > 3199)
	{
		throw exception("out of limit!!");
	}
	seekToSector(sectorNumber);
	currDiskSectorNr = sectorNumber;
	readSector(s);
}
/// <name>
/// writeSector-1 parameters
/// </name>
/// <summary>
/// The role of this function write buffers pointed to the parameter into the virtual disk current sector
/// </summary>
/// <param name="s">pointer to buffer(length of sector)</param>
void Disk::writeSector(Sector *s) {

	if (!dskfl)
	{
		throw exception("there is no file \n");
	}
	else
	{
		dskfl.write((char*)s, sizeof(Sector));
		currDiskSectorNr++;
	}
}

/// <name>
/// writeSector-2 parameters
/// </name>
/// <summary>
/// The role of this function write buffers pointed to the second parameter into the virtual disk specific sector
/// </summary>
/// <param name="SectorNumber">The serial number of the virtual disk specific sector</param>
/// <param name="s">pointer to buffer(length of sector)</param>
void Disk :: writeSector(uint SectorNumber, Sector * s) {  
	if (SectorNumber < 0 || SectorNumber>3199)
	{
		throw exception("out of limit! \n");
	}
	seekToSector(SectorNumber);
	currDiskSectorNr = SectorNumber;
	writeSector(s);
}

//destructor
Disk::~Disk(void)
{
	if (mounted)//àí àåúçì
	{
		UnmountDisk();
	}
}
/// <name>
/// recreatedisk-1 parameters
/// </name>
/// <summary>
/// The role of this function is to reboot the virtual disk
/// </summary>
/// <param name="diskowner">The name of the owner</param>
void Disk::recreatedisk(string diskowner) {
	if (!mounted)
	{
		dskfl.open(vhd.diskName, ios::in | ios::out | ios::binary);
		if (!dskfl)
		{
			throw exception("file doesn't found \n");
		}
#pragma region 
		vhd.addrDAT = 1;
		vhd.addrDataStart = 4;
		vhd.addrDATcpy = 3198;
		vhd.addrRootDir = 2;
		vhd.addrRootDirCpy = 3196;
		vhd.ClusQty = 1600;
		vhd.dataClusQty = 1596;
		strncpy_s(vhd.diskOwner, diskowner.c_str(), sizeof(vhd.diskOwner));
		vhd.diskOwner[sizeof(vhd.diskOwner) - 1] = NULL;
		vhd.isFormatted = false;
		vhd.sectorNr = 0;
		strncpy_s(vhd.formatDate, "", sizeof(vhd.formatDate));
		strncpy_s(vhd.prodDate, getCurrnetDate().c_str(), sizeof(vhd.formatDate));
		vhd.prodDate[sizeof(vhd.prodDate) - 1] = NULL;
#pragma endregion
#pragma region 
		writeSector(0, (Sector*)&vhd);
		writeSector((Sector*)&dat);
		//////

		writeSector(3198,(Sector*)&dat);
#pragma endregion
	}
	else
	{
		throw exception("cannot recreate disk while mounted! \n");
	}
}
/// <name>
/// getdskfl-0 parameters
/// </name>
/// <summary>
/// The role of this function to return pointer of type fstream represents the file
/// </summary>
/// <return>Fstream type pointer to the address of dskl represents the file that contains the virtual disk</return>
fstream* Disk::getdskfl() {
	if (dskfl)
	{
		return &dskfl;
	}
	else
	{
		return NULL;
	}
}

#pragma endregion 

#pragma region level 1
/// <name>
/// format-1 parameters
/// </name>
/// <summary>
/// The role of this function to format a virtual disk
/// </summary>
/// <param name="OwnerName">The name of the owner</param>
void Disk::format(string  diskOwnerName)
{
	if (vhd.diskOwner != diskOwnerName)
	{
		throw exception("You aren't allow to format");
	}
	//update the data
	dat.data.set();
	dat.data.set(0, false);
	dat.data.set(1, false);
	dat.data.set(1598, false);
	dat.data.set(1599, false);
	for (int i = 0; i < 14; i++)
	{
		rootdir.Part1.dirEntry[i].entryStatus = 0;
		rootdir.Part2.dirEntry[i].entryStatus = 0;
	}
	vhd.isFormatted = true;
	_strdate_s(vhd.formatDate);
	vhd.formatDate[sizeof(vhd.formatDate) - 1] = NULL;
}

/// <name>
/// howmuchempty-0 parameters
/// </name>
/// <summary>
/// The role of this function is to calculate the total number of Free clusters from the virtual disk
/// </summary>
/// <return>the total number of Free clusters</return>
int Disk::HowMuchEmpty() {
	int sum = 0;
	for (int i = 0; i < 1600; i++)
	{
		sum += dat.data[i];//sum all of the 1
	}
	return sum;
}

/// <name>
/// alloc-4 parameters
/// </name>
/// <summary>
/// The role of this function is to handle the allocation of space on the disk
/// </summary>
/// <param name="Fat">File Allocation Table</param>
/// <param name="SectorsNumber">How many sector to allocat</param>
/// <param name="algoType">algorithm type for allcation</param>
/// <param name="start">Start position </param>
void Disk::alloc(DATtype & Fat, uint SectorsNumber, uint algoType, int start = 4)
{
	int space = 0, count = 0, begin = 0;
	bool flag = true;
	int Size_In_Clusters = int(((float)SectorsNumber / 2) + 0.5);//הגודל בקלסטרים
	if (Size_In_Clusters == 0) throw exception("are you kidding me, cannot allocate 0 \n");//במקרה ומנסים להקצות 0 מקומות
	if (HowMuchEmpty()<Size_In_Clusters)//במקרה ואין מקום בקובץ
		throw exception("Cant Find Enough Space for File...\n");
	switch (algoType)
	{
	case 0://first
	{
#pragma region מציאת הגודל הרציף הראשון בזיכרון שהוא גדול או שווה לגודל המבוקש
		for (int i = start; i < dat.data.size() - 1; i++)
		{
			if (dat.data[i])
				count++;
			else count = 0;

			if (count == Size_In_Clusters)
			{
				space = count;
				begin = i - space + 1;
				break;
			}
		}
#pragma endregion
		break;
	}
	case 1://best
	{
#pragma region מציאת המקום המינימלי שהוא לפחות הגודל המבוקש
		for (int i = start; i < dat.data.size() - 1; i++)
		{
			if (dat.data[i])
				count++;
			else
			{
				if (count >= Size_In_Clusters)
				{
					if (flag)//בדיקה אם זו פעם ראשונה שאנו מאתחלים את המשתנים
					{
						space = count;
						begin = i - space;
						flag = false;
					}
					else
					{
						if (space > count)//כיוון שהמשתנים כבר אותחלו פעם אחת לפחות ניתן לבצע את הבדיקה הזאת
						{
							space = count;
							begin = i - space;
						}
					}
				}
				count = 0;

			}
		}
#pragma endregion
		break;
	}

	case 2://worst
	{
#pragma region מציאת הגודל המקסימאלי שהוא מינימום הגודל שאנו מחפשים
		for (int i = start; i < dat.data.size() - 1; i++)
		{
			if (dat.data[i])
				count++;

			if (!(dat.data[i]) && space<count&& count >= Size_In_Clusters)
			{
				space = count;
				begin = i - space;
			}
			if (!dat.data[i])
				count = 0;
		}
#pragma endregion
		break;
	}
	default: {throw exception("Invalid Choice For Alogorithm Type..\n"); break;}//במקרה של בחירה של אלגוריתם לא אפשרי
	}
	if (space == 0)//במקרה ולא נמצא מקום רציף בזיכרון נשלח ברקורסיה 
	{
		alloc(Fat, SectorsNumber - 1, algoType);//N-1
		alloc(Fat, 1, algoType);//1
	}
	else//כאשר מצאנו מקום רציף בזיכרון אז נקצה את המקומות
	{
		for (int i = 0;i<Size_In_Clusters;i++)
		{
			Fat.set(begin + i, true);
			dat.data.set(begin + i, false);
		}
	}



}
/// <name>
/// alloc-3 parameters
/// </name>
/// <summary>
/// The role of this function is to take care of adding space allocation on the disk
/// </summary>
/// <param name="Fat">File Allocation Table</param>
/// <param name="SectorsNumber">How many sector to allocat</param>
/// <param name="algoType">algorithm type for allcation  0  –  first fit, 1  –  best fit, 2  –  worst fit</param>
void Disk::allocextend(DATtype & Fat, uint SectorsNumber, uint algoType)
{
	int start = 0;
#pragma region מציאת המקום האחרון שהוקצה לקובץ בזיכרון והכנסתו למשתנה
	for (int i = Fat.size()-1; i >= 0; i--)
	{
		if (Fat[i])
		{
			start = i;
			break;
		}
	}
#pragma endregion
	if (start == 0) throw exception("the file doesn't exist. cannot do extend method..\n");//במקרה והקובץ לא קיים
	alloc(Fat, SectorsNumber, algoType, ++start);//הרחבה מהמקום האחרון
}
/// <name>
/// dealloc-1 parameters
/// </name>
/// <summary>
/// The role of this function release space occupied
/// </summary>
/// <param name="Fat">File Allocation Table</param>
void Disk::dealloc(DATtype &FAT)
{
	dat.data |= FAT;
	FAT &= 0; //איפוס FAT
}
#pragma endregion

#pragma region level 2

/// <name>
/// createfile-9 parameters
/// </name>
/// <summary>
/// The role of this function is to make the creation of a data file
/// </summary>
/// <param name="FileName">The name of the file</param>
/// <param name="OwnerName">The name of the owner</param>
/// <param name="fileType">Determines the file type ("F" - records with fixed length; "V" - records with variable length)</param>
/// <param name="RecLength">Record length</param>
/// <param name="numSectorNeeded">Number of sectors requested</param>
/// <param name="keyType">Data type of the key</param>/// <param name="Fat">File Allocation Table</param>
/// <param name="OffsetKey">The offset of the start key in the record</param>
/// <param name="keyLength">Key length</param>
/// <param name="algoType">algorithm type for allcation  0  –  first fit, 1  –  best fit, 2  –  worst fit</param>
void Disk::createfile(string FileName, string OwnerName, string fileType, uint RecLength, uint numSectorNeeded, string keyType, uint OffsetKey, uint keyLength, int algoType)
{
	int indexP1 = -1, indexP2 = -1;
	bool stopCond1 = false, stopCond2 = false;;
	FileHeader FHD;
#pragma region מציאת המקום הפנוי הראשון והכנסת האינדק למשתנה + בדיקה האם הקובץ כבר קיים
	for (int i = 0; i < 14; i++)
	{
		if ((rootdir.Part1.dirEntry[i].entryStatus == '1'&&rootdir.Part1.dirEntry[i].FileName == FileName) || (rootdir.Part2.dirEntry[i].entryStatus == '1'&&rootdir.Part2.dirEntry[i].FileName == FileName))//בדיקה שהקובץ לא קיים
			throw exception("file already exist ... :(");
		if ((!stopCond1) && rootdir.Part1.dirEntry[i].entryStatus != '1')//הכנסת האינדקס במקרה ויש מקום בחלק הראשון בזיכרון
		{
			indexP1 = i;
			stopCond1 = true;
			break;
		}
		if ((!stopCond2) && rootdir.Part2.dirEntry[i].entryStatus != '1')//הכנסת האינדקס במקרה ויש מקום בחלק השני בזיכרון
		{
			indexP2 = i;
			stopCond2 = true;
		}
	}
#pragma endregion
#pragma region אם יש מקום בחלק הראשון בזיכרון
	if (indexP1 != -1)
	{
#pragma region אתחול ערכים למשתנים וכתיבה לקובץ
		strncpy_s(rootdir.Part1.dirEntry[indexP1].FileName, FileName.c_str(), sizeof(FileName));
		strncpy_s(rootdir.Part1.dirEntry[indexP1].fileOwner, OwnerName.c_str(), sizeof(OwnerName));
		strncpy_s(rootdir.Part1.dirEntry[indexP1].crDate, getCurrnetDate().c_str(),9);
		rootdir.Part1.dirEntry[indexP1].fileSize = numSectorNeeded;
		rootdir.Part1.dirEntry[indexP1].maxRecSize = RecLength;
		if (fileType == "F")
		{
			rootdir.Part1.dirEntry[indexP1].actualRecSize = RecLength;
		}
		else if (fileType == "V")
		{
			throw "Not carried for V :(";
		}
		else//במקרה ונבחר משהו לא הגיוני
		{
			throw "Invalid FileType :(";
		}
		strncpy_s(rootdir.Part1.dirEntry[indexP1].recFormat, fileType.c_str(), 1);
		rootdir.Part1.dirEntry[indexP1].keyOffset = OffsetKey;
		rootdir.Part1.dirEntry[indexP1].keySize = keyLength;
		strncpy_s(rootdir.Part1.dirEntry[indexP1].keyType, keyType.c_str(), 1);
		rootdir.Part1.dirEntry[indexP1].entryStatus = '1';
		alloc(FHD.FAT, numSectorNeeded, algoType);
		int i = 2;
		for (; i < FHD.FAT.size(); i++)
			if (FHD.FAT[i])
				break;
		rootdir.Part1.dirEntry[indexP1].fileAddr = 2 * i - 1;
		rootdir.Part1.dirEntry[indexP1].eofRecNr = 0;
		FHD.fileDesc = rootdir.Part1.dirEntry[indexP1];
		FHD.sectorNr = 2 * i - 1;
		writeSector(2 * i - 1, (Sector*)&FHD);//כתיבה לקובץ
#pragma endregion
	}
#pragma endregion
#pragma region אם יש מקום בחלק השני בדיסק
	else if (indexP2 != -1)
	{
#pragma region אתחול ערכים וכתיבה לקובץ
		strncpy_s(rootdir.Part2.dirEntry[indexP2].FileName, FileName.c_str(), sizeof(FileName));
		strncpy_s(rootdir.Part2.dirEntry[indexP2].fileOwner, OwnerName.c_str(), sizeof(OwnerName));
		strncpy_s(rootdir.Part2.dirEntry[indexP2].crDate, getCurrnetDate().c_str(), 9);
		rootdir.Part2.dirEntry[indexP2].fileSize = numSectorNeeded;
		rootdir.Part2.dirEntry[indexP2].maxRecSize = RecLength;
		if (fileType == "F")
		{
			rootdir.Part2.dirEntry[indexP2].actualRecSize = RecLength;
		}
		else if (fileType == "V")
		{
			throw "Not carried for V :(";
		}
		else//בקרה ונבחר משהו לא הגיוני
		{
			throw "Invalid FileType :(";
		}
		strncpy_s(rootdir.Part2.dirEntry[indexP2].recFormat, fileType.c_str(), 1);
		rootdir.Part2.dirEntry[indexP2].keyOffset = OffsetKey;
		rootdir.Part2.dirEntry[indexP2].keySize = keyLength;
		strncpy_s(rootdir.Part2.dirEntry[indexP2].keyType, keyType.c_str(), 1);
		rootdir.Part2.dirEntry[indexP2].entryStatus = '1';
		alloc(FHD.FAT, numSectorNeeded, algoType);
		int i = 2;
		for (; i < FHD.FAT.size(); i++)
			if (FHD.FAT[i])
				break;
		rootdir.Part2.dirEntry[indexP2].fileAddr = 2 * i - 1;
		rootdir.Part2.dirEntry[indexP2].eofRecNr = 0;
		FHD.fileDesc = rootdir.Part2.dirEntry[indexP2];
		FHD.sectorNr = 2 * i - 1;
		writeSector(2 * i - 1, (Sector*)&FHD);//כתיבה לקובץ
#pragma endregion
	}
#pragma endregion
	else throw exception("Disk is FULL... :(");//במקרה ואין מקום
}

/// <name>
/// delfile-2 parameters
/// </name>
/// <summary>
/// The role of this function deletion of an existing file
/// </summary>
/// <param name="FileName">The name of the file</param>
/// <param name="OwnerName">The name of the owner</param>
void Disk::delfile(string FileName, string OwnerName)
{
	bool Exist = false;
	FileHeader FHD;
	for (int i = 0; i < 14; i++)
	{
		if ((rootdir.Part1.dirEntry[i].entryStatus == '1'&&rootdir.Part1.dirEntry[i].FileName == FileName))//חיפוש הקובץ בחלק הראשון
		{
			Exist = true;
			if (rootdir.Part1.dirEntry[i].fileOwner != OwnerName)//במקרה ומישהו שלא מוסמך מנסה למחוק את הקובץ
				throw exception("only file owner can delete the file..\n");
			rootdir.Part1.dirEntry[i].entryStatus = '2';//מחיקה
			readSector(rootdir.Part1.dirEntry[i].fileAddr, (Sector*)&FHD);
			dealloc(FHD.FAT);//איפוס ההקצאה
			break;
		}
		if ((rootdir.Part2.dirEntry[i].entryStatus == '1'&&rootdir.Part2.dirEntry[i].FileName == FileName))//חיפוש הקובץ בחלק השני
		{
			Exist = true;
			if (rootdir.Part2.dirEntry[i].fileOwner != OwnerName)//במקרה ומישהו שלא מוסמך מנסה למחוק את הקובץ
				throw exception("only file owner can delete the file... :(");
			rootdir.Part2.dirEntry[i].entryStatus = '2';//מחיקה
			readSector(rootdir.Part2.dirEntry[i].fileAddr, (Sector*)&FHD);
			dealloc(FHD.FAT);//איפוס ההקצאה
			break;
		}
	}
	if (!Exist)
		throw exception("File Doesn't Exist!... :(");
}

/// <name>
/// extendfile-4 parameters
/// </name>
/// <summary>
/// The role of this function to add space to an existing file
/// </summary>
/// <param name="FileName">The name of the file</param>
/// <param name="OwnerName">The name of the owner</param>
/// <param name="numSectorNeeded">Number of sectors requested</param>
/// <param name="algoType">algorithm type for allcation  0  –  first fit, 1  –  best fit, 2  –  worst fit</param>
void Disk::extendfile(string FileName, string OwnerName, uint numSectorNeeded, uint algoType)
{
	int Size_In_Clusters = int(((float)numSectorNeeded / 2) + 0.5);//הגודל בקלסטרים
	bool Exist = false;
	FileHeader FHD;
	for (int i = 0; i < 14; i++)
	{
		if ((rootdir.Part1.dirEntry[i].entryStatus == '1'&&rootdir.Part1.dirEntry[i].FileName == FileName))//אם נמצא בחלק הראשון
		{
			Exist = true;
			if (rootdir.Part1.dirEntry[i].fileOwner != OwnerName)//במקרה ומישהו שלא מוסמך מנסה להגדיל את הקובץ
				throw exception("only file owner can extend the file.\n");
			readSector(rootdir.Part1.dirEntry[i].fileAddr, (Sector*)&FHD);//קריאה למשתנה
			allocextend(FHD.FAT, Size_In_Clusters, algoType);//הרחבה
			rootdir.Part1.dirEntry[i].fileSize += numSectorNeeded;
			rootdir.Part1.dirEntry[i].eofRecNr = 0;
			break;
		}
		if ((rootdir.Part2.dirEntry[i].entryStatus == '1'&&rootdir.Part2.dirEntry[i].FileName == FileName))//אם נמצא בחלק השני
		{
			Exist = true;
			if (rootdir.Part2.dirEntry[i].fileOwner != OwnerName)//במקרה ומישהו שלא מוסמך מנסה להגדיל את הקובץ
				throw exception("only file owner can extend the file...\n");
			readSector(rootdir.Part2.dirEntry[i].fileAddr, (Sector*)&FHD);//קריאה למשתנה
			allocextend(FHD.FAT, Size_In_Clusters, algoType);//הרחבה
			rootdir.Part2.dirEntry[i].fileSize += numSectorNeeded;
			rootdir.Part2.dirEntry[i].eofRecNr = 0;
			break;
		}
	}

	if (!Exist)//במקרה ולא קיים
		throw exception("File Doesn't Exist!... \n");
}

#pragma endregion



#pragma region level 3
/// <name>
/// openfile-3 parameters
/// </name>
/// <summary>
/// The role of this function is to Open a file
/// </summary>
/// <param name="FileName">The name of the file</param>
/// <param name="userName">Name of user who opened the file</param>
/// <param name="openType">How to open (input - "I", O - "O", I / O - "IO", added - "E")</param>
/// <return>A pointer to an object of type FCB that function dynamically creates and initializes it according to parameter values ​​obtained</return>
FCB *Disk::openfile(string fileName, string userName, string openType)
{
	if (!mounted)
		throw exception("Disk unmounted..");

	FCB* fcb = new FCB();
	FileHeader fhd;
	bool Found = false;
	fcb->d = this;
	for (int i = 0; i < 14 && !Found; i++)
	{
		if (rootdir.Part1.dirEntry[i].FileName == fileName&& rootdir.Part1.dirEntry[i].entryStatus == '1')
		{
			fcb->fileDesc = rootdir.Part1.dirEntry[i];
			readSector(rootdir.Part1.dirEntry[i].fileAddr, (Sector*)&fhd);
			fcb->FAT = fhd.FAT;
			Found = true;
			break;
		}
		if (rootdir.Part2.dirEntry[i].FileName == fileName&& rootdir.Part2.dirEntry[i].entryStatus == '1')
		{
			fcb->fileDesc = rootdir.Part1.dirEntry[i];
			readSector(rootdir.Part1.dirEntry[i].fileAddr, (Sector*)&fhd);
			fcb->FAT = fhd.FAT;
			Found = true;
			break;
		}
	}
	if (openType == "O" || openType == "IO" || openType == "I")
	{
		if (fcb->fileDesc.fileOwner != userName&& openType != "I")
			throw exception("NO Permission ONLY Owner Can do Output.. :( ");
		fcb->currSecNr = 0;
		fcb->currRecNr = 0;
		fcb->d->seekToSector(fhd.fileDesc.fileAddr);
	}
	else if (openType == "E")
	{
		if (fcb->fileDesc.fileOwner != userName)
			throw exception("NO Permission ONLY Owner Can do Extend.. :( ");
		fcb->currRecNr = fhd.fileDesc.eofRecNr;
		fcb->currSecNr = (fhd.fileDesc.eofRecNr / (1020 / fhd.fileDesc.maxRecSize));
		fcb->d->seekToSector(findEOFSectorNr(fhd));

	}
	else
	{
		throw exception("invalid open type..");
	}
	fcb->format = openType;
	fcb->isOpen = true;
	return fcb;
	
}

/// <name>
/// findEOFSectorNr-1 parameters
/// </name>
/// <summary>
/// The role of this function is to find the number of EOF sector
/// </summary>
/// <param name="fileHeader">File Header</param>
/// <return>The number of EOF sector</return>
int Disk::findEOFSectorNr(FileHeader fhd)
{
	int Place = fhd.fileDesc.eofRecNr + 1; //assuming Record number starts with 0
	int index, End, numOfRecInSec = 1020 / fhd.fileDesc.maxRecSize;

	for (End = (fhd.FAT.size() - 1); End >= 0; End--)
		if (fhd.FAT[End])
			break;
	for (index = 0; index < fhd.FAT.size(); index++)
		if (fhd.FAT[index] && index<End)
			Place -= numOfRecInSec * 2;
	if (Place>numOfRecInSec)
		return index * 2 + 1;
	else
		return index * 2;

}

/// <name>
/// findEntry-3 parameters
/// </name>
/// <summary>
/// Find the place of entry
/// </summary>
/// <param name="FileName">The name of the file</param>
/// <param name="part1">out parameter-value will be true if what we were looking is in rootdir.Part1</param>
/// <param name="part2">out parameter-value will be true if what we were looking is in rootdir.Part2</param>
/// <return>Returns the index in Part1||Part2 that file is located</return>
int Disk::findEntry(string fileName, bool& part1, bool& part2)
{
	for (int i = 0; i < 14; i++)
	{
		if (rootdir.Part1.dirEntry[i].FileName == fileName&&rootdir.Part1.dirEntry[i].entryStatus == '1')
		{
			part1 = true;
			return i;
		}
		if (rootdir.Part2.dirEntry[i].FileName == fileName && rootdir.Part2.dirEntry[i].entryStatus == '1')
		{
			part2 = true;
			return i;
		}
	}
	throw exception("File Not Found..");
}
VolumeHeader Disk::getVolumeHeader()
{
	return this->vhd;
}

DirEntry Disk::GetEntry(bool part, int index)
{
	if (part && this->rootdir.Part1.dirEntry[index].entryStatus == '1')
		return this->rootdir.Part1.dirEntry[index];
	if (!part && this->rootdir.Part2.dirEntry[index].entryStatus == '1')
		return this->rootdir.Part2.dirEntry[index];
	DirEntry temp;
	temp.entryStatus = '0';
	return temp;
}
#pragma endregion