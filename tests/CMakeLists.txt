find_package(Catch2 REQUIRED)

add_executable(test_msgs TestMessage.cpp TestUAVMessage.cpp)
target_link_libraries(test_msgs PRIVATE
        aurora_msgs
        Catch2::Catch2WithMain
        )
add_test(NAME TestMsgs COMMAND test_msgs)
