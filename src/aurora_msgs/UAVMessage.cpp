#include "aurora_msgs/UAVMessage.h"

#include <cstring>


namespace aurora
{

UAVMessage::UAVMessage(bool lights, bool camera, uint8_t action, const std::string& name)
{
    setLights(lights);
    setCamera(camera);
    setAction(action);
    setName(name);
}

std::string UAVMessage::send()
{
    return Message::send();
}

void UAVMessage::receive(const std::string &message)
{
    Message::receive(message);

    std::string payload = getPayload();
    setLights(static_cast<uint8_t>(payload[0]) & 0x80);
    setCamera(static_cast<uint8_t>(payload[0]) & 0x40);
    setAction(static_cast<uint8_t>(payload[0]));
    setName(payload.substr(1));
}

bool UAVMessage::getLights()
{
    return m_lights;
}

void UAVMessage::setLights(bool lights)
{
    m_lights = lights;
    setPayload();
}

bool UAVMessage::getCamera()
{
    return m_camera;
}

void UAVMessage::setCamera(bool camera)
{
    m_camera = camera;
    setPayload();
}

uint8_t UAVMessage::getAction()
{
    return m_action;
}

void UAVMessage::setAction(const uint8_t& action)
{
    m_action = action;
    setPayload();
}

std::string UAVMessage::getName()
{
    return m_name;
}

void UAVMessage::setName(const std::string& name)
{
    name.copy(m_name, 17);
    setPayload();
}

void UAVMessage::setPayload()
{
    std::string payload;
    payload.resize(18);  // 8 bits for lights, camera, action and 64 for name.
    payload[0] = (m_lights << 7) | (m_camera << 6) | m_action;  // MSB will be lights, second is camera, rest is action.
    std::memcpy(&payload[1], &m_name[0], 16);

    Message::setPayload(payload);
}

}
