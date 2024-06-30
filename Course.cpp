#include "Course.h"

// constructor
Course::Course() {
	CRN = 000;
	year = 0000;
	credits = 0;
	title = "default";
	department = "default";
	time = "default";
	days = "default";
	semester = "default";
}

Course::Course(int num, int in_year, int cr, string in_title, string dept, string t, string d, string sem) {
	CRN = num;
	year = in_year;
	credits = cr;
	title = in_title;
	department = dept;
	time = t;
	days = d;
	semester = sem;
}

// method
void Course::print_info() {
	cout << "CRN: " << CRN << ", Title: " << title << endl;
	cout << department << ", " << semester << " " << year << endl;
	cout << time << ", " << days << endl;
	cout << "Credits: " << credits << endl;
}

// destructor
Course::~Course() {

}