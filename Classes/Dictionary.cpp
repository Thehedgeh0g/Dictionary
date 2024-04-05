#include <iostream>
#include <sstream>
#include <numeric>
#include "Dictionary.h"

Dictionary::Dictionary(const char *path)
{
    dictPath = path;
    isEdited = false;
    std::ifstream dictStream(path);
    if (!dictStream.is_open())
    {
        throw std::invalid_argument("Couldn't open dict file to read");
    }
    std::string translation;
    std::string word;

    while (std::getline(dictStream, word) && std::getline(dictStream, translation))
    {
        std::vector<std::string> translations = ExplodeTranslation(translation, '|');
        for (const std::string& translationVariant: translations)
        {
            dict[word].push_back(translationVariant);
        }
    }
    dictStream.close();
}

std::string Dictionary::GetTranslation(const std::string& query)
{
    std::string translation;
    auto it = dict.find(query);
    if (it != dict.end())
    {
        return Trim(std::accumulate(it->second.begin(), it->second.end(), std::string(),
                                    [](const std::string& a, const std::string& b) {
                                        return a + ", " + b;
                                    })).substr(2);
    }
    std::vector<std::string> keys = FindKeysByValue(dict, query);
    if (!keys.empty())
    {
        return Trim(std::accumulate(keys.begin(), keys.end(), std::string(),
                                    [](const std::string& a, const std::string& b) {
                                        return a + ", " + b;
                                    })).substr(2);
    }
    return "";
}

void Dictionary::AddTranslation(const std::string& query, const std::string& translation)
{
    isEdited = true;
    std::vector<std::string> translations = ExplodeTranslation(translation, '|');
    for (const std::string& translationVariant: translations)
    {
        dict[query].push_back(translationVariant);
    }
}

void Dictionary::SaveChanges()
{
    std::ofstream dictStream(dictPath);
    for (const auto& translationPair: dict)
    {
        dictStream << translationPair.first << std::endl;
        for (const auto& translation: dict[translationPair.first])
        {
            dictStream << translation << "|";
        }
        dictStream << std::endl;
    }
    dictStream.close();
}

void Dictionary::Exit()
{
    dict.clear();
}

std::vector<std::string> Dictionary::FindKeysByValue(
        const std::unordered_map<std::string, std::vector<std::string>>& inputMap,
        const std::string& value
)
{
    std::vector<std::string> result;
    for (const auto& pair: inputMap)
    {
        for (const auto& str: pair.second)
        {
            if (str == value)
            {
                result.push_back(pair.first);
                break;
            }
        }
    }
    return result;
}

bool Dictionary::IsEdited() const
{
    return isEdited;
}

std::vector<std::string> Dictionary::ExplodeTranslation(const std::string& str, char delimiter)
{
    std::vector<std::string> result;
    std::stringstream ss(str);
    std::string token;
    while (std::getline(ss, token, delimiter))
    {
        result.push_back(token);
    }
    return result;
}

std::string Dictionary::Trim(const std::string& str)
{
    size_t start = 0;
    size_t end = str.length();

    while (start < end && std::isspace(str[start]))
    {
        ++start;
    }

    while (end > start && std::isspace(str[end - 1]))
    {
        --end;
    }

    return str.substr(start, end - start);
}