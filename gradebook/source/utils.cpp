#include "../include/utils.h"
#include <iostream>
#include <limits>
#include <ctime>
#include <stdexcept>

// TODO Add some
std::string timeToString(time_t time)
{
    char dueDateChr[11]; // Buffer size is large enough for "%Y-%m-%d"
    if (std::strftime(dueDateChr, sizeof(dueDateChr), "%Y-%m-%d", std::localtime(&time)) == 0)
    {
        // Handle strftime error here
        std::cerr << "Error formatting date. Please check the format string." << std::endl;
        // Optionally, throw an exception or return a specific error string
        // throw std::runtime_error("Failed to format date.");
        return "Error";
    }
    return std::string(dueDateChr);
}

// Wait for user input before continuing
void waitForKey()
{
    std::cout << "Press ENTER to continue...";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Clear input buffer
    std::cin.get();                                                     // Wait for user to press Enter
}