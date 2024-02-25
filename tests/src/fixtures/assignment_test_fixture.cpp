#include "fixtures/assignment_test_fixture.h"

#include "gradebook.h"

AssignmentTestFixture::AssignmentTestFixture()
{
    const std::string fileName = "assets/assignmentdata.csv";
    this->gradebook.loadAssignments(fileName);
}