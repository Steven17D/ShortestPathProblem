cmake_minimum_required(VERSION 3.7)
project(ShortestPathProblem)

set(CMAKE_C_STANDARD 90)

# gcc main1.c -IC:\MinGW\include -LC:\MinGW\lib -w -Wl,-subsystem,windows -lmingw32 -lSDL2main -lSDL2 -o main.exe
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -w -Wl,-subsystem,windows")

set(CMAKE_CXX_FLAGS_RELEASE "-O3")

set(SOURCE_FILES
        src/main.c
        src/properties.h
        src/stack.h
        src/circle.h src/circle.c
        src/file_utils.c src/file_utils.h
        src/graph.h src/graph.c
        src/depth_first_search.h
        src/String.c src/String.h)

add_executable(ShortestPathProblem ${SOURCE_FILES})
set_target_properties(ShortestPathProblem
        PROPERTIES CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -w -Wl,-subsystem,windows")
target_link_libraries(ShortestPathProblem mingw32 SDL2main SDL2)

# Tests
set(STACK_TEST_FILES
        src/tests/stack_test.c
        src/String.h src/String.c
        src/stack.h)

add_executable(StackTest ${STACK_TEST_FILES})

set(GRAPH_TEST_FILES
        src/tests/graph_test.c
        src/String.h src/String.c
        src/graph.h src/graph.c)

add_executable(GraphTest ${GRAPH_TEST_FILES})

set(STRING_TEST_FILES
        src/tests/string_test.c
        src/String.h src/String.c)

add_executable(StringTest ${STRING_TEST_FILES})

set(DEPTH_FIRST_SEARCH_TEST_FILES
        src/tests/depth_first_search_test.c
        src/String.h src/String.c
        src/graph.h src/graph.c
        src/depth_first_search.h)

add_executable(DepthFirstSearchTest ${DEPTH_FIRST_SEARCH_TEST_FILES})

