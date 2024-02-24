#ifndef UTILS_H
#define UTILS_H

#include <iostream>
#include <vector>
#include <string>
#include <time.h>
#include <ctime>
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

std::string timeToString(time_t time);

void waitForKey();

#endif