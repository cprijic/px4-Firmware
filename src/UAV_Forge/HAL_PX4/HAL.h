// Copyright 2015 Christopher Prijic

#ifndef SRC_UAV_FORGE_HAL_PX4_HAL_H_
#define SRC_UAV_FORGE_HAL_PX4_HAL_H_

#include "Timer.h"
#include "RCOutput.h"

class HAL {
private:
protected:
public:
    RCOutput* rcout;
    Timer*    time;

            HAL();
    virtual ~HAL() {}

    void    init() const;
};

#endif /* SRC_UAV_FORGE_HAL_PX4_HAL_H_ */
