cmake_minimum_required(VERSION 3.28)
project(trab_ies)

find_package(wxWidgets REQUIRED COMPONENTS  core base)
include(${wxWidgets_USE_FILE})
set(CMAKE_CXX_STANDARD 17)

add_executable(trab_ies main.cpp)
target_link_libraries(trab_ies ${wxWidgets_LIBRARIES})
