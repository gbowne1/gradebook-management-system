#include "fixtures/teacher_test_fixture.h"

#include "gradebook.h"

TeacherTestFixture::TeacherTestFixture()
{
    const std::string fileName = "assets/teacherdata.csv";
    this->gradebook.loadTeachers(fileName);
}