//
//  student.h
//  reading_writing_data
//
//  Created by Kamil Fedorowicz on 18/06/2024.
//

#ifndef student_h
#define student_h

#include <iostream>
#include <string>
#include<iostream>
#include<fstream> // what do these do?

class Student
{
public:
    Student(std::string name_par, int id_par, int grade_par): name(name_par), student_id(id_par), grade(grade_par) {};
    
    Student()
    {
        name = "none";
        student_id = 0;
        grade = 0;
    }
    
    // functions modifying data
    void write_id(int id_par)
    {
        student_id = id_par;
    }
    
    void write_grade(int grade_par)
    {
        grade = grade_par;
    }
    
    void write_name(const std::string& name_par)
    {
        name = name_par;
    }
    
    // functions returnning data
    int return_id() const
    {
        return student_id;
    }
    
    std::string return_name() const
    {
        return name;
    }
    
    int return_grade() const
    {
        return grade;
    }
    
    // print info
    void print_info() const
    {
        std::cout <<std::left << std::setw(10) << name
        << std::right << std::setw(10) << student_id
        << std::right << std::setw(10) << grade << std::endl;
    }
    
    
private:
    std::string name;
    int student_id;
    int grade;
};


#endif /* student_h */
