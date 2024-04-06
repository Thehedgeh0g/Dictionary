#include <iostream>
#include "Classes/Dictionary.h"

void replaceAllOccurrences(std::string& str, char target, char replacement)
{
    for (char& ch: str)
    {
        if (ch == target)
        {
            ch = replacement;
        }
    }
}

int main(int argc, char *argv[])
{
    setlocale(LC_ALL, "Russian");
    std::string query, translation;
    Dictionary dictionary(argv[1]);
    std::getline(std::cin, query);
    while (query != "...")
    {
        translation = dictionary.GetTranslation(query);
        if (!translation.empty())
        {
            std::cout << translation << std::endl;
            std::getline(std::cin, query);
            continue;
        }

        std::cout << "Unknown word " << query
                  << ". Enter a translation in form of 'translation1|translation2|translation3...' or an empty string to reject."
                  << std::endl;
        std::getline(std::cin, translation);
        if (!translation.empty())
        {
            dictionary.AddTranslation(query, translation);
            replaceAllOccurrences(translation, '|', ' ');
            std::cout << "The word '" << query << "' is stored in the dictionary as '" << translation << "'."
                      << std::endl;
        }

        std::getline(std::cin, query);
        while (std::empty(query))
        {
            std::getline(std::cin, query);
        }
    }
    if (dictionary.IsEdited())
    {
        std::cout << "Changes have been made to the dictionary. Enter Y or y to save before exiting." << std::endl;
        std::cin >> query;
        if (query == "Y" || query == "y")
        {
            dictionary.SaveChanges();
            std::cout << "Changes saved. ";
        }
    }
    dictionary.Exit();
    std::cout << "Goodbye" << std::endl;
    return 0;
}
