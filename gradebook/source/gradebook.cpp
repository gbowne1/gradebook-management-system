// File:   gradebook.cpp
// Author: Gregory K. Bowne
// Date:   20 Oct 2023
// Time:   22:50:08
// Brief:  This program is a gradebook program.
//         This program was meant for use in grades K through 12

#include "gradebook.h"
#include "dataframe.h"
#include "exceptions.h"
#include "utils.h"

#include <iostream>
#include <sstream>
#include <fstream>
#include <cstring>
#include <iomanip>

void GradeBook::addTeachersFromCSV(const std::string &fileName)
{
	DataFrame teacherData(fileName);

	for (int i = 0; i < teacherData.sizeCols(); i++)
	{
		Teacher teacher = {teacherData["name"][i]};
		const std::string teacherID = teacherData["teacher_id"][i];
		this->addTeacher(teacherID, teacher);
	}
}

void GradeBook::addTeacher(const std::string &teacherID, const Teacher &teacher)
{
	this->teachers[teacherID] = teacher;
}

void GradeBook::removeTeacher(const std::string &teacherID)
{
	this->teachers.erase(teacherID);
}

Teacher GradeBook::getTeacher(const std::string &teacherID) const
{
	if (!this->teachers.count(teacherID))
		throw GBResourceNotFoundException("Teacher with ID " + teacherID + " was not found!");

	return this->teachers.at(teacherID);
}

std::vector<Teacher> GradeBook::getTeachers() const
{
	return getMapValues(this->teachers);
}

void GradeBook::addStudentsFromCSV(const std::string &fileName)
{
	DataFrame studentData(fileName);

	for (int i = 0; i < studentData.sizeCols(); i++)
	{
		Student student = {
			studentData["name"][i],
			(unsigned short)std::stoi(studentData["grade_level"][i]),
			std::stof(studentData["gpa"][i])};
		const std::string studentID = studentData["student_id"][i];
		this->addStudent(studentID, student);
	}
}

void GradeBook::addStudent(const std::string &studentID, const Student &student)
{
	this->students[studentID] = student;
}

void GradeBook::removeStudent(const std::string &studentID)
{
	this->students.erase(studentID);
}

Student GradeBook::getStudent(const std::string &studentID) const
{
	if (!this->students.count(studentID))
		throw GBResourceNotFoundException("Student with ID " + studentID + " was not found!");

	return this->students.at(studentID);
}

std::vector<Student> GradeBook::getStudents() const
{
	return getMapValues(this->students);
}

void GradeBook::addClassesFromCSV(const std::string &fileName)
{
	DataFrame classData(fileName);

	for (int i = 0; i < classData.sizeCols(); i++)
	{
		Class clss = {
			classData["name"][i],
			(unsigned short)std::stoi(classData["grade_level"][i]),
			std::stoi(classData["teacher_id"][i])};
		const std::string classID = classData["class_id"][i];
		this->addClass(classID, clss);
	}
}

void GradeBook::addClass(const std::string &classID, const Class &clss)
{
	this->classes[classID] = clss;
}

void GradeBook::removeClass(const std::string &classID)
{
	this->classes.erase(classID);
}

Class GradeBook::getClass(const std::string &classID) const
{
	if (!this->classes.count(classID))
		throw GBResourceNotFoundException("Class with ID " + classID + " was not found!");

	return this->classes.at(classID);
}

std::vector<Class> GradeBook::getClasses() const
{
	return getMapValues(this->classes);
}

void GradeBook::addAssignmentsFromCSV(const std::string &fileName)
{
	DataFrame assignmentData(fileName);

	for (int i = 0; i < assignmentData.sizeCols(); i++)
	{
		struct tm t;
		memset(&t, 0, sizeof(struct tm));
		if (strptime(assignmentData["due_date"][i].c_str(), "%Y-%m-%d", &t) == NULL)
		{
			std::cout << "Failed to read date: " << assignmentData["due_date"][i] << ". Format: YYYY-mm-dd" << std::endl;
		}

		std::time_t dueDate = std::mktime(&t);

		Assignment assignment = {
			assignmentData["name"][i],
			dueDate,
			std::stoi(assignmentData["class_id"][i])};
		const std::string assignmentID = assignmentData["assignment_id"][i];
		this->addAssignment(assignmentID, assignment);
	}
}

void GradeBook::addAssignment(const std::string &assignmentID, const Assignment &assignment)
{
	this->assignments[assignmentID] = assignment;
}

void GradeBook::removeAssignment(const std::string &assignmentID)
{
	this->assignments.erase(assignmentID);
}

Assignment GradeBook::getAssignment(const std::string &assignmentID) const
{
	if (!this->assignments.count(assignmentID))
		throw GBResourceNotFoundException("Assignment with ID " + assignmentID + " was not found!");

	return this->assignments.at(assignmentID);
}

std::vector<Assignment> GradeBook::getAssignments() const
{
	return getMapValues(this->assignments);
}

void GradeBook::addGradesFromCSV(const std::string &fileName)
{
	DataFrame gradeData(fileName);

	for (int i = 0; i < gradeData.sizeCols(); i++)
	{
		const std::string assignmentID = gradeData["assignment_id"][i];
		const std::string studentID = gradeData["student_id"][i];
		this->addGrade(assignmentID, studentID, std::stoi(gradeData["score"][i]));
	}
}

void GradeBook::addGrade(const std::string &assignmentID, const std::string &studentID, int score)
{
	Grade grade = {score};
	this->grades[std::make_pair(assignmentID, studentID)] = grade;
}

void GradeBook::removeGrade(const std::string &assignmentID, const std::string &studentID)
{
	this->grades.erase(std::make_pair(assignmentID, studentID));
}

Grade GradeBook::getGrade(const std::string &assignmentID, const std::string &studentID) const
{
	auto key = std::make_pair(assignmentID, studentID);
	if (!this->grades.count(key))
		throw GBResourceNotFoundException("Grade with assignment ID " + assignmentID + " and student ID " + studentID + " was not found!");

	return this->grades.at(key);
}

std::vector<std::tuple<Assignment, Student, Grade>> GradeBook::getGrades() const
{
	std::vector<std::tuple<Assignment, Student, Grade>> values;
	for (const auto &entry : this->grades)
	{
		// Get assignment
		const std::string &assignmentID = entry.first.first;
		if (!this->assignments.count(assignmentID))
			throw GBResourceNotFoundException("Assignment with ID " + assignmentID + " was not found! Perhaps it has not been loaded into the database?");

		Assignment assignment = this->assignments.at(assignmentID);

		// Get student
		const std::string &studentID = entry.first.second;
		if (!this->students.count(studentID))
			throw GBResourceNotFoundException("Student with ID " + studentID + " was not found! Perhaps it has not been loaded into the database?");

		Student student = this->students.at(studentID);
		values.push_back(std::make_tuple(assignment, student, entry.second));
	}

	return values;
}

std::vector<std::pair<Assignment, Grade>> GradeBook::getStudentGrades(const std::string &studentID) const
{
	std::vector<std::pair<Assignment, Grade>> matchingGrades;
	for (const auto &entry : this->grades)
	{
		// Get Student ID
		if (entry.first.second != studentID)
			continue;

		const std::string &assignmentID = entry.first.first;
		if (!this->assignments.count(assignmentID))
			throw GBResourceNotFoundException("Assignment with ID " + assignmentID + " was not found! Perhaps it has not been loaded into the database?");

		Assignment assignment = this->assignments.at(assignmentID);
		matchingGrades.push_back(std::make_pair(assignment, entry.second));
	}

	return matchingGrades;
}

std::vector<std::pair<Student, Grade>> GradeBook::getAssignmentGrades(const std::string &assignmentID) const
{
	std::vector<std::pair<Student, Grade>> matchingGrades;
	for (const auto &entry : this->grades)
	{
		// Get Assignment ID
		if (entry.first.first != assignmentID)
			continue;

		const std::string &studentID = entry.first.second;
		if (!this->students.count(studentID))
			throw GBResourceNotFoundException("Student with ID " + studentID + " was not found! Perhaps it has not been loaded into the database?");

		Student student = this->students.at(studentID);
		matchingGrades.push_back(std::make_pair(student, entry.second));
	}

	return matchingGrades;
}

float GradeBook::calculateAverage(const std::string &studentID) const
{
	if (!this->students.count(studentID))
		return 0.0;

	Student student = this->students.at(studentID);
	float sum = 0.0;
	unsigned int assignmentCount = 0;

	for (auto it = this->assignments.begin(); it != this->assignments.end(); it++)
	{
		const std::string assignmentID = it->first;

		const std::pair<std::string, std::string> key = std::make_pair(assignmentID, studentID);
		// TODO: If there is no grade for that student + assignment, should we skip it or count it as a 0?
		if (!this->grades.count(key))
			continue;

		sum += this->grades.at(key).score;
		assignmentCount++;
	}

	return sum / ((float)assignmentCount);
}

float GradeBook::calculateClassAverage(const std::string &classID) const
{
	// TODO: Need some data structure to link students and classes
	return 0.0;
}

DataFrame GradeBook::studentsToDataFrame() const
{
	DataFrame studentDF;
	std::vector<std::string> header = {"student_id", "name", "grade_level", "gpa"};
	studentDF.initialize(header);

	for (auto it = this->students.begin(); it != this->students.end(); it++)
	{
		std::map<std::string, std::string> studentMap;
		Student student = it->second;

		std::stringstream gpaFormat;
		gpaFormat << std::fixed << std::setprecision(1) << student.gpa;

		studentMap["student_id"] = it->first;
		studentMap["name"] = student.name;
		studentMap["grade_level"] = std::to_string(student.gradeLevel);
		studentMap["gpa"] = gpaFormat.str();
		studentDF.append(studentMap);
	}

	return studentDF;
}

DataFrame GradeBook::teachersToDataFrame() const
{
	DataFrame teacherDF;
	std::vector<std::string> header = {"teacher_id", "name"};
	teacherDF.initialize(header);

	for (auto it = this->teachers.begin(); it != this->teachers.end(); it++)
	{
		std::map<std::string, std::string> teacherMap;
		Teacher teacher = it->second;

		teacherMap["teacher_id"] = it->first;
		teacherMap["name"] = teacher.name;
		teacherDF.append(teacherMap);
	}

	return teacherDF;
}

DataFrame GradeBook::classesToDataFrame() const
{
	DataFrame classDF;
	std::vector<std::string> header = {"class_id", "name", "grade_level", "teacher_id"};
	classDF.initialize(header);

	for (auto it = this->classes.begin(); it != this->classes.end(); it++)
	{
		std::map<std::string, std::string> classMap;
		Class clss = it->second;

		classMap["class_id"] = it->first;
		classMap["name"] = clss.name;
		classMap["grade_level"] = std::to_string(clss.gradeLevel);
		classMap["teacher_id"] = std::to_string(clss.teacherId);
		classDF.append(classMap);
	}

	return classDF;
}

DataFrame GradeBook::assignmentsToDataFrame() const
{
	DataFrame assignmentDF;
	std::vector<std::string> header = {"assignment_id", "name", "due_date", "class_id"};
	assignmentDF.initialize(header);

	for (auto it = this->assignments.begin(); it != this->assignments.end(); it++)
	{
		std::map<std::string, std::string> assignmentMap;
		Assignment assignment = it->second;

		std::string dueDateStr = timeToString(assignment.dueDate);

		assignmentMap["assignment_id"] = it->first;
		assignmentMap["name"] = assignment.name;
		assignmentMap["due_date"] = dueDateStr;
		assignmentMap["class_id"] = std::to_string(assignment.classId);
		assignmentDF.append(assignmentMap);
	}

	return assignmentDF;
}

DataFrame GradeBook::gradesToDataFrame() const
{
	DataFrame gradeDF;
	std::vector<std::string> header = {"assignment_id", "student_id", "score"};
	gradeDF.initialize(header);

	for (auto it = this->grades.begin(); it != this->grades.end(); it++)
	{
		std::map<std::string, std::string> gradeMap;
		Grade grade = it->second;

		gradeMap["assignment_id"] = it->first.first;
		gradeMap["student_id"] = it->first.second;
		gradeMap["score"] = std::to_string(grade.score);
		gradeDF.append(gradeMap);
	}

	return gradeDF;
}

bool GradeBook::checkFileExists(const std::string &fileName) const
{
	std::ifstream file(fileName);
	return file.good();
}

void GradeBook::saveGrades(const std::string &fileName) const
{
	this->gradesToDataFrame().save(fileName);
}

void GradeBook::loadGrades(const std::string &fileName)
{
	if (!this->checkFileExists(fileName))
	{
		std::cout << "File " << fileName << " does not exist!" << std::endl;
		return;
	}

	// TODO: Checks to validate the CSV file data, telling whether the load was successful or not
	this->addGradesFromCSV(fileName);
	std::cout << "Grades have been loaded successfully!" << std::endl;
}

void GradeBook::saveStudents(const std::string &fileName) const
{
	this->studentsToDataFrame().save(fileName);
}

void GradeBook::loadStudents(const std::string &fileName)
{
	if (!this->checkFileExists(fileName))
	{
		std::cout << "File " << fileName << " does not exist!" << std::endl;
		return;
	}

	// TODO: Checks to validate the CSV file data, telling whether the load was successful or not
	this->addStudentsFromCSV(fileName);
	std::cout << "Students have been loaded successfully!" << std::endl;
}

void GradeBook::saveTeachers(const std::string &fileName) const
{
	this->teachersToDataFrame().save(fileName);
}

void GradeBook::loadTeachers(const std::string &fileName)
{
	if (!this->checkFileExists(fileName))
	{
		std::cout << "File " << fileName << " does not exist!" << std::endl;
		return;
	}

	// TODO: Checks to validate the CSV file data, telling whether the load was successful or not
	this->addTeachersFromCSV(fileName);
	std::cout << "Teachers have been loaded successfully!" << std::endl;
}

void GradeBook::saveAssignments(const std::string &fileName) const
{
	this->assignmentsToDataFrame().save(fileName);
}

void GradeBook::loadAssignments(const std::string &fileName)
{
	if (!this->checkFileExists(fileName))
	{
		std::cout << "File " << fileName << " does not exist!" << std::endl;
		return;
	}

	// TODO: Checks to validate the CSV file data, telling whether the load was successful or not
	this->addAssignmentsFromCSV(fileName);
	std::cout << "Assignments have been loaded successfully!" << std::endl;
}