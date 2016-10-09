/*
 *  RangeFinder test code
 */

#include <AP_HAL/AP_HAL.h>
#include <AP_CollisionAvoidance/AP_CollisionAvoidance.h>

const AP_HAL::HAL& hal = AP_HAL::get_HAL();

static AP_SerialManager serial_manager;
static CollisionAvoidance sonar {serial_manager};

void setup()
{
    // print welcome message
    hal.console->println("CollisionAvoidance library test");

    // setup for analog pin 13
    AP_Param::set_object_value(&sonar, sonar.var_info, "_TYPE", CollisionAvoidance::CollisionAvoidance_TYPE_PLI2C);
    AP_Param::set_object_value(&sonar, sonar.var_info, "_PIN", -1);
    AP_Param::set_object_value(&sonar, sonar.var_info, "_SCALING", 1.0);

    // initialise sensor, delaying to make debug easier
    hal.scheduler->delay(2000);
    sonar.init();
    hal.console->printf("CollisionAvoidance: %d devices detected\n", sonar.num_sensors());
}

void loop()
{
    // Delay between reads
    hal.scheduler->delay(100);
    sonar.update();

    hal.console->printf("Primary: status %d distance_cm %d \n", (int)sonar.status(), sonar.distance_cm());
    hal.console->printf("All: device_0 type %d status %d distance_cm %d, device_1 type %d status %d distance_cm %d\n",
    (int)sonar._type[0], (int)sonar.status(0), sonar.distance_cm(0), (int)sonar._type[1], (int)sonar.status(1), sonar.distance_cm(1));

}
AP_HAL_MAIN();
