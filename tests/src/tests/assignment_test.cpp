#include <gtest/gtest.h>

#include "fixtures/assignment_test_fixture.h"
#include "dataframe.h"
#include "utils.h"

void validateAssignmentsDataFrame(DataFrame &df)
{
    EXPECT_EQ(df["assignment_id"][0], "1");
    EXPECT_EQ(df["name"][0], "Chemical Elements");
    EXPECT_EQ(df["due_date"][0], "2023-12-01");
    EXPECT_EQ(df["class_id"][0], "1");

    EXPECT_EQ(df["assignment_id"][1], "2");
    EXPECT_EQ(df["name"][1], "Nuclear Fission");
    EXPECT_EQ(df["due_date"][1], "2023-11-15");
    EXPECT_EQ(df["class_id"][1], "1");

    EXPECT_EQ(df["assignment_id"][2], "3");
    EXPECT_EQ(df["name"][2], "Matrices");
    EXPECT_EQ(df["due_date"][2], "2023-11-13");
    EXPECT_EQ(df["class_id"][2], "2");
}

TEST_F(AssignmentTestFixture, LoadAssignments)
{
    DataFrame df = this->gradebook.assignmentsToDataFrame();
    validateAssignmentsDataFrame(df);
}

TEST_F(AssignmentTestFixture, SaveAssignments)
{
    const std::string fileName = "saved_assignments.csv";
    this->gradebook.saveAssignments(fileName);

    DataFrame df;
    df.load(fileName);
    validateAssignmentsDataFrame(df);

    EXPECT_EQ(remove(fileName.c_str()), 0);
}

TEST_F(AssignmentTestFixture, PrintAssignments)
{
    testing::internal::CaptureStdout();
    this->gradebook.assignmentsToDataFrame().print();
    const std::string output = testing::internal::GetCapturedStdout();

    const std::string expectedResult =
        std::string("-------------------------------------------------------------------\n") +
        "| assignment_id |                    name |   due_date | class_id | \n" +
        "-------------------------------------------------------------------\n" +
        "|             1 |       Chemical Elements | 2023-12-01 |        1 | \n" +
        "|             2 |         Nuclear Fission | 2023-11-15 |        1 | \n" +
        "|             3 |                Matrices | 2023-11-13 |        2 | \n" +
        "|             4 |                Graphing | 2023-11-30 |        2 | \n" +
        "|             5 |         Gravity Studies | 2023-12-03 |        3 | \n" +
        "|             6 |              NASA Visit | 2023-11-09 |        3 | \n" +
        "|             7 | Shakespeare Book Review | 2023-12-04 |        4 | \n" +
        "|             8 |             Old English | 2023-11-17 |        4 | \n" +
        "|             9 |           Vikings Raids | 2023-11-28 |        5 | \n" +
        "-------------------------------------------------------------------\n";

    EXPECT_EQ(output, expectedResult);
}

TEST_F(AssignmentTestFixture, QueryOneAssignment)
{
    Assignment assignment = this->gradebook.getAssignment("1");
    EXPECT_EQ(assignment.name, "Chemical Elements");
    EXPECT_EQ(timeToString(assignment.dueDate), "2023-12-01");
    EXPECT_EQ(assignment.classId, 1);

    assignment = this->gradebook.getAssignment("2");
    EXPECT_EQ(assignment.name, "Nuclear Fission");
    EXPECT_EQ(timeToString(assignment.dueDate), "2023-11-15");
    EXPECT_EQ(assignment.classId, 1);

    assignment = this->gradebook.getAssignment("3");
    EXPECT_EQ(assignment.name, "Matrices");
    EXPECT_EQ(timeToString(assignment.dueDate), "2023-11-13");
    EXPECT_EQ(assignment.classId, 2);
}

TEST_F(AssignmentTestFixture, QueryAllAssignments)
{
    std::vector<Assignment> assignments = this->gradebook.getAssignments();

    EXPECT_EQ(assignments[0].name, "Chemical Elements");
    EXPECT_EQ(timeToString(assignments[0].dueDate), "2023-12-01");
    EXPECT_EQ(assignments[0].classId, 1);

    EXPECT_EQ(assignments[1].name, "Nuclear Fission");
    EXPECT_EQ(timeToString(assignments[1].dueDate), "2023-11-15");
    EXPECT_EQ(assignments[1].classId, 1);

    EXPECT_EQ(assignments[2].name, "Matrices");
    EXPECT_EQ(timeToString(assignments[2].dueDate), "2023-11-13");
    EXPECT_EQ(assignments[2].classId, 2);
}