find_package(Boost REQUIRED)

add_executable(testscom testscom.cpp)
target_link_libraries(testscom fsi)

add_executable(testmbox testmbox.cpp)
target_link_libraries(testmbox fsi)
