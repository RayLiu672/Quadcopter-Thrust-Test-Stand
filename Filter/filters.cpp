#include "filters.h"

LowpassFilter::LowpassFilter(float time_const)
{
    _time_const = time_const;
}

LowpassFilter::~LowpassFilter()
{
}

float LowpassFilter::get_time_const()
{
    return _time_const;
}

void LowpassFilter::set_time_const(float curr_time)
{
    _time_const = curr_time;
}

float LowpassFilter::filter(float val, float dt)
{  
    const float a = dt / (_time_const + dt);
    float filtered_val = a * val + (1 - a) * _prev_filtered_val;
    _prev_filtered_val = filtered_val; 
    return filtered_val;
}

HighpassFilter::HighpassFilter(float time_const)
{
    _time_const = time_const;
}

HighpassFilter::~HighpassFilter()
{
}

float HighpassFilter::filter(float val, float dt)
{
    const float a = _time_const / (_time_const + dt);
    float filtered_val = a*_prev_filtered_val + a*(val-_prev_val);
    _prev_filtered_val = filtered_val;
    _prev_val = val;
    return filtered_val;
}
