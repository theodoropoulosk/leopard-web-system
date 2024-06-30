#pragma once
#include "User.h"
class Instructor :
    public User
{
    // attribute
    int hireyear;
    string title, department;

public:
    // constructor
    Instructor();
    Instructor(string first, string last, string em, string in_title, string dept, int id, int year);

    // method
    void print_schedule();
    void print_class_list();
    void search_courses();
    void print_info();

    // destructor
    ~Instructor();
};

