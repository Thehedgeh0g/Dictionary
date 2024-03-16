//
// Created by flipd on 12.03.2024.
//

#include <iostream>
#include "Dictionary.h"

Dictionary::Dictionary(const char* path) : dict()
{
    dictPath = path;
    std::ifstream dictStream(path);
    if (!dictStream.is_open())
    {
        throw std::runtime_error("Couldn't open dict file to read");
    }
    std::string translation;
    std::string word;

    while (std::getline(dictStream, word) && std::getline(dictStream, translation))
    {
        dict[word] = translation;
    }
    dictStream.close();
}

std::string Dictionary::GetTranslation(const std::string& query)
{
    std::string translation;
    std::string word;
    auto it = dict.find(query);
    if (it != dict.end())
    {
        return it->second;
    }
    if (!findKeysByValue(dict, query).empty())
    {
        return findKeysByValue(dict, query)[0];
    }
    it = buff.find(query);
    if (it != buff.end())
    {
        return it->second;
    }
    if (!findKeysByValue(buff, query).empty())
    {
        return findKeysByValue(buff, query)[0];
    }
    return "";
}

void Dictionary::AddTranslation(const std::string &query, const std::string &translation)
{
    buff[query] = translation;
}

void Dictionary::FlushBuff()
{
    dict.insert(buff.begin(), buff.end());
    buff.clear();
}

void Dictionary::SaveChanges()
{
    FlushBuff();
    std::fstream dictStream(dictPath, std::fstream::out);
    for (const auto& translationPair : dict)
    {
        dictStream << translationPair.first << std::endl << translationPair.second << std::endl;
    }
    dictStream.close();
}

void Dictionary::Exit()
{
    FlushBuff();
    dict.clear();
}

std::vector<std::string> Dictionary::findKeysByValue(
    const std::unordered_map<std::string,
    std::string> &inputMap,
    const std::string &value
)
{
    std::vector<std::string> result;
    for (auto const& pair : inputMap) {
        if (pair.second == value) {
            result.push_back(pair.first);
        }
    }
    return result;
}