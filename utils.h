
#ifndef UTILS_H
#define UTILS_H

#include <vector>
#include <map>

template <typename T, typename U>
std::vector<T> getMapValues(const std::map<U, T> map)
{
    std::vector<T> values;
    for (const std::pair<U, T> &entry : map)
    {
        values.push_back(entry.second);
    }

    return values;
}

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

#endif