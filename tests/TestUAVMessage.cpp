#include <catch2/catch.hpp>

#include "aurora_msgs/UAVMessage.h"


TEST_CASE("TestUAVMsgConstruction", "Ensure all forms of construction work.")
{
    aurora::UAVMessage msg(true, false, 10, "TestSender");
    msg.setMessageId(1234);
    msg.setSenderId(42);
    msg.setReceiverId(43);

    REQUIRE(msg.getLights());
    REQUIRE(!msg.getCamera());
    REQUIRE(msg.getAction() == 10);
    REQUIRE(msg.getName() == "TestSender");
    REQUIRE(msg.getMessageId() == 1234);
    REQUIRE(msg.getSenderId() == 42);
    REQUIRE(msg.getReceiverId() == 43);
}

TEST_CASE("TestUAVMsgPayload", "Ensure payload setting and retrieval work.")
{
    aurora::UAVMessage msg(true, false, 10, "TestSender");
    REQUIRE(msg.getPayloadLength() == 18);
}

TEST_CASE("TestUAVMsgSendReceive", "Ensure message sending and receiving works.")
{
    aurora::UAVMessage msg(true, false, 10, "TestSender");
    msg.setMessageId(1234);
    msg.setSenderId(42);
    msg.setReceiverId(43);

    std::string sentMessage = msg.send();

    aurora::UAVMessage rcvdMsg;
    rcvdMsg.receive(sentMessage);

    REQUIRE(rcvdMsg.getLights());
    REQUIRE(!rcvdMsg.getCamera());
    REQUIRE(rcvdMsg.getAction() == 10);
    REQUIRE(rcvdMsg.getName() == "TestSender");
    REQUIRE(rcvdMsg.getMessageId() == 1234);
    REQUIRE(rcvdMsg.getSenderId() == 42);
    REQUIRE(rcvdMsg.getReceiverId() == 43);
}
