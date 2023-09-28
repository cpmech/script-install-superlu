cmake_minimum_required(VERSION 3.22)
project(Project)

add_definitions(-g -Wall)

include(FindSuperLU.cmake)
if(SUPERLU_FOUND)
    include_directories(${SUPERLU_INCLUDE})
else()
    message(FATAL_ERROR "cannot compile the code without SUPERLU")
endif()

set(EXAMPLES
    example01
    example02
    example03
)

foreach(example ${EXAMPLES})
    add_executable(${example} ${example}.cpp)
    target_link_libraries(${example} PUBLIC ${SUPERLU_LIBS})
endforeach()

