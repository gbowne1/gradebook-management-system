#include <gtest/gtest.h>

#include "fixtures/teacher_test_fixture.h"
#include "dataframe.h"

void validateTeachersDataFrame(DataFrame &df)
{
    EXPECT_EQ(df["teacher_id"][0], "1");
    EXPECT_EQ(df["name"][0], "Adam Bell");

    EXPECT_EQ(df["teacher_id"][1], "2");
    EXPECT_EQ(df["name"][1], "Tommy Barrett");

    EXPECT_EQ(df["teacher_id"][2], "3");
    EXPECT_EQ(df["name"][2], "Ollie Perry");
}

TEST_F(TeacherTestFixture, Loadteachers)
{
    DataFrame df = this->gradebook.teachersToDataFrame();
    validateTeachersDataFrame(df);
}

TEST_F(TeacherTestFixture, SaveTeachers)
{
    const std::string fileName = "saved_teachers.csv";
    this->gradebook.saveTeachers(fileName);

    DataFrame df;
    df.load(fileName);
    validateTeachersDataFrame(df);

    EXPECT_EQ(remove(fileName.c_str()), 0);
}

TEST_F(TeacherTestFixture, PrintTeachers)
{
    testing::internal::CaptureStdout();
    this->gradebook.teachersToDataFrame().print();
    const std::string output = testing::internal::GetCapturedStdout();

    const std::string expectedResult =
        std::string("-------------------------------\n") +
        "| teacher_id |           name | \n" +
        "-------------------------------\n" +
        "|          1 |      Adam Bell | \n" +
        "|          2 |  Tommy Barrett | \n" +
        "|          3 |    Ollie Perry | \n" +
        "|          4 |  Elliot Hudson | \n" +
        "|          5 | Freddie Harris | \n" +
        "-------------------------------\n";

    EXPECT_EQ(output, expectedResult);
}

TEST_F(TeacherTestFixture, QueryOneTeacher)
{
    Teacher teacher = this->gradebook.getTeacher("1");
    EXPECT_EQ(teacher.name, "Adam Bell");

    teacher = this->gradebook.getTeacher("2");
    EXPECT_EQ(teacher.name, "Tommy Barrett");

    teacher = this->gradebook.getTeacher("3");
    EXPECT_EQ(teacher.name, "Ollie Perry");
}

TEST_F(TeacherTestFixture, QueryAllTeachers)
{
    std::vector<Teacher> teachers = this->gradebook.getTeachers();

    EXPECT_EQ(teachers[0].name, "Adam Bell");
    EXPECT_EQ(teachers[1].name, "Tommy Barrett");
    EXPECT_EQ(teachers[2].name, "Ollie Perry");
}