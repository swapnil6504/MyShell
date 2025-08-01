cmake_minimum_required(VERSION 3.10)
project(MyShell)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add executable
add_executable(myshell myshell.cpp)

# Link Windows libraries
target_link_libraries(myshell shell32)
