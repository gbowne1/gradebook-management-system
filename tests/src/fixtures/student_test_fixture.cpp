#include "fixtures/student_test_fixture.h"

#include "gradebook.h"

StudentTestFixture::StudentTestFixture()
{
    const std::string fileName = "assets/studentdata.csv";
    this->gradebook.loadStudents(fileName);
}