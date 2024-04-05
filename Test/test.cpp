#include <gtest/gtest.h>
#include "./../Classes/Dictionary.h"


TEST(DictionaryTest, ConstructorTest)
{
    std::ofstream file("./../Test/test_dictionary.txt");
    file.close();
    ASSERT_NO_THROW(
            {
                Dictionary dict("./../Test/test_dictionary.txt");
            }
        );
}

TEST(DictionaryTest, testCanNotOpenFile)
{
    std::ofstream file("./../Test/test_dictionary.txt");
    file.close();
    ASSERT_THROW(
            {
                Dictionary dict("test_dictionary.txt");
            },
            std::invalid_argument
    );
}


TEST(DictionaryTest, GetTranslationTest)
{
    std::ofstream file("./../Test/test_dictionary.txt");
    file.close();
    
    Dictionary dict("./../Test/test_dictionary.txt");
    dict.AddTranslation("apple", "Appel");

    
    EXPECT_EQ(dict.GetTranslation("apple"), "Appel");
    
    EXPECT_EQ(dict.GetTranslation("banana"), "");
    std::remove("./../Test/test_dictionary.txt");
}


TEST(DictionaryTest, GetMultiTranslationTest)
{
    std::ofstream file("./../Test/test_dictionary.txt");
    file.close();

    Dictionary dict("./../Test/test_dictionary.txt");
    dict.AddTranslation("apple", "Appel|Aple");


    EXPECT_EQ(dict.GetTranslation("apple"), "Appel, Aple");

    EXPECT_EQ(dict.GetTranslation("banana"), "");
    std::remove("./../Test/test_dictionary.txt");
}


TEST(DictionaryTest, AddTranslationTest)
{
    std::ofstream file("./../Test/test_dictionary.txt");
    file.close();
    
    Dictionary dict("./../Test/test_dictionary.txt");
    dict.AddTranslation("apple", "Appel");

    
    EXPECT_EQ(dict.GetTranslation("apple"), "Appel");
    std::remove("./../Test/test_dictionary.txt");
}


TEST(DictionaryTest, SaveChangesTest)
{
    std::ofstream file("./../Test/test_dictionary.txt");
    file.close();
    
    Dictionary dict("./../Test/test_dictionary.txt");
    dict.AddTranslation("apple", "Appel");

    
    dict.SaveChanges();

    
    Dictionary newDict("./../Test/test_dictionary.txt");
    EXPECT_EQ(newDict.GetTranslation("apple"), "Appel");
    std::remove("./../Test/test_dictionary.txt");
}


TEST(DictionaryTest, ExitTest)
{
    std::ofstream file("./../Test/test_dictionary.txt");
    file.close();
    
    Dictionary dict("./../Test/test_dictionary.txt");
    dict.AddTranslation("apple", "Appel");

    
    dict.Exit();

    
    EXPECT_EQ(dict.GetTranslation("apple"), "");
    std::remove("./../Test/test_dictionary.txt");
}

int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
