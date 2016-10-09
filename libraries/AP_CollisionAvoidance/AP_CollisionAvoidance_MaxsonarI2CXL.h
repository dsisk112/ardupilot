// -*- tab-width: 4; Mode: C++; c-basic-offset: 4; indent-tabs-mode: nil -*-

#ifndef __AP_COLLISIONAVOIDANCE_MAXSONARI2CXL_H__
#define __AP_COLLISIONAVOIDANCE_MAXSONARI2CXL_H__

#include "CollisionAvoidance.h"
#include "CollisionAvoidance_Backend.h"

#define AP_COLLISION_AVOIDANCE_MAXSONARI2CXL_DEFAULT_ADDR   0x71

#define AP_COLLISIONAVOIDANCE_MAXSONARI2CXL                4
#define AP_COLLISION_AVOIDANCE_MAXSONARI2CXL_SCALER        1.0
#define AP_COLLISION_AVOIDANCE_MAXSONARI2CXL_MIN_DISTANCE  20
#define AP_COLLISION_AVOIDANCE_MAXSONARI2CXL_MAX_DISTANCE  765

#define AP_COLLISION_AVOIDANCE_MAXSONARI2CXL_COMMAND_TAKE_RANGE_READING 0x51

class AP_CollisionAvoidance_MaxsonarI2CXL : public AP_CollisionAvoidance_Backend
{
public:
    // constructor
    AP_CollisionAvoidance_MaxsonarI2CXL(CollisionAvoidance &ranger, uint8_t instance, CollisionAvoidance::CollisionAvoidance_State &_state);

    // static detection function
    static bool detect(CollisionAvoidance &ranger, uint8_t instance);

    // update state
    void update(void);

private:
    // start a reading
    static bool start_reading(void);
    static bool get_reading(uint16_t &reading_cm);
};
#endif  // __AP_COLLISIONAVOIDANCE_MAXSONARI2CXL_H__
