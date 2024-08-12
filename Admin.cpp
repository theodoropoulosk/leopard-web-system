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
void Admin::add_courses(string crn, string title, string dept, string time,
	string days, string semester, string year, string credits) {
	sqlite3* DB;
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

	sqlite3_close(DB);
}

void Admin::remove_courses(int in_crn) {
	sqlite3* DB;
	int exit = 0;
	exit = sqlite3_open("assignment3.db", &DB);
	char* messageError;

	string crn = std::to_string(in_crn);
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

void Admin::add_instructor(string id, string name, string surname, string title,
	string hireyear, string dept, string email, string pass) {
	sqlite3* DB;
	int exit = 0;
	exit = sqlite3_open("assignment3.db", &DB);
	char* messageError;

	string sql("INSERT INTO INSTRUCTOR VALUES(" + id + ",'" + name + "','" + surname + "','" + title + "'," +
		hireyear + ",'" + dept + "','" + email + "','" + pass + "');");

	exit = sqlite3_exec(DB, sql.c_str(), NULL, 0, &messageError);

	if (exit != SQLITE_OK)
	{
		std::cerr << "Error Insert" << std::endl;
		sqlite3_free(messageError);
	}
	else
		std::cout << "Records created Successfully!" << std::endl;

	sqlite3_close(DB);
}

void Admin::remove_instructor(string id_in) {
	sqlite3* DB;
	int exit = 0;
	exit = sqlite3_open("assignment3.db", &DB);
	char* messageError;

	string sql("DELETE FROM INSTRUCTOR WHERE ID = " + id_in);

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

void Admin::add_student(string id, string name, string surname,
	string gradyear, string major, string email, string pass) {
	sqlite3* DB;
	int exit = 0;
	exit = sqlite3_open("assignment3.db", &DB);
	char* messageError;

	string sql("INSERT INTO STUDENT VALUES(" + id + ",'" + name + "','" + surname + "'," + gradyear + ",'"
		+ major + "','" + email + "','" + pass + "');");

	exit = sqlite3_exec(DB, sql.c_str(), NULL, 0, &messageError);

	if (exit != SQLITE_OK)
	{
		std::cerr << "Error Insert" << std::endl;
		sqlite3_free(messageError);
	}
	else
		std::cout << "Records created Successfully!" << std::endl;

	sqlite3_close(DB);
}

void Admin::remove_student(string id_in) {
	sqlite3* DB;
	int exit = 0;
	exit = sqlite3_open("assignment3.db", &DB);
	char* messageError;

	string sql("DELETE FROM STUDENT WHERE ID = " + id_in);

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

void Admin::print_roster() {
	cout << "Method for printing roster called by Admin" << endl;
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