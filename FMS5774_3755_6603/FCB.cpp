#include "FCB.h"
#include "disk.h"

/// <name>
/// constractor without parameters
/// </name>
/// <summary>
/// constractor without parameters-Update fields of FCB
/// </summary>
FCB::FCB(void)
{
	d = NULL;
	currRecNrInBuff = currSecNr = currRecNr = 0;
	isOpen = false;
	lock = false;
}
/// <name>
/// constractor with 1 parameters
/// </name>
/// <summary>
/// constractor with 1 parameters-The role of this constructor to initialize an object of type FCB
/// </summary>
/// <param name="d">Pointer to particular disk</param>
FCB::FCB(Disk* d)
{
	this->d = d;
	currRecNrInBuff = currSecNr = currRecNr = 0;
	isOpen = false;
	lock = false;
}
/// <name>
/// destractor with out parameters
/// </name>
/// <summary>
/// destractor with out parameters-The role of this function to destroy an object of this type automatically at the appropriate moment.
/// </summary>
FCB::~FCB(void)
{
	if (d)
		delete d;
}
/// <name>
/// closefile-0 parameters
/// </name>
/// <summary>
/// The role of this function is to close the particular file
/// </summary>
void FCB::closefile()
{
	FileHeader fhd;
	int index;
	bool part1 = false, part2 = false;
	if (lock)
		throw exception("file Locked, cannot complete the action...:(");
	if (!isOpen)
		return;
	if (format != "I")
		flushfile();
	index = d->findEntry(fileDesc.FileName, part1, part2);
	if (part1)
		d->rootdir.Part1.dirEntry[index] = fileDesc;
	if (part2)
		d->rootdir.Part2.dirEntry[index] = fileDesc;
	fhd.FAT = FAT;
	fhd.fileDesc = fileDesc;
	fhd.sectorNr = fileDesc.fileAddr;
	d->writeSector(fileDesc.fileAddr, (Sector*)&fhd);
	isOpen = false;
	d = NULL;
	format = "";

}
/// <name>
/// flushfile-0 parameters
/// </name>
/// <summary>
/// The role of this function physically write buffer contents back to the appropriate sector
/// </summary>
void FCB::flushfile()
{
	if (lock)
		throw exception("file Locked, cannot complete the action...:(");
	if (format == "I")
		throw exception("you have nothing to write. it's input Mode...:(");
	d->writeSector(Buffer.sectorNr, &(Buffer));
}
/// <name>
/// findCurrnetSector-0 parameters
/// </name>
/// <summary>
/// Finding the present Sector
/// </summary>
/// <return>Present Sector</return>
int FCB::findCurrnetSector()
{
	int target = currRecNr;
	int i = 0;
	int RecordNrInSec = (1020 / fileDesc.maxRecSize);
	for (; i<1600; i++)
		if (FAT[i])
		{
			if (target < RecordNrInSec)
				return i * 2;
			if(target<2*RecordNrInSec)
				return i * 2 + 1;
			target -= 2 * RecordNrInSec;

		}
}
/// <name>
/// read-2 parameters
/// </name>
/// <summary>
/// The role of this function is to read the current record of the file
/// </summary>
/// <param name="record">Current record</param>
/// <param name="readForUpdate">Whether the file is opened as read for update</param>
void FCB::read(char * record, bool readForUpdate)
{
	if (format == "O" || format == "E")
		throw exception("file open type , cannot perform read...:(");
	if (lock)
		throw exception("file Locked, cannot complete the action...:(");

	if (readForUpdate && format == "I")
		throw exception("file opened in Input, cannot perform update...:(");

	if (currRecNr>fileDesc.eofRecNr)
		throw exception("End of file...:(");

	if (readForUpdate)
		lock = true;

	if (currRecNrInBuff == 0)
		d->readSector(findCurrnetSector(), &Buffer);
	memcpy(record, ((char*)(&Buffer) + 4 + currRecNrInBuff*fileDesc.maxRecSize), fileDesc.maxRecSize);

	if (!readForUpdate)
	{
		int nextRecNrInBuff = (currRecNrInBuff + 1) % (1020 / fileDesc.maxRecSize);
		++currRecNr;
		currRecNrInBuff = nextRecNrInBuff;
		if (currRecNrInBuff == 0)
			currSecNr++;
	}


}
/// <name>
/// write-1 parameters
/// </name>
/// <summary>
/// The role of this function is to write the record first parameter passed into the current position of the file
/// </summary>
/// <param name="record">Current record</param>
void FCB::write(char* record)
{
	if (lock)
		throw exception("file Locked, cannot complete the action...:(");
	if (format == "I")
		throw exception("you Have Nothing to write. it's input Mode...:(");

	if (currRecNrInBuff == 0)
		d->readSector(findCurrnetSector(), &Buffer);
	memcpy((char*)&Buffer + 4 + fileDesc.maxRecSize*currRecNrInBuff, record, fileDesc.maxRecSize);
	currRecNr++;
	if (currRecNr > fileDesc.eofRecNr)
		fileDesc.eofRecNr = currRecNr;
	currRecNrInBuff= (currRecNrInBuff + 1) % (1020 / fileDesc.maxRecSize);
	if (currRecNrInBuff == 0)
	{
		flushfile();
		currSecNr++;
	}
}
/// <name>
/// seek-2 parameters
/// </name>
/// <summary>
/// The role of this function is to read the current record of the file
/// </summary>
/// <param name="SearchType">Search type (0 - beginning of file, 1 - from the current record, 2 - the end of the logical file)</param>
/// <param name="JumpNr">Some records the user wants to "jump" forward or backward</param>
void FCB::seek(uint SearchType, int JumpNr)
{
	if (lock)
		throw exception("file Locked, cannot complete the action...:(");
	if(SearchType==0&&JumpNr<0||SearchType==2&&JumpNr>0)
		throw exception("cannot seek according to parmeters.. out of boundries");

	switch (SearchType)
	{
	case 0:
		{
			if (JumpNr > fileDesc.eofRecNr)
				throw exception("out of boundries");
			else
				currRecNr = JumpNr;
			break;
		}
		case 1:
		{
			if (currRecNr + JumpNr > fileDesc.eofRecNr || currRecNr + JumpNr < 0)
				throw exception("out of boundries");
			else
			currRecNr += JumpNr;
			break;
		}
		case 2:
		{
			if (fileDesc.eofRecNr + JumpNr < 0)
				throw exception("out of boundries");
			else
				currRecNr = fileDesc.eofRecNr + JumpNr;
			break;
		}
	}
	if (format != "I")
		flushfile();
	if (currSecNr != (currRecNr / (1020 / fileDesc.maxRecSize)))
	{
		currSecNr = (currRecNr / (1020 / fileDesc.maxRecSize));
		d->readSector(findCurrnetSector(), &Buffer);
	}
	currRecNrInBuff = currRecNr % (1020 / fileDesc.maxRecSize);

}
/// <name>
/// updateCancel-0 parameters
/// </name>
/// <summary>
/// The role of this function to cancel the lock status of the current record
/// </summary>
void FCB::updateCancel()
{
	if (format != "IO")
		throw exception("Error- File is not in a update position...:(");
	lock = false;
}
/// <name>
/// deleteRec-0 parameters
/// </name>
/// <summary>
/// The role of this function to delete a record instead of the current file
/// </summary>
void FCB::deleteRec()
{
	if(!lock)
		throw exception("the file must be locked... :(");
	int reset = 0;
	for (int i = 0; i<fileDesc.keyOffset; i++)
		memcpy((char*)&(Buffer)+currRecNrInBuff*fileDesc.maxRecSize + fileDesc.keyOffset + i, &reset, 1);
	lock = false;
	currRecNr++;
	currRecNrInBuff = (currRecNrInBuff + 1) % (1020 / fileDesc.maxRecSize);
	if (currRecNrInBuff == 0)
		currSecNr++;
}
/// <name>
/// updateRec-1 parameters
/// </name>
/// <summary>
/// The role of this function is to write a record instead of the current file, to update
/// </summary>
/// <param name="record">Current record</param>
void FCB::updateRec(char* record)
{
	if (!lock)
		throw exception("file Locked, cannot complete the action...:(");
	lock = false;
	write(record);
}