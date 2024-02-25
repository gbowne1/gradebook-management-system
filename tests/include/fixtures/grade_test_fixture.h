#ifndef GRADE_TEST_FIXTURE_H
#define GRADE_TEST_FIXTURE_H

#include <gtest/gtest.h>

#include "gradebook.h"
#include "dataframe.h"

class GradeTestFixture : public testing::Test
{
protected:
    GradeTestFixture();
    virtual ~GradeTestFixture() = default;

    GradeBook gradebook;
};

#endif