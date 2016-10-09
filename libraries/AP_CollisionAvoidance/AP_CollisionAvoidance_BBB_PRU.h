#ifndef __AP_COLLISIONAVOIDANCE_PRU_H__
#define __AP_COLLISIONAVOIDANCE_PRU_H__

#include "CollisionAvoidance.h"
#include "CollisionAvoidance_Backend.h"


#define PRU0_CTRL_BASE 0x4a322000

#define PRU0_IRAM_BASE 0x4a334000
#define PRU0_IRAM_SIZE 0x2000

#define PRU0_DRAM_BASE 0x4a300000
#define PRU0_DRAM_SIZE 0x2000

struct range {
        uint32_t distance;
	uint32_t status;
};

class AP_CollisionAvoidance_BBB_PRU : public AP_CollisionAvoidance_Backend
{
public:
    // constructor
    AP_CollisionAvoidance_BBB_PRU(CollisionAvoidance &ranger, uint8_t instance, CollisionAvoidance::CollisionAvoidance_State &_state);

    // static detection function
    static bool detect(CollisionAvoidance &ranger, uint8_t instance);

    // update state
    void update(void);

private:

};
#endif  // __AP_COLLISIONAVOIDANCE_PRU_H__
