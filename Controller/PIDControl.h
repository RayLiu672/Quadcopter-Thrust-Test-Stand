#ifndef PIDCONTROL_H
#define PIDCONTROL_H

class pidControl
{
    // PID Functions
    public:
        // constructor creates object
        pidControl(float kp, float ki, float kd);
       /**
         * @param ref reference angle 
         * @param yout angle sensor data
         * @param dt difference between current and previous time
         * used to calculate error in through numerical integration
         */  

        float control(float ref, float yout, float dt);
        /**
         * @param ref reference angle (position) 
         * @param yout angle sensor data output (position) 
         * @param dt difference between current and previous time
         * Calculate error through numerical differentiation(sensor data)
         */ 

        float control(float ref, float ref_dot, float yout, float yout_dot, float dt);
        /**
         * @param ref reference angle (position) 
         * @param ref_dot reference rate (velocity) 
         * @param yout angle sensor data output (position) 
         * @param yout_dot angular rate deriviatve from sensor data (velocity)
         * @param dt difference between current and previous time
         * Calculate error through numerical differentiation(sensor data)
         */ 

        float piError(float ref, float yout, float dt);
        /**
         * @param ref reference angle 
         * @param yout angle sensor data output
         * @param dt difference between current and previous time
         * Calculates the Proportional and Integral error in PID
         */

        float pidError(float error, float error_dot);
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
        float _integral_error = 0.0f;
};

class PdControl
{
    //PdControl functions
    public:
        // constructor creates object
        PdControl(float kp, float kd);

        float control(float ref, float yout, float dt);
        /**
         * @param ref reference angle (position) 
         * @param yout angle sensor data (position) 
         * @param dt difference between current and previous time
         * Calculate error through numerical differentiation(sensor data)
         */ 

        float control(float ref, float ref_dot, float yout, float yout_dot);
        /**
         * @param ref reference angle (position) 
         * @param ref_dot reference rate (velocity) 
         * @param yout angle sensor data output (position) 
         * @param yout_dot angular rate deriviatve from sensor data (velocity)
         * @param dt difference between current and previous time
         * Calculate error through numerical differentiation(sensor data)
         */ 

        float pdError(float error, float error_dot);
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
