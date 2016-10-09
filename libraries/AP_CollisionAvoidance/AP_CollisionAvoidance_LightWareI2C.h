// -*- tab-width: 4; Mode: C++; c-basic-offset: 4; indent-tabs-mode: nil -*-

#ifndef __AP_COLLISIONAVOIDANCE_LIGHTWARELRF_H__
#define __AP_COLLISIONAVOIDANCE_LIGHTWARELRF_H__

#include "CollisionAvoidance.h"
#include "CollisionAvoidance_Backend.h"

class AP_CollisionAvoidance_LightWareI2C : public AP_CollisionAvoidance_Backend
{

public:
    // constructor
    AP_CollisionAvoidance_LightWareI2C(CollisionAvoidance &ranger, uint8_t instance, CollisionAvoidance::CollisionAvoidance_State &_state);

    // static detection function
    static bool detect(CollisionAvoidance &ranger, uint8_t instance);

    // update state
    void update(void);

private:
    // get a reading
    bool get_reading(uint16_t &reading_cm);
};
#endif  // __AP_COLLISIONAVOIDANCE_LIGHTWARELRF_H__
