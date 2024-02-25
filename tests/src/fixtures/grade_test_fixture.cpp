#include "fixtures/grade_test_fixture.h"

#include "gradebook.h"

GradeTestFixture::GradeTestFixture()
{
    const std::string gradesFileName = "assets/grades.csv";
    const std::string studentsFileName = "assets/studentdata.csv";
    const std::string assignmentsFileName = "assets/assignmentdata.csv";

    this->gradebook.loadGrades(gradesFileName);
    this->gradebook.loadStudents(studentsFileName);
    this->gradebook.loadAssignments(assignmentsFileName);
}