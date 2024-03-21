// File:   reportgenerator.h
// Author: Gregory K. Bowne
// Date:   28 Feb 2024
// Time:   14:48:32
// Brief:  Report generator

#include <iostream>
#include <fstream>
#include <string>

// Function to generate a report card for a student
void generateReportCard(const std::string &studentName, const std::string &grade, const std::string &teacherComments)
{
    std::ofstream reportCard("report_card_" + studentName + ".txt");

    if (reportCard.is_open())
    {
        reportCard << "Student Name: " << studentName << "\n";
        reportCard << "Grade: " << grade << "\n";
        reportCard << "Teacher Comments: " << teacherComments << "\n";

        reportCard.close();
        std::cout << "Report card generated successfully for " << studentName << std::endl;
    }
    else
    {
        std::cout << "Unable to generate the report card for " << studentName << std::endl;
    }
}

// Function to generate a report for school administrators and teachers
void generateReport(const std::string &reportTitle, const std::string &content)
{
    std::ofstream reportFile(reportTitle + ".txt");

    if (reportFile.is_open())
    {
        reportFile << "Report Title: " << reportTitle << "\n\n";
        reportFile << content;

        reportFile.close();
        std::cout << "Report generated successfully: " << reportTitle << ".txt" << std::endl;
    }
    else
    {
        std::cout << "Unable to generate the report: " << reportTitle << ".txt" << std::endl;
    }
}