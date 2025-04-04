#include "../include/dataframe.h"

#include <fstream>
#include <sstream>
#include <iomanip>
#include <stdexcept>

DataFrame::DataFrame() {}

DataFrame::DataFrame(const std::string &fileName)
{
    this->load(fileName);
}

std::map<std::string, std::string *> DataFrame::operator[](size_t index)
{
    std::map<std::string, std::string *> series;

    for (auto it = this->data.begin(); it != this->data.end(); it++)
    {
        series[it->first] = &it->second[index];
    }

    return series;
}

std::vector<std::string> &DataFrame::operator[](const std::string &key)
{
    auto it = this->data.find(key);
    if (it == this->data.end())
    {
        throw std::out_of_range("Key not found in DataFrame");
    }
    return it->second;
}

size_t DataFrame::sizeRows()
{
    return this->data.size();
}

size_t DataFrame::sizeCols()
{
    auto it = this->data.begin();
    if (it == this->data.end())
        return 0;

    return it->second.size();
}

void DataFrame::clear()
{
    this->data.clear();
    this->header.clear();
}

void DataFrame::initialize(const std::vector<std::string> &header)
{
    if (!this->header.empty())
        this->header.clear();

    if (!this->data.empty())
        this->data.clear();

    for (const std::string &label : header)
    {
        this->header.push_back(label);
        this->data[label] = std::vector<std::string>();
    }
}

void DataFrame::append(const std::map<std::string, std::string> &row)
{
    if (this->header.empty())
    {
        std::vector<std::string> header;
        for (const auto &it : row)
        {
            header.push_back(it.first);
        }
        this->initialize(header);
    }

    for (auto it = this->data.begin(); it != this->data.end(); it++)
    {
        std::string key = it->first;
        std::vector<std::string> &col = it->second;
        if (!row.count(key))
        {
            col.push_back("");
            continue;
        }

        col.push_back(row.at(key));
    }
}

void DataFrame::remove(size_t index)
{
    if (index >= this->sizeCols())
    {
        throw std::out_of_range("Index out of range in DataFrame::remove");
    }

    for (auto it = this->data.begin(); it != this->data.end(); it++)
    {
        it->second.erase(it->second.begin() + index);
    }
}

bool DataFrame::hasColumn(const std::string &columnName) const
{
    return this->data.find(columnName) != this->data.end();
}

std::vector<size_t> DataFrame::getMaxColumnSizes()
{
    std::vector<size_t> columnSizes;

    for (const std::string &key : this->header)
    {
        size_t max = key.size();
        for (const std::string &value : this->data[key])
        {
            size_t strSize = value.size();
            if (strSize > max)
                max = strSize;
        }
        columnSizes.push_back(max);
    }

    return columnSizes;
}

void DataFrame::printLine(std::ostream &out, size_t lineWidth)
{
    for (size_t i = 0; i < lineWidth; i++)
        out << "-";
    out << std::endl;
}

void DataFrame::print(std::ostream &out)
{
    if (this->header.empty())
        return;

    std::vector<size_t> columnSizes = this->getMaxColumnSizes();

    size_t lineWidth = 1 + 3 * columnSizes.size();
    for (size_t columnSize : columnSizes)
        lineWidth += columnSize;

    printLine(out, lineWidth);

    out << "| ";
    for (size_t i = 0; i < this->header.size(); i++)
    {
        out << std::setw(columnSizes[i]) << this->header[i] << " | ";
    }

    out << std::endl;
    printLine(out, lineWidth);

    for (size_t i = 0; i < this->data[this->header[0]].size(); i++)
    {
        out << "| ";
        for (size_t j = 0; j < this->header.size(); j++)
        {
            const std::string &key = this->header[j];
            out << std::setw(columnSizes[j]) << this->data[key][i] << " | ";
        }

        out << std::endl;
    }

    printLine(out, lineWidth);
}

int DataFrame::load(const std::string &fileName)
{
    std::ifstream ifs(fileName);

    if (!ifs.is_open())
    {
        return 1; // Failed to open file
    }

    std::string line, cell;
    size_t index = 0;

    while (getline(ifs, line))
    {
        size_t rowIndex = 0;
        std::stringstream str(line);
        while (getline(str, cell, ','))
        {
            if (index == 0)
            {
                this->header.push_back(cell);
                continue;
            }

            this->data[this->header[rowIndex]].push_back(cell);
            rowIndex++;
        }

        index++;
    }

    return 0;
}

int DataFrame::save(const std::string &fileName)
{
    if (this->header.empty())
        return 1;

    std::ofstream ofs(fileName);
    for (size_t i = 0; i < this->header.size(); i++)
    {
        ofs << this->header[i];
        if (i != this->header.size() - 1)
        {
            ofs << ",";
        }
    }
    ofs << std::endl;

    for (size_t i = 0; i < this->sizeCols(); i++)
    {
        for (size_t j = 0; j < this->header.size(); j++)
        {
            ofs << this->data[this->header[j]][i];
            if (j != this->header.size() - 1)
            {
                ofs << ",";
            }
        }
        ofs << std::endl;
    }

    return 0;
}
