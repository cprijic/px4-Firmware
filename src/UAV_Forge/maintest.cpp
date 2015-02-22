// Copyright 2015 Christopher Prijic

#include "main.h"
#include "HAL_PX4/HAL.h"
#include "maintest.h"

#include <nuttx/config.h>
#include <stdio.h>
#include <errno.h>

const HAL& hal = HAL();

int setup() {
    printf("Hello, Sky!\n");
    return OK;
}

void loop() {
    printf("Loop...\n");
}

UAV_FORGE_MAIN();
