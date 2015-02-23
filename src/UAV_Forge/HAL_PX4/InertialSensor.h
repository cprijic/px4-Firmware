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

    /**
     * Grabs a sample from the sensors.
     */
    void                   _get_sample();

    /**
     * Corrects accelerometer readings.
     *
     * The corrections are made in the form of an offset for each axis,
     * and a scaling.
     *
     * @param instance the accelerometer instance being corrected.
     * @param accel the currently read acceleration to be corrected.
     */
    void                   _correct_accel(uint8_t instance, vec3 accel);

    /**
     * Corrects gyro readings.
     *
     * The corrections are made in the form of an offset for each axis.
     *
     * @param instance the accelerometer instance being corrected.
     * @param gyro the currently read gyro reading to be corrected.
     */
    void                   _correct_gyro(uint8_t instance, vec3 gyro);

    /**
     * An Inertial Sensor constructor.
     *
     * @see create()
     */
                           InertialSensor() {}
protected:
public:
    /**
     * The current accelerometer reading (acceleration, m/s).
     */
    vec3      accel;

    /**
     * The current gyro reading (angular rate, radians).
     */
    vec3      gyro;

    virtual                ~InertialSensor() {}

    /**
     * Creates and initializes the inertial sensor.
     */
    static InertialSensor* create();

    /**
     * Initializes the inertial sensor.
     *
     * @see create()
     */
    bool                   init();

    /**
     * The number of accelerometers that can be polled.
     *
     * @return the number of accelerometers that can be polled.
     */
    inline uint8_t         get_num_accel() {return _num_accel_instances;}

    /**
     * The number of gyros that can be polled.
     *
     * @return the number of gyros that can be polled.
     */
    inline uint8_t         get_num_gyros() {return _num_gyro_instances;}

    /**
     * Updates the readings from the sensors.
     *
     * @return whether or not the update was successful.
     */
    bool                   update();
};

#endif /* SRC_UAV_FORGE_INERTIALSENSOR_H_ */
