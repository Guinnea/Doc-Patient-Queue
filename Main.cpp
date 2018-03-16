/*
This is the Doctor's Office Simulator
Use of the program is very straight forward
I used the C++ implemented queue for the patients waiting in line
I also made the queue part of the doctor class, as the rooms are related to the doctor specifically
I used an Enum to define the types of specialties for the Doctors
Other than there, there is a basic class for the Patient and for the Doctor
*/

#include "Specialty Codes.h"
#include "Patient.h"
#include "Doctor.h"
#include "Queue.h"
#include <iostream>
#include <String>
#include <queue>

using namespace std;

// Prototypes
char promptDP();
char promptIO();
void docCheck(bool r[], Doctor d[], int& doc);
void patCheck(bool r[], Doctor d[], int& docs);
SpecCode chooseSpec();
int compareSpec(SpecCode sc1, Doctor d1[], int numD);
void assignPatient(Doctor d1[], Patient p1, int numD, int numFound);

//The good stuff
void main()
{
	bool roomOpen[100];
	int numDoc = 0;
	Doctor doc[100];
	queue<Patient> Q1;
	char tempC = ' ';

	//Initialize the rooms to open
	for (int i = 0; i < 100; i++)
		roomOpen[i] = true;

	cout << "Welcome to the Doctor's Office Simulator!\n\n";

	//Loop asking for input
	while (tempC != 'E')
	{
		cout << "***** MAIN MENU *****\n\n";

		//Check if Patient of Doctor
		tempC = promptDP();
		if (tempC == 'D')		//DOCTOR
			docCheck(roomOpen, doc, numDoc);
		else if(tempC = 'P')	//PATIENT
			patCheck(roomOpen, doc, numDoc);
		else if (tempC = 'E')	//EXIT
			cout << "Have a good day ! \n\n";
		else
			cout << "INVALID ENTRY!\n\n";
	}
}

char promptDP()
{
	char check = ' ';
	while (check != 'D' && check != 'P' && check != 'E')
	{
		cout << "Please enter if you're a Doctor or Patient (D or P) : ";
		cin >> check;
	}
	return check;
}

char promptIO()
{
	char check = ' ';
	while (check != 'I' && check != 'O')
	{
		cout << "Are you checking In or Out? (I or O) : ";
		cin >> check;
	}
	return check;
}

void docCheck(bool r[], Doctor d[], int& doc)
{
	char tempC = promptIO();
	string sTemp = " ";
	int rTemp = -1;
	SpecCode scTemp;

	if (tempC == 'I')
	{

		//Doctors name
		while (sTemp.length() < 3)
		{
			sTemp = " ";
			cout << "Please enter your last name, Doctor : ";
			cin >> sTemp;
		}

		//Doctor's Specialization
		scTemp = chooseSpec();

		//Choosing Room
		while (rTemp < 0 || rTemp > 99)
		{
			cout << "Please enter desired room number (0 - 99) : ";
			cin >> rTemp;
		}
		
		//Check if Room is available
		if (r[rTemp])
		{ // Doctor Checking In
			
			//Add Doctor to list of Doctors present
			Doctor tempDoc(sTemp, rTemp, scTemp);
			d[doc] = tempDoc;
			doc++;

			//Set room status as taken
			r[rTemp] = false;

			//Out information to user
			cout << "Dr. "
				<< tempDoc.getName()
				<< " has successfully checked into Room "
				<< tempDoc.getRoom()
				<< "\n\n";
		}
		else
		{ // Room is Taken
			cout << "Sorry, that room is already taken! Please try again!\n\n";
		}
	}
	else
	{
		string sTemp;
		bool found = false;
		int tempI;

		//Input name to find and compare to list of checked in doctors
		cout << "Please enter your name to Check Out : ";
		cin >> sTemp;

		//Go through the list of doctors and compare to inputed
		for (int i = 0; i < doc; i++)
		{
			if (d[i].getName() == sTemp)
			{
				found = true;
				tempI = i;
			}
		}

		//Check if name has been found
		if (found)
		{
			//Set that room to open
			r[d[tempI].getRoom()] = true;

			//Out information to user
			cout << "Dr. "
				<< d[tempI].getName()
				<< " has successfully checked out of Room "
				<< d[tempI].getRoom()
				<< "\n\n";

			//Shift everything over
			for (int i = tempI + 1; i < doc; i++)
			{
				d[i - 1] = d[i];
			}
			
			//1 less doctor
			doc--;
		}
		else
		{
			cout << "Sorry, but your name was not found, or you havent checked in yet today.\nPlease Try Again\n\n";
		}
	}
}

void patCheck(bool r[], Doctor d[], int& docs)
{
	char tempC = promptIO();
	string tempName = " ";
	unsigned int tempAge = 0;
	SpecCode tempSC;
	char tempER = ' ';

	if (tempC == 'I')
	{
		//Get the name of a patient
		cout << "Please enter your first name : ";
		cin >> tempName;

		//Get the Age
		cout << "Please enter your age : ";
		cin >> tempAge;

		//Get the specialist type
		if (tempAge < 16)
			tempSC = PED;
		else
			tempSC = chooseSpec();

		//Check if it's an emergency
		while (tempER != 'Y' && tempER != 'N')
		{
			cout << "Is this an emergency? (Y/N) : ";
			cin >> tempER;
		}

		//Create Patient
		Patient tempPatient(tempName, tempAge, tempSC, (tempER == 'Y'));

		//Check how many of your specialists are in
		int tempSpecialist = compareSpec(tempSC, d, docs);

		//Check if specialist is in
		if (tempSpecialist > 0)
		{	//atleast 1 Specialist is in
			assignPatient(d, tempPatient, docs, tempSpecialist);
		}
		else
		{	//No specialist in
			cout << "Your specialist isn't in!\n";
			tempPatient.setSpecialty(GP);
			tempSpecialist = compareSpec(GP, d, docs);

			if (tempSpecialist > 0)
			{	//atleast 1 GP is in
				assignPatient(d, tempPatient, docs, tempSpecialist);
			}
			else
			{	//Assign to any doctor
				if (docs > 0)
				{ //Make sure there are doctors in
					cout << "A General Practitioner isn't in!\n";
					assignPatient(d, tempPatient, docs, tempSpecialist);
				}
				else
				{ //No doctors checked in
					cout << "No doctors have checked in yet, please check in later!\n\n";
				}
			}
		}

	}
	else //Checking out
	{
		string tempName;
		int whichDoc = -1;
		cout << "You are now checking out\n"
			<< "Please enter your first name : ";
		cin >> tempName;

		//Go through the list of doctors and fronts of queue to find the patient to remove
		for (int i = 0; i < docs; i++)
			if (d[i].q1.front().getName() == tempName)
				whichDoc = i;

		if (whichDoc >= 0)
		{//Patient was found and will be removed from queue
			d[whichDoc].q1.pop();
			cout << "Have a great day " << tempName << "!\n\n";
			cout << "Dr. "
				<< d[whichDoc].getName()
				<< " will now be helping "
				<< d[whichDoc].q1.front().getName()
				<< " in Room "
				<< d[whichDoc].getRoom();
		}
		else
		{//Patient not found
			cout << "Sorry, we don't have that name in our database,\nPlease try checking out again!\n\n";
		}
	}



}

SpecCode chooseSpec()
{
	int i = -2;
	int selection;

	cout << "Please select the corresponding number of your specialization from the list : \n"
		<< "1. Pediatrics \n"
		<< "2. General practice (GP) \n"
		<< "3. General practice (GEN) \n"
		<< "4. Internal medicine \n"
		<< "5. Cardiology \n"
		<< "6. Surgeon \n"
		<< "7. Obstetrics \n"
		<< "8. Psychiatry \n"
		<< "9. Neurology \n"
		<< "10. Orthopedics \n"
		<< "11. Dermatology \n"
		<< "12. Ophthalmology \n"
		<< "13. Ear, Nose, and Throat\n\n";

	while (i < 0)
	{
		if (i == -1)
			cout << "INVALID CHOICE, Choose from numebrs 1 - 13 !!!\n\n";

		cout << "Your choice : ";
		
		cin >> selection;

		switch (selection)
		{
			case 1:
				return PED;
			case 2:
			case 3:
				return GP;
			case 4:
				return INT;
			case 5:
				return CAR;
			case 6:
				return SUR;
			case 7:
				return OBS;
			case 8:
				return PSY;
			case 9:
				return NEU;
			case 10:
				return ORT;
			case 11:
				return DET;
			case 12:
				return OPT;
			case 13:
				return ENT;
			default:
				i = -1;
		}
	}
	return GEN; //If everything goes wrong
}

int compareSpec(SpecCode sc1, Doctor d1[], int numD)
{
	int j = 0;
	for (int i = 0; i < numD; i++)
	{
		if (d1[i].getSpecialty() == sc1)
			j++;
	}
	return j;
}

void assignPatient(Doctor d1[], Patient p1, int numD, int numFound)
{
	int j = 0;

	//Check if no matching specialists were found, find the shortest queue
	if (numFound == 0)
	{
		for (int i = 1; i < numD; i++)
		{
			if (d1[i].q1.size() < d1[j].q1.size())
				j = i;
		}
	}
	//check if 1 matching specialist was found
	else if(numFound == 1)
	{
		for (int i = 0; i < numD; i++)
		{
			if (d1[i].getSpecialty() == p1.getSpecialty())
				j = i;
		}
	}
	//Check if multiple specialists were found, find the one with the shortest queue
	else
	{
		for (int i = 0; i < numD; i++)
		{
			if (d1[i].getSpecialty() == p1.getSpecialty() &&
				d1[i].q1.size() < d1[j].q1.size())
				j = i;
		}
	}
	
	if (p1.getEmergency())
	{
		//If it's an emergency, temporarily store all patients into another queue (in the same order), put current patient at the front of the queue
		//and then put all the patients back into the doctors original queue in the same order
		queue<Patient> tempQ;
		for (unsigned i = 0; i < d1[j].q1.size(); i++)
		{
			tempQ.push(d1[j].q1.front());
			d1[j].q1.pop();
		}
		d1[j].q1.push(p1);
		for (unsigned i = 0; i < tempQ.size(); i++)
		{
			d1[j].q1.push(tempQ.front());
			tempQ.pop();
		}

		cout
			<< "Patient "
			<< p1.getName()
			<< ", Age "
			<< p1.getAge()
			<< ", is now being placed with Dr. "
			<< d1[j].getName()
			<< ", who is located in Room "
			<< d1[j].getRoom()
			<< ".\nYou are currently number 1 in the queue\n\n";
	}
	else
	{
		cout
			<< "Patient "
			<< p1.getName()
			<< ", Age "
			<< p1.getAge()
			<< ", is now being placed with Dr. "
			<< d1[j].getName()
			<< ", who is located in Room "
			<< d1[j].getRoom()
			<< ".\nYou are currently number "
			<< (d1[j].q1.size() + 1)
			<< "in the queue\n\n";
		d1[j].q1.push(p1);
	}


}