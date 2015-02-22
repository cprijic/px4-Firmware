// Copyright 2015 Christopher Prijic

#include "HAL.h"

extern const HAL& hal;

static RCOutput rcoutDriver;
static Timer    timer;

HAL::HAL() : rcout(&rcoutDriver), time(&timer) {}

static int main_loop() {
    extern void setup(void);
    extern void loop(void);

    hal.rcout->init();

    setup();
    loop();

    return OK;
}

void HAL::init() const {
    main_loop();
}
