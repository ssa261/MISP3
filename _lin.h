#ifndef TIMEMETER_LIN_H
#define TIMEMETER_LIN_H

#include "TimeMeter.h"
#include <ctime>

class TimeMeter::Impl {
public:
    Impl(unsigned count) : count(count) {
        timeStamps = new timespec[count];
        clock_gettime(CLOCK_MONOTONIC, &startTime);
    }
    
    ~Impl() {
        delete[] timeStamps;
    }
    
    double setTimeStamp(unsigned num) {
        clock_gettime(CLOCK_MONOTONIC, &timeStamps[num]);
        return getTimeStamp(num);
    }
    
    double getTimeStamp(unsigned num) {
        timespec delta;
        delta.tv_sec = timeStamps[num].tv_sec - startTime.tv_sec;
        delta.tv_nsec = timeStamps[num].tv_nsec - startTime.tv_nsec;
        return delta.tv_sec + delta.tv_nsec * 1e-9;
    }
    
    int64_t getMSTimeStamp(unsigned num) {
        timespec delta;
        delta.tv_sec = timeStamps[num].tv_sec - startTime.tv_sec;
        delta.tv_nsec = timeStamps[num].tv_nsec - startTime.tv_nsec;
        return delta.tv_sec * 1000 + delta.tv_nsec / 1000000;
    }
    
    double getSDiff(unsigned first, unsigned second) {
        timespec delta;
        delta.tv_sec = timeStamps[second].tv_sec - timeStamps[first].tv_sec;
        delta.tv_nsec = timeStamps[second].tv_nsec - timeStamps[first].tv_nsec;
        return delta.tv_sec + delta.tv_nsec * 1e-9;
    }
    
    int64_t getMSDiff(unsigned first, unsigned second) {
        timespec delta;
        delta.tv_sec = timeStamps[second].tv_sec - timeStamps[first].tv_sec;
        delta.tv_nsec = timeStamps[second].tv_nsec - timeStamps[first].tv_nsec;
        return delta.tv_sec * 1000 + delta.tv_nsec / 1000000;
    }
    
    bool isLess(unsigned first, unsigned second, int64_t expected) {
        return getMSDiff(first, second) < expected;
    }
    
    bool isLess(unsigned num, int64_t expected) {
        return getMSTimeStamp(num) < expected;
    }

private:
    timespec startTime;
    timespec* timeStamps;
    unsigned count;
};

#endif
