project (pq1)

cmake_minimum_required(VERSION 2.8 FATAL_ERROR)

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/../cmake")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra")
set(CMAKE_C_FLAGS_RELEASE "-DNDEBUG -Os -Werror")
set(CMAKE_C_FLAGS_DEBUG "-DDEBUG -O0 -ggdb")

###############################################################################
# Subdirectories
add_subdirectory(src)
add_subdirectory(tests)

###############################################################################
# Unit tests
enable_testing()
add_test(NAME check_pq1 COMMAND pq1)

