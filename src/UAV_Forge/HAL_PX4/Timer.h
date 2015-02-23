// Copyright 2015 Christopher Prijic

#ifndef SRC_UAV_FORGE_HAL_PX4_TIMER_H_
#define SRC_UAV_FORGE_HAL_PX4_TIMER_H_

#include <sys/types.h>

class Timer {
private:
protected:
public:
             Timer() {}
    virtual  ~Timer() {}
    uint32_t millis();
    uint32_t micros();
    uint64_t millis64();
    uint64_t micros64();
};

#endif /* SRC_UAV_FORGE_HAL_PX4_TIMER_H_ */
