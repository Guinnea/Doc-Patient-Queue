#pragma once
#include "Specialty Codes.h"
#include <String>
#include <iostream>

using namespace std;

class Patient
{
public:
	Patient();
	Patient(string s1, unsigned int i1, SpecCode sc1, bool b1);
	//~Patient(); Donut need
	void setName(string s1);
	string getName();
	void setAge(unsigned int i1);
	unsigned int getAge();
	void setSpecialty(SpecCode sc1);
	SpecCode getSpecialty();
	void setEmergency(bool b1);
	bool getEmergency();
	

private:
	string name;
	unsigned int age;
	SpecCode specialty;
	bool emergency;
};

