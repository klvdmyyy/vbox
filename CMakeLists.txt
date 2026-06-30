set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/cmake)
cmake_minimum_required(VERSION 3.31.6)

project(VBox)

set(CMAKE_CXX_STANDARD 26)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin)

if (MINGW AND (CMAKE_CXX_COMPILER_ID STREQUAL GNU OR CMAKE_CXX_COMPILER_ID STREQUAL Clang))
  link_libraries(stdc++exp) # std:: print, println, ...
endif()

file(
  GLOB_RECURSE
  CL_FILES
  *.[hc]
  *.[hc]pp
  *.vert
  *.frag
)

include(etags)
etags_generate(${CL_FILES})

file(
  GLOB_RECURSE
  VBOX_CL_FILES
  *.[hc]
  *.[hc]pp
  *.vert
  *.frag
)

list(FILTER VBOX_CL_FILES EXCLUDE REGEX ${CMAKE_CURRENT_SOURCE_DIR}/cmake)
list(FILTER VBOX_CL_FILES EXCLUDE REGEX ${CMAKE_CURRENT_SOURCE_DIR}/build)
list(FILTER VBOX_CL_FILES EXCLUDE REGEX ${CMAKE_CURRENT_SOURCE_DIR}/out)
list(FILTER VBOX_CL_FILES EXCLUDE REGEX ${CMAKE_CURRENT_SOURCE_DIR}/third-party)

include(formatting)
clang_format(format ${VBOX_CL_FILES})

add_subdirectory(third-party)

##########################################
################ Runtime ##################

add_subdirectory(runtime)

##########################################
################# VBox ###################

add_subdirectory(source)

##########################################
################ Tests ###################

# GoogleTest requires at least C++17

include(FetchContent)

FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest
    GIT_TAG v1.17.0
    OVERRIDE_FIND_PACKAGE
)

# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

FetchContent_Declare(
  benchmark
  GIT_REPOSITORY https://github.com/google/benchmark
  GIT_TAG v1.9.5
  OVERRIDE_FIND_PACKAGE
)

set(BENCHMARK_ENABLE_TESTING OFF CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(benchmark)

enable_testing()
add_subdirectory(runtime/tests)
