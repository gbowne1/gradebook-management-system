// File:   gradebook.h
// Author: Gregory K. Bowne
// Date:   20 Oct 2023
// Time:   23:39:08
// Brief:  This is the header file for gradebook.cpp This program is a gradebook program.
//         This program is meant for grades K through 12 in the United States of America.

#ifndef GRADEBOOK_H
#define GRADEBOOK_H

#include <map>
#include <string>
#include <time.h>
#include <chrono>
#include "dataframe.h"

/**
 * Struct Student
 *
 * This struct represents a student in an American school system.
 */
typedef struct
{
    std::string name;
    unsigned short int gradeLevel;
    float gpa;
} Student;

/**
 * Struct Teacher
 *
 * This struct represents a teacher in an American school system.
 */
typedef struct
{
    std::string name;
} Teacher;

/**
 * Struct Class
 *
 * This struct represents a school class within a grade level.
 */
typedef struct
{
    std::string name;
    unsigned short int gradeLevel;
    int teacherId;
} Class;

/**
 * Struct Assignment
 *
 * This struct represents an assignment within a class.
 */
typedef struct
{
    std::string name;
    std::time_t dueDate;
    int classId;
} Assignment;

/**
 * Struct Grade
 *
 * This struct represents the grade of a student in a given assignment.
 */
typedef struct
{
    int score;
} Grade;

/**
 * Class GradeBook
 *
 * This class represents the entity that manages school data, across students, teachers, classes, assignments and grades.
 */
class GradeBook
{
private:
    std::map<std::string, Student> students;
    std::map<std::string, Teacher> teachers;
    std::map<std::string, Class> classes;
    std::map<std::string, Assignment> assignments;
    std::map<
        std::pair<std::string, std::string>, Grade>
        grades;

    bool checkFileExists(const std::string &fileName) const;

public:
    /**
     * Load a CSV file containing teacher data into the GradeBook structure
     * The CSV file must be in the following format:
     * teacher_id,name
     *
     * @param fileName Path to the CSV file
     */
    void addTeachersFromCSV(const std::string &fileName);

    /**
     * Adds a Teacher object into the GradeBook structure, given their ID
     *
     * @param teacherID ID of the teacher
     * @param teacher Teacher object
     */
    void addTeacher(const std::string &teacherID, const Teacher &teacher);

    /**
     * Deregisters a teacher from the system, given their ID
     *
     * @param teacherID ID of the teacher
     */
    void removeTeacher(const std::string &teacherID);

    /**
     * Gets a teacher given their ID
     *
     * @param teacherID ID of the teacher
     * @returns Teacher corresponding to the given ID
     * @throws GBResourceNotFoundException
     */
    Teacher getTeacher(const std::string &teacherID) const;

    /**
     * Gets all teachers in the system
     *
     * @returns All teachers registered in the system
     */
    std::vector<Teacher> getTeachers() const;

    /**
     * Load a CSV file containing student data into the GradeBook structure
     * The CSV file must be in the following format:
     * student_id,name,grade_level,gpa
     *
     * @param fileName Path to the CSV file
     */
    void addStudentsFromCSV(const std::string &fileName);

    /**
     * Adds a Student object into the GradeBook structure, given their ID
     *
     * @param studentID ID of the student
     * @param student Student object
     */
    void addStudent(const std::string &studentID, const Student &student);

    /**
     * Deregisters a student from the system, given their ID
     *
     * @param studentID ID of the student
     */
    void removeStudent(const std::string &studentID);

    /**
     * Gets a student given their ID
     *
     * @param studentID ID of the student
     * @returns Student corresponding to the given ID
     * @throws GBResourceNotFoundException
     */
    Student getStudent(const std::string &studentID) const;

    /**
     * Gets all students in the system
     *
     * @returns All students registered in the system
     */
    std::vector<Student> getStudents() const;

    /**
     * Load a CSV file containing class data into the GradeBook structure
     * The CSV file must be in the following format:
     * class_id,name,grade_level,teacher_id
     *
     * @param fileName Path to the CSV file
     */
    void addClassesFromCSV(const std::string &fileName);

    /**
     * Adds a Class object into the GradeBook structure, given its ID
     *
     * @param classID ID of the class
     * @param clss Class object
     */
    void addClass(const std::string &classID, const Class &clss);

    /**
     * Deregisters a class from the system, given its ID
     *
     * @param classID ID of the class
     */
    void removeClass(const std::string &classID);

    /**
     * Gets a class given its ID
     *
     * @param classID ID of the class
     * @returns Class corresponding to the given ID
     * @throws GBResourceNotFoundException
     */
    Class getClass(const std::string &classID) const;

    /**
     * Gets all classes in the system
     *
     * @returns All classes registered in the system
     */
    std::vector<Class> getClasses() const;

    /**
     * Load a CSV file containing assignment data into the GradeBook structure
     * The CSV file must be in the following format:
     * assignment_id,name,due_date,class_id
     *
     * @param fileName Path to the CSV file
     */
    void addAssignmentsFromCSV(const std::string &fileName);

    /**
     * Adds an Assignment object into the GradeBook structure, given its ID
     *
     * @param assignmentID ID of the assignment
     * @param assignment Assignment object
     */
    void addAssignment(const std::string &assignmentID, const Assignment &assignment);

    /**
     * Deregisters an assignment from the system, given its ID
     *
     * @param assignmentID ID of the assignment
     */
    void removeAssignment(const std::string &assignmentID);

    /**
     * Gets an assignment given its ID
     *
     * @param assignmentID ID of the assignment
     * @returns Assignment corresponding to the given ID
     * @throws GBResourceNotFoundException
     */
    Assignment getAssignment(const std::string &assignmentID) const;

    /**
     * Gets all assignments in the system
     *
     * @returns All assignments registered in the system
     */
    std::vector<Assignment> getAssignments() const;

    /**
     * Load a CSV file containing grade data into the GradeBook structure
     * The CSV file must be in the following format:
     * assignment_id,student_id,score
     *
     * @param fileName Path to the CSV file
     */
    void addGradesFromCSV(const std::string &fileName);

    /**
     * Creates a Grade object, given an assignment and student ID.
     *
     * @param assignmentID ID of the assignment
     * @param studentID ID of the student
     * @param score Score level
     */
    void addGrade(const std::string &assignmentID, const std::string &studentID, int score);

    /**
     * Removes a grade from the system, given an assignment and student ID.
     *
     * @param assignmentID ID of the assignment
     * @param studentID ID of the student
     */
    void removeGrade(const std::string &assignmentID, const std::string &studentID);

    /**
     * Gets a grade given an assignment and student ID.
     *
     * @param assignmentID ID of the assignment
     * @param studentID ID of the student
     * @returns Grade corresponding to the given pair of assignment and student
     * @throws GBResourceNotFoundException
     */
    Grade getGrade(const std::string &assignmentID, const std::string &studentID) const;

    /**
     * Gets a grade given an assignment and student ID.
     *
     * @returns All grades registered in the system, alongside their respective assignments and students.
     */
    std::vector<std::tuple<Assignment, Student, Grade>> getGrades() const;

    /**
     * Gets all grades of a given student ID.
     *
     * @returns All grades of all assignments belonging to the given student.
     */
    std::vector<std::pair<Assignment, Grade>> getStudentGrades(const std::string &studentID) const;

    /**
     * Gets grades all students given an assignment ID.
     *
     * @returns All grades of all students that completed the assignment.
     */
    std::vector<std::pair<Student, Grade>> getAssignmentGrades(const std::string &assignmentID) const;

    /**
     * Calculates the average score of a student.
     *
     * @returns The average score amongst all assignments completed by the student.
     */
    float calculateAverage(const std::string &studentID) const;

    /**
     * Calculates the average score of a class.
     *
     * @returns The average score amongst all students in a given class.
     */
    float calculateClassAverage(const std::string &classID) const;

    /**
     * Exports student data into a DataFrame.
     *
     * @returns DataFrame containing student data.
     */
    DataFrame studentsToDataFrame() const;

    /**
     * Exports teacher data into a DataFrame.
     *
     * @returns DataFrame containing teacher data.
     */
    DataFrame teachersToDataFrame() const;

    /**
     * Exports class data into a DataFrame.
     *
     * @returns DataFrame containing class data.
     */
    DataFrame classesToDataFrame() const;

    /**
     * Exports assignment data into a DataFrame.
     *
     * @returns DataFrame containing assignment data.
     */
    DataFrame assignmentsToDataFrame() const;

    /**
     * Exports grading data into a DataFrame.
     *
     * @returns DataFrame containing grading data.
     */
    DataFrame gradesToDataFrame() const;

    /**
     * Exports grades to a CSV file.
     *
     * @param fileName Name of the CSV file to be exported to.
     */
    void saveGrades(const std::string &fileName) const;

    /**
     * Loads grades from a CSV file.
     * The CSV file must be in the following format:
     * assignment_id,student_id,score
     *
     * @param fileName Name of the CSV file to import data from.
     */
    void loadGrades(const std::string &fileName);

    /**
     * Exports students to a CSV file.
     *
     * @param fileName Name of the CSV file to be exported to.
     */
    void saveStudents(const std::string &fileName) const;

    /**
     * Loads students from a CSV file.
     * The CSV file must be in the following format:
     * student_id,name,grade_level,gpa
     *
     * @param fileName Name of the CSV file to import data from.
     */
    void loadStudents(const std::string &fileName);

    /**
     * Exports teachers to a CSV file.
     *
     * @param fileName Name of the CSV file to be exported to.
     */
    void saveTeachers(const std::string &fileName) const;

    /**
     * Loads teachers from a CSV file.
     * The CSV file must be in the following format:
     * teacher_id,name
     *
     * @param fileName Name of the CSV file to import data from.
     */
    void loadTeachers(const std::string &fileName);

    /**
     * Exports assignments to a CSV file.
     *
     * @param fileName Name of the CSV file to be exported to.
     */
    void saveAssignments(const std::string &fileName) const;

    /**
     * Loads assignments from a CSV file.
     * The CSV file must be in the following format:
     * assignment_id,name,due_date,class_id
     *
     * @param fileName Name of the CSV file to import data from.
     */
    void loadAssignments(const std::string &fileName);
};

#endif