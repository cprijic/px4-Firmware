//Copyright 2015 Christopher Prijic

#include "Timer.h"
#include <drivers/drv_hrt.h>

uint32_t Timer::millis() {
    return millis64() & 0xFFFFFFFF;
}

uint32_t Timer::micros() {
    return micros64() & 0xFFFFFFFF;
}

uint64_t Timer::millis64() {
    return micros64() / 1000;
}

uint64_t Timer::micros64() {
    return hrt_absolute_time();
}
