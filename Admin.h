#pragma once
#include "User.h"
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
    void add_courses();
    void remove_courses();
    void add_remove_user();
    void add_remove_student();
    void print_roster();
    void search_courses();
    void print_info();

    // destructor
    ~Admin();
};

