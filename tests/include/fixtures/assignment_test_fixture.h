#ifndef ASSIGNMENT_TEST_FIXTURE_H
#define ASSIGNMENT_TEST_FIXTURE_H

#include <gtest/gtest.h>

#include "gradebook.h"
#include "dataframe.h"

class AssignmentTestFixture : public testing::Test
{
protected:
    AssignmentTestFixture();
    virtual ~AssignmentTestFixture() = default;

    GradeBook gradebook;
};

#endif