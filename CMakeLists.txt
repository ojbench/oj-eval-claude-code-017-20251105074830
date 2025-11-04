cmake_minimum_required(VERSION 3.10)
project(train_ticket_system)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Use default compiler (don't specify g++-13)

# Compiler flags
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O2 -std=c++17 -Wall -Wextra")

# Create the executable named 'code'
add_executable(code main.cpp train_system.cpp train_system.h)