#include "fixtures/student_test_fixture.h"

#include "gradebook.h"

#include <memory>

StudentTestFixture::StudentTestFixture()
{
    const std::string fileName = "assets/studentdata.csv";
    this->gradebook = std::make_unique<GradeBook>();
    this->gradebook->loadStudents(fileName);
}