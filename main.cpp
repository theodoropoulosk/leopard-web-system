#include <iostream> 
#include "sqlite3.h" 
#include <string> 
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

int main(int argc, char** argv)
{
	sqlite3* DB;

	/*******************************************************************
	 Creating a table
	 Create a string then pass the string into the sqlite3_exec function
	********************************************************************/
	string table = "CREATE TABLE COURSE("
		"CRN INTEGER PRIMARY KEY, "
		"TITLE TEXT NOT NULL, "
		"DEPARTMENT TEXT NOT NULL, "
		"TIME TEXT NOT NULL, "
		"DAYS TEXT NOT NULL, "
		"SEMESTER TEXT NOT NULL, "
		"YEAR INTEGER NOT NULL, "
		"CREDITS INTEGER NOT NULL); ";

	int exit = 0;

	exit = sqlite3_open("assignment3.db", &DB);			//open the database

	char* messageError;

	// execute the create table command
	// sqlite3_exec( pointer to database file, string for sql command, callback function 
	//					(used to respond to queries, not used here), input to callback, error message address)
	exit = sqlite3_exec(DB, table.c_str(), NULL, 0, &messageError);

	if (exit != SQLITE_OK)
	{
		std::cerr << "Error Create Table" << std::endl;
		sqlite3_free(messageError);
	}
	else
		cout << "Table created Successfully" << std::endl;


	/*******************************************************************
	 Inserting values into a table.
	 Create a string then pass the string into the sqlite3_exec function
	********************************************************************/
	// hard-code (push) a few values into the database - NOTE you can create a single string with multiple INSERT commands
	string sql("INSERT INTO COURSE VALUES(101, 'Applied Programming', 'BSCO', '8:00-10:00', 'T-R', 'SUMMER', 2024, 3);"
		"INSERT INTO COURSE VALUES(102, 'Internal Combustion Engines', 'BSME', '15:30-17:00', 'W-F', 'FALL', 2024, 3);"
		"INSERT INTO COURSE VALUES(103, 'Network Theory', 'BSEE', '11:00-12:20', 'W-F', 'SPRING', 2024, 4);"
		"INSERT INTO COURSE VALUES(104, 'Global Economy', 'HUSS', '14:00-15:50', 'M-W', 'FALL', 2024, 3);"
		"INSERT INTO COURSE VALUES(105, 'Engineering Physics', 'BSAS', '9:30-10:50', 'M-W', 'FALL', 2024, 4);"
	);

	// execute the command
	exit = sqlite3_exec(DB, sql.c_str(), NULL, 0, &messageError);

	if (exit != SQLITE_OK)
	{
		std::cerr << "Error Insert" << std::endl;
		sqlite3_free(messageError);
	}
	else
		std::cout << "Records created Successfully!" << std::endl;

	// hard-code (push) a few values into STUDENT section
	string sql1("INSERT INTO STUDENT VALUES(10011, 'Claire', 'Dunphy', 2023, 'BSCO', 'dunphyc1');"
		"INSERT INTO STUDENT VALUES(10012, 'Sheldon', 'Cooper', 2004, 'BSAS', 'coopers2');"
	);

	// execute the command
	exit = sqlite3_exec(DB, sql1.c_str(), NULL, 0, &messageError);

	if (exit != SQLITE_OK)
	{
		std::cerr << "Error Insert" << std::endl;
		sqlite3_free(messageError);
	}
	else
		std::cout << "Records created Successfully!" << std::endl;

	// delete value from INSTRUCTOR section
	string sql2("DELETE FROM INSTRUCTOR WHERE ID = 20002;");

	// execute the command
	exit = sqlite3_exec(DB, sql2.c_str(), NULL, 0, &messageError);

	if (exit != SQLITE_OK)
	{
		std::cerr << "Error Delete" << std::endl;
		sqlite3_free(messageError);
	}
	else
		std::cout << "Records deleted Successfully!" << std::endl;	

	// update value of ADMIN
	string sql3("UPDATE ADMIN SET TITLE = 'Vice-President' WHERE ID = 30002;");

	// execute the command
	exit = sqlite3_exec(DB, sql3.c_str(), NULL, 0, &messageError);

	if (exit != SQLITE_OK)
	{
		std::cerr << "Error Update" << std::endl;
		sqlite3_free(messageError);
	}
	else
		std::cout << "Records updated Successfully!" << std::endl;

	/***********************************************
	 print all data in the table with SELECT * FROM
	 create string with query then execute
	 **********************************************/
	string query = "SELECT * FROM COURSE;";

	cout << endl << query << endl;		//print the string to screen

	// you need the callback function this time since there could be multiple rows in the table
	sqlite3_exec(DB, query.c_str(), callback, NULL, NULL);

	// print courses that match to an instructor
	cout << "Printing courses that match to an instructor..." << endl;
	string query2 = "SELECT * FROM INSTRUCTOR, COURSE WHERE INSTRUCTOR.DEPT = COURSE.DEPARTMENT";

	cout << endl << query2 << endl;		//print the string to screen

	// you need the callback function this time since there could be multiple rows in the table
	sqlite3_exec(DB, query2.c_str(), callback, NULL, NULL);

	// print courses that don't match to an instructor
	cout << "Printing courses that don't match to an instructor..." << endl;
	string query3 = "SELECT * FROM COURSE WHERE COURSE.DEPARTMENT NOT IN (SELECT INSTRUCTOR.DEPT FROM INSTRUCTOR)";

	cout << endl << query3 << endl;		//print the string to screen

	// you need the callback function this time since there could be multiple rows in the table
	sqlite3_exec(DB, query3.c_str(), callback, NULL, NULL);

	/**********************************************
	 adding from a file or user input
	 get input --> create string --> call command
	**********************************************/
	//string fname, lname;
	//string year;			//year is an integer in the database table, but we beed to create a string to pass in to the sql command
	//cout << endl << "Enter the first name, last name, and birth year of a famous programmer separated by spaces: ";
	//cin >> fname >> lname >> year;
	//cout << endl;

	// Adding from a file or a user input means some string additions (see below)
	//string UID = "6";
	//string userInput("INSERT INTO PROGRAMMER VALUES(" + UID + ",'" + fname + "','" + lname + "'," + year + ");");

	//exit = sqlite3_exec(DB, userInput.c_str(), callback, NULL, NULL);



	/***********************************
	 refining queries --> SELECT example
	 create string --> call command
	***********************************/
	//string surname = "SELECT SURNAME FROM PROGRAMMER WHERE BIRTHYEAR < 1950;";
	//cout << endl << "SQL Command: " << surname << endl;

	//exit = sqlite3_exec(DB, surname.c_str(), callback, NULL, &messageError);

	//query = "SELECT * FROM PROGRAMMER;";

	//cout << endl << query << endl;		//print the string to screen

	// you need the callback function this time since there could be multiple rows in the table
	//sqlite3_exec(DB, query.c_str(), callback, NULL, NULL);


	// other possible commands from SQL (update, delete, etc.), try those. Same concept, create string then call command

	sqlite3_close(DB);
	return 0;
}
