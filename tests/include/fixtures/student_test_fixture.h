#ifndef STUDENT_TEST_FIXTURE_H
#define STUDENT_TEST_FIXTURE_H

#include <gtest/gtest.h>

#include "gradebook.h"
#include "dataframe.h"

class StudentTestFixture : public testing::Test
{
protected:
    StudentTestFixture();
    virtual ~StudentTestFixture() = default;

    GradeBook gradebook;
};

#endif