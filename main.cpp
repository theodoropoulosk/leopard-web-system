#include <iostream>
#include "User.h"
#include "Student.h"
#include "Instructor.h"
#include "Admin.h"
#include "Course.h"
#include "sqlite3.h"
#include <string>
#include <vector>
#include <stdio.h>

using namespace std;

static int callback(void* data, int argc, char** argv, char** azColName)
{
	int i;

	for (i = 0; i < argc; i++)
	{
		printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
	}

	printf("\n");

	return 0;
}

// Konstantinos
static int callbackStudent(void* data, int argc, char** argv, char** azColName) {
	
	int i = 0;
	if (argc == 0) return -1;
	auto& container = *static_cast<std::vector<std::string>*>(data);
	
	for (i = 0; i < argc; i++)
	{
		if (!argv[i]) container.push_back("NULL");
		else container.push_back(argv[i]);
	}
	
	return 0;
}

// Daniel
void searchAllCourses(sqlite3* db) {
	const char* sql = "SELECT * FROM courses;";
	sqlite3_stmt* stmt;

	if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK) {
		cerr << "Failed to prepare statement\n";
		return;
	}

	cout << "Courses:\n";
	while (sqlite3_step(stmt) == SQLITE_ROW) {
		cout << "Course ID: " << sqlite3_column_text(stmt, 0)
			<< ", Course Name: " << sqlite3_column_text(stmt, 1)
			<< ", Day/Time: " << sqlite3_column_text(stmt, 2) << "\n";
	}

	sqlite3_finalize(stmt);
}

// Daniel
void searchCoursesByParameters(sqlite3* db, const string& param, const string& value) {
	string sql = "SELECT * FROM courses WHERE " + param + " = ?;";
	sqlite3_stmt* stmt;

	if (sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
		cerr << "Failed to prepare statement\n";
		return;
	}

	sqlite3_bind_text(stmt, 1, value.c_str(), -1, SQLITE_STATIC);

	cout << "Courses:\n";
	while (sqlite3_step(stmt) == SQLITE_ROW) {
		cout << "Course ID: " << sqlite3_column_text(stmt, 0)
			<< ", Course Name: " << sqlite3_column_text(stmt, 1)
			<< ", Day/Time: " << sqlite3_column_text(stmt, 2) << "\n";
	}

	sqlite3_finalize(stmt);
}

// Daniel
void menu(sqlite3* db) {
	int choice;
	string param, value;

	do {
		cout << "Menu:\n";
		cout << "1. Search All Courses\n";
		cout << "2. Search Courses by Parameter\n";
		cout << "3. Exit\n";
		cout << "Enter your choice: ";
		cin >> choice;

		switch (choice) {
		case 1:
			searchAllCourses(db);
			break;
		case 2:
			cout << "Enter parameter (course_code/day_time): ";
			cin >> param;
			cout << "Enter value: ";
			cin >> value;
			searchCoursesByParameters(db, param, value);
			break;
		case 3:
			cout << "Exiting...\n";
			break;
		default:
			cout << "Invalid choice, please try again.\n";
		}
	} while (choice != 3);
}

// Michael
bool isLoggedIn = false;
string loggedInUser;

// Michael
bool loginUser(sqlite3* DB, const string& username, const string& password) {
	string query = "SELECT * FROM USER WHERE USERNAME = '" + username + "' AND PASSWORD = '" + password + "';";
	sqlite3_stmt* stmt;
	int rc = sqlite3_prepare_v2(DB, query.c_str(), -1, &stmt, 0);

	if (rc != SQLITE_OK) {
		cerr << "Error preparing statement: " << sqlite3_errmsg(DB) << endl;
		return false;
	}

	rc = sqlite3_step(stmt);
	if (rc == SQLITE_ROW) {
		isLoggedIn = true;
		loggedInUser = username;
		cout << "Login successful!" << endl;
		sqlite3_finalize(stmt);
		return true;
	}
	else {
		cout << "Login failed. Incorrect username or password." << endl;
		sqlite3_finalize(stmt);
		return false;
	}
}

// Michael
void logoutUser() {
	isLoggedIn = false;
	loggedInUser = "";
	cout << "Logged out successfully!" << endl;
}

int main(int argc, char** argv)
{
	sqlite3* DB;

	int exit = 0;

	exit = sqlite3_open("assignment3.db", &DB);		//open the database

	char* messageError;

	/* ---------------- Daniel ---------------- */
	if (exit) {
		cerr << "Can't open database: " << sqlite3_errmsg(DB) << endl;
		return(0);
	}
	else {
		cout << "Opened database successfully!" << endl;
	}

	/* ---------------- Michael ---------------- */
	string userTable = "CREATE TABLE USER("
		"USERNAME TEXT PRIMARY KEY, "
		"PASSWORD TEXT NOT NULL); ";

	exit = sqlite3_exec(DB, userTable.c_str(), NULL, 0, &messageError);
	if (exit != SQLITE_OK) {
		cerr << "Error creating USER table: " << messageError << endl;
		sqlite3_free(messageError);
	}
	else {
		cout << "USER table created successfully!" << endl;
	}

	string insertUsers = "INSERT OR IGNORE INTO USER (USERNAME, PASSWORD) VALUES('admin', 'admin123');"
		"INSERT OR IGNORE INTO USER (USERNAME, PASSWORD) VALUES('user1', 'password1');";
	exit = sqlite3_exec(DB, insertUsers.c_str(), NULL, 0, &messageError);
	if (exit != SQLITE_OK) {
		cerr << "Error inserting users: " << messageError << endl;
		sqlite3_free(messageError);
	}
	else {
		cout << "Sample users inserted successfully!" << endl;
	}

	string username, password;
	do {
		cout << "Enter username: ";
		cin >> username;
		cout << "Enter password: ";
		cin >> password;
	} while (!loginUser(DB, username, password));

	menu(DB); // Daniel

	/* ---------------- Konstantinos ---------------- */
	vector<string> container;

	cout << "Printing the name of a student" << endl;
	string query4 = "SELECT NAME FROM STUDENT WHERE STUDENT.ID = 10011";
	exit = sqlite3_exec(DB, query4.c_str(), callbackStudent, &container, &messageError);
	cout << endl << query4 << endl;

	if (exit != SQLITE_OK)
	{
		std::cerr << "Error getting name" << std::endl;
		sqlite3_free(messageError);
	}
	else
		cout << "Name saved Successfully" << std::endl;
	
	string cname;
	cname = container[0];
	cout << "cname variable: " << cname << endl;;

	container.clear();
	cout << endl << "Creating a student object..." << endl;
	string query5 = "SELECT * FROM STUDENT WHERE STUDENT.ID = 10011";
	exit = sqlite3_exec(DB, query5.c_str(), callbackStudent, &container, &messageError);
	cout << endl << query5 << endl;

	if (exit != SQLITE_OK)
	{
		std::cerr << "Error getting name" << std::endl;
		sqlite3_free(messageError);
	}
	else
		cout << "Name saved Successfully" << std::endl;

	cname = container[1];
	string clast = container[2];
	string email = container[5];
	string major = container[4];
	string id = container[0];
	string year = container[3];
	cout << cname << " " << clast << " " << email << " " << major << " " << id << " " << year << endl;
	int id_int = stoi(id);
	int year_int = stoi(year);
	Student student1("Simon", "Stabler", "stablers", "BSCO", 10001, 2024);
	Student student_claire(cname, clast, email, major, id_int, year_int);
	student_claire.print_info();

	sqlite3_close(DB);
	return 0;
}