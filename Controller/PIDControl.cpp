#include "PIDControl.h" 

pidControl::pidControl(float kp, float ki, float kd)
{
    _ki = ki;
    _kd = kd;
    _kp = kp;    
}

float pidControl::control(float ref, float yout, float dt)
{
    // Call error_calc fxn to calculate P_error and I_error
    float error = piError(ref, yout, dt);
    // Derivative Error
    float error_dot = (error - _prev_error) / dt;
    // Used to calculate rate at which error changes
    _prev_error = error;
    return pidError(error, error_dot);
}

float pidControl::control(float ref, float ref_dot, float yout, float yout_dot, float dt)
{
    // Call error_calc fxn to calculate P_error and I_error
    float error = piError(ref, yout, dt);
    // Calculates error based on expected angular velocity vs sensor data
    float error_dot = ref_dot - yout_dot;
    // Calculates PID error
    return pidError(error, error_dot);
}

float pidControl::piError(float ref, float yout, float dt)
{
    // Proportional error
    float error = ref - yout;
    // Integral error
    _integral_error = _integral_error + (error * dt);
    return error;
}

float pidControl::pidError(float error, float error_dot)
{
 // Calculates the PID error and returns it
 return _kp*error + _ki*_integral_error + _kd*error_dot;   
}

float PdControl::control(float ref, float yout, float dt)
{
    // Proportional error
    float error = ref - yout;   
    // Derivative Error
    float error_dot = (error - _prev_error) / dt;
    // Calculates Pd_error
    return pdError(error, error_dot);
}
float PdControl::control(float ref, float ref_dot, float yout, float yout_dot)
{
    // Proportional Error
    float error = ref - yout;
    // Calculates error based on expected angular velocity vs sensor data
    float error_dot = ref_dot - yout_dot;
    // Calculates PD error
    return pdError(error, error_dot);
}

float PdControl::pdError(float error, float error_dot)
{
    // Calculates the PID error and returns it
    return _kp*error + _kd*error_dot;  
}
