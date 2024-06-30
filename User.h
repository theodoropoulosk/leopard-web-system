#pragma once
#include <string>
#include <iostream>

using std::string;
using std::cout;
using std::cin;
using std::endl;

class User
{
	// attribute
public:
	int ID;
	string name, surname, email;

	// constructor
	User();
	User(string first, string last, string em, int id);

	// method
	void change_first_name(string new_name);
	void change_last_name(string new_name);
	void change_ID(int new_id);
	virtual void print_info();

	// destructor
	~User();
};