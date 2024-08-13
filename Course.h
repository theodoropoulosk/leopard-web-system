#pragma once
#include <string>
#include <iostream>

using std::string;
using std::cout;
using std::cin;
using std::endl;

class Course
{
	// attribute
	int CRN, year, credits;
	string title, department, time, days, semester;

public:
	// constructor
	Course();
	Course(int num, int in_year, int cr, string in_title, string dept, string t, string d, string sem);

	// method
	void print_info();

	// destructor
	~Course();
};

