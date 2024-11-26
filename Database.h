#ifndef DATABASE_H
#define DATABASE_H

#include "Table.h"
#include <unordered_map>
#include <fstream>

class Database {
public:
    std::unordered_map<std::string, Table> tables;

    void execute(const std::string& query);
    void save_to_file(const std::string& filename);
    void load_from_file(const std::string& filename);

private:
    std::vector<std::string> tokenize(const std::string& query);
    void createTable(const std::vector<std::string>& tokens);
    void insertIntoTable(const std::vector<std::string>& tokens);
    void selectFromTable(const std::vector<std::string>& tokens);
    void updateTable(const std::vector<std::string>& tokens);
    void deleteFromTable(const std::vector<std::string>& tokens);
};

#endif // DATABASE_H
