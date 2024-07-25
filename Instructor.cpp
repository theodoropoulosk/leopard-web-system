#include "Instructor.h"

// constructor
Instructor::Instructor() {
	name = "default";
	surname = "default";
	email = "default";
	title = "default";
	department = "default";
	ID = 00000;
	hireyear = 0000;
}

Instructor::Instructor(string first, string last, string em, string in_title, string dept, int id, int year)
: User(first, last, em, id) {
	name = first;
	surname = last;
	email = em;
	title = in_title;
	department = dept;
	ID = id;
	hireyear = year;
}

// method
void Instructor::print_schedule() {
	/*sqlite3* DB;
	int exit = 0;
	exit = sqlite3_open("assignment3.db", &DB);

	string query3 = "SELECT * FROM COURSE WHERE COURSE.DEPARTMENT NOT IN (SELECT INSTRUCTOR.DEPT FROM INSTRUCTOR)";

	sqlite3_exec(DB, query3.c_str(), NULL, 0, NULL);

	sqlite3_close(DB);*/
}

void Instructor::print_class_list() {
	cout << "Method for printing class list called by Instructor" << endl;
}

void Instructor::search_courses() {
	cout << "Method for searching courses called by Instructor" << endl;
}

void Instructor::print_info() {
	cout << "ID: " << ID << ", Name: " << name << " " << surname << endl;
	cout << "Title: " << title << ", Hire year: " << hireyear << endl;
	cout << "Department: " << department << endl;
	cout << "email: " << email << "@wit.edu" << endl;
}


// destructor
Instructor::~Instructor() {

}