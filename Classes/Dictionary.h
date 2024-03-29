//
// Created by flipd on 12.03.2024.
//

#ifndef DICTIONARY_DICTIONARY_H
#define DICTIONARY_DICTIONARY_H


#include <string>
#include <fstream>
#include <unordered_map>
#include <vector>

class Dictionary
{
public:
    explicit Dictionary(const char *path);

    std::string GetTranslation(const std::string& query);

    void AddTranslation(const std::string& query, const std::string& translation);

    void SaveChanges();

    void Exit();

    bool IsEdited() const;

private:
    std::string dictPath;
    std::unordered_map<std::string, std::vector<std::string>> dict;
    bool isEdited;

    static std::vector<std::string> ExplodeTranslation(const std::string& str, char delimiter);

    static std::string Trim(const std::string& str);

    static std::vector<std::string> FindKeysByValue(
            const std::unordered_map<std::string, std::vector<std::string>>& inputMap,
            const std::string& value
    );
};


#endif //DICTIONARY_DICTIONARY_H
