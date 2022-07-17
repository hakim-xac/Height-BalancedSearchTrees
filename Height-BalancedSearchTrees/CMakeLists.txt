# CMakeList.txt: проект CMake для Height-BalancedSearchTrees; включите исходный код и определения,
# укажите здесь логику для конкретного проекта.
#
cmake_minimum_required (VERSION 3.8)

# Добавьте источник в исполняемый файл этого проекта.
add_executable (Height-BalancedSearchTrees 
    "Height-BalancedSearchTrees.cpp"
    "Height-BalancedSearchTrees.h"
    "Interface.h"
    "Interface.cpp"
    "TaskExecution.h"
    "TaskExecution.cpp"
    "Node.h"
    "AVLTree.h"
    "AVLTree.cpp"
    "Node.cpp"
    "Enums.h")

# TODO: Добавьте тесты и целевые объекты, если это необходимо.
