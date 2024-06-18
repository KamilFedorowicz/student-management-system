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
    int return_id()
    {
        return student_id;
    }
    
    std::string return_name()
    {
        return name;
    }
    
    int return_grade()
    {
        return grade;
    }
    
    // print info
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
    
    std::cout <<std::left << std::setw(10) << "Name"
    << std::right << std::setw(10) << "student id"
    << std::right << std::setw(10) << "grade" << std::endl;
    while(inFile.read(reinterpret_cast<char*> (&student), sizeof(Student)))
    {
        student.print_info();
    }
    inFile.close();
    
}

void change_grade()
{
    system("clear");
    std::fstream File;
    File.open("test1", std::ios::binary | std::ios::in | std::ios::out);
    if(!File)
    {
        std::cout << "Cannot open";
        return;
    }
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

int main(int argc, const char * argv[]) {
    
    
    system("clear");
    
    //add_student();

    
    char ch;
    do {
        system("clear");
        std::cout << "Welcome to the student notes program. You can do the following: " << std::endl;
        std::cout << "1. Add student." << std::endl;
        std::cout << "2. Student list." << std::endl;
        std::cout << "3. Modify students grade." << std::endl;
        std::cout << "4. Remove student." << std::endl;
        std::cout << "5. Calculate student average." << std::endl;
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
            case '3':
                change_grade();
                break;
            case '4':
                remove_student();
                break;
            case '5':
                calculate_average();
                
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
