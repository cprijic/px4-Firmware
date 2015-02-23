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

    for (int i = 0; i < 100000; i++) {
        sensor->update();
        printf("accel: %8.4f, %8.4f, %8.4f\n", (double)sensor->accel.x, (double)sensor->accel.y, (double)sensor->accel.z);
        printf("gyro:  %8.4f, %8.4f, %8.4f\n", (double)sensor->gyro.x, (double)sensor->gyro.y, (double)sensor->gyro.z);
    }

    return OK;
}

void loop() {
    printf("Loop...\n");
}

UAV_FORGE_MAIN();
