#pragma once
#include "User.h"
#include "sqlite3.h"

class Admin :
    public User
{
    // attribute
    string title, office;

public:
    // constructor
    Admin();
    Admin(string first, string last, string em, string in_title, string in_office, int id);

    // method
    void add_courses(string crn, string title, string dept, string time,
        string days, string semester, string year, string credits);
    void remove_courses(int in_crn);
    void add_instructor(string id, string name, string surname, string title,
        string hireyear, string dept, string email, string pass);
    void remove_instructor(string id_in);
    void add_student(string id, string name, string surname, string gradyear, string major, string email, string pass);
    void remove_student(string id_in);
    void print_info();

    // destructor
    ~Admin();
};

