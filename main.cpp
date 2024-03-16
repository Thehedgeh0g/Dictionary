#include <iostream>
#include "Classes/Dictionary.h"

int main(int argc, char* argv[])
{
    std::string query, translation;
    Dictionary dictionary(argv[1]);
    std::cin >> query;
    while (query != "...")
    {
        translation = dictionary.GetTranslation(query);
        if (!translation.empty())
        {
            std::cout << translation << std::endl;
            std::cin >> query;
            continue;
        }

        std::cin >> translation;
        if (!translation.empty())
        {
            dictionary.AddTranslation(query, translation);
        }

        std::cin >> query;
    }
    std::cin >> query;
    if (query == "Y" || query == "y")
    {
        dictionary.SaveChanges();
    }
    dictionary.Exit();
    return 0;
}
