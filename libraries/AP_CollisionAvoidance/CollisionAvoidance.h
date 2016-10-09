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

#ifndef __COLLISIONAVOIDANCE_H__
#define __COLLISIONAVOIDANCE_H__

#include <AP_Common/AP_Common.h>
#include <AP_HAL/AP_HAL.h>
#include <AP_Param/AP_Param.h>
#include <AP_Math/AP_Math.h>
#include <AP_SerialManager/AP_SerialManager.h>

// Maximum number of range finder instances available on this platform
#define COLLISIONAVOIDANCE_MAX_INSTANCES 5
#define COLLISIONAVOIDANCE_GROUND_CLEARANCE_CM_DEFAULT 10
#define COLLISIONAVOIDANCE_PREARM_ALT_MAX_CM           200
#define COLLISIONAVOIDANCE_PREARM_REQUIRED_CHANGE_CM   50

class AP_CollisionAvoidance_Backend;

class CollisionAvoidance
{
public:
    friend class AP_CollisionAvoidance_Backend;

    CollisionAvoidance(AP_SerialManager &_serial_manager);

    // CollisionAvoidance driver types
    enum CollisionAvoidance_Type {
        CollisionAvoidance_TYPE_NONE   = 0,
        CollisionAvoidance_TYPE_ANALOG = 1,
        CollisionAvoidance_TYPE_MBI2C  = 2,
        CollisionAvoidance_TYPE_PLI2C  = 3,
        CollisionAvoidance_TYPE_PX4    = 4,
        CollisionAvoidance_TYPE_PX4_PWM= 5,
        CollisionAvoidance_TYPE_BBB_PRU= 6,
        CollisionAvoidance_TYPE_LWI2C  = 7,
        CollisionAvoidance_TYPE_LWSER  = 8
    };

    enum CollisionAvoidance_Function {
        FUNCTION_LINEAR    = 0,
        FUNCTION_INVERTED  = 1,
        FUNCTION_HYPERBOLA = 2
    };

    enum CollisionAvoidance_Status {
        CollisionAvoidance_NotConnected = 0,
        CollisionAvoidance_NoData,
        CollisionAvoidance_OutOfRangeLow,
        CollisionAvoidance_OutOfRangeHigh,
        CollisionAvoidance_Good
    };

    // The CollisionAvoidance_State structure is filled in by the backend driver
    struct CollisionAvoidance_State {
        uint8_t                instance;    // the instance number of this CollisionAvoidance
        uint16_t               distance_cm; // distance: in cm
        uint16_t               voltage_mv;  // voltage in millivolts,
                                            // if applicable, otherwise 0
        enum CollisionAvoidance_Status status;     // sensor status
        uint8_t                range_valid_count;   // number of consecutive valid readings (maxes out at 10)
        bool                   pre_arm_check;   // true if sensor has passed pre-arm checks
        uint16_t               pre_arm_distance_min;    // min distance captured during pre-arm checks
        uint16_t               pre_arm_distance_max;    // max distance captured during pre-arm checks
    };

    // parameters for each instance
    AP_Int8  _type[COLLISIONAVOIDANCE_MAX_INSTANCES];
    AP_Int8  _pin[COLLISIONAVOIDANCE_MAX_INSTANCES];
    AP_Int8  _ratiometric[COLLISIONAVOIDANCE_MAX_INSTANCES];
    AP_Int8  _stop_pin[COLLISIONAVOIDANCE_MAX_INSTANCES];
    AP_Int16 _settle_time_ms[COLLISIONAVOIDANCE_MAX_INSTANCES];
    AP_Float _scaling[COLLISIONAVOIDANCE_MAX_INSTANCES];
    AP_Float _offset[COLLISIONAVOIDANCE_MAX_INSTANCES];
    AP_Int8  _function[COLLISIONAVOIDANCE_MAX_INSTANCES];
    AP_Int16 _min_distance_cm[COLLISIONAVOIDANCE_MAX_INSTANCES];
    AP_Int16 _max_distance_cm[COLLISIONAVOIDANCE_MAX_INSTANCES];
    AP_Int8  _ground_clearance_cm[COLLISIONAVOIDANCE_MAX_INSTANCES];
    AP_Int8  _address[COLLISIONAVOIDANCE_MAX_INSTANCES];
    AP_Int16 _powersave_range;

    static const struct AP_Param::GroupInfo var_info[];

    // Return the number of range finder instances
    uint8_t num_sensors(void) const {
        return num_instances;
    }

    // detect and initialise any available rangefinders
    void init(void);

    // update state of all rangefinders. Should be called at around
    // 10Hz from main loop
    void update(void);

#define _CollisionAvoidance_STATE(instance) state[instance]

    uint16_t distance_cm(uint8_t instance) const {
        return (instance<num_instances? _CollisionAvoidance_STATE(instance).distance_cm : 0);
    }
    uint16_t distance_cm() const {
        return distance_cm(primary_instance);
    }

    uint16_t voltage_mv(uint8_t instance) const {
        return _CollisionAvoidance_STATE(instance).voltage_mv;
    }
    uint16_t voltage_mv() const {
        return voltage_mv(primary_instance);
    }

    int16_t max_distance_cm(uint8_t instance) const {
        return _max_distance_cm[instance];
    }
    int16_t max_distance_cm() const {
        return max_distance_cm(primary_instance);
    }

    int16_t min_distance_cm(uint8_t instance) const {
        return _min_distance_cm[instance];
    }
    int16_t min_distance_cm() const {
        return min_distance_cm(primary_instance);
    }
    int16_t ground_clearance_cm(uint8_t instance) const {
        return _ground_clearance_cm[instance];
    }
    int16_t ground_clearance_cm() const {
        return _ground_clearance_cm[primary_instance];
    }

    // query status
    CollisionAvoidance_Status status(uint8_t instance) const;
    CollisionAvoidance_Status status(void) const {
        return status(primary_instance);
    }

    // true if sensor is returning data
    bool has_data(uint8_t instance) const;
    bool has_data() const {
        return has_data(primary_instance);
    }

    // returns count of consecutive good readings
    uint8_t range_valid_count() const {
        return range_valid_count(primary_instance);
    }
    uint8_t range_valid_count(uint8_t instance) const {
        return _CollisionAvoidance_STATE(instance).range_valid_count;
    }

    /*
      set an externally estimated terrain height. Used to enable power
      saving (where available) at high altitudes.
     */
    void set_estimated_terrain_height(float height) {
        estimated_terrain_height = height;
    }

    /*
      returns true if pre-arm checks have passed for all range finders
      these checks involve the user lifting or rotating the vehicle so that sensor readings between
      the min and 2m can be captured
     */
    bool pre_arm_check() const;

private:
    CollisionAvoidance_State state[COLLISIONAVOIDANCE_MAX_INSTANCES];
    AP_CollisionAvoidance_Backend *drivers[COLLISIONAVOIDANCE_MAX_INSTANCES];
    uint8_t primary_instance:3;
    uint8_t num_instances:3;
    float estimated_terrain_height;
    AP_SerialManager &serial_manager;

    void detect_instance(uint8_t instance);
    void update_instance(uint8_t instance);

    void update_pre_arm_check(uint8_t instance);
};
#endif // __COLLISIONAVOIDANCE_H__
