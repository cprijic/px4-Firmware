//Copyright 2015 Christopher Prijic

#include "Timer.h"
#include <unistd.h>
#include <stdlib.h>
#include <sched.h>
#include <errno.h>
#include <stdio.h>
#include <drivers/drv_hrt.h>
#include <nuttx/arch.h>
#include <systemlib/systemlib.h>
#include <pthread.h>
#include <poll.h>

#include <cstring>

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

void Timer::delay_microseconds_semaphore(uint16_t usec)
{
    sem_t wait_semaphore;
    struct hrt_call wait_call;
    sem_init(&wait_semaphore, 0, 0);
    memset(&wait_call, 0, sizeof(wait_call));
    hrt_call_after(&wait_call, usec, (hrt_callout)sem_post, &wait_semaphore);
    sem_wait(&wait_semaphore);
}

void Timer::delay_microseconds(uint16_t usec) {
    delay_microseconds_semaphore(usec);
}

void Timer::delay(uint64_t ms) {
    uint64_t start = micros64();

    while ((micros64() - start) / 1000 < ms) {
        delay_microseconds(1000);
    }
}
