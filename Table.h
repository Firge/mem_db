#ifndef TABLE_H
#define TABLE_H

#include "Record.h"
#include <vector>
#include <string>
#include <iostream>

class Table {
public:
    std::string name;
    std::vector<std::string> columns;
    std::vector<Record> records;

    Table() = default;

    Table(const std::string& name, const std::vector<std::string>& columns)
        : name(name), columns(columns) {}

    void insert(const std::unordered_map<std::string, std::string>& data) {
        records.emplace_back(data);
    }

    void display() const {
        for (const auto& column : columns) {
            std::cout << column << "\t";
        }
        std::cout << std::endl;

        for (const auto& record : records) {
            for (const auto& column : columns) {
                std::cout << record.fields.at(column) << "\t";
            }
            std::cout << std::endl;
        }
    }
};

#endif // TABLE_H
