# CMakeList.txt: файл проекта CMake верхнего уровня; проведите глобальную конфигурацию
# и включите сюда подпроекты.
#
cmake_minimum_required (VERSION 3.8)

project ("Height-BalancedSearchTrees")
set (CMAKE_CXX_STANDARD 17)
# Включите подпроекты.
add_subdirectory ("Height-BalancedSearchTrees")
