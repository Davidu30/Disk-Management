#include "TestLevel1.h"
#include <string>


TestLevel1::TestLevel1(void)
{ 
	try
	{
		d.createdisk("Test 1", "David");
		d.MountDisk("Test 1");
		d.format("David");
		if (d.vhd.isFormatted)
			cout << "format date: " << d.vhd.formatDate << endl;
		alocations();
		printDat();
		extend();
		printDat();
		extend();
		d.dealloc(fat);
		printDat();
	}
	catch (...)
	{
		cout << "ERROR... :(";
	}


}


TestLevel1::~TestLevel1(void)
{
}

void TestLevel1::alocations()
{


	d.dat.data[60] = 0;
	fat[60] = 1;
	d.dat.data[48] = 0;
	fat[48] = 1;

	d.dat.data[16 * 4 - 1] = 0;
	fat[63] = 1;

	d.dat.data[16 * 4 + 10] = 0;
	fat[16 * 4 + 10] = 1;



	d.dat.data[16 * 20 - 1] = 0;
	fat[16 * 20 - 1] = 1;

	d.dat.data[16 * 40 - 1] = 0;
	fat[16 * 40 - 1] = 1;


	d.dat.data[16 * 50 - 1] = 0;
	fat[16 * 50 - 1] = 1;

	d.dat.data[16 * 75 - 1] = 0;
	fat[16 * 75 - 1] = 1;

	d.dat.data[16 * 100 - 20] = 0;
	fat[16 * 100 - 20] = 1;





	d.alloc(fat, 10, 0,4);//first fit

	d.alloc(fat, 10, 1,4);//best fit

	d.alloc(fat, 10, 2,4);//worst fit

}
void TestLevel1::printDat()
{

	for (int i = 0;i<d.dat.data.size() / 16;i++)
	{
		cout << i << " : ";
		for (int j = 0;j<16;j++)
			cout << d.dat.data[i * 16 + j] << " ";
		cout << endl;
	}
	cout << endl;

};
void TestLevel1::extend()
{
	d.allocextend(fat, 5, 0);
	d.allocextend(fat, 5, 1);




}