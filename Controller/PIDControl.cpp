#include "PIDControl.h" 

PidControl::PidControl(float kp, float ki, float kd)
{
    _ki = ki;
    _kd = kd;
    _kp = kp;    
}

float PidControl::control(float ref, float y_out, float dt)
{
    // Call error_calc fxn to calculate P_error and I_error
    float error = PI_error(ref, y_out, dt);
    // Derivative Error
    float error_dot = (error - _prev_error) / dt;
    // Used to calculate rate at which error changes
    _prev_error = error;
    return PID_error(error, error_dot);
}

float PidControl::control(float ref, float ref_dot, float y_out, float yout_dot, float dt)
{
    // Call error_calc fxn to calculate P_error and I_error
    float error = PI_error(ref, y_out, dt);
    // Calculates error based on expected angular velocity vs sensor data
    float error_dot = ref_dot - yout_dot;
    // Calculates PID error
    return PID_error(error, error_dot);
}

float PidControl::PI_error(float ref, float y_out, float dt)
{
    // Proportional error
    float error = ref - y_out;
    // Integral error
    integral_error = integral_error + (error * dt);
    return error;
}

float PidControl::PID_error(float error, float error_dot)
{
 // Calculates the PID error and returns it
 return _kp*error + _ki*integral_error + _kd*error_dot;   
}

float PdControl::control(float ref, float y_out, float dt)
{
    // Proportional error
    float error = ref - y_out;   
    // Derivative Error
    float error_dot = (error - _prev_error) / dt;
    // Calculates Pd_error
    return Pd_error(error, error_dot);
}
float PdControl::control(float ref, float ref_dot, float y_out, float yout_dot)
{
    // Proportional Error
    float error = ref - y_out;
    // Calculates error based on expected angular velocity vs sensor data
    float error_dot = ref_dot - yout_dot;
    // Calculates PD error
    return Pd_error(error, error_dot);
}

float PdControl::Pd_error(float error, float error_dot)
{
    // Calculates the PID error and returns it
    return _kp*error + _kd*error_dot;  
}