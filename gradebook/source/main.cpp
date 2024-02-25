#include "../include/gradebook.h"
#include "../include/exceptions.h"
#include "../include/utils.h"

int main(int argc, char const *argv[])
{
    GradeBook gradebook;
    int choice;

    while (true)
    {
        std::cout << "1. Load Grades\n";
        std::cout << "2. Save Grades\n";
        std::cout << "3. Show Grades\n";
        std::cout << "4. Add Student\n";
        std::cout << "5. Remove Student\n";
        std::cout << "6. Load Students\n";
        std::cout << "7. Save Students\n";
        std::cout << "8. Show Students\n";
        std::cout << "9. Exit\n";
        std::cout << "Choose an option: ";
        std::cin >> choice;

        // TODO Probably put each of these cases into functions for better readability
        switch (choice)
        {
        case 1:
        {
            std::string fileName;
            std::cout << "Please type the name of the CSV file to load the grades from: ";
            std::getline(std::cin >> std::ws, fileName);
            gradebook.loadGrades(fileName);
            break;
        }
        case 2:
        {
            std::string fileName;
            std::cout << "Please type the name of the CSV file to save the grades to: ";
            std::getline(std::cin >> std::ws, fileName);
            gradebook.saveGrades(fileName);
            break;
        }
        case 3:
        {
            gradebook.gradesToDataFrame().print();
            std::cout << "Press ENTER to continue...";
            std::cin.ignore();
            std::getchar();
            break;
        }
        case 4:
        {
            std::string studentID, studentName;
            unsigned short gradeLevel;
            float gpa;

            std::cout << "Student ID: ";
            std::cin >> studentID;

            std::cout << "Student Name: ";
            std::cin >> studentName;

            std::cout << "Grade Level: ";
            std::cin >> gradeLevel;

            std::cout << "GPA: ";
            std::cin >> gpa;

            Student student = {studentName, gradeLevel, gpa};
            gradebook.addStudent(studentID, student);
            break;
        }
        case 5:
        {
            std::string studentID;
            std::cout << "Please type the student ID to be removed: ";
            std::cin >> studentID;
            gradebook.removeStudent(studentID);
            break;
        }
        case 6:
        {
            std::string fileName;
            std::cout << "Please type the name of the CSV file to load the students from: ";
            std::getline(std::cin >> std::ws, fileName);
            gradebook.loadStudents(fileName);
            break;
        }
        case 7:
        {
            std::string fileName;
            std::cout << "Please type the name of the CSV file to save the students to: ";
            std::getline(std::cin >> std::ws, fileName);
            gradebook.saveStudents(fileName);
            break;
        }
        case 8:
        {
            gradebook.studentsToDataFrame().print();
            waitForKey();
            break;
        }
        case 9:
            return 0;
        default:
            std::cout << "Invalid choice. Try again.\n";
        }
    }

    return 0;
}