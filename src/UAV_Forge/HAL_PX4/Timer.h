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

    /**
     * The current time, in milliseconds.
     *
     * @return the time, in milliseconds.
     */
    uint32_t millis();

    /**
     * The current time, in microseconds.
     *
     * @return the time, in microseconds.
     */
    uint32_t micros();

    /**
     * The current time, in milliseconds, more accurately.
     *
     * @return the time, in milliseconds.
     */
    uint64_t millis64();

    /**
     * The current time, in microseconds, more accurately.
     *
     * @return the time, in microseconds.
     */
    uint64_t micros64();
};

#endif /* SRC_UAV_FORGE_HAL_PX4_TIMER_H_ */
