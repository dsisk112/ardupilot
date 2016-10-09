/// -*- tab-width: 4; Mode: C++; c-basic-offset: 4; indent-tabs-mode: nil -*-

#include "Copter.h"

// distance in cm
#define CA_DISTANCE_FIRSTSTAGE      200
#define CA_DISTANCE_SECONDSTAGE     150
#define CA_DISTANCE_THIRDSTAGE      100
#define CA_DISTANCE_FOURTHSTAGE     50


/*
 * control_collisionavoid.pde - init and run calls for collisionavoid flight mode
 */

// collisionavoid_init - initialise sport controller
bool Copter::collisionavoid_init(bool ignore_checks)
{

    // initialize sensors
    ca.init();

    // run position hold init after our init
    poshold_init(ignore_checks);

    return true;
}

// collisionavoid_run - runs the collisionavoid controller
// should be called at 100hz or more
void Copter::collisionavoid_run()
{

    // Get distance reading from sonar
    ca.update();

    // exit immediately if sonar is disabled
    if (ca.status() != CollisionAvoidance::CollisionAvoidance_Good) {
        return;
    }

    adjustForward(ca.distance_cm(0));
    adjustBackward(ca.distance_cm(2));
    adjustRight(ca.distance_cm(1));
    adjustLeft(ca.distance_cm(3));

    // run position hold run method after we make our adjustments
    poshold_run();
}

void Copter::adjustForward(int16_t distance)
{
    if (distance <= CA_DISTANCE_FIRSTSTAGE && distance > CA_DISTANCE_SECONDSTAGE)
    {

    }
    else if (distance <= CA_DISTANCE_SECONDSTAGE && distance > CA_DISTANCE_THIRDSTAGE)
    {

    }
    else if (distance <= CA_DISTANCE_THIRDSTAGE && distance > CA_DISTANCE_FOURTHSTAGE)
    {

    }
    else if (distance <= CA_DISTANCE_FOURTHSTAGE)
    {

    }

}

void Copter::adjustBackward(int16_t distance)
{
    if (distance <= CA_DISTANCE_FIRSTSTAGE && distance > CA_DISTANCE_SECONDSTAGE)
    {

    }
    else if (distance <= CA_DISTANCE_SECONDSTAGE && distance > CA_DISTANCE_THIRDSTAGE)
    {

    }
    else if (distance <= CA_DISTANCE_THIRDSTAGE && distance > CA_DISTANCE_FOURTHSTAGE)
    {

    }
    else if (distance <= CA_DISTANCE_FOURTHSTAGE)
    {

    }

}

void Copter::adjustLeft(int16_t distance)
{
    if (distance <= CA_DISTANCE_FIRSTSTAGE && distance > CA_DISTANCE_SECONDSTAGE)
    {

    }
    else if (distance <= CA_DISTANCE_SECONDSTAGE && distance > CA_DISTANCE_THIRDSTAGE)
    {

    }
    else if (distance <= CA_DISTANCE_THIRDSTAGE && distance > CA_DISTANCE_FOURTHSTAGE)
    {

    }
    else if (distance <= CA_DISTANCE_FOURTHSTAGE)
    {

    }

}

void Copter::adjustRight(int16_t distance)
{
    if (distance <= CA_DISTANCE_FIRSTSTAGE && distance > CA_DISTANCE_SECONDSTAGE)
    {

    }
    else if (distance <= CA_DISTANCE_SECONDSTAGE && distance > CA_DISTANCE_THIRDSTAGE)
    {

    }
    else if (distance <= CA_DISTANCE_THIRDSTAGE && distance > CA_DISTANCE_FOURTHSTAGE)
    {

    }
    else if (distance <= CA_DISTANCE_FOURTHSTAGE)
    {

    }

}


