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

// for testing
#include <fstream>
using std::ifstream;

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
static int callback2save(void* data, int argc, char** argv, char** azColName) {
	
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
	const char* sql = "SELECT * FROM COURSE;"; // Corrected table name
	sqlite3_stmt* stmt;

	if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK) {
		cerr << "Failed to prepare statement: " << sqlite3_errmsg(db) << endl;
		return;
	}

	cout << "Courses:\n";
	while (sqlite3_step(stmt) == SQLITE_ROW) {
		cout << "CRN: " << sqlite3_column_text(stmt, 0)
			<< ", Title: " << sqlite3_column_text(stmt, 1)
			<< ", Department: " << sqlite3_column_text(stmt, 2)
			<< ", Time: " << sqlite3_column_text(stmt, 3)
			<< ", Days: " << sqlite3_column_text(stmt, 4)
			<< ", Semester: " << sqlite3_column_text(stmt, 5)
			<< ", Year: " << sqlite3_column_text(stmt, 6)
			<< ", Credits: " << sqlite3_column_text(stmt, 7) << "\n";
	}

	sqlite3_finalize(stmt);
}

// Daniel
void searchCoursesByParameters(sqlite3* db, const string& param, const string& value) {
	string sql = "SELECT * FROM COURSE WHERE " + param + " = ?;"; // Corrected table name
	sqlite3_stmt* stmt;

	if (sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
		cerr << "Failed to prepare statement: " << sqlite3_errmsg(db) << endl;
		return;
	}

	sqlite3_bind_text(stmt, 1, value.c_str(), -1, SQLITE_STATIC);

	cout << "Courses:\n";
	while (sqlite3_step(stmt) == SQLITE_ROW) {
		cout << "CRN: " << sqlite3_column_text(stmt, 0)
			<< ", Title: " << sqlite3_column_text(stmt, 1)
			<< ", Department: " << sqlite3_column_text(stmt, 2)
			<< ", Time: " << sqlite3_column_text(stmt, 3)
			<< ", Days: " << sqlite3_column_text(stmt, 4)
			<< ", Semester: " << sqlite3_column_text(stmt, 5)
			<< ", Year: " << sqlite3_column_text(stmt, 6)
			<< ", Credits: " << sqlite3_column_text(stmt, 7) << "\n";
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
			cout << "Enter parameter (DEPARTMENT/TIME/DAYS/SEMESTER/YEAR/CREDITS): ";
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

	/* ---------------- Log-in Code ---------------- */
	string username, password;
	ifstream readFile1("login_test.txt");
	do {
		cout << "Enter username: ";
		readFile1 >> username;
		cout << username << endl;
		cout << "Enter password: ";
		readFile1 >> password;
		cout << password << endl;
	} while (!loginUser(DB, username, password));
	readFile1.close();

	menu(DB); // Daniel

	/* ---------------- Konstantinos ---------------- */
	vector<string> container;

	cout << "Printing the name of a student" << endl;
	string query4 = "SELECT NAME FROM STUDENT WHERE STUDENT.ID = 10011";
	exit = sqlite3_exec(DB, query4.c_str(), callback2save, &container, &messageError);
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
	exit = sqlite3_exec(DB, query5.c_str(), callback2save, &container, &messageError);
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
	Admin admin1("Simon","Stabler","stablers","VP","Dobbs 305",11190);
	//admin1.add_courses();
	Student student_claire(cname, clast, email, major, id_int, year_int);
	Student student2(container[1], container[2], container[5], container[4], stoi(container[0]), stoi(container[3]));
	student_claire.print_info();
	student2.print_info();

	container.clear();

	/* ---- Testing adding courses to the database as an Admin ----*/
	admin1.add_courses();

	/* ---- Removing courses from the database as an Admin ---- */
	int crn;
	ifstream readFile3("remove_course_test.txt");
	for (int i = 0; i < 5; i++) {
		readFile3 >> crn;
		admin1.remove_courses(crn);
	}
	readFile3.close();
	
	/* ---- Printing course roster for instructor ---- */

	string dept;	// department of the instructor
	ifstream readFile2("course_roster_test.txt");
	for (int i = 0; i < 4; i++) {
		readFile2 >> dept;
		string query6 = "SELECT * FROM COURSE WHERE COURSE.DEPARTMENT = '" + dept + "'";
		exit = sqlite3_exec(DB, query6.c_str(), callback2save, &container, &messageError);

		if (exit != SQLITE_OK)
		{
			std::cerr << "Error getting course data" << std::endl;
			sqlite3_free(messageError);
		}
		else
			cout << "Course data stored successfully!" << std::endl;

		cout << "CRN -- TITLE -- DEPT -- TIME -- DAYS -- SEMESTER -- YEAR -- CREDITS" << endl;
		int L = container.size();
		for (int i = 0; i < L; i++) {
			cout << container[0];
			container.erase(container.begin());
			if ((((i + 1) % 8) == 0) && (i > 0))
				cout << endl;
			else
				cout << " -- ";
		}
		container.clear();
	}
	
	readFile2.close();

	
	

	

	sqlite3_close(DB);
	return 0;
}