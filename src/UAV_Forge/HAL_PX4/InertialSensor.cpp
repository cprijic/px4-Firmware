// Copyright 2015 Christopher Prijic

#include "InertialSensor.h"


InertialSensor* InertialSensor::create() {
    InertialSensor* sensor = new InertialSensor();

    if (sensor == NULL) {
        return NULL;
    }

    if (!sensor->init()) {
        delete sensor;
        return NULL;
    }

    return sensor;
}

bool InertialSensor::init() {
    // assumes max 3 instances
    _accel_fd[0] = open(ACCEL_BASE_DEVICE_PATH "0", O_RDONLY);
    _accel_fd[1] = open(ACCEL_BASE_DEVICE_PATH "1", O_RDONLY);
    _accel_fd[2] = open(ACCEL_BASE_DEVICE_PATH "2", O_RDONLY);
    _gyro_fd[0] = open(GYRO_BASE_DEVICE_PATH "0", O_RDONLY);
    _gyro_fd[1] = open(GYRO_BASE_DEVICE_PATH "1", O_RDONLY);
    _gyro_fd[2] = open(GYRO_BASE_DEVICE_PATH "2", O_RDONLY);

    _num_accel_instances = 0;
   _num_gyro_instances = 0;
   for (uint8_t i=0; i<INS_MAX_INSTANCES; i++) {
       if (_accel_fd[i] >= 0) {
           _num_accel_instances = i+1;
       }
       if (_gyro_fd[i] >= 0) {
           _num_gyro_instances = i+1;
       }
   }

   if (_num_accel_instances == 0) {
       return false;
   }
   if (_num_gyro_instances == 0) {
       return false;
   }

   for (int i = 0; i < INS_MAX_INSTANCES; i++) {
       _accel_scale[i] = vec3(1, 1, 1);
   }

   return true;
}

void InertialSensor::_get_sample() {
    for (uint8_t i=0; i<_num_accel_instances; i++) {
        struct accel_report accel_report;
        while (_accel_fd[i] != -1 &&
               ::read(_accel_fd[i], &accel_report, sizeof(accel_report)) == sizeof(accel_report) &&
               accel_report.timestamp != _last_accel_timestamp[i]) {
            _accel_info[i] = vec3(accel_report.x, accel_report.y, accel_report.z);
            _last_accel_timestamp[i] = accel_report.timestamp;
            _accel_error_count[i] = accel_report.error_count;
        }
    }
    for (uint8_t i=0; i<_num_gyro_instances; i++) {
        struct gyro_report  gyro_report;
        while (_gyro_fd[i] != -1 &&
               ::read(_gyro_fd[i], &gyro_report, sizeof(gyro_report)) == sizeof(gyro_report) &&
               gyro_report.timestamp != _last_gyro_timestamp[i]) {
            _gyro_info[i] = vec3(gyro_report.x, gyro_report.y, gyro_report.z);
            _last_gyro_timestamp[i] = gyro_report.timestamp;
            _gyro_error_count[i] = gyro_report.error_count;
        }
    }
    _last_get_sample_timestamp = hal.time->micros64();
}

bool InertialSensor::update()
{
    // get the latest sample from the sensor drivers
    _get_sample();

    for (uint8_t k=0; k<_num_accel_instances; k++) {
        vec3 accel_reading = _accel_info[k];

        if (_last_accel_timestamp[k] != _last_accel_update_timestamp[k]) {
            _correct_accel(k, accel_reading);
            _last_accel_update_timestamp[k] = _last_accel_timestamp[k];
        }
    }

    for (uint8_t k=0; k<_num_gyro_instances; k++) {
        vec3 gyro_reading = _gyro_info[k];

        if (_last_gyro_timestamp[k] != _last_gyro_update_timestamp[k]) {
            _correct_gyro(k, gyro_reading);
            _last_gyro_update_timestamp[k] = _last_gyro_timestamp[k];
        }
    }

    for (uint8_t k = 0; k < _num_accel_instances; k++) {
        if (!_accel_error_count[k]) {
            _accepted_accel_instance = k;
            accel = _accel_corrected_info[k];
            break;
        }
    }

    for (uint8_t k = 0; k < _num_gyro_instances; k++) {
        if (!_gyro_error_count[k]) {
            _accepted_gyro_instance = k;
            gyro = _gyro_corrected_info[k];
            break;
        }
    }

    return true;
}

void InertialSensor::_correct_accel(uint8_t instance, vec3 accel_reading) {
    vec3 corrected_accel = accel_reading;
    vec3 accel_scale = _accel_scale[instance];
    corrected_accel.x *= accel_scale.x;
    corrected_accel.y *= accel_scale.y;
    corrected_accel.z *= accel_scale.z;
    corrected_accel -= _accel_offset[instance];
    _accel_corrected_info[instance] = corrected_accel;
}

void InertialSensor::_correct_gyro(uint8_t instance, vec3 gyro_reading) {
    vec3 corrected_gyro = gyro_reading;
    corrected_gyro -= _gyro_offset[instance];
    _gyro_corrected_info[instance] = corrected_gyro;
}











