#include "TestLevel_3.h"
TestLevel_3::TestLevel_3(void)
{
	try
	{
		cout << sizeof(Record) << endl;
		cout << sizeof(Sector) << endl;
		this->D.createdisk("TEst_level_3", "Ori&David");
		this->D.MountDisk("TEst_level_3");
		this->D.format("Ori&David");
		this->D.createfile("students", "Ori&David", "F", sizeof(Record), 30, "int", 4);
		Sector x;
		f = this->D.openfile("students", "Ori&David", "IO");
		write();
		read();
		this->f->closefile();
		f = this->D.openfile("students", "Ori&David", "I");
		printAll();
		this->f->closefile();
		f = this->D.openfile("students", "Ori&David", "O");
		Record r;
		cout << "trying to read in O format\n";
		f->read((char*)&r, 0);
	}
	catch (exception messege)
	{
		cout << messege.what() << endl;
	}

}

void TestLevel_3::printAll()
{
	try
	{
		Record r;
		this->f->seek(0, 0);
		for (int i = 0;i<70;i++)
		{
			this->f->read((char*)&r, 0);
			cout << "KEY: " << r.key << " ";
			cout << "FN: " << r.firstname << " ";
		}
		cout << endl;
	}
	catch (exception messege)
	{
		cout << messege.what() << endl;
	}


}

void TestLevel_3::write()
{
	try
	{
		cout << "writing 70 records into file\n";
		Record r;
		r.grade = 8;
		memcpy(r.firstname, "Ori", 3);
		r.firstname[3] = NULL;
		memcpy(r.lastName, "Eshel", 5);
		r.lastName[5] = NULL;
		memcpy(r.Id, "205873755", 10);
		r.Id[10] = NULL;
		char a[220];
		for (int i = 0; i<70; i++)
		{
			r.key = i + 1;
			f->write((char*)&r);
		}
		cout << "\nattemting to move the IO pointer after EOF\n";
		this->f->seek(0, 70);
		cout << endl << "Trying to exceed file memory allocation\n";
		Record r1;
		for (int i = 70;i<200;i++)
		{
			r1.key = i + 1;
			f->write((char*)&r1);
		}
	}
	catch (exception messege)
	{
		cout << messege.what() << endl;
	}
	
}
TestLevel_3::~TestLevel_3(void)
{
}
void TestLevel_3::read()
{
	Record r;
	this->f->seek(0, 37);
	this->f->read((char*)&r,0);
	cout << "print key and first name of record number 37 after reading it from the file\n" <<
		r.key << " " << r.firstname << endl << "trying to delete recrod with out locking first\n";
	deleteRec();
	cout << "trying to update recrod with out locking first\n";

	update(r);
	cout << "updateing record 38\n";
	this->f->seek(0, 37);
	this->f->read((char*)&r, 1);
	memcpy(r.firstname, "David", 5);
	r.firstname[5] = NULL;
	this->update(r);
	cout << "reading from file after update\n";
	this->f->seek(0, 37);
	this->f->read((char*)&r,0);
	cout << "name after update: " << r.firstname << endl;
	this->f->read((char*)&r, 1);
	cout << "\nVerifying the system is freezd when recrod is locked\n";
	try
	{
		this->f->seek(0, 0);
		f->read((char*)&r,0);
		this->f->flushfile();
		this->f->write((char*)&r);
		this->f->closefile();
	}
	catch (exception messege)
	{
		cout << messege.what() << endl;
	}
	cout << endl << "deleting record number 39\n";
	deleteRec();
	this->f->seek(0, 38);
	this->f->read((char*)&r,0);
	cout << "Key after deleted\n" << r.key << endl;

}
void TestLevel_3::deleteRec()
{
	try
	{
		this->f->deleteRec();
	}
	catch (exception messege)
	{
		cout << messege.what() << endl;
	}
}
void TestLevel_3::update(Record r)
{
	try
	{
		this->f->updateRec((char*)&r);
	}

	catch (exception messege)
	{
		cout << messege.what() << endl;
	}

}
void TestLevel_3::updateCancel()
{
	this->f->updateCancel();
}