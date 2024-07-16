#include "Admin.h"

// constructor
Admin::Admin() {
	name = "default";
	surname = "default";
	ID = 00000;
}
Admin::Admin(string first, string last, string em, string in_title, string in_office, int id)
	: User(first, last, em, id) {
	name = first;
	surname = last;
	email = em;
	title = in_title;
	office = in_office;
	ID = id;
}

// method
void Admin::add_courses() {
	sqlite3* DB;
	ifstream readFile4("add_course_test.txt");
	string crn, title, dept, time, days, semester, year, credits;

	for (int i = 0; i < 2; i++) {
		cout << "Enter CRN of new course: ";
		readFile4 >> crn;
		cout << crn << endl;
		cout << "Enter title of new course: ";
		readFile4.ignore();	// this solution here: https://cplusplus.com/forum/beginner/132429/
		getline(readFile4, title);
		cout << title << endl;
		cout << "Enter department of new course: ";
		readFile4 >> dept;
		cout << dept << endl;
		cout << "Enter time of new course: ";
		readFile4 >> time;
		cout << time << endl;
		cout << "Enter days of new course: ";
		readFile4 >> days;
		cout << days << endl;
		cout << "Enter the semester the course is available: ";
		readFile4 >> semester;
		cout << semester << endl;
		cout << "Enter year the course is available: ";
		readFile4 >> year;
		cout << year << endl;
		cout << "Enter credits of new course: ";
		readFile4 >> credits;
		cout << credits << endl;

		int exit = 0;
		exit = sqlite3_open("assignment3.db", &DB);
		char* messageError;

		string sql("INSERT INTO COURSE VALUES(" + crn + ",'" + title + "','" + dept + "','" + time + "','" +
			days + "','" + semester + "','" + year + "'," + credits + ");");

		exit = sqlite3_exec(DB, sql.c_str(), NULL, 0, &messageError);

		if (exit != SQLITE_OK)
		{
			std::cerr << "Error Insert" << std::endl;
			sqlite3_free(messageError);
		}
		else
			std::cout << "Records created Successfully!" << std::endl;
	}

	readFile4.close();

	sqlite3_close(DB);
}

void Admin::remove_courses(int crn) {
	sqlite3* DB;
	int exit = 0;
	exit = sqlite3_open("assignment3.db", &DB);
	char* messageError;
	
	string sql("DELETE FROM COURSE WHERE CRN = " + crn);

	exit = sqlite3_exec(DB, sql.c_str(), NULL, 0, &messageError);

	if (exit != SQLITE_OK)
	{
		std::cerr << "Error Delete" << std::endl;
		sqlite3_free(messageError);
	}
	else
		std::cout << "Records deleted Successfully!" << std::endl;

	sqlite3_close(DB);
}

void Admin::add_remove_user() {
	cout << "Method for adding/removing user called by Admin" << endl;
}

void Admin::add_remove_student() {
	cout << "Method for adding/removing student called by Admin" << endl;
}

void Admin::print_roster() {
	cout << "Method for printing roster called by Admin" << endl;
}

void Admin::search_courses() {
	cout << "Method for searching courses called by Admin" << endl;
}

void Admin::print_info() {
	cout << "ID: " << ID << ", Name: " << name << " " << surname << endl;
	cout << "Title: " << title << endl;
	cout << "Office: " << office << endl;
	cout << "email: " << email << "@wit.edu" << endl;
}

// destructor
Admin::~Admin() {

}