#include <iostream>
#include <string>
#include<iostream>
#include<fstream> // what do these do?
#include "student.h"
#include "functions.h"



int main(int argc, const char * argv[]) {
    
    
    system("clear");
    
    //add_student();

    
    char ch;
    do {
        system("clear");
        std::cout << "Welcome to the student notes program. You can do the following: " << std::endl;
        std::cout << "0. Exit. " << std::endl;
        std::cout << "1. Add student." << std::endl;
        std::cout << "2. Student list." << std::endl;
        std::cout << "3. Modify students grade." << std::endl;
        std::cout << "4. Remove student." << std::endl;
        std::cout << "5. Calculate student average." << std::endl;
        std::cout << "6. Return the best student." << std::endl;
        std::cout << "7. Search by name." << std::endl;
        std::cout << "8. Display students in a grade range." << std::endl;
        std::cout << "9. Sort by grade. \n" << std::endl;
        
        
        std::cout << "What do you want to do: \n";
        
        std::cin >> ch ;
        switch(ch)
        {
            case '0':
                std::cout << "Program terminating";
                break;
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
                break;
            case '6':
                best_student();
                break;
            case '7':
                search_by_name();
                break;
            case '8':
                search_by_grade_range();
                break;
            case '9':
                sort_by_grade();
                break;
                
            
            
            
            default:
                std::cout << "\a";
        }
        std::cin.ignore();
        std::cin.get();
        
    } while (ch!='0');
    
    
    
    
    
    
    return 0;
}
