#include "TimeMeter.h"
#include <iostream>

#ifdef _WIN32    // работает на любых, а не только 32 битных системах
    #include "TimeMeter_win.h"
#elif __linux__
    #include "TimeMeter_lin.h"
#else
    std::cout << "Ошибка системы" << std::endl;
    std::abort();
#endif

TimeMeter::TimeMeter(unsigned count) : impl_(new Impl(count)) {}
TimeMeter::~TimeMeter() { 
    delete impl_; 
}
double TimeMeter::setTimeStamp(unsigned num) { 
    return impl_->setTimeStamp(num); 
}
double TimeMeter::setTimeStamp(unsigned num) {
    return impl_->setTimeStamp(num);
}
double TimeMeter::getTimeStamp(unsigned num) {
    return impl_->getTimeStamp(num);
}
int64_t TimeMeter::getMSTimeStamp(unsigned num) {
    return impl_->getMSTimeStamp(num);
}
double TimeMeter::getSDiff(unsigned first, unsigned second) {
    return impl_->getSDiff(first, second);
}
int64_t TimeMeter::getMSDiff(unsigned first, unsigned second) {
    return impl_->getMSDiff(first, second);
}
bool TimeMeter::isLess(unsigned first, unsigned second, int64_t expected) {
    return impl_->isLess(first, second, expected);
}
bool TimeMeter::isLess(unsigned num, int64_t expected) {
    return impl_->isLess(num, expected);
}
