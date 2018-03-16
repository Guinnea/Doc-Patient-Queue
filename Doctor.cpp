#include "Doctor.h"

Doctor::Doctor()
{
	name = "";
	roomNum = 0;
	specialty = GEN;
}

Doctor::Doctor(string s1, int i1, SpecCode sc1)
{
	name = s1;
	roomNum = i1;
	specialty = sc1;
}

void Doctor::setName(string s1)
{
	name = s1;
}

string Doctor::getName()
{
	return name;
}

void Doctor::setRoom(int i1)
{
	roomNum = i1;
}

int Doctor::getRoom()
{
	return roomNum;
}

void Doctor::setSpecialty(SpecCode sc1)
{
	specialty = sc1;
}

SpecCode Doctor::getSpecialty()
{
	return specialty;
}

void Doctor::operator=(Doctor d1)
{
	name = d1.getName();
	roomNum = d1.getRoom();
	specialty = d1.getSpecialty();
}

//Not needed
//Doctor::~Doctor()
//{
//}
