#ifndef FILTERS_H
#define FILTERS_H

class LowpassFilter
{
    public: 
        // constructor
        LowpassFilter(float time_const);

        ~LowpassFilter();
        
        /**
         * Apply lowpass filter to incoming val
         *  
         * @param val value to be filtered
         * @param dt difference between current and previous time
         * @return Filtered val with respect to _time_const and
         */
        float filter(float val, float dt);
        //method
        float get_time_const();

        void Reset(float val);
        
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

        /**
         * Apply lowpass filter to incoming val
         *  
         * @param val value to be filtered
         * @param dt difference between current and previous time
         * @return Filtered val with respect to _time_const and
         */
        float filter(float val, float dt);

        void Reset(float val);

    private:
        float _time_const;
        float _prev_filtered_val = 0.0f;
        float prev_val = 0;
};

class ComplimentaryFilter
{
    
} ;

#endif // FILTERS_H
