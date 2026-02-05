#include "MyTime.h"
#include <stdexcept>

//default constructor initializes time to 0:00
MyTime::MyTime() : hour(0), minute(0) {}

int MyTime::GetHour() const {
    return hour;
}

int MyTime::GetMinute() const {
    return minute;
}

void MyTime::SetHour(int h) {
    if (h < 0 || h > 23) throw std::invalid_argument("Hour must be 0-23");
    hour = h;
}

void MyTime::SetMinute(int m) {
    if (m < 0 || m > 59) throw std::invalid_argument("Minute must be 0-59");
    minute = m;
}
