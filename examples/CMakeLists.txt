cmake_minimum_required(VERSION 3.22)
project(Project)

add_definitions(-g -Wall)

include(FindSuperLU.cmake)
if(SUPERLU_FOUND)
    include_directories(${SUPERLU_INCLUDE})
else()
    message(FATAL_ERROR "cannot compile the code without SUPERLU")
endif()

add_executable(example01 example01.cpp)
target_link_libraries(example01 PUBLIC ${SUPERLU_LIBS})
