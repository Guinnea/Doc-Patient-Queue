#pragma once
#include "Specialty Codes.h"
#include "Patient.h"
#include <String>
#include <queue>
#include <iostream>

using namespace std;

class Doctor
{
public:
	//Constructors
	Doctor();
	Doctor(string s1, int i1, SpecCode sc1);
	//~Doctor(); Not needed

	//Setters and Getters
	void setName(string s1);
	string getName();
	void setRoom(int i1);
	int getRoom();
	void setSpecialty(SpecCode sc1);
	SpecCode getSpecialty();
	void operator=(Doctor d1);

	queue<Patient> q1;

private:
	string name;
	int roomNum;
	SpecCode specialty;
};

