#include <iostream>
#include "Disk.h"
#include "TestLevel_0.h"
#include "TestLevel1.h"
#include "TestLevel_2.h"
#include "TestLevel_3.h"
using namespace std;


int main()

{
	
	unsigned int choice,index = 3;
	string diskName, diskOwner;

	do
	{
		cout << "\n=====================================================================\n\n";
		cout << "Please choose a functionality to test \n\n";
		cout << "\t1) Create Disk\n";
		cout << "\t2) Mount Disk\n";
		cout << "\t3) Print Sizes\n";
		cout << "\t4) Read and write to Sector\n";
		cout << "\t5) Do extend and allocations \n";
		cout << "\t6) Add file and extend file and delete file \n";
		cout << "\t7) Write and read file to Disk\n";
		cout << "\t10) exit\n\n";
		cout << "Your choice [    ]\b\b\b\b";
		cin >> choice;
		cout << "=====================================================================\n\n";

		switch (choice)
		{

		case 1: // Create disk

			cout << "Please enter a valid disk name: ";
			cin >> diskName;
			cout << "Please enter the disk owner: ";
			cin >> diskOwner;



			try
			{
				TestLevel_0::test_create(diskName, diskOwner);
			}
			catch (exception err)
			{
				cout << "Exception: " << err.what() << endl;
			}

			break;

		case 2: // Mount disk
			cout << "Please enter a valid disk name: ";
			cin >> diskName;

			try
			{
				TestLevel_0::test_mount(diskName);
			}
			catch (exception err)
			{
				cout << "Exception: " << err.what() << endl;
			}

			break;


		case 3: // Print the size of all classes
			try
			{
				TestLevel_0::printStructSize();
			}
			catch (exception err)
			{
				cout << "Exception: " << err.what() << endl;
			}


			break;


		case 4: // Write to sector

			cout << "Please enter a valid disk name: ";
			cin >> diskName;
			/*cout << "Enter a Sector Number to be written: ";
			cin >> index;*/

			try
			{
				TestLevel_0::test_rwSector(diskName);
			}
			catch (exception err)
			{
				cout << "Exception: " << err.what() << endl;
			}

			break;
		case 5:
			try
			{
				TestLevel1 a;
			}
			catch (exception err)
			{
				cout << "Exception: " << err.what() << endl;
			
			}
			break;
		case 6:
			try
			{
				TestLevel_2 a;
			}
		
			catch (exception err)
			{
				cout << "Exception: " << err.what() << endl;

			}
			break;
		case 7:
			try
			{
				TestLevel_3 a;
			}

			catch (exception err)
			{
				cout << "Exception: " << err.what() << endl;

			}
			break;
		case 10:
			cout << "good bye" << endl;
			break;
		default:

			cout << "Option not found \n\n";

		}
		

	} while (choice != 10 );

	system("pause");
	return 0;




	try
	{

		//call test
		TestLevel_0::test_0();
	}
	catch (char * err)
	{
		cout << err;
	}
	
	return 0;

}