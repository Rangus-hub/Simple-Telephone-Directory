
//                 PROJECT ON TELEPHONE DIRECTORY
/*
  The programme helps to collect student telephone information.
  The programme is menu driven and offers various options like
  add, delete, modify and display telephone records.
  The records are stored in a file called Phone.dat.
  The program uses a TeleDict Class to hold a student information
  and informtion is then used to add, modify, delete and display student
  information.
*/

//LIBRARIES
#include<fstream>
#include<conio.h>
#include<stdio.h>
#include <stdlib.h>
#include<iostream>
using namespace std;
//PROTOTYPES USED IN THE PROGRAMME
void Options();   			//Function to display menu options and run project
void AddNewTelephone();   		//Function to add new record in a Binary File.
void DisplayAllStudentRecords();	//Function to read data file & display on screen.
void SearchByStudentID();   		//Function to search and display record by sr no.
void DeleteByStudentID();   		//Function to delete a specific record from file.
void ModifyByStudentID();  		//Function to modify a specific record in file.

//DECLARATION OF CLASS TO STORE DATA
class TeleRecord{
	int srno;
	char name[25];
	char mobile[15];
	char email[30];
	char group[20];
	public:
	int getSrNo() {return srno;}

	void storeData()
	{
		cout<<"\n...............ENTER NEW TELEPHONE RECORD...............\n";
		cout<<"Enter Student ID : "; cin>>srno; cin.ignore();
		cout<<"Enter Student Name   : "; cin.getline(name,25);
		cout<<"Enter Mobile Number : "; cin.getline(mobile,15);
		cout<<"Enter E-Mail ID  : "; cin.getline(email,30);
		cout<<"Enter Student Group  : "; cin.getline(group,20);
		cout<<endl;
	}

	void showData()
	{
		cout<<"\n...............TELEPHONE RECORD...............\n";
		cout<<"Student ID    : "<<srno<<endl;
		cout<<"Student Name       : "<<name<<endl;
		cout<<"Mobile No. : "<<mobile<<endl;
		cout<<"Email ID   : "<<email<<endl;
		cout<<"Student Group      : "<<group<<endl;
	}
}X;

void AddNewTelephone()
{
	ofstream fout;
	fout.open("TeleDict.dat",ios::out|ios::binary|ios::app);
	X.storeData();
	fout.write((char*)&X,sizeof(X));
	fout.close();
	cout<<"\nStudent Record Saved to File......\n";
}


void DisplayAllStudentRecords()
{
	ifstream fin;
	fin.open("TeleDict.dat",ios::out|ios::binary|ios::app);
	while(fin.read((char*)&X,sizeof(X)))
	{
		X.showData();
	}
	fin.close();
	cout<<"\n......Finished Reading Data From File......\n";
}

void SearchByStudentID()
{
	ifstream fin;
	int n, flag=0;
	fin.open("TeleDict.dat",ios::out|ios::binary|ios::app);
	cout<<"Enter Student ID of Record To Display: ";
	cin>>n;

	while(fin.read((char*)&X,sizeof(X)))
	{
		if(n==X.getSrNo())
		{
			X.showData();
			flag++;
			cout<<"\n\n.....Student Record Found and Displayed......\n";
		}
	}
	fin.close();
	if(flag==0)
		cout<<"\nThe Student ID Record "<<n<<" is not in file....\n";
	cout<<"\n.......Finished Reading Data From File......\n";
}

void DeleteByStudentID()
{
	ifstream fin;
	ofstream fout;
	int n, flag=0;
	fin.open("TeleDict.dat",ios::out|ios::binary|ios::app);
	fout.open("temp.dat",ios::out|ios::binary);
	cout<<"Enter Student ID of Record To Delete : ";
	cin>>n;

	while(fin.read((char*)&X,sizeof(X)))
	{
		if(n==X.getSrNo())
		{
			cout<<"\n.......The Following Student Record is Deleted....\n";
			X.showData();
			flag++;
		}
		else
		{
			fout.write((char*)&X,sizeof(X));
		}
	}
	fin.close();
	fout.close();
	if(flag==0)
		cout<<"\n.......The Student ID Record "<<n<<" is not in file....\n";
	cout<<"\n.......Finished Reading Data From File......\n";
	remove("TeleDict.dat");
	rename("temp.dat","TeleDict.dat");
}

void ModifyByStudentID()
{
	fstream fio;
	int n, flag=0,pos;
	fio.open("TeleDict.dat",ios::out|ios::binary|ios::in);

	cout<<"Enter Student ID of Record To Modify : ";
	cin>>n;

	while(fio.read((char*)&X,sizeof(X)))
	{
		pos=fio.tellg();
		if(n==X.getSrNo())
		{
			cout<<"\n.....The Following Student Record Will Be Modified....\n";
			X.showData();
			flag++;
			cout<<"\n.....Change or Re-Enter the New Details.....\n";
			X.storeData();
			fio.seekg(pos-sizeof(X));
			fio.write((char*)&X,sizeof(X));
			cout<<"\n.....Student Record Modified Successfully....\n";
		}
	}
	fio.close();
	if(flag==0)
		cout<<"\n...The Student ID Record  "<<n<<" is not in file....\n";
	cout<<"\n.......Finished Reading Data From File......\n";
}

void Options()
{
	int ch;


	do
	{
		//CLEAR THE DISPLAY SCREEN
		system("CLS");

		//DISPLAYING OPTIONS
		cout<<"............................................\n";
		cout<<"           TELEPHONE DICTIONARY \n";
		cout<<"............................................\n\n";
		cout<<"::::::::::::::: PROGRAM OPTIONS :::::::::::::::\n";
		cout<<"0. Exit\n";
		cout<<"1. Save New Phone Record\n";
		cout<<"2. Display All Saved Records\n";
		cout<<"3. Search Specific Record\n";
		cout<<"4. Delete Specific Record\n";
		cout<<"5. Modify Existing Record\n";
		cout<<"Enter Your Choice : ";
		cin>>ch;

		//Clear Screen to display the result of the Option chosen by the user
		system("CLS");

		//TO CALLED THE DESIRED FUNCTION FROM THE MENU
		switch(ch)
		{
			case 1: AddNewTelephone(); break;
			case 2: DisplayAllStudentRecords(); break;
			case 3: SearchByStudentID(); break;
			case 4: DeleteByStudentID(); break;
			case 5: ModifyByStudentID(); break;
		}

		//TO WAIT TILL USER PRESSES A KEY(TO PAUSE)
		getch();

	}while(ch);
}

int main()
{
	//TO START THE PROGRAMME
	Options();
}