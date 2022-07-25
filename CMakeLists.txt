cmake_minimum_required(VERSION 3.16)

project(ds)

set(CMAKE_CXX_STANDARD 14)

set(OPTION "0" CACHE STRING "OPTION")

if(OPTION EQUAL 1)
    message("Constructing test files!")
    add_executable(TEST test/main.cpp)
else()
    include_directories(src)
    file(GLOB_RECURSE SOURCE_FILES "src/*.cpp")
    add_executable(ds ${SOURCE_FILES})
endif()