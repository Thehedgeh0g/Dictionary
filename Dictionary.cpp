//
// Created by flipd on 12.03.2024.
//

#include <iostream>
#include "Dictionary.h"

Dictionary::Dictionary(const char* path) : dictFile()
{
    dictFile.open(path, std::fstream::app | std::fstream::in);
    if (!dictFile.is_open())
    {
        throw std::runtime_error("Can not open dictionary file");
    }
    tmpFile.open(getDirectoryPath(path) + "/tmp.txt", std::fstream::app | std::fstream::in);
    if (!dictFile.is_open())
    {
        throw std::runtime_error("Can not open temp file");
    }
}

std::string Dictionary::GetTranslation(const std::string& query)
{
    std::string translation;
    std::string word;
    while (dictFile >> word >> translation) {
        if (word == query) return translation;
        if (translation == query) return word;
    }
    while (tmpFile >> word >> translation) {
        if (word == query) return translation;
        if (translation == query) return word;
    }
    auto it = buff.find(query);
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
//    if (buff.size() > 100)
//    {
        FlushBuff();
//    }
    buff[query] = translation;
}

void Dictionary::FlushBuff()
{
    std::string line;
    char* bytes;
    int bytesCount;
    for (const auto& dictPair : buff)
    {
        tmpFile.seekp(1);
        line = dictPair.first + " " + dictPair.second + "\n";
        bytes = const_cast<char *>(line.c_str());
        bytesCount = line.size();

        tmpFile.write(bytes, bytesCount);

        std::cout << tmpFile.bad() << std::endl;
    }
    tmpFile.flush();
    buff.clear();

}

void Dictionary::SaveChanges()
{
    FlushBuff();
    std::string translationPair;
    while (std::getline(tmpFile, translationPair))
    {
        dictFile << translationPair << std::endl;
    }
}

void Dictionary::Exit()
{
    tmpFile.close();
    dictFile.close();
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

std::string Dictionary::getDirectoryPath(const std::string &filePath)
{
    size_t found = filePath.find_last_of("/\\");
    return filePath.substr(0, found);
}