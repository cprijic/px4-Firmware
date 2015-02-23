// Copyright 2015 Christopher Prijic

#ifndef SRC_UAV_FORGE_INERTIALSENSOR_H_
#define SRC_UAV_FORGE_INERTIALSENSOR_H_

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#include "defines.h"
#include "HAL.h"
#include "../Math/Vector.h"

#include <drivers/drv_accel.h>
#include <drivers/drv_gyro.h>
#include <drivers/drv_hrt.h>
#include <uORB/uORB.h>
#include <uORB/topics/sensor_combined.h>

const extern HAL& hal;

#define INS_MAX_INSTANCES 3

class InertialSensor {
private:
    FILE_DESC _accel_fd[INS_MAX_INSTANCES];
    FILE_DESC _gyro_fd[INS_MAX_INSTANCES];

    uint8_t   _num_accel_instances = 0;
    uint8_t   _num_gyro_instances = 0;
    uint8_t   _accepted_accel_instance = 0;
    uint8_t   _accepted_gyro_instance = 0;

    uint64_t  _last_accel_timestamp[INS_MAX_INSTANCES];
    uint64_t  _last_gyro_timestamp[INS_MAX_INSTANCES];
    uint64_t  _last_accel_update_timestamp[INS_MAX_INSTANCES];
    uint64_t  _last_gyro_update_timestamp[INS_MAX_INSTANCES];
    uint64_t  _last_get_sample_timestamp = 0;
    uint64_t  _last_sample_timestamp = 0;

    vec3      _accel_info[INS_MAX_INSTANCES];
    vec3      _gyro_info[INS_MAX_INSTANCES];
    vec3      _accel_corrected_info[INS_MAX_INSTANCES];
    vec3      _gyro_corrected_info[INS_MAX_INSTANCES];
    vec3      _accel_scale[INS_MAX_INSTANCES];
    vec3      _accel_offset[INS_MAX_INSTANCES];
    vec3      _gyro_offset[INS_MAX_INSTANCES];

    uint64_t  _accel_error_count[INS_MAX_INSTANCES];
    uint64_t  _gyro_error_count[INS_MAX_INSTANCES];

    void                   _get_sample();
    void                   _correct_accel(uint8_t instance, vec3 accel);
    void                   _correct_gyro(uint8_t instance, vec3 gyro);
protected:
public:
    vec3      accel;
    vec3      gyro;
                           InertialSensor() {}
    virtual                ~InertialSensor() {}

    static InertialSensor* create();
    bool                   init();

    inline uint8_t         get_num_accel() {return _num_accel_instances;}
    inline uint8_t         get_num_gyros() {return _num_gyro_instances;}
    bool                   update();
};

#endif /* SRC_UAV_FORGE_INERTIALSENSOR_H_ */
