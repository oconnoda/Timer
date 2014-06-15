// Timer.cpp
// Provide timer class
// David O'Connor, Feb 15, 2014
#include "timer.h"
#include "Arduino.h"
#include <limits.h>

#define OFF 0
#define ON 1
#define PENDING 2

Timer::Timer() {
    int i;

    timerCount = 2;
    _timers = (struct _Timer *)malloc(sizeof(struct _Timer)*timerCount);
    for (i=0;i<timerCount;i++) {
        _timers[i].status = OFF;
    }
}

int Timer::getIndex() {
    int i;
    struct _Timer *t;
    
    for (i=0;i<timerCount;i++) {
        if (_timers[i].status == OFF) return i;
    }
    timerCount++;
    t = (struct _Timer *)malloc(sizeof(struct _Timer)*timerCount);
    for (i=0;i<timerCount-1;i++) {
        t[i] = _timers[i];
    }
    free(_timers);
    _timers = t;
    return timerCount - 1;
}

void Timer::runTimers() {
    int i;
    unsigned long currentTime = millis();
    
    for (i=0;i<timerCount;i++) {
        if (_timers[i].status == ON) {
            if (_timers[i].interval == 0) {
                // interval 0 timers only run when triggered
                if (_timers[i].lastTime == 0) {
                    _timers[i].lastTime = currentTime;
                    (*_timers[i].action)(i);
                }
            }
            // millis() rollover
            else if (currentTime < _timers[i].lastTime) {
                if (ULONG_MAX - _timers[i].lastTime + currentTime > _timers[i].interval) {
                    _timers[i].lastTime = currentTime;
                    (*_timers[i].action)(i);
                }
            }
            else if (currentTime - _timers[i].lastTime > _timers[i].interval) {
                _timers[i].lastTime = currentTime;
                (*_timers[i].action)(i);
            }
        }
        else if (_timers[i].status == PENDING) {
            _timers[i].status = ON;
        }
    }
}

int Timer::startTimer(unsigned long interval, void (*action)(int)) {
    int index = getIndex();
    if (index >= timerCount || index < 0) return index;
    _timers[index].status = PENDING;
    _timers[index].lastTime = millis();
    _timers[index].action = action;
    _timers[index].interval = interval;
    return index;
}

void Timer::triggerTimer(int index) {
  if (index >= timerCount || index < 0) return;
  _timers[index].lastTime = 0;
}

void Timer::stopTimer(int index) {
  if (index >= timerCount || index < 0) return;
  _timers[index].status = OFF;
}

