// Copyright 2015 Christopher Prijic

#ifndef SRC_UAV_FORGE_RCOUTPUT_H_
#define SRC_UAV_FORGE_RCOUTPUT_H_

#include <uORB/topics/actuator_outputs.h>
#include <uORB/topics/actuator_armed.h>

#define PX4_NUM_OUTPUT_CHANNELS 16

class RCOutput {
public:
    typedef int ORB_HANDLE;
private:
    int                _pwm_fd;
    uint16_t           _pwm_freq;
    uint16_t           _period[PX4_NUM_OUTPUT_CHANNELS];
    volatile uint8_t   _max_channel;
    volatile bool      _need_update;
    uint32_t           _last_output;
    unsigned           _servo_count;
    uint32_t           _rate_mask;
    uint16_t           _enabled_channels;
    ORB_HANDLE         _pwm_sub;
    actuator_outputs_s _outputs;
    actuator_armed_s   _armed;
    ORB_HANDLE         _actuator_direct_pub = -1;
    ORB_HANDLE         _actuator_armed_pub = -1;
    uint16_t           _esc_pwm_min = 1000;
    uint16_t           _esc_pwm_max = 2000;

    void     _publish_actuators(void);
    void     _arm_actuators(bool arm);
protected:
public:
    void     init();
    void     set_freq(uint32_t chmask, uint16_t freq_hz);
    uint16_t get_freq(uint8_t ch);
    void     enable_ch(uint8_t ch);
    void     disable_ch(uint8_t ch);
    void     write(uint8_t ch, uint16_t period_us);
    void     write(uint8_t ch, uint16_t* period_us, uint8_t len);
    uint16_t read(uint8_t ch);
    void     read(uint16_t* period_us, uint8_t len);
    void     set_safety_pwm(uint32_t chmask, uint16_t period_us);
    void     set_failsafe_pwm(uint32_t chmask, uint16_t period_us);
    bool     force_safety_on();
    void     force_safety_off();
    void     _timer_tick();
    void     set_esc_scaling(uint16_t min_pwm, uint16_t max_pwm) {
        _esc_pwm_min = min_pwm;
        _esc_pwm_max = max_pwm;
    }
};


#endif /* SRC_UAV_FORGE_RCOUTPUT_H_ */
