#include <gtest/gtest.h>

#include "fixtures/grade_test_fixture.h"
#include "dataframe.h"

void validateGradesDataFrame(DataFrame &df)
{
    EXPECT_EQ(df["assignment_id"][0], "1");
    EXPECT_EQ(df["student_id"][0], "1");
    EXPECT_EQ(df["score"][0], "72");

    EXPECT_EQ(df["assignment_id"][1], "1");
    EXPECT_EQ(df["student_id"][1], "2");
    EXPECT_EQ(df["score"][1], "20");

    EXPECT_EQ(df["assignment_id"][2], "1");
    EXPECT_EQ(df["student_id"][2], "3");
    EXPECT_EQ(df["score"][2], "7");
}

TEST_F(GradeTestFixture, LoadGrades)
{
    DataFrame df = this->gradebook.gradesToDataFrame();
    validateGradesDataFrame(df);
}

TEST_F(GradeTestFixture, SaveGrades)
{
    const std::string fileName = "saved_grades.csv";
    this->gradebook.saveGrades(fileName);

    DataFrame df;
    df.load(fileName);
    validateGradesDataFrame(df);

    EXPECT_EQ(remove(fileName.c_str()), 0);
}

TEST_F(GradeTestFixture, PrintGrades)
{
    testing::internal::CaptureStdout();
    this->gradebook.gradesToDataFrame().print();
    const std::string output = testing::internal::GetCapturedStdout();

    const std::string expectedResult =
        std::string("--------------------------------------\n") +
        "| assignment_id | student_id | score | \n" +
        "--------------------------------------\n" +
        "|             1 |          1 |    72 | \n" +
        "|             1 |          2 |    20 | \n" +
        "|             1 |          3 |     7 | \n" +
        "|             1 |          4 |    50 | \n" +
        "|             1 |          5 |    25 | \n" +
        "|             1 |          6 |    11 | \n" +
        "|             1 |          7 |    78 | \n" +
        "|             1 |          8 |    75 | \n" +
        "|             1 |          9 |    98 | \n" +
        "|             2 |          1 |    26 | \n" +
        "|             2 |          2 |    23 | \n" +
        "|             2 |          3 |     8 | \n" +
        "|             2 |          4 |    46 | \n" +
        "|             2 |          5 |    54 | \n" +
        "|             2 |          6 |    22 | \n" +
        "|             2 |          7 |    93 | \n" +
        "|             2 |          8 |    29 | \n" +
        "|             2 |          9 |    73 | \n" +
        "|             3 |          1 |    51 | \n" +
        "|             3 |          2 |    67 | \n" +
        "|             3 |          3 |    13 | \n" +
        "|             3 |          4 |    42 | \n" +
        "|             3 |          5 |    52 | \n" +
        "|             3 |          6 |    36 | \n" +
        "|             3 |          7 |     7 | \n" +
        "|             3 |          8 |    95 | \n" +
        "|             3 |          9 |    52 | \n" +
        "|             4 |          1 |     3 | \n" +
        "|             4 |          2 |    41 | \n" +
        "|             4 |          3 |    22 | \n" +
        "|             4 |          4 |    95 | \n" +
        "|             4 |          5 |    33 | \n" +
        "|             4 |          6 |    39 | \n" +
        "|             4 |          7 |    50 | \n" +
        "|             4 |          8 |    82 | \n" +
        "|             4 |          9 |    74 | \n" +
        "|             5 |          1 |    20 | \n" +
        "|             5 |          2 |    65 | \n" +
        "|             5 |          3 |    13 | \n" +
        "|             5 |          4 |    26 | \n" +
        "|             5 |          5 |    25 | \n" +
        "|             5 |          6 |    43 | \n" +
        "|             5 |          7 |    75 | \n" +
        "|             5 |          8 |    22 | \n" +
        "|             5 |          9 |    54 | \n" +
        "|             6 |          1 |    22 | \n" +
        "|             6 |          2 |    22 | \n" +
        "|             6 |          3 |    57 | \n" +
        "|             6 |          4 |    59 | \n" +
        "|             6 |          5 |    28 | \n" +
        "|             6 |          6 |    20 | \n" +
        "|             6 |          7 |     5 | \n" +
        "|             6 |          8 |    74 | \n" +
        "|             6 |          9 |    33 | \n" +
        "|             7 |          1 |    69 | \n" +
        "|             7 |          2 |    82 | \n" +
        "|             7 |          3 |    34 | \n" +
        "|             7 |          4 |    33 | \n" +
        "|             7 |          5 |    59 | \n" +
        "|             7 |          6 |    32 | \n" +
        "|             7 |          7 |    14 | \n" +
        "|             7 |          8 |    23 | \n" +
        "|             7 |          9 |    35 | \n" +
        "|             8 |          1 |    13 | \n" +
        "|             8 |          2 |    36 | \n" +
        "|             8 |          3 |    27 | \n" +
        "|             8 |          4 |    97 | \n" +
        "|             8 |          5 |    71 | \n" +
        "|             8 |          6 |    25 | \n" +
        "|             8 |          7 |    42 | \n" +
        "|             8 |          8 |    77 | \n" +
        "|             8 |          9 |    56 | \n" +
        "|             9 |          1 |    56 | \n" +
        "|             9 |          2 |    26 | \n" +
        "|             9 |          3 |    39 | \n" +
        "|             9 |          4 |    87 | \n" +
        "|             9 |          5 |     8 | \n" +
        "|             9 |          6 |    15 | \n" +
        "|             9 |          7 |    55 | \n" +
        "|             9 |          8 |    48 | \n" +
        "|             9 |          9 |    65 | \n" +
        "--------------------------------------\n";

    EXPECT_EQ(output, expectedResult);
}

TEST_F(GradeTestFixture, QueryOneGrade)
{
    Grade grade = this->gradebook.getGrade("1", "1");
    EXPECT_EQ(grade.score, 72);

    grade = this->gradebook.getGrade("1", "2");
    EXPECT_EQ(grade.score, 20);

    grade = this->gradebook.getGrade("1", "3");
    EXPECT_EQ(grade.score, 7);
}

TEST_F(GradeTestFixture, QueryGradesByAssignment)
{
    auto grades = this->gradebook.getAssignmentGrades("1");

    Student student = grades[0].first;
    Grade grade = grades[0].second;
    EXPECT_EQ(student.name, "John Doe");
    EXPECT_EQ(grade.score, 72);

    student = grades[1].first;
    grade = grades[1].second;
    EXPECT_EQ(student.name, "Luke Sutton");
    EXPECT_EQ(grade.score, 20);

    student = grades[2].first;
    grade = grades[2].second;
    EXPECT_EQ(student.name, "Jayden Gibson");
    EXPECT_EQ(grade.score, 7);
}

TEST_F(GradeTestFixture, QueryGradeByStudent)
{
    auto grades = this->gradebook.getStudentGrades("1");

    Assignment assignment = grades[0].first;
    Grade grade = grades[0].second;
    EXPECT_EQ(assignment.name, "Chemical Elements");
    EXPECT_EQ(grade.score, 72);

    assignment = grades[1].first;
    grade = grades[1].second;
    EXPECT_EQ(assignment.name, "Nuclear Fission");
    EXPECT_EQ(grade.score, 26);

    assignment = grades[2].first;
    grade = grades[2].second;
    EXPECT_EQ(assignment.name, "Matrices");
    EXPECT_EQ(grade.score, 51);
}

TEST_F(GradeTestFixture, QueryAllGrades)
{
    auto grades = this->gradebook.getGrades();

    Assignment assignment = std::get<0>(grades[0]);
    Student student = std::get<1>(grades[0]);
    Grade grade = std::get<2>(grades[0]);
    EXPECT_EQ(assignment.name, "Chemical Elements");
    EXPECT_EQ(student.name, "John Doe");
    EXPECT_EQ(grade.score, 72);

    assignment = std::get<0>(grades[1]);
    student = std::get<1>(grades[1]);
    grade = std::get<2>(grades[1]);
    EXPECT_EQ(assignment.name, "Chemical Elements");
    EXPECT_EQ(student.name, "Luke Sutton");
    EXPECT_EQ(grade.score, 20);

    assignment = std::get<0>(grades[2]);
    student = std::get<1>(grades[2]);
    grade = std::get<2>(grades[2]);
    EXPECT_EQ(assignment.name, "Chemical Elements");
    EXPECT_EQ(student.name, "Jayden Gibson");
    EXPECT_EQ(grade.score, 7);
}