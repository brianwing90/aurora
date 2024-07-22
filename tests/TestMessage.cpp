#include <catch2/catch.hpp>

#include "aurora_msgs/Message.h"


TEST_CASE("TestMsgConstruction", "Ensure all forms of construction work.")
{
    aurora::Message msg(1234, 42, 43);
    REQUIRE(msg.getMessageId() == 1234);
    REQUIRE(msg.getSenderId() == 42);
    REQUIRE(msg.getReceiverId() == 43);
}

TEST_CASE("TestMsgPayload", "Ensure payload setting and retrieval work.")
{
    aurora::Message msg(1234, 42, 43);
    msg.setPayload("ABCD");

    REQUIRE(msg.getPayloadLength() == 4);
    REQUIRE(msg.getPayload() == "ABCD");
}

TEST_CASE("TestMsgSendReceive", "Ensure message sending and receiving works.")
{
    aurora::Message msg(1234, 42, 43);
    msg.setPayload("ABCD");
    std::string sentMessage = msg.send();

    aurora::Message rcvdMsg;
    rcvdMsg.receive(sentMessage);

    REQUIRE(rcvdMsg.getMessageId() == 1234);
    REQUIRE(rcvdMsg.getSenderId() == 42);
    REQUIRE(rcvdMsg.getReceiverId() == 43);
    REQUIRE(rcvdMsg.getPayloadLength() == 4);
    REQUIRE(rcvdMsg.getPayload() == "ABCD");
}
