#ifndef STUDENT_TEST_FIXTURE_H
#define STUDENT_TEST_FIXTURE_H

#include <gtest/gtest.h>
#include <memory>

#include "gradebook.h"
#include "dataframe.h"

class StudentTestFixture : public testing::Test
{
protected:
    StudentTestFixture();
    virtual ~StudentTestFixture() = default;

    std::unique_ptr<GradeBook> gradebook;
};

#endif