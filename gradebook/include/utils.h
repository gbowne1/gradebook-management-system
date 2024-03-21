#ifndef UTILS_H
#define UTILS_H

#include <iostream>
#include <vector>
#include <string>
#include <time.h>
#include <ctime>
#include <map>

/**
 * Gets all values contained in the given map.
 *
 * @param map Map to extract values from
 * @returns Vector of values
 */
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

/**
 * Converts epochs into a string-formatted date, with the following format: YYYY-mm-dd.
 *
 * @param time Time in epochs
 * @returns String-formatted date
 */
std::string timeToString(time_t time);

/**
 * Pauses the console until ENTER is pressed.
 */
void waitForKey();

#endif