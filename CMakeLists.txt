cmake_minimum_required(VERSION 3.2)
project(Trabalho_OAC)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
SET(CMAKE_CXX_COMPILER /usr/bin/g++)
set(SOURCE_FILES
    Assembler.cpp
    HelpFuncts.cpp
    AsmFuncts.cpp
    Conversion.cpp
    Codes.cpp
    Disassembler.cpp
    Main.cpp)

add_executable(Trabalho_OAC ${SOURCE_FILES})