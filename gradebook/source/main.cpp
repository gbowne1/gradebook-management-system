#include "gradebook.h"
#include "exceptions.h"
#include "utils.h"

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
        std::cout << "1000. [TEST] Find one student\n";
        std::cout << "1001. [TEST] Find all students\n";
        std::cout << "1002. [TEST] Find one teacher\n";
        std::cout << "1003. [TEST] Find all teachers\n";
        std::cout << "1004. [TEST] Find one assignment\n";
        std::cout << "1005. [TEST] Find all assignments\n";
        std::cout << "1006. [TEST] Find one grade\n";
        std::cout << "1007. [TEST] Find all grades\n";
        std::cout << "1008. [TEST] Find all grades of a student\n";
        std::cout << "1009. [TEST] Find all grades of an assignment\n";
        std::cout << "1010. [TEST] Load Assignments\n";
        std::cout << "1011. [TEST] Load Teachers\n";
        std::cout << "9. Exit\n";
        std::cout << "Choose an option: ";
        std::cin >> choice;

        // TODO: Probably put each of these cases into functions for better readability
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

        case 1000:
        {
            // [TEST] Find one student
            int studentID;
            std::cout << "Please type the ID of the student you wish to view: ";
            std::cin >> studentID;
            try
            {
                Student student = gradebook.getStudent(std::to_string(studentID));
                std::cout << "Student name: " << student.name << std::endl;
                std::cout << "Student level: " << student.gradeLevel << std::endl;
                std::cout << "GPA: " << student.gpa << std::endl;
            }
            catch (GBResourceNotFoundException &e)
            {
                std::cout << e.what() << std::endl;
            }
            waitForKey();
            break;
        }
        case 1001:
        {
            // [TEST] Find all students
            std::vector<Student> students = gradebook.getStudents();
            for (const auto &student : students)
            {
                std::cout << "==========================" << std::endl;
                std::cout << "Student name: " << student.name << std::endl;
                std::cout << "Student level: " << student.gradeLevel << std::endl;
                std::cout << "GPA: " << student.gpa << std::endl;
            }
            std::cout << "==========================" << std::endl;
            waitForKey();
            break;
        }
        case 1002:
        {
            // [TEST] Find one teacher
            int teacherID;
            std::cout << "Please type the ID of the teacher you wish to view: ";
            std::cin >> teacherID;
            try
            {
                Teacher teacher = gradebook.getTeacher(std::to_string(teacherID));
                std::cout << "Teacher name: " << teacher.name << std::endl;
            }
            catch (GBResourceNotFoundException &e)
            {
                std::cout << e.what() << std::endl;
            }
            waitForKey();
            break;
        }
        case 1003:
        {
            // [TEST] Find all teachers
            std::vector<Teacher> teachers = gradebook.getTeachers();
            for (const auto &teacher : teachers)
            {
                std::cout << "==========================" << std::endl;
                std::cout << "Teacher name: " << teacher.name << std::endl;
            }
            std::cout << "==========================" << std::endl;
            waitForKey();
            break;
        }
        case 1004:
        {
            // [TEST] Find one assignment
            int assignmentID;
            std::cout << "Please type the ID of the assignment you wish to view: ";
            std::cin >> assignmentID;
            try
            {
                Assignment assignment = gradebook.getAssignment(std::to_string(assignmentID));
                std::cout << "Assignment name: " << assignment.name << std::endl;
                std::cout << "Assignment due date: " << timeToString(assignment.dueDate) << std::endl;
                std::cout << "Assignment name: " << assignment.classId << std::endl;
            }
            catch (GBResourceNotFoundException &e)
            {
                std::cout << e.what() << std::endl;
            }
            waitForKey();
            break;
        }
        case 1005:
        {
            // [TEST] Find all assignments
            std::vector<Assignment> assignments = gradebook.getAssignments();
            for (const auto &assignment : assignments)
            {
                std::cout << "==========================" << std::endl;
                std::cout << "Assignment name: " << assignment.name << std::endl;
                std::cout << "Assignment due date: " << timeToString(assignment.dueDate) << std::endl;
                std::cout << "Assignment name: " << assignment.classId << std::endl;
            }
            std::cout << "==========================" << std::endl;
            waitForKey();
            break;
        }
        case 1006:
        {
            // [TEST] Find one grade
            int assignmentID;
            int studentID;
            std::cout << "Please type the ID of the assignment for the grade you wish to view: ";
            std::cin >> assignmentID;
            std::cout << "Please type the ID of the student for the grade you wish to view: ";
            std::cin >> studentID;
            try
            {
                Grade grade = gradebook.getGrade(std::to_string(assignmentID), std::to_string(studentID));
                std::cout << "Score for student " << studentID
                          << " on assignment " << assignmentID << ": "
                          << grade.score << std::endl;
            }
            catch (GBResourceNotFoundException &e)
            {
                std::cout << e.what() << std::endl;
            }
            waitForKey();
            break;
        }
        case 1007:
        {
            // [TEST] Find all grades
            auto data = gradebook.getGrades();
            for (const auto &entry : data)
            {
                std::cout << "==========================" << std::endl;
                std::cout << "Assignment name: " << std::get<0>(entry).name << std::endl;
                std::cout << "Student name: " << std::get<1>(entry).name << std::endl;
                std::cout << "Score: " << std::get<2>(entry).score << std::endl;
            }
            std::cout << "==========================" << std::endl;
            waitForKey();
            break;
        }
        case 1008:
        {
            // [TEST] Find all grades of a student
            int studentID;
            std::cout << "Please type the ID of the student whose grades you wish to view: ";
            std::cin >> studentID;
            auto data = gradebook.getStudentGrades(std::to_string(studentID));
            std::cout << "Data for student " << studentID << std::endl;
            for (const auto &entry : data)
            {
                std::cout << "==========================" << std::endl;
                std::cout << "Assignment name: " << entry.first.name << std::endl;
                std::cout << "Score: " << entry.second.score << std::endl;
            }
            std::cout << "==========================" << std::endl;
            waitForKey();
            break;
        }
        case 1009:
        {
            // [TEST] Find all grades of in an assignment
            int assignmentId;
            std::cout << "Please type the ID of the assignment whose grades you wish to view: ";
            std::cin >> assignmentId;
            auto data = gradebook.getAssignmentGrades(std::to_string(assignmentId));
            std::cout << "Data for assignment " << assignmentId << std::endl;
            for (const auto &entry : data)
            {
                std::cout << "==========================" << std::endl;
                std::cout << "Student name: " << entry.first.name << std::endl;
                std::cout << "Score: " << entry.second.score << std::endl;
            }
            std::cout << "==========================" << std::endl;
            waitForKey();
            break;
        }
        case 1010:
        {
            // [TEST] Load assignments
            std::string fileName;
            std::cout << "Please type the name of the CSV file to load the assignments from: ";
            std::getline(std::cin >> std::ws, fileName);
            gradebook.loadAssignments(fileName);
            break;
        }
        case 1011:
        {
            // [TEST] Load teachers
            std::string fileName;
            std::cout << "Please type the name of the CSV file to load the teachers from: ";
            std::getline(std::cin >> std::ws, fileName);
            gradebook.loadTeachers(fileName);
            break;
        }
        default:
            std::cout << "Invalid choice. Try again.\n";
        }
    }

    return 0;
}