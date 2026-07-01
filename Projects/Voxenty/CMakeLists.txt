add_executable(Voxenty)

target_link_libraries(Voxenty PRIVATE
  Entix::Runtime
  Entix::Drivers
  Entix::GameFramework)
