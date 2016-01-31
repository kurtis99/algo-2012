include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../src)

find_package(Check REQUIRED)

include_directories(${CHECK_INCLUDE_DIRS})

set(TEST_SOURCES
  check_pq.c
)

add_executable(check_pq1 ${TEST_SOURCES})
target_link_libraries(check_pq1 ${CHECK_LIBRARIES} m rt pthread)

