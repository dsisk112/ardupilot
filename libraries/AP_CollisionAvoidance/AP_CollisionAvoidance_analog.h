/// -*- tab-width: 4; Mode: C++; c-basic-offset: 4; indent-tabs-mode: nil -*-

#ifndef __AP_COLLISIONAVOIDANCE_ANALOG_H__
#define __AP_COLLISIONAVOIDANCE_ANALOG_H__

#include "CollisionAvoidance.h"
#include "CollisionAvoidance_Backend.h"

class AP_CollisionAvoidance_analog : public AP_CollisionAvoidance_Backend
{
public:
    // constructor
    AP_CollisionAvoidance_analog(CollisionAvoidance &ranger, uint8_t instance, CollisionAvoidance::CollisionAvoidance_State &_state);

    // static detection function
    static bool detect(CollisionAvoidance &ranger, uint8_t instance);

    // update state
    void update(void);

private:
    // update raw voltage
    void update_voltage(void);

    AP_HAL::AnalogSource *source;
};
#endif // __AP_COLLISIONAVOIDANCE_ANALOG_H__

