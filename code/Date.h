#include <ctime>
#include <iostream>

using namespace std;

class Date 
{
private:
    int day;
    int month;
    int year;

public:
    Date() {
        storeCurrentDate();
    }

    Date(int d, int m, int y) : day(d), month(m), year(y) {}

    int getDay() { 
        return day; 
    }

    int getMonth() { 
        return month; 
    }

    int getYear() { 
        return year; 
    }

    void displayDate() {
        cout << "Date: " << day << "/" << month << '/' << year;
    }

    void storeCurrentDate() {
        time_t t = time(nullptr);
        tm currentTime;
        localtime_s(&currentTime, &t);
 
        day = currentTime.tm_mday;
        month = currentTime.tm_mon + 1;
        year = currentTime.tm_year + 1900;
    }

    bool operator==(const Date& other) const {
        return (day == other.day && month == other.month && year == other.year);
    }

    bool operator<(const Date& other) const {
        if (year != other.year)
            return year < other.year;
        if (month != other.month)
            return month < other.month;
        return day < other.day;
    }

    bool operator>(const Date& other) const {
        return (!(*this < other) && !(*this == other));
    }

    bool operator<=(const Date& other) const {
        return !(*this > other);
    }

    bool operator>=(const Date& other) const {
        return !(*this < other);
    }

    bool operator!=(const Date& other) const {
        return !(*this == other);
    }
};