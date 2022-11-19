cmake_minimum_required(VERSION 3.5)

project(PlainCPP LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(PlainCPP main.cpp)

install(TARGETS PlainCPP
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})
