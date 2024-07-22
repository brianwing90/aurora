add_subdirectory(aurora_msgs)

add_executable(msg_test main.cpp)
target_link_libraries(msg_test PRIVATE aurora_msgs)
