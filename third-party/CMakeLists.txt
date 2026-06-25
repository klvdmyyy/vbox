add_library(glad glad/src/glad.c)

set_target_properties(glad PROPERTIES POSITION_INDEPENDENT_CODE ON)

target_include_directories(glad PUBLIC glad/include)