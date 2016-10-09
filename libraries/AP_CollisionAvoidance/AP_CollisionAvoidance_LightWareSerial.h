// -*- tab-width: 4; Mode: C++; c-basic-offset: 4; indent-tabs-mode: nil -*-

#ifndef __AP_COLLISIONAVOIDANCE_LIGHTWARESERIAL_H__
#define __AP_COLLISIONAVOIDANCE_LIGHTWARESERIAL_H__

#include "CollisionAvoidance.h"
#include "CollisionAvoidance_Backend.h"

class AP_CollisionAvoidance_LightWareSerial : public AP_CollisionAvoidance_Backend
{

public:
    // constructor
    AP_CollisionAvoidance_LightWareSerial(CollisionAvoidance &ranger, uint8_t instance, CollisionAvoidance::CollisionAvoidance_State &_state,
                                   AP_SerialManager &serial_manager);

    // static detection function
    static bool detect(CollisionAvoidance &ranger, uint8_t instance, AP_SerialManager &serial_manager);

    // update state
    void update(void);

private:
    // get a reading
    bool get_reading(uint16_t &reading_cm);

    AP_HAL::UARTDriver *uart = nullptr;
    uint32_t last_reading_ms = 0;
    char linebuf[10];
    uint8_t linebuf_len = 0;
};
#endif  // __AP_COLLISIONAVOIDANCE_LIGHTWARESERIAL_H__
