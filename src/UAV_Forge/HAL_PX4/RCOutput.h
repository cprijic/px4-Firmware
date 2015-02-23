// Copyright 2015 Christopher Prijic

#ifndef SRC_UAV_FORGE_RCOUTPUT_H_
#define SRC_UAV_FORGE_RCOUTPUT_H_

#include <uORB/topics/actuator_outputs.h>
#include <uORB/topics/actuator_armed.h>
#include "defines.h"
#define PX4_NUM_OUTPUT_CHANNELS 16

class RCOutput {
private:
    FILE_DESC          _pwm_fd;
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

    /**
     * Publishes the actuators to the system, for output.
     */
    void     _publish_actuators(void);

    /**
     * Arms the actuators for output.
     */
    void     _arm_actuators(bool arm);
protected:
public:

    /**
     * Initializes the RC Outputs for use.
     */
    void     init();

    /**
     * Sets the frequency of the PWM signal for the given channel mask.
     *
     * @param chmask the mask of channels to apply the frequency to.
     * @param freq_hz the frequency to set the given channels to.
     */
    void     set_freq(uint32_t chmask, uint16_t freq_hz);

    /**
     * The frequency of the PWM output.
     *
     * @return the frequency of the PWM output.
     */
    uint16_t get_freq(uint8_t ch);

    /**
     * Enables a channel for use.
     *
     * @ ch the channel to enable.
     */
    void     enable_ch(uint8_t ch);

    /**
     * Disable a channel to not be used.
     *
     * @param ch the channel to disable.
     */
    void     disable_ch(uint8_t ch);

    /**
     * Writes a PWM signal to a channel.
     *
     * @param ch the channel to write to.
     * @param period_us the length of the pulse to send.
     */
    void     write(uint8_t ch, uint16_t period_us);

    /**
     * Writes a PWM signal to a channel.
     *
     * @param ch the channel to write to.
     * @param period_us the message to write.
     * @param len the length of the message to send.
     */
    void     write(uint8_t ch, uint16_t* period_us, uint8_t len);

    /**
     * Reads the previously written message.
     *
     * @return the previously send message, in microseconds.
     */
    uint16_t read(uint8_t ch);

    /**
     * Reads the previously written message and places it into the given array.
     *
     * @param period_us the array to fill.
     * @param len the length of the given array.
     */
    void     read(uint16_t* period_us, uint8_t len);

    /**
     * Sets the safety signal for the channel.
     *
     * @param chmask the channels to set.
     * @param period_us the signal to set safety.
     */
    void     set_safety_pwm(uint32_t chmask, uint16_t period_us);

    /**
     * Sets the faisfafe for the channel.
     *
     * @param chmask the channels to set.
     * @param period_us the signal to set failsafe.
     */
    void     set_failsafe_pwm(uint32_t chmask, uint16_t period_us);

    /**
     * Forces the safety on.
     *
     * @return whether it was successful or not.
     */
    bool     force_safety_on();

    /**
     * Forces the safety off.
     */
    void     force_safety_off();

    /**
     * The update method for RC Outputs.
     */
    void     _timer_tick();

    /**
     * Sets the scaling for ESC outputs.
     *
     * @param min_pwm the minimum signal for pwm output.
     * @param max_pwm the maximum signal for pwm output.
     */
    void     set_esc_scaling(uint16_t min_pwm, uint16_t max_pwm) {
        _esc_pwm_min = min_pwm;
        _esc_pwm_max = max_pwm;
    }
};


#endif /* SRC_UAV_FORGE_RCOUTPUT_H_ */
