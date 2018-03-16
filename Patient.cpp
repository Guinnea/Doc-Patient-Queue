#include "Specialty Codes.h"
#include "Patient.h"
#include <String>
#include <iostream>

using namespace std;


Patient::Patient()
{
	name = "";
	age = 0;
	specialty = GEN;
	emergency = false;
}

Patient::Patient(string s1, unsigned int i1, SpecCode sc1, bool b1)
{
	name = s1;
	age = i1;
	specialty = sc1;
	emergency = b1;
}

void Patient::setName(string s1)
{
	name = s1;
}

string Patient::getName()
{
	return name;
}

void Patient::setAge(unsigned int i1)
{
	age = i1;
}

unsigned int Patient::getAge()
{
	return age;
}

void Patient::setSpecialty(SpecCode sc1)
{
	specialty = sc1;
}

SpecCode Patient::getSpecialty()
{
	return specialty;
}

void Patient::setEmergency(bool b1)
{
	emergency = b1;
}

bool Patient::getEmergency()
{
	return emergency;
}

// Donut need u
//Patient::~Patient()
//{
//}
