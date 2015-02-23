// Copyright 2015 Christopher Prijic

#include "maintest.h"
#include "main.h"
#include "HAL_PX4/HAL.h"
#include "HAL_PX4/InertialSensor.h"

#include <nuttx/config.h>
#include <stdio.h>
#include <errno.h>

const HAL& hal = HAL();

int setup() {
    printf("Hello, Sky!\n");

    InertialSensor* sensor = InertialSensor::create();
    uint8_t num_accel = sensor->get_num_accel();
    uint8_t num_gyros = sensor->get_num_gyros();

    printf("#accels: %u\n", num_accel);
    printf("#gyros: %u\n", num_gyros);

    return OK;
}

void loop() {
    printf("Loop...\n");
}

UAV_FORGE_MAIN();
