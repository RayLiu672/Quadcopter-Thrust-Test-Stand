#ifndef PIDCONTROL_H
#define PIDCONTROL_H

class PidControl
{
    // PID Functions
    public:
        // constructor creates object
        PidControl(float kp, float ki, float kd);
       /**
         * @param ref reference angle 
         * @param y_out angle sensor data
         * @param dt difference between current and previous time
         * used to calculate error in through numerical integration
         */  

        float control(float ref, float y_out, float dt);
        /**
         * @param ref reference angle (position) 
         * @param y_out angle sensor data output (position) 
         * @param dt difference between current and previous time
         * Calculate error through numerical differentiation(sensor data)
         */ 

        float control(float ref, float ref_dot, float y_out, float yout_dot, float dt);
        /**
         * @param ref reference angle (position) 
         * @param ref_dot reference rate (velocity) 
         * @param y_out angle sensor data output (position) 
         * @param yout_dot angular rate deriviatve from sensor data (velocity)
         * @param dt difference between current and previous time
         * Calculate error through numerical differentiation(sensor data)
         */ 

        float PI_error(float ref, float y_out, float dt);
        /**
         * @param ref reference angle 
         * @param y_out angle sensor data output
         * @param dt difference between current and previous time
         * Calculates the Proportional and Integral error in PID
         */

        float PID_error(float error, float error_dot);
        /**
         * @param error Proportional error  
         * @param error_dot Derivative error
         * Calculates the Proportional and Integral error in PID
         */

    private:
        float _kp;
        float _ki;
        float _kd;
        float _prev_error = 0.0f;
        float integral_error = 0.0f;
};

class PdControl
{
    //PdControl functions
    public:
        // constructor creates object
        PdControl(float kp, float kd);

        float control(float ref, float y_out, float dt);
        /**
         * @param ref reference angle (position) 
         * @param y_out angle sensor data (position) 
         * @param dt difference between current and previous time
         * Calculate error through numerical differentiation(sensor data)
         */ 

        float control(float ref, float ref_dot, float y_out, float yout_dot);
        /**
         * @param ref reference angle (position) 
         * @param ref_dot reference rate (velocity) 
         * @param y_out angle sensor data output (position) 
         * @param yout_dot angular rate deriviatve from sensor data (velocity)
         * @param dt difference between current and previous time
         * Calculate error through numerical differentiation(sensor data)
         */ 

        float Pd_error(float error, float error_dot);
        /**
         * @param error Proportional error  
         * @param error_dot Derivative error
         * Calculates the Proportional and Integral error in PID
         */
        
    private:
        float _kp;
        float _kd;
        float _prev_error = 0.0f;
};

#endif // PID_H
