// Copyright 2015 Christopher Prijic

#ifndef SRC_UAV_FORGE_MAIN_H_
#define SRC_UAV_FORGE_MAIN_H_

#include "maintest.h"

#define UAV_FORGE_MAIN() \
    extern "C" __EXPORT int UAV_Forge_px4_controller_main(int argc, char * const argv[]); \
    int UAV_Forge_px4_controller_main(int argc, char * const argv[]) { \
        MainTest test; \
        test.run(); \
        return OK; \
    }

#endif /* SRC_UAV_FORGE_MAINTEST_H_ */
