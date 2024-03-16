cmake_minimum_required(VERSION 3.27)
project(Dictionary)

set(CMAKE_CXX_STANDARD 23)


set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -static")
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/bin)

include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)

FetchContent_MakeAvailable(googletest)

add_executable(${PROJECT_NAME}Test
        Test/test.cpp
        Classes/Dictionary.h
        Classes/Dictionary.cpp
)

target_link_libraries(${PROJECT_NAME}Test gtest_main)
enable_testing()
add_test(NAME ${PROJECT_NAME}Test COMMAND ${PROJECT_NAME}Test)

# Добавьте ваш исполняемый файл и любые другие исходные файлы
add_executable(${PROJECT_NAME}
        main.cpp
        Classes/Dictionary.h
        Classes/Dictionary.cpp
)

