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
    
    void show_id()
    {
        std::cout << "ID: " << student_id << std::endl;
    }
    
    void show_name()
    {
        std::cout << "Name: " << name << std::endl;
    }
    
    void show_grade()
    {
        std::cout << "Grade: " << grade << std::endl;
    }
    
    void print_info()
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
    while(inFile.read(reinterpret_cast<char*> (&student), sizeof(Student)))
    {
        student.print_info();
    }
    inFile.close();
    
}


int main(int argc, const char * argv[]) {
    
    
    system("clear");
    
    //add_student();

    
    char ch;
    do {
        system("clear");
        std::cout << "Welcome to the student notes program. You can do the following: " << std::endl;
        std::cout << "1. Add student." << std::endl;
        std::cout << "2. Student list." << std::endl;
        std::cout << "9. Exit. \n " << std::endl;
        std::cout << "What do you want to do: \n";
        
        std::cin >> ch ;
        switch(ch)
        {
            case '1':
                add_student();
                break;
                
            case '2':
                show_students();
                break;
                
            case '9':
                std::cout << "Program terminating";
                break;
            
            
            default:
                std::cout << "\a";
        }
        std::cin.ignore();
        std::cin.get();
        
    } while (ch!='9');
    
    
    
    
    
    
    return 0;
}
