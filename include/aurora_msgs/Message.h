#ifndef AURORA_MSGS_MESSAGE_H
#define AURORA_MSGS_MESSAGE_H

#include <string>
#include <vector>

namespace aurora
{

/**
 * A base class for future messages to inherit from.
 *
 * @todo: Doesn't this make more sense as a template for a generator like protobuf?
 */
class Message
{
public:

    /**
     * Creates and returns a new Message.
     *
     * @param[in] messageId The identifier for this Message type.
     * @param[in] senderId The unique identifier of the sender of this Message.
     * @param[in] receiverId The unique identifier of the receiver of this Message.
     * @param[in] payloadLength The size of the payload, either expected or currently provided in the payload parameter.
     * @param[in] payload
     */
    explicit Message(uint16_t messageId = 0, uint8_t senderId = 0, uint8_t receiverId = 0, uint32_t payloadLength = 0, const std::string& payload = "");
    ~Message() = default;

    /**
     * Sends and returns the current Message as a string.
     *
     * @return The string representation of this Message.
     */
    virtual std::string send();

    /**
     * Populates this Message with the contents in the given string.
     *
     * @param[in] message The string to fill out this Message with.
     */
    virtual void receive(const std::string& message);

    /**
     * Returns this Message's ID.
     *
     * @return The uint16 message ID.
     */
    uint16_t getMessageId();

    /**
     * Updates this Message's ID to the given ID.
     *
     * @param[in] messageId The new ID of the Message.
     */
    void setMessageId(const uint16_t& messageId);

    /**
     * Returns this Message sender's ID.
     *
     * @return The uint8 sender ID.
     */
    uint8_t getSenderId();

    /**
     * Updates the sender ID to the given ID.
     *
     * @param[in] senderId The new ID of the sending module.
     */
    void setSenderId(const uint8_t& senderId);

    /**
     * Returns this Message receiver's ID.
     *
     * @return The uint8 receiver ID.
     */
    uint8_t getReceiverId();

    /**
     * Updates the receiver ID to the given ID.
     *
     * @param[in] receiverId The new ID of the intended receiver.
     */
    void setReceiverId(const uint8_t& receiverId);

    /**
     * Returns the size of this Message's current payload.
     *
     * @return The uint32 payload size.
     */
    uint32_t getPayloadLength();

    /**
     * Sets the size of the current payload.
     *
     * @param[in] payloadLength The new size for the current payload.
     */
    void setPayloadLength(const uint32_t& payloadLength);

    /**
     * Returns this Message's current payload as a string.
     *
     * @return The current payload.
     */
    std::string getPayload();

    /**
     * Sets the current payload to the given payload string. Also updates the payload length to match the new payload.
     *
     * @param[in] payload The new payload for this Message.
     */
    void setPayload(const std::string& payload);

private:
    uint16_t m_messageId;
    uint8_t m_senderId;
    uint8_t m_receiverId;
    uint32_t m_payloadLength;
    std::vector<uint8_t> m_payload;
};

}

#endif //AURORA_MSGS_MESSAGE_H
