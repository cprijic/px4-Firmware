// Copyright 2015 Christopher Prijic

#ifndef SRC_UAV_FORGE_HAL_PX4_HAL_H_
#define SRC_UAV_FORGE_HAL_PX4_HAL_H_

#include "Timer.h"
#include "RCOutput.h"

class HAL {
private:
protected:
public:
    /**
     * The RC Output to the motors.
     */
    RCOutput* rcout;

    /**
     * The timer handle for the pixhawk -- grab system time,
     * or delay your progress.
     */
    Timer*    time;

            HAL();
    virtual ~HAL() {}

    /**
     * Initializes the hardware abstraction layer;
     * Prepares for use.
     */
    void    init() const;
};

#endif /* SRC_UAV_FORGE_HAL_PX4_HAL_H_ */
