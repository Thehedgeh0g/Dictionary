#include <gtest/gtest.h>
#include "./../Classes/Dictionary.h"

// Тестирование конструктора Dictionary
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

// Тестирование метода GetTranslation
TEST(DictionaryTest, GetTranslationTest)
{
    std::ofstream file("./../Test/test_dictionary.txt");
    file.close();
    // Создаем объект словаря и добавляем в него пару ключ-значение
    Dictionary dict("./../Test/test_dictionary.txt");
    dict.AddTranslation("apple", "яблоко");

    // Проверяем, что метод GetTranslation возвращает ожидаемое значение
    EXPECT_EQ(dict.GetTranslation("apple"), "яблоко");
    // Проверяем, что метод GetTranslation возвращает пустую строку для отсутствующего слова
    EXPECT_EQ(dict.GetTranslation("banana"), "");
    std::remove("./../Test/test_dictionary.txt");
}

// Тестирование метода AddTranslation
TEST(DictionaryTest, AddTranslationTest)
{
    std::ofstream file("./../Test/test_dictionary.txt");
    file.close();
    // Создаем объект словаря и добавляем в него пару ключ-значение
    Dictionary dict("./../Test/test_dictionary.txt");
    dict.AddTranslation("apple", "яблоко");

    // Проверяем, что метод GetTranslation возвращает ожидаемое значение после добавления
    EXPECT_EQ(dict.GetTranslation("apple"), "яблоко");
    std::remove("./../Test/test_dictionary.txt");
}

// Тестирование метода SaveChanges
TEST(DictionaryTest, SaveChangesTest)
{
    std::ofstream file("./../Test/test_dictionary.txt");
    file.close();
    // Создаем объект словаря и добавляем в него пару ключ-значение
    Dictionary dict("./../Test/test_dictionary.txt");
    dict.AddTranslation("apple", "яблоко");

    // Сохраняем изменения
    dict.SaveChanges();

    // Создаем новый объект словаря и проверяем, что изменения сохранились
    Dictionary newDict("./../Test/test_dictionary.txt");
    EXPECT_EQ(newDict.GetTranslation("apple"), "яблоко");
    std::remove("./../Test/test_dictionary.txt");
}

// Тестирование метода Exit
TEST(DictionaryTest, ExitTest)
{
    std::ofstream file("./../Test/test_dictionary.txt");
    file.close();
    // Создаем объект словаря и добавляем в него пару ключ-значение
    Dictionary dict("./../Test/test_dictionary.txt");
    dict.AddTranslation("apple", "яблоко");

    // Вызываем метод Exit
    dict.Exit();

    // Проверяем, что словарь пуст
    EXPECT_EQ(dict.GetTranslation("apple"), "");
    std::remove("./../Test/test_dictionary.txt");
}

int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
