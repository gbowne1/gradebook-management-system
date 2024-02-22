#include "utils.h"

std::string timeToString(time_t time)
{
    char dueDateChr[11];
    std::strftime(dueDateChr, sizeof(dueDateChr), "%Y-%m-%d", std::localtime(&time));
    return dueDateChr;
}

void waitForKey()
{
    std::cout << "Press ENTER to continue...";
    std::cin.ignore();
    std::getchar();
}