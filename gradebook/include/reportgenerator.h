// File:   reportgenerator.h
// Author: Gregory K. Bowne
// Date:   28 Feb 2024
// Time:   14:51:12
// Brief:  Permission system for GradeBook user hierarchy

#ifndef REPORT_GENERATOR_H // Include guards to prevent multiple inclusions
#define REPORT_GENERATOR_H

#include <string>

// Function declarations
void generateReportCard(const std::string& studentName, const std::string& grade, const std::string& teacherComments);
void generateReport(const std::string& reportTitle, const std::string& content);

#endif // REPORT_GENERATOR_H