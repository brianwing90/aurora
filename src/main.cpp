#include <iostream>

#include "aurora_msgs/Message.h"
#include "aurora_msgs/UAVMessage.h"


int main() {
    using namespace aurora;

    /**
     * Generic message.
     */
    Message message(0x1234, 0x56, 0x78, 4);
    message.setPayload("ABCD");

    // Send the message.
    std::string sentMessage = message.send();
    std::cout << "Sent Message: ";
    for (unsigned char c : sentMessage) {
        printf("%02X ", c);
    }
    std::cout << std::endl;

    // Receive the message.
    Message receivedMessage;
    receivedMessage.receive(sentMessage);
    std::cout << "Received Message ID: " << std::hex << receivedMessage.getMessageId() << std::endl;
    std::cout << "Received Sender ID: " << std::hex << static_cast<int>(receivedMessage.getSenderId()) << std::endl;
    std::cout << "Received Receiver ID: " << std::hex << static_cast<int>(receivedMessage.getReceiverId()) << std::endl;
    std::cout << "Received Payload Length: " << std::dec << receivedMessage.getPayloadLength() << std::endl;

    std::string receivedPayload = receivedMessage.getPayload();
    std::cout << "Received Payload: " << receivedPayload << std::endl;

    /**
     * UAVMessage
     */
    UAVMessage uavMessage(true, false, 0x2A, "AuroraUAVMessage");
    uavMessage.setMessageId(0x1234);
    uavMessage.setSenderId(0x56);
    uavMessage.setReceiverId(0x78);

    // Send the message.
    std::string sentUAVMessage = uavMessage.send();
    std::cout << "Sent Message: ";
    for (unsigned char c : sentUAVMessage) {
        printf("%02X ", c);
    }
    std::cout << std::endl;

    // Receive the message.
    UAVMessage receivedUAVMessage;
    receivedUAVMessage.receive(sentUAVMessage);
    std::cout << "Received Message ID: " << std::hex << receivedUAVMessage.getMessageId() << std::endl;
    std::cout << "Received Sender ID: " << std::hex << static_cast<int>(receivedUAVMessage.getSenderId()) << std::endl;
    std::cout << "Received Receiver ID: " << std::hex << static_cast<int>(receivedUAVMessage.getReceiverId()) << std::endl;
    std::cout << "Received Payload Length: " << std::dec << receivedUAVMessage.getPayloadLength() << std::endl;

    std::cout << "Received Lights: " << std::boolalpha << receivedUAVMessage.getLights() << std::endl;
    std::cout << "Received Camera: " << std::boolalpha << receivedUAVMessage.getCamera() << std::endl;
//    std::cout << "Received Action: " << std::hex << static_cast<int>(receivedUAVMessage.getAction()) << std::endl;
    printf("Received Action: %02X\n", static_cast<int>(receivedUAVMessage.getAction()));
    std::string receivedUAVName = receivedUAVMessage.getName();
    std::cout << "Received Name: " << receivedUAVName << std::endl;

    return 0;
}