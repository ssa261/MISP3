#ifndef TIMEMETER_WIN_H
#define TIMEMETER_WIN_H

#include "TimeMeter.h"
#include <windows.h>

class TimeMeter::Impl {
public:
    Impl(unsigned count) : count(count) {
        timeStamps = new LARGE_INTEGER[count];
        ZeroMemory(timeStamps, count * sizeof(LARGE_INTEGER));
        QueryPerformanceFrequency(&frequency);
        QueryPerformanceCounter(&startTime);
    }
    
    ~Impl() {
        delete[] timeStamps;
    }
    
    double setTimeStamp(unsigned num) {
        QueryPerformanceCounter(&timeStamps[num]);
        return getTimeStamp(num);
    }
    
    double getTimeStamp(unsigned num) {
        LARGE_INTEGER delta;
        delta.QuadPart = timeStamps[num].QuadPart - startTime.QuadPart;
        return static_cast<double>(delta.QuadPart) / frequency.QuadPart;
    }
    
    int64_t getMSTimeStamp(unsigned num) {
        return static_cast<int64_t>(getTimeStamp(num) * 1000);
    }
    
    double getSDiff(unsigned first, unsigned second) {
        LARGE_INTEGER delta;
        delta.QuadPart = timeStamps[second].QuadPart - timeStamps[first].QuadPart;
        return static_cast<double>(delta.QuadPart) / frequency.QuadPart;
    }
    
    int64_t getMSDiff(unsigned first, unsigned second) {
        return static_cast<int64_t>(getSDiff(first, second) * 1000);
    }
    
    bool isLess(unsigned first, unsigned second, int64_t expected) {
        return getMSDiff(first, second) < expected;
    }
    
    bool isLess(unsigned num, int64_t expected) {
        return getMSTimeStamp(num) < expected;
    }

private:
    LARGE_INTEGER startTime;
    LARGE_INTEGER frequency;
    LARGE_INTEGER* timeStamps;
    unsigned count;
};

#endif
