#ifndef TIMEMETER_H      
#define TIMEMETER_H

class TimeMeter {
public:
        TimeMeter(unsigned count);
        ~TimeMeter();

        double setTimeStamp(unsigned num);

        double getTimeStamp(unsigned num);

        int64_t getMSTimeStamp(unsigned num);

        double getSDiff(unsigned first, unsigned second);

        int64_t getMSDiff(unsigned first, unsigned second);

        bool isLess(unsigned first, unsigned second, int64_t expected);

        bool isLess(unsigned num, int64_t expected);
private:
        TimeMeter(const TimeMeter&);
        TimeMeter& operator=(const TimeMeter&);
        // комментарий для защиты: Семён, ты запретил копирование по примеру с семинара 08.09.2025

        class Impl;
        Impl *impl_;

};

#endif
