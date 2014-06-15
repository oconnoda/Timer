Timer
=====

Arduino timer library

This library provides a timer class to perform actions periodically. There is no set
maximum number of timers available. The number of timers is limited only by memory and CPU.

Public methods

    // Call this function to start a timer. Interval is in milliseconds.
    // The timer number will be passed to the callback. If you want the
    // timer to run only when triggered, use an interval of 0.
    int startTimer(unsigned long interval, void (*action)(int));
    
    // Call this function to stop a timer. Can be used in the callback
    // function for a "one shot" timer.
    void stopTimer(int index);
    
    // Use this function to trigger a timer. Useful in interrupt handlers when
    // you have a lot of work to do also when you want to do something
    // periodically or when an event happens.
    void triggerTimer(int index);
    
    // Call this function in loop to run all your timers.
    void runTimers();
