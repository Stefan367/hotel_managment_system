#pragma once

#include "../core/my_string.h"
#include "../Constants.h"

class Date
{
private:
    int day;
    int month;
    int year;

    bool isValidDate(int d, int m, int y) const;

public:
    Date() = default;
    Date(int d, int m, int y);
    Date(const my_string& str);

    my_string to_string() const;
    void parseFromString(const my_string& str);

    bool isLeapYear(const int year) const;

    bool isDateWithValidFormat(const my_string date);

    int getDay() const;
    int getMonth() const;
    int getYear() const;

    bool operator<(const Date& other) const;
    bool operator==(const Date& other) const;
    bool operator>=(const Date& other) const;
    bool operator>(const Date& other) const;
    bool operator<=(const Date& other) const;

    int daysSinceYearStart() const;
    int daysUntil(const Date& other) const;

    int daysSince1900() const;
    bool isWeekend() const;

    static int getDaysInMonth(int month, int year);
    void addDays(int days);

    void print() const;
};