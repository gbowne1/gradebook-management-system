#include <gtest/gtest.h>

#include "fixtures/student_test_fixture.h"
#include "dataframe.h"

void validateStudentsDataFrame(DataFrame &df)
{
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

TEST_F(StudentTestFixture, LoadStudents)
{
    DataFrame df = this->gradebook->studentsToDataFrame();
    validateStudentsDataFrame(df);
}

TEST_F(StudentTestFixture, SaveStudents)
{
    const std::string fileName = "saved_students.csv";
    this->gradebook->saveStudents(fileName);

    DataFrame df;
    df.load(fileName);
    validateStudentsDataFrame(df);
}

TEST_F(StudentTestFixture, PrintStudents)
{
    testing::internal::CaptureStdout();
    this->gradebook->studentsToDataFrame().print();
    const std::string output = testing::internal::GetCapturedStdout();

    const std::string expectedResult =
        std::string("----------------------------------------------------\n") +
        "| student_id |            name | grade_level | gpa | \n" +
        "----------------------------------------------------\n" +
        "|          1 |        John Doe |          12 | 3.8 | \n" +
        "|          2 |     Luke Sutton |          12 | 4.7 | \n" +
        "|          3 |   Jayden Gibson |          12 | 4.6 | \n" +
        "|          4 |     Leon Porter |          12 | 3.3 | \n" +
        "|          5 | William Edwards |          12 | 3.2 | \n" +
        "|          6 |  Morgan Bennett |          12 | 3.4 | \n" +
        "|          7 | Zander Bradford |          12 | 3.3 | \n" +
        "|          8 | Franklin Osborn |          12 | 3.3 | \n" +
        "|          9 |    Mauricio Orr |          12 | 4.3 | \n" +
        "----------------------------------------------------\n";

    EXPECT_EQ(output, expectedResult);
}

TEST_F(StudentTestFixture, QueryOneStudent)
{
    Student student = this->gradebook->getStudent("1");

    EXPECT_EQ(student.name, "John Doe");
    EXPECT_EQ(student.gradeLevel, 12);
    EXPECT_EQ(student.gpa, (float)3.8);

    student = this->gradebook->getStudent("2");

    EXPECT_EQ(student.name, "Luke Sutton");
    EXPECT_EQ(student.gradeLevel, 12);
    EXPECT_EQ(student.gpa, (float)4.7);

    student = this->gradebook->getStudent("3");

    EXPECT_EQ(student.name, "Jayden Gibson");
    EXPECT_EQ(student.gradeLevel, 12);
    EXPECT_EQ(student.gpa, (float)4.6);
}

TEST_F(StudentTestFixture, QueryAllStudents)
{
    std::vector<Student> students = this->gradebook->getStudents();

    EXPECT_EQ(students[0].name, "John Doe");
    EXPECT_EQ(students[0].gradeLevel, 12);
    EXPECT_EQ(students[0].gpa, (float)3.8);

    EXPECT_EQ(students[1].name, "Luke Sutton");
    EXPECT_EQ(students[1].gradeLevel, 12);
    EXPECT_EQ(students[1].gpa, (float)4.7);

    EXPECT_EQ(students[2].name, "Jayden Gibson");
    EXPECT_EQ(students[2].gradeLevel, 12);
    EXPECT_EQ(students[2].gpa, (float)4.6);
}