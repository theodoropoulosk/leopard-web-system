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
	cout << "Method for adding courses called by Admin" << endl;
}

void Admin::remove_courses() {
	cout << "Method for removing courses called by Admin" << endl;
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