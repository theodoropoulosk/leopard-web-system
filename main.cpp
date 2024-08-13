#include <iostream>
#include "User.h"
#include "Student.h"
#include "Instructor.h"
#include "Admin.h"
//#include "Course.h"
#include "sqlite3.h"
#include <string>
#include <vector>
#include <stdio.h>
#include <Python.h>


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
void menuStudent(sqlite3* db, string username) {
	int choice;
	string param, value;

	vector<string> container;
	vector<string> container2;
	int exit = 0;
	char* messageError;

	string query = "SELECT * FROM STUDENT WHERE STUDENT.EMAIL = '" + username + "'";
	exit = sqlite3_exec(db, query.c_str(), callback2save, &container, &messageError);

	/*if (exit != SQLITE_OK)
	{
		std::cerr << "Error getting name" << std::endl;
		sqlite3_free(messageError);
	}
	else
		cout << "Data saved Successfully" << std::endl;*/

	string name = container[1];
	string last = container[2];
	string email = container[5];
	string major = container[4];
	string id = container[0];
	string year = container[3];
//	cout << name << " " << last << " " << email << " " << major << " " << id << " " << year << endl;
	int id_int = stoi(id);
	int year_int = stoi(year);
	Student student1(name, last, email, major, id_int, year_int);
	container.clear();

	int L;
	int found = 0;
	string crn;
	string search[5];
	search[0] = "SELECT CRN FROM ROSTER WHERE ROSTER.STUDENT1 = '" + email + "'";
	search[1] = "SELECT CRN FROM ROSTER WHERE ROSTER.STUDENT2 = '" + email + "'";
	search[2] = "SELECT CRN FROM ROSTER WHERE ROSTER.STUDENT3 = '" + email + "'";
	search[3] = "SELECT CRN FROM ROSTER WHERE ROSTER.STUDENT4 = '" + email + "'";
	search[4] = "SELECT CRN FROM ROSTER WHERE ROSTER.STUDENT5 = '" + email + "'";

	do {
		cout << "Menu:\n";
		cout << "1. Search All Courses\n";
		cout << "2. Search Courses by Parameter\n";
		cout << "3. Register for Course\n";
		cout << "4. Drop Course\n";
		cout << "5. Print Schedule\n";
		cout << "6. Print Information\n";
		cout << "7. Exit\n";
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
		case 3:	// register for course
			cout << "Enter the CRN of the course: ";
			cin >> crn;

			query = "SELECT * FROM ROSTER WHERE ROSTER.CRN = '" + crn + "'";
			exit = sqlite3_exec(db, query.c_str(), callback2save, &container, &messageError);

			cout << "CRN -- STUDENT 1 -- STUDENT 2 -- STUDENT 3 -- STUDENT 4 -- STUDENT 5" << endl;
			L = container.size();
			for (int i = 0; i < L; i++) {
				cout << container[i];
				//container.erase(container.begin());
				if ((((i + 1) % 6) == 0) && (i > 0))
					cout << endl;
				else
					cout << " -- ";
			}
			if (container[5] != "EMPTY") {
				cout << "There is no more space in this course." << endl;
			}
			else {
				for (int i = 1; i < 6; i++) {
					if (container[i] == email) {
						found = 1;
					}
				}
				if (found == 1) {
					cout << "Student is already registered for this course." << endl;
					break;
				}
				else {
					for (int i = 1; i < 6; i++) {
						if (container[i] == "EMPTY") {
							container[i] = email;
							break;
						}
					}
				}
			}
			query = ("DELETE FROM ROSTER WHERE CRN = " + crn);
			exit = sqlite3_exec(db, query.c_str(), NULL, 0, &messageError);
			query = ("INSERT INTO ROSTER VALUES(" + container[0] + ",'" + container[1] + "','" + container[2] + "','" +
				container[3] + "','" + container[4] + "','" + container[5] + "');");
			exit = sqlite3_exec(db, query.c_str(), NULL, 0, &messageError);
			if (exit != SQLITE_OK)
			{
				std::cerr << "Error Insert" << std::endl;
				sqlite3_free(messageError);
			}
			else
				std::cout << "Roster created successfully!" << std::endl;

			container.clear();
			break;
		case 4:	// drop course
			cout << "Enter the CRN of the course: ";
			cin >> crn;

			query = "SELECT * FROM ROSTER WHERE ROSTER.CRN = '" + crn + "'";
			exit = sqlite3_exec(db, query.c_str(), callback2save, &container, &messageError);

			cout << "CRN -- STUDENT 1 -- STUDENT 2 -- STUDENT 3 -- STUDENT 4 -- STUDENT 5" << endl;
			L = container.size();
			for (int i = 0; i < L; i++) {
				cout << container[i];
				//container.erase(container.begin());
				if ((((i + 1) % 6) == 0) && (i > 0))
					cout << endl;
				else
					cout << " -- ";
			}
			if (container[1] == "EMPTY") {
				cout << "There are no students in this course." << endl;
			}
			else {
				for (int i = 1; i < 6; i++) {
					if (container[i] == email) {
						container.erase(container.begin() + i);
						container.push_back("EMPTY");
						break;
					}
				}
			}
			query = ("DELETE FROM ROSTER WHERE CRN = " + crn);
			exit = sqlite3_exec(db, query.c_str(), NULL, 0, &messageError);
			query = ("INSERT INTO ROSTER VALUES(" + container[0] + ",'" + container[1] + "','" + container[2] + "','" +
				container[3] + "','" + container[4] + "','" + container[5] + "');");
			exit = sqlite3_exec(db, query.c_str(), NULL, 0, &messageError);
			if (exit != SQLITE_OK)
			{
				std::cerr << "Error Insert" << std::endl;
				sqlite3_free(messageError);
			}
			else
				std::cout << "Roster created successfully!" << std::endl;
			container.clear();
			break;
		case 5:	// print schedule
			cout << "CRN -- TITLE -- DEPT -- TIME -- DAYS -- SEMESTER -- YEAR -- CREDITS" << endl;
			for (int i = 0; i < 5; i++) {
				exit = sqlite3_exec(db, search[i].c_str(), callback2save, &container, &messageError);
				L = container.size();
				if (L != 0) {
					query = "SELECT * FROM COURSE WHERE COURSE.CRN = " + container[0];
					exit = sqlite3_exec(db, query.c_str(), callback2save, &container2, &messageError);
					L = container2.size();
					for (int i = 0; i < L; i++) {
						cout << container2[0];
						container2.erase(container2.begin());
						if ((((i + 1) % 8) == 0) && (i > 0))
							cout << endl;
						else
							cout << " -- ";
					}
					container2.clear();
				}
				container.clear();
			}
			break;
		case 6:
			student1.print_info();
			break;
		case 7:
			cout << "Exiting...\n";
			break;
		default:
			cout << "Invalid choice, please try again.\n";
		}
	} while (choice != 7);

	student1.~student1();
}

void menuInstructor(sqlite3* db, string username) {
	int choice;
	string param, value;

	vector<string> container;
	int exit = 0;
	char* messageError;

	string query = "SELECT * FROM INSTRUCTOR WHERE INSTRUCTOR.EMAIL = '" + username + "'";
	exit = sqlite3_exec(db, query.c_str(), callback2save, &container, &messageError);

	/*if (exit != SQLITE_OK)
	{
		std::cerr << "Error getting name" << std::endl;
		sqlite3_free(messageError);
	}
	else
		cout << "Data saved Successfully" << std::endl;*/

	string name = container[1];
	string last = container[2];
	string title = container[3];
	string dept = container[5];
	string email = container[6];
	string id = container[0];
	string year = container[4];
	//	cout << name << " " << last << " " << email << " " << major << " " << id << " " << year << endl;
	int id_int = stoi(id);
	int year_int = stoi(year);
	Instructor instructor1(name, last, email, title, dept, id_int, year_int);
	container.clear();

	do {
		cout << "Menu:\n";
		cout << "1. Search All Courses\n";
		cout << "2. Search Courses by Parameter\n";
		cout << "3. Print Information\n";
		cout << "4. Print Instructor's Courses\n";
		cout << "5. Print Course Roster\n";
		cout << "6. Exit\n";
		cout << "Enter your choice: ";
		cin >> choice;

		int L;
		string crn;

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
			instructor1.print_info();
			break;
		case 4:	// printing instructor's courses
			query = "SELECT * FROM COURSE WHERE COURSE.DEPARTMENT = '" + dept + "'";
			exit = sqlite3_exec(db, query.c_str(), callback2save, &container, &messageError);

			/*if (exit != SQLITE_OK)
			{
				std::cerr << "Error getting course data" << std::endl;
				sqlite3_free(messageError);
			}
			else
				cout << "Course data stored successfully!" << std::endl;*/

			cout << "CRN -- TITLE -- DEPT -- TIME -- DAYS -- SEMESTER -- YEAR -- CREDITS" << endl;
			L = container.size();
			for (int i = 0; i < L; i++) {
				cout << container[0];
				container.erase(container.begin());
				if ((((i + 1) % 8) == 0) && (i > 0))
					cout << endl;
				else
					cout << " -- ";
			}
			container.clear();
			break;
		case 5:	// print course roster
			cout << "Enter CRN of course: ";
			cin >> crn;

			query = "SELECT * FROM ROSTER WHERE ROSTER.CRN = '" + crn + "'";
			exit = sqlite3_exec(db, query.c_str(), callback2save, &container, &messageError);

			cout << "CRN -- STUDENT 1 -- STUDENT 2 -- STUDENT 3 -- STUDENT 4 -- STUDENT 5" << endl;
			L = container.size();
			for (int i = 0; i < L; i++) {
				cout << container[0];
				container.erase(container.begin());
				if ((((i + 1) % 6) == 0) && (i > 0))
					cout << endl;
				else
					cout << " -- ";
			}
			container.clear();
			break;
		case 6:
			cout << "Exiting...\n";
			break;
		default:
			cout << "Invalid choice, please try again.\n";
		}
	} while (choice != 6);

	instructor1.~instructor1();
}

void menuAdmin(sqlite3* db, string username) {
	int choice;
	string param, value;

	vector<string> container;
	int exit = 0;
	char* messageError;

	string query = "SELECT * FROM ADMIN WHERE ADMIN.EMAIL = '" + username + "'";
	exit = sqlite3_exec(db, query.c_str(), callback2save, &container, &messageError);

	/*if (exit != SQLITE_OK)
	{
		std::cerr << "Error getting name" << std::endl;
		sqlite3_free(messageError);
	}
	else
		cout << "Data saved Successfully" << std::endl;*/

	string name = container[1];
	string last = container[2];
	string title = container[3];
	string email = container[5];
	string office = container[4];
	string id = container[0];
	//	cout << name << " " << last << " " << email << " " << major << " " << id << " " << year << endl;
	int id_int = stoi(id);
	Admin admin1(name, last, email, title, office, id_int);
	container.clear();

	do {
		cout << "Menu:\n";
		cout << "1. Search All Courses\n";
		cout << "2. Search Courses by Parameter\n";
		cout << "3. Print Information\n";
		cout << "4. Print Course Roster\n";
		cout << "5. Add Course\n";
		cout << "6. Remove Course\n";
		cout << "7. Add Instructor\n";
		cout << "8. Remove Instructor\n";
		cout << "9. Add Student\n";
		cout << "10. Remove Student\n";
		cout << "11. Add Student to Course\n";
		cout << "12. Remove Student from Course\n";
		cout << "13. Exit\n";
		cout << "Enter your choice: ";
		cin >> choice;

		string crn, course_title, course_dept, time, days, semester, course_year, credits;
		int course_crn, L;
		string id2, name2, surname2, title2, year2, dept2, email2, major2, pass2;
		int found = 0;

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
			admin1.print_info();
			break;
		case 4:	// print course roster
			cout << "Enter CRN of course: ";
			cin >> crn;

			query = "SELECT * FROM ROSTER WHERE ROSTER.CRN = '" + crn + "'";
			exit = sqlite3_exec(db, query.c_str(), callback2save, &container, &messageError);

			cout << "CRN -- STUDENT 1 -- STUDENT 2 -- STUDENT 3 -- STUDENT 4 -- STUDENT 5" << endl;
			L = container.size();
			for (int i = 0; i < L; i++) {
				cout << container[0];
				container.erase(container.begin());
				if ((((i + 1) % 6) == 0) && (i > 0))
					cout << endl;
				else
					cout << " -- ";
			}
			container.clear();
			break;
		case 5: // add courses
			cout << "Enter CRN of new course: ";
			cin >> crn;
			cout << "Enter title of new course: ";
			cin.ignore();	// this solution here: https://cplusplus.com/forum/beginner/132429/
			getline(cin, title);
			cout << "Enter department of new course: ";
			cin >> course_dept;
			cout << "Enter time of new course: ";
			cin >> time;
			cout << "Enter days of new course: ";
			cin >> days;
			cout << "Enter the semester the course is available: ";
			cin >> semester;
			cout << "Enter year the course is available: ";
			cin >> course_year;
			cout << "Enter credits of new course: ";
			cin >> credits;
			admin1.add_courses(crn, title, course_dept, time, days, semester, course_year, credits);
			break;
		case 6: // remove courses
			cout << "Please enter the CRN of the course you want to remove: ";
			cin >> crn;
			course_crn = stoi(crn);
			admin1.remove_courses(course_crn);
			break;
		case 7: // add instructor
			cout << "Adding an instructor" << endl;
			cout << "Enter ID number of new instructor: ";
			cin >> id2;
			cout << "Enter name of new instructor: ";
			cin >> name2;
			cout << "Enter surname of new instructor: ";
			cin >> surname2;
			cout << "Enter title of new instructor: ";
			cin.ignore();	// this solution here: https://cplusplus.com/forum/beginner/132429/
			getline(cin, title2);
			cout << "Enter hire year of new instructor: ";
			cin >> year2;
			cout << "Enter department of new instructor: ";
			cin >> dept2;
			cout << "Enter email address of new instructor: ";
			cin >> email2;
			cout << "Enter password of new instructor: ";
			cin >> pass2;
			admin1.add_instructor(id2, name2, surname2, title2, year2, dept2, email2, pass2);
			break;
		case 8: // remove instructor
			cout << "Enter the ID of the instructor you want to remove: ";
			cin >> id2;
			admin1.remove_instructor(id2);
			break;
		case 9: // add student
			cout << "Adding a student" << endl;
			cout << "Enter ID of new student: ";
			cin >> id2;
			cout << "Enter name of new student: ";
			cin >> name2;
			cout << "Enter surname of new student: ";
			cin >> surname2;
			cout << "Enter graduation year of new student: ";
			cin >> year2;
			cout << "Enter major of new student: ";
			cin >> major2;
			cout << "Enter email of new student: ";
			cin >> email2;
			cout << "Enter password of new student: ";
			cin >> pass2;
			admin1.add_student(id2, name2, surname2, year2, major2, email2, pass2);
			break;
		case 10:	// remove student
			cout << "Enter the ID of the student you want to remove: ";
			cin >> id2;
			admin1.remove_student(id2);
			break;
		case 11:	// add student to course
			cout << "Enter the CRN of the course: ";
			cin >> crn;

			query = "SELECT * FROM ROSTER WHERE ROSTER.CRN = '" + crn + "'";
			exit = sqlite3_exec(db, query.c_str(), callback2save, &container, &messageError);

			cout << "CRN -- STUDENT 1 -- STUDENT 2 -- STUDENT 3 -- STUDENT 4 -- STUDENT 5" << endl;
			L = container.size();
			for (int i = 0; i < L; i++) {
				cout << container[i];
				//container.erase(container.begin());
				if ((((i + 1) % 6) == 0) && (i > 0))
					cout << endl;
				else
					cout << " -- ";
			}
			if (container[5] != "EMPTY") {
				cout << "There is no more space in this course." << endl;
			}
			else {
				cout << "Enter the username of the student: ";
				cin >> email2;
				for (int i = 1; i < 6; i++) {
					if (container[i] == email2) {
						found = 1;
					}
				}
				if (found == 1) {
					cout << "Student is already registered for this course." << endl;
					break;
				}
				else {
					for (int i = 1; i < 6; i++) {
						if (container[i] == "EMPTY") {
							container[i] = email2;
							break;
						}
					}
				}
			}
			query = ("DELETE FROM ROSTER WHERE CRN = " + crn);
			exit = sqlite3_exec(db, query.c_str(), NULL, 0, &messageError);
			query = ("INSERT INTO ROSTER VALUES(" + container[0] + ",'" + container[1] + "','" + container[2] + "','" +
				container[3] + "','" + container[4] + "','" + container[5] + "');");
			exit = sqlite3_exec(db, query.c_str(), NULL, 0, &messageError);
			if (exit != SQLITE_OK)
			{
				std::cerr << "Error Insert" << std::endl;
				sqlite3_free(messageError);
			}
			else
				std::cout << "Roster created successfully!" << std::endl;

			container.clear();
			break;
		case 12:	// remove student from course
			cout << "Enter the CRN of the course: ";
			cin >> crn;

			query = "SELECT * FROM ROSTER WHERE ROSTER.CRN = '" + crn + "'";
			exit = sqlite3_exec(db, query.c_str(), callback2save, &container, &messageError);

			cout << "CRN -- STUDENT 1 -- STUDENT 2 -- STUDENT 3 -- STUDENT 4 -- STUDENT 5" << endl;
			L = container.size();
			for (int i = 0; i < L; i++) {
				cout << container[i];
				//container.erase(container.begin());
				if ((((i + 1) % 6) == 0) && (i > 0))
					cout << endl;
				else
					cout << " -- ";
			}
			if (container[1] == "EMPTY") {
				cout << "There are no students in this course." << endl;
			}
			else {
				cout << "Enter the username of the student: ";
				cin >> email2;
				for (int i = 1; i < 6; i++) {
					if (container[i] == email2) {
						container.erase(container.begin() + i);
						container.push_back("EMPTY");
						break;
					}
				}
			}
			query = ("DELETE FROM ROSTER WHERE CRN = " + crn);
			exit = sqlite3_exec(db, query.c_str(), NULL, 0, &messageError);
			query = ("INSERT INTO ROSTER VALUES(" + container[0] + ",'" + container[1] + "','" + container[2] + "','" +
				container[3] + "','" + container[4] + "','" + container[5] + "');");
			exit = sqlite3_exec(db, query.c_str(), NULL, 0, &messageError);
			if (exit != SQLITE_OK)
			{
				std::cerr << "Error Insert" << std::endl;
				sqlite3_free(messageError);
			}
			else
				std::cout << "Roster created successfully!" << std::endl;
			container.clear();
			break;
		case 13:
			cout << "Exiting...\n";
			break;
		default:
			cout << "Invalid choice, please try again.\n";
		}
	} while (choice != 13);

	admin1.~admin1();
}

// Michael
bool isLoggedIn = false;
string loggedInUser;

// Michael
bool loginUser(sqlite3* DB, const string& username, const string& password) {
	int success = 0;
	string query[3];
	query[0] = "SELECT * FROM STUDENT WHERE EMAIL = '" + username + "' AND Password = '" + password + "';";
	query[1] = "SELECT * FROM INSTRUCTOR WHERE EMAIL = '" + username + "' AND Password = '" + password + "';";
	query[2] = "SELECT * FROM ADMIN WHERE EMAIL = '" + username + "' AND Password = '" + password + "';";
	sqlite3_stmt* stmt;

	for (int i = 0; i < 3; i++) {
		int rc = sqlite3_prepare_v2(DB, query[i].c_str(), -1, &stmt, 0);

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
			success = 1;
			break;
		}
		else success = 0;
	}
	if (success == 1)
		return true;
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
	// Initialize the Python interpreter
	Py_Initialize();

	// Path to your Python script
	const char* script_path = "C:/Users/Dan/source/repos/FINAL/GUI.py";

	// Open and run the Python script
	FILE* file = fopen(script_path, "r");
	if (file != nullptr) {
		PyRun_SimpleFile(file, script_path);
		fclose(file);
	}
	else {
		std::cerr << "Failed to open script: " << script_path << std::endl;
	}

	// Finalize the Python interpreter
	Py_Finalize();

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

	string username, password;
	do {
		cout << "Enter username: ";
		cin >> username;
		cout << "Enter password: ";
		cin >> password;
	} while (!loginUser(DB, username, password));

	int user_type;
	string query[3];
	query[0] = "SELECT * FROM STUDENT WHERE EMAIL = '" + username + "' AND Password = '" + password + "';";
	query[1] = "SELECT * FROM INSTRUCTOR WHERE EMAIL = '" + username + "' AND Password = '" + password + "';";
	query[2] = "SELECT * FROM ADMIN WHERE EMAIL = '" + username + "' AND Password = '" + password + "';";

	sqlite3_stmt* stmt;
	for (int i = 0; i < 3; i++) {
		int rc = sqlite3_prepare_v2(DB, query[i].c_str(), -1, &stmt, 0);

		if (rc != SQLITE_OK) {
			cerr << "Error preparing statement: " << sqlite3_errmsg(DB) << endl;
			return false;
		}
		rc = sqlite3_step(stmt);
		if (rc == SQLITE_ROW) {
			user_type = i + 1;
			sqlite3_finalize(stmt);;
			break;
		}
	}

	if (user_type == 1) {
		cout << "User type is: Student" << endl;
		menuStudent(DB, username);
	}
	else if (user_type == 2) {
		cout << "User type is: Instructor" << endl;
		menuInstructor(DB, username);
	}
	else if (user_type == 3) {
		cout << "User type is: Administrator" << endl;
		menuAdmin(DB, username);
	}

	sqlite3_close(DB);
	return 0;
}
