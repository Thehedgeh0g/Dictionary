//
// Created by flipd on 12.03.2024.
//

#ifndef DICTIONARY_DICTIONARY_H
#define DICTIONARY_DICTIONARY_H


#include <string>ъ
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
    std::unordered_map<std::string, std::string> buff;
    std::fstream dictFile;
    std::fstream tmpFile;

    void FlushBuff();

    static std::vector<std::string> findKeysByValue(const std::unordered_map<std::string, std::string>& inputMap, const std::string& value);
    std::string getDirectoryPath(const std::string& filePath);
};


#endif //DICTIONARY_DICTIONARY_H
