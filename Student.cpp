#include "Student.h"

// constructor
Student::Student() {
	name = "default";
	surname = "default";
	email = "default";
	major = "default";
	ID = 00000;
	gradyear = 0000;
}
Student::Student(string first, string last, string em, string in_major, int id, int year)
: User(first, last, em, id) {
	name = first;
	surname = last;
	email = em;
	major = in_major;
	ID = id;
	gradyear = year;
}

// method
void Student::search_courses() {
	cout << "Method to search courses called by Student" << endl;
}

void Student::add_drop_courses() {
	cout << "Method to add/drop courses called by Student" << endl;
}

void Student::print_schedule() {
	cout << "Method to print schedule called by Student" << endl;
}

void Student::print_info() {
	cout << "ID: " << ID << ", Name: " << name << " " << surname << endl;
	cout << "Major: " << major << ", Graduation year: " << gradyear << endl;
	cout << "email: " << email << "@wit.edu" << endl;
}

// destructor
Student::~Student() {

}