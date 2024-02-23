#include <gtest/gtest.h>
#include "gradebook.h"
#include "dataframe.h"

// Demonstrate some basic assertions.
TEST(Student, LoadStudent)
{
    const std::string fileName = "assets/studentdata.csv";
    GradeBook gradebook;
    gradebook.loadStudents(fileName);

    DataFrame df = gradebook.studentsToDataFrame();

    EXPECT_EQ(df["student_id"][0], "1");
    EXPECT_EQ(df["name"][0], "John Doe");
    EXPECT_EQ(df["grade_level"][0], "12");
    EXPECT_EQ(df["gpa"][0], "3.8");

    EXPECT_EQ(df["student_id"][1], "2");
    EXPECT_EQ(df["name"][1], "Luke Sutton");
    EXPECT_EQ(df["grade_level"][1], "12");
    EXPECT_EQ(df["gpa"][1], "4.7");

    EXPECT_EQ(df["student_id"][2], "3");
    EXPECT_EQ(df["name"][2], "Jayden Gibson");
    EXPECT_EQ(df["grade_level"][2], "12");
    EXPECT_EQ(df["gpa"][2], "4.6");
}
