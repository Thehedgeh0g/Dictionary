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
    explicit Dictionary(const char* path);

    std::string GetTranslation(const std::string& query);
    void AddTranslation(const std::string& query, const std::string& translation);
    void SaveChanges();
    void Exit();
private:
    std::string dictPath;
    std::unordered_map<std::string, std::string> dict;
    std::unordered_map<std::string, std::string> buff;

    void FlushBuff();

    static std::vector<std::string> findKeysByValue(const std::unordered_map<std::string, std::string>& inputMap, const std::string& value);
};


#endif //DICTIONARY_DICTIONARY_H
