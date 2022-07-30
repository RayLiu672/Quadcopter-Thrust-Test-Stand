#ifndef FILTERS_H
#define FILTERS_H

class LowpassFilter
{
    public: 
        // constructor creates object
        LowpassFilter(float time_const);

        ~LowpassFilter();
        
        float filter(float val, float dt);
        /**
         * @param val value to be filtered
         * @param dt difference between current and previous time
         * @return Filtered val with respect to _time_const and
         */

        float get_time_const();

        void set_time_const(float curr_time);

        void Reset(float val);

        float get_prev_filtered_val();

        void set_prev_filt(float filtered_val);
        
    private:
        float _time_const;
        float _prev_filtered_val = 0.0f;
};

class HighpassFilter
{
    public: 
        // constructor
        HighpassFilter(float time_const);

        ~HighpassFilter();

        float filter(float val, float dt);
        /**
         * @param val value to be filtered
         * @param dt difference between current and previous time
         * @return Filtered val with respect to _time_const
         */

        void Reset(float val);

        void set_prev_filt(float prev);

    private:
        float _time_const;
        float _prev_filtered_val = 0.0f;
        float _prev_val = 0;
};

#endif // FILTERS_H
