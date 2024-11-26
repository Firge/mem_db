#ifndef RECORD_H
#define RECORD_H

#include <unordered_map>
#include <string>

class Record {
public:
    std::unordered_map<std::string, std::string> fields;

    Record(const std::unordered_map<std::string, std::string>& fields) : fields(fields) {}
};

#endif // RECORD_H
