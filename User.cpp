#include "User.h"

// constructor
User::User() {
	name = "default";
	surname = "default";
	email = "default";
	ID = 00000;
}

User::User(string first, string last, string em, int id) {
	name = first;
	surname = last;
	email = em;
	ID = id;
}

// method
void User::change_first_name(string new_name) {
	name = new_name;
}
void User::change_last_name(string new_name) {
	surname = new_name;
}

void User::change_ID(int new_id) {
	ID = new_id;
}

void User::print_info() {
	cout << "ID: " << ID << ", Name: " << name << " " << surname << endl;
	cout << "email: " << email << "@wit.edu" << endl;
}

// destructor
User::~User() {

}