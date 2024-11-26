#include "Database.h"
#include <algorithm>

void Database::execute(const std::string& query) {
    auto tokens = tokenize(query);
    if (tokens[0] == "create" && tokens[1] == "table") {
        createTable(tokens);
    } else if (tokens[0] == "insert") {
        insertIntoTable(tokens);
    } else if (tokens[0] == "select") {
        selectFromTable(tokens);
    } else if (tokens[0] == "update") {
        updateTable(tokens);
    } else if (tokens[0] == "delete") {
        deleteFromTable(tokens);
    } else {
        std::cout << "Unknown command" << std::endl;
    }
}

std::vector<std::string> Database::tokenize(const std::string& query) {
    std::vector<std::string> tokens;
    std::string token;
    for (char ch : query) {
        if (ch == ' ' || ch == '(' || ch == ')' || ch == ',') {
            if (!token.empty()) {
                tokens.push_back(token);
                token.clear();
            }
        } else {
            token += ch;
        }
    }
    if (!token.empty()) {
        tokens.push_back(token);
    }
    return tokens;
}

void Database::createTable(const std::vector<std::string>& tokens) {
    std::string tableName = tokens[2];
    std::vector<std::string> columns(tokens.begin() + 3, tokens.end());
    tables.emplace(std::piecewise_construct,
                   std::forward_as_tuple(tableName),
                   std::forward_as_tuple(tableName, columns));
    std::cout << "Table " << tableName << " created." << std::endl;
}

void Database::insertIntoTable(const std::vector<std::string>& tokens) {
    std::string tableName = tokens.back();
    std::unordered_map<std::string, std::string> data;
    for (size_t i = 1; i < tokens.size() - 2; i += 2) {
        data[tokens[i]] = tokens[i + 1];
    }
    tables[tableName].insert(data);
    std::cout << "Record inserted into " << tableName << "." << std::endl;
}

void Database::selectFromTable(const std::vector<std::string>& tokens) {
    std::string tableName = tokens.back();
    tables[tableName].display();
}

void Database::updateTable(const std::vector<std::string>& tokens) {
    // Format: update <table> set <column> <value> where <condition_column> <condition_value>
    if (tokens.size() < 8) {
        std::cout << "Invalid UPDATE command format" << std::endl;
        return;
    }
    
    std::string tableName = tokens[1];
    std::string columnName = tokens[3];  // after 'set'
    std::string newValue = tokens[4];    // value after column name
    std::string conditionColumn = tokens[6];  // after 'where'
    std::string conditionValue = tokens[7];   // value after condition column
    
    for (auto& record : tables[tableName].records) {
        if (record.fields[conditionColumn] == conditionValue) {
            record.fields[columnName] = newValue;
        }
    }
    std::cout << "Records updated in " << tableName << "." << std::endl;
}

void Database::deleteFromTable(const std::vector<std::string>& tokens) {
    // Format: delete <table> where <column> <value>
    if (tokens.size() < 5) {
        std::cout << "Invalid DELETE command format" << std::endl;
        return;
    }
    
    std::string tableName = tokens[1];
    std::string conditionColumn = tokens[3];  // after 'where'
    std::string conditionValue = tokens[4];   // value after condition column
    
    auto& records = tables[tableName].records;
    records.erase(
        std::remove_if(records.begin(), records.end(),
                      [&conditionColumn, &conditionValue](const Record& record) {
                          return record.fields.at(conditionColumn) == conditionValue;
                      }),
        records.end());
    std::cout << "Records deleted from " << tableName << "." << std::endl;
}

void Database::save_to_file(const std::string& filename) {
    std::ofstream file(filename);
    for (const auto& [name, table] : tables) {
        file << "create table " << name << " ";
        for (const auto& column : table.columns) {
            file << column << " ";
        }
        file << "\n";
        for (const auto& record : table.records) {
            file << "insert ";
            for (const auto& column : table.columns) {
                file << column << " " << record.fields.at(column) << " ";
            }
            file << "to " << name << "\n";
        }
    }
    file.close();
}

void Database::load_from_file(const std::string& filename) {
    std::ifstream file(filename);
    std::string query;
    while (std::getline(file, query)) {
        execute(query);
    }
    file.close();
}
