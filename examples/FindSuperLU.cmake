set(SUPERLU_INCLUDE_SEARCH_PATH
  /usr/include
  /usr/local/include/superlu)

set(SUPERLU_LIBRARY_SEARCH_PATH
  /usr/lib/x86_64-linux-gnu
  /usr/local/lib/superlu
  /usr/lib)

find_path(SUPERLU_SUPERLU_H slu_ddefs.h ${SUPERLU_INCLUDE_SEARCH_PATH})

find_library(SUPERLU_SUPERLU NAMES superlu PATHS ${SUPERLU_LIBRARY_SEARCH_PATH})

set(SUPERLU_FOUND 1)

foreach(var SUPERLU_SUPERLU_H SUPERLU_SUPERLU)
    if(NOT ${var})
        set(SUPERLU_FOUND 0)
    endif()
endforeach()

message(STATUS "SUPERLU_FOUND = ${SUPERLU_FOUND}")

if(SUPERLU_FOUND)
    set(SUPERLU_INCLUDE ${SUPERLU_SUPERLU_H})
    set(SUPERLU_LIBS    ${SUPERLU_SUPERLU})
endif()

message(STATUS "SUPERLU_INCLUDE_DIRS = ${SUPERLU_INCLUDE_DIRS}")
message(STATUS "SUPERLU_LIBRARIES = ${SUPERLU_LIBRARIES}")

if(SUPERLU_FOUND)
    message(STATUS "SuperLU: Found Successfully!!!")
endif()
