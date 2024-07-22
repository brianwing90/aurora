#ifndef AURORA_MSGS_UAVMESSAGE_H
#define AURORA_MSGS_UAVMESSAGE_H

#include "Message.h"


namespace aurora
{

/**
 * A message intended for a UAV that participates in the theatre.
 */
class UAVMessage : public Message
{
public:

    /**
     * Creates and returns a new UAVMessage.
     *
     * @param[in] lights Whether or not the lights are on.
     * @param[in] camera Whether or not the camera is rolling.
     * @param[in] action The scene ID for the current shoot.
     * @param[in] name The string name of the actor on this UAV.
     */
    explicit UAVMessage(bool lights = false, bool camera = false, uint8_t action = 0, const std::string& name = "");

    std::string send() override;
    void receive(const std::string& message) override;

    /**
     * Returns the current state of the lights on this UAV.
     *
     * @return true if the lights are on, false otherwise.
     */
    bool getLights();

    /**
     * Sets the current state of the lights to the given state.
     *
     * @param[in] action If true, the lights are on; false otherwise.
     */
    void setLights(bool lights);

    /**
     * Returns the current state of the camera on this UAV.
     *
     * @return true if the camera is rolling, false otherwise.
     */
    bool getCamera();

    /**
     * Sets the current state of the cameras to the given state.
     *
     * @param[in] action If true, the cameras are rolling; false otherwise.
     */
    void setCamera(bool camera);

    /**
     * Returns the current state of the action on this UAV.
     *
     * @return If > 0, this is the current scene being filmed.
     */
    uint8_t getAction();

    /**
     * Sets the current scene ID on this UAV to the given uint8.
     *
     * @param[in] action The scene ID being filmed.
     */
    void setAction(const uint8_t& action);

    /**
     * Returns the name of the actor on this UAV.
     *
     * @return A string name of the actor on this UAV.
     */
    std::string getName();

    /**
     * Sets the current name of the actor on this UAV to the given string.
     *
     * @param[in] name String name of the actor on this UAV.
     */
    void setName(const std::string& name);

private:
    bool m_lights;
    bool m_camera;
    unsigned int m_action : 6;  // Limited to 6 bits for an action.
    char m_name[16];  // Limited to 64 bits for a name.

    /**
     * Updates the base class with the current payload information.
     */
    void setPayload();
};

}

#endif //AURORA_MSGS_UAVMESSAGE_H
