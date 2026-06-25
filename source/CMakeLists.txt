add_executable(vbox)

target_include_directories(vbox PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(vbox PRIVATE entixruntime)

file(
  GLOB_RECURSE
  VBOX_SOURCES
  ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp
)

target_sources(vbox PRIVATE ${VBOX_SOURCES})