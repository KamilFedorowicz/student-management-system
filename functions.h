//
//  functions.h
//  reading_writing_data
//
//  Created by Kamil Fedorowicz on 18/06/2024.
//


#ifndef functions_h
#define functions_h

#include <iostream>
#include <string>
#include <fstream>
#include "student.h"
#include <vector>

// this is just for clarify purposes where a header with name, id and grade is displayed
void header()
{
    std::cout <<std::left << std::setw(10) << "Name"
    << std::right << std::setw(10) << "student id"
    << std::right << std::setw(10) << "grade" << std::endl;
    std::cout << "------------------------------" << std::endl;
}

void add_student()
{
    
    std::string name;
    int student_id;
    int grade;
    system("clear");
    std::cout << "name: ";
    std::cin >> name;
    std::cout << "students id: ";
    std::cin >> student_id;
    std::cout << "grade: ";
    std::cin >> grade;
    
    Student student(name, student_id, grade);
    
    std::ofstream outFile;
    outFile.open("test1", std::ios::binary | std::ios::app);
    
    outFile.write(reinterpret_cast<char*> (&student), sizeof(Student));
    outFile.close();
    std::cout << "Student record added..." ;
    
}

void show_students()
{
    system("clear");
    Student student;
    std::ifstream inFile;
    inFile.open("test1", std::ios::binary);
    
    header();
    while(inFile.read(reinterpret_cast<char*> (&student), sizeof(Student)))
    {
        student.print_info();
    }
    inFile.close();
    
}

void change_grade()
{
    system("clear");
    // fstream allows to read and write data
    std::fstream File;
    // file should be in binary mode
    // in and out mean that it should be for input and output mode
    File.open("test1", std::ios::binary | std::ios::in | std::ios::out);
    if(!File)
    {
        std::cout << "Cannot open";
        return;
    }
    
    // just displaying a student list for convenience
    std::cout << "Here is the student list:" << std::endl;
    show_students() ;
    
    std::cout << "Enter student id: " ;
    int id;
    std::cin >> id;
    bool found = false;
    Student student;
    while( !File.eof() && found == false)
    {
        // reinterpret_cast<char*>(&student) casts the address of student to a char* (character pointer), which is required by the read function.
        //sizeof(Student) specifies the number of bytes to read. should correspond to the size of the Student object.
        File.read(reinterpret_cast<char*> (&student), sizeof(Student));
        if(student.return_id()==id)
        {
            std::cout << "Modify the following student: " << std::endl;
            student.print_info();
            std::cout << "Enter the grade: ";
            int new_grade;
            std::cin >> new_grade ;
            student.write_grade(new_grade);
            
            // seekp move the file pointer by sizeof(student) relative to the current position
            int pos = (-1) * static_cast<int>(sizeof(Student));
            File.seekp(pos, std::ios::cur);
            // write at the correct position, i.e. overwrite the record
            File.write(reinterpret_cast<char*> (&student), sizeof(Student));
            std::cout << "Grade updated";
            
            found = true;
        }
    }
    File.close();
    if(found==false)
    {
        std::cout << "Did not find the id" << std::endl;
    }
    
}

void remove_student()
{
    system("clear");
    std::ifstream inFile;
    std::ofstream outFile;
    inFile.open("test1", std::ios::binary );
    if(!inFile)
    {
        std::cout << "Cannot open";
        return;
    }
    
    std::cout << "Enter student id to remove: " ;
    int id;
    std::cin >> id;
    bool flag=false;
    
    Student student;
    outFile.open("temp", std::ios::binary);
    inFile.seekg(0, std::ios::beg);
    while(inFile.read(reinterpret_cast<char*> (&student), sizeof(Student)))
    {
        if(student.return_id()!=id)
        {
            outFile.write(reinterpret_cast<char*>(&student), sizeof(Student));
        }else
        {
            flag = true;
        }
        
    }
        
    inFile.close();
    outFile.close();
    remove("test1");
    rename("temp", "test1");
    if(flag == true)
    {
        std::cout << "Student deleted";
    }else
    {
        std::cout << "Id does not exist";
    }
    
}

void calculate_average()
{
    system("clear");
    std::ifstream inFile;
    inFile.open("test1", std::ios::binary);
    Student student;
    if(!inFile)
    {
        std::cout << "Cannot open";
        return;
    }
    int sum=0;
    int count=0;
    
    while(inFile.read(reinterpret_cast<char*> (&student), sizeof(Student)))
    {
        sum+=student.return_grade();
        count++;
    }
    double average = static_cast<double>(sum)/count ;
    std::cout << std::fixed << std::setprecision(2);
    std::cout << "The average is " << average << std::endl;
    
    inFile.close();
    
}

int find_max_grade()
{
    system("clear");
    std::ifstream inFile;
    inFile.open("test1", std::ios::binary);
    Student student;
    
    int max_grade = -1;
    while(inFile.read(reinterpret_cast<char*>(&student), sizeof(Student)))
    {
        if(student.return_grade()>max_grade)
        {
            max_grade = student.return_grade();
        }
    }
    inFile.close();
    return max_grade;
    
}

void best_student()
{
    system("clear");
    std::ifstream inFile;
    inFile.open("test1", std::ios::binary);
    Student student;
    if(!inFile)
    {
        std::cout << "Cannot open";
        return;
    }
    
    int max_grade;
    max_grade = find_max_grade();
    Student best_student;

    std::cout << "The student(s) with the best grade is/are: " ;
    while(inFile.read(reinterpret_cast<char*> (&student), sizeof(Student)))
    {
        if(student.return_grade()==max_grade)
        {
            std::cout << student.return_name() << " ";
        }
    }
    
    
    inFile.close();
    
}

void search_by_name()
{
    system("clear");
    std::string name_par;
    std::cout << "Provide the name: ";
    std::cin >> name_par;
    
    std::ifstream inFile;
    inFile.open("test1", std::ios::binary);
    Student student;
    if(!inFile)
    {
        std::cout << "Cannot open";
        return;
    }
    
    bool flag=false;
    while(inFile.read(reinterpret_cast<char*> (&student), sizeof(Student)))
    {
        if(student.return_name()==name_par)
        {
            student.print_info();
            flag = true;
        }
    }
    if(flag==false)
    {
        std::cout << "No such name." << std::endl;
    }
        
    inFile.close();
    
    
}

void search_by_grade_range()
{
    system("clear");
    std::ifstream inFile;
    inFile.open("test1", std::ios::binary);
    if(!inFile)
    {
        std::cout << "No file!" << std::endl;
    }
    Student student;
    
    int grade_min;
    int grade_max;
    bool flag = false;
    
    std::cout << "Provide the minimum grade (inclusive): ";
    std::cin>> grade_min;
    std::cout << "Provide the maximum grade (inclusive): ";
    std::cin >> grade_max;
    
    
    header();
    while(inFile.read(reinterpret_cast<char*>(&student), sizeof(Student)))
    {
        if(student.return_grade()>=grade_min && student.return_grade()<=grade_max)
        {
            student.print_info();
            flag = true;
        }
    }
    if (flag==false)
    {
        std::cout << "No students in this grade range" << std::endl;
    }
    
    inFile.close();
    
}


void sort_by_grade()
{
    system("clear");
    std::ifstream inFile;
    inFile.open("test1", std::ios::binary);
    
    Student student;
    std::vector <Student> students;
    
    while (inFile.read(reinterpret_cast<char*>(&student), sizeof(Student))) {
            students.push_back(student);
        }
    inFile.close();
    
    std::sort(students.begin(), students.end(), [](const Student& a, const Student& b) {
            return a.return_grade() > b.return_grade();
        });
        
    // Print header
    header();
        
    // Print sorted students
    for (const auto& student : students) {
        student.print_info();
    }
    
    
//    int temp_grade = find_max_grade();
//    
//    header();
//    while(temp_grade>0)
//    {
//        inFile.clear();
//        inFile.seekg(0, std::ios::beg);
//        while(inFile.read(reinterpret_cast<char*>(&student), sizeof(Student)))
//        {
//            if(student.return_grade()==temp_grade)
//            {
//                student.print_info();
//            }
//        }
//        temp_grade--;
//
//    }
//    inFile.close();
    
}

#endif /* functions_h */
