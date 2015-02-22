// Copyright 2015 Christopher Prijic

#ifndef SRC_UAV_FORGE_MAINTEST_H_
#define SRC_UAV_FORGE_MAINTEST_H_

#include "main.h"

#include <nuttx/config.h>
#include <stdio.h>
#include <errno.h>

class MainTest {
public:
    MainTest() {}
    virtual ~MainTest() {}

    int run();
};

#endif /* SRC_UAV_FORGE_MAINTEST_H_ */
