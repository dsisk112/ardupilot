// -*- tab-width: 4; Mode: C++; c-basic-offset: 4; indent-tabs-mode: nil -*-
/*
   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef AP_CollisionAvoidance_PX4_PWM_H
#define AP_CollisionAvoidance_PX4_PWM_H

#include "CollisionAvoidance.h"
#include "CollisionAvoidance_Backend.h"

class AP_CollisionAvoidance_PX4_PWM : public AP_CollisionAvoidance_Backend
{
public:
    // constructor
    AP_CollisionAvoidance_PX4_PWM(CollisionAvoidance &ranger, uint8_t instance, CollisionAvoidance::CollisionAvoidance_State &_state);

    // destructor
    ~AP_CollisionAvoidance_PX4_PWM(void);

    // static detection function
    static bool detect(CollisionAvoidance &ranger, uint8_t instance);

    // update state
    void update(void);

private:
    int _fd;
    uint64_t _last_timestamp;
    uint64_t _last_pulse_time_ms;
    uint32_t _disable_time_ms;
    uint32_t _good_sample_count;
    float _last_sample_distance_cm;
};

#endif // AP_CollisionAvoidance_PX4_PWM_H
