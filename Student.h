#pragma once
#include "User.h"

class Student :
    public User
{
    // attribute
    int gradyear;
    string major;

public:
    // constructor
    Student();
    Student(string first, string last, string em, string in_major, int id, int year);

    // method
    void search_courses();
    void add_drop_courses();
    void print_schedule();
    void print_info();

    // destructor
    ~Student();
};