cmake_minimum_required(VERSION 3.16)

project(ds)

set(CMAKE_CXX_STANDARD 14)

file(GLOB_RECURSE SOURCE_FILES "src/*.cpp")
add_executable(ds ${SOURCE_FILES})