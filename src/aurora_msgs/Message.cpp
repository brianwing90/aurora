#include "aurora_msgs/Message.h"

#include <cstring>


namespace aurora
{

Message::Message(uint16_t messageId, uint8_t senderId, uint8_t receiverId, uint32_t payloadLength, const std::string& payload)
: m_messageId(messageId), m_senderId(senderId), m_receiverId(receiverId), m_payloadLength(payloadLength)
{
    setPayload(payload);
}

uint16_t Message::getMessageId()
{
    return m_messageId;
}

void Message::setMessageId(const uint16_t& messageId)
{
    m_messageId = messageId;
}

uint8_t Message::getSenderId()
{
    return m_senderId;
}

void Message::setSenderId(const uint8_t& senderId)
{
    m_senderId = senderId;
}

uint8_t Message::getReceiverId()
{
    return m_receiverId;
}

void Message::setReceiverId(const uint8_t& receiverId)
{
    m_receiverId = receiverId;
}

uint32_t Message::getPayloadLength()
{
    return m_payloadLength;
}

void Message::setPayloadLength(const uint32_t& payloadLength)
{
    m_payloadLength = payloadLength;
    m_payload.resize(m_payloadLength);
}

std::string Message::getPayload()
{
    std::string payload;

    for(char c : m_payload)
        payload += c;

    return payload;
}

void Message::setPayload(const std::string& payload)
{
    setPayloadLength(payload.size());
    std::memcpy(m_payload.data(), &payload[0], m_payloadLength);
}

std::string Message::send()
{
    std::string message;
    message.resize(8 + m_payloadLength);  // 8 chars (64 bits) for metadata.

    // Message ID (2 bytes).
    message[0] = (m_messageId >> 8) & 0xFF;
    message[1] = m_messageId & 0xFF;

    // Sender ID (1 byte).
    message[2] = m_senderId;

    // Receiver ID (1 byte).
    message[3] = m_receiverId;

    // Payload size (4 bytes).
    message[4] = (m_payloadLength >> 24) & 0xFF;
    message[5] = (m_payloadLength >> 16) & 0xFF;
    message[6] = (m_payloadLength >> 8) & 0xFF;
    message[7] = m_payloadLength & 0xFF;

    // Payload of variable size.
    std::memcpy(&message[8], m_payload.data(), m_payloadLength);

    return message;
}

void Message::receive(const std::string &message)
{
    m_messageId = (static_cast<uint8_t>(message[0]) << 8) | static_cast<uint8_t>(message[1]);
    m_senderId = static_cast<uint8_t>(message[2]);
    m_receiverId = static_cast<uint8_t>(message[3]);
    m_payloadLength = (static_cast<uint8_t>(message[4]) << 24) | (static_cast<uint8_t>(message[5]) << 16) |
            (static_cast<uint8_t>(message[6]) << 8) | static_cast<uint8_t>(message[7]);

    setPayload(message.substr(8));
}

}
