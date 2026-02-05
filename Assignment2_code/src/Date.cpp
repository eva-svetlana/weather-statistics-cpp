#include "Date.h"
#include <stdexcept>

//default constructor
//sets an invalid date for safety
Date::Date() : day(-1), month(-1), year(-2000) {}

int Date::GetDay() const {
    return day;
}
int Date::GetMonth() const {
    return month;
}
int Date::GetYear() const {
    return year;
}

void Date::SetDay(int d) {
    if (d < 1 || d > 31) throw std::invalid_argument("Day must be 1-31");
    day = d;
}

void Date::SetMonth(int m) {
    if (m < 1 || m > 12) throw std::invalid_argument("Month must be 1-12");
    month = m;
}

void Date::SetYear(int y) {
    year = y;
}
