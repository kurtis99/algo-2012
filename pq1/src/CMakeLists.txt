set(MAIN_SOURCES
  main.c
)

add_definitions(-DCURRENT_TEST_DIR="${CMAKE_CURRENT_SOURCE_DIR}/")
add_executable(pq1 ${HEADERS} ${MAIN_SOURCES})
add_executable(pq1_test ${HEADERS} tests.c)
