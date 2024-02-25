#ifndef TEACHER_TEST_FIXTURE_H
#define TEACHER_TEST_FIXTURE_H

#include <gtest/gtest.h>

#include "gradebook.h"
#include "dataframe.h"

class TeacherTestFixture : public testing::Test
{
protected:
    TeacherTestFixture();
    virtual ~TeacherTestFixture() = default;

    GradeBook gradebook;
};

#endif