#include <ctime>
#include <iostream>

using namespace std;

#ifndef _Date_H
#define _Date_H
class Date 
{
private:
    int day;
    int month;
    int year;

public:
    // Default constructor that initializes the date to the current date
    Date() { storeCurrentDate(); }

    // Constructor that initializes the date to the provided day, month, and year
    Date(int d, int m, int y) : day(d), month(m), year(y) {}

    // Getter for the day
    int getDay() { 
        return day; 
    }

    // Getter for the month
    int getMonth() { 
        return month; 
    }

    // Getter for the year
    int getYear() { 
        return year; 
    }

    // Function to display the date in DD/MM/YYYY format
    void displayDate() { 
        cout << "Date: " << day << "/" << month << '/' << year;
    }

    // Overloaded operator<= to compare two dates
    bool operator<=(const Date& other) const { 
        if ((day == other.day && month == other.month && year == other.year))
            return true;
        else {
            if (year != other.year)
                return year < other.year;
            if (month != other.month)
                return month < other.month;
            return day < other.day;
        }
    }

    // Overloaded operator>= to compare two dates
    bool operator>=(const Date& other) const { 
        if ((day == other.day && month == other.month && year == other.year))
            return true;
        else {
            if (year != other.year)
                return year > other.year;
            if (month != other.month)
                return month > other.month;
            return day > other.day;
        }
    }

private:
    // Function to store the current date
    void storeCurrentDate() {
        time_t t = time(nullptr);  // Get the current time
        tm currentTime;
        localtime_s(&currentTime, &t);  // Convert the time to local time

        day = currentTime.tm_mday;  // Store the day
        month = currentTime.tm_mon + 1;  // Store the month
        year = currentTime.tm_year + 1900;  // Store the year
    }
};
#endif //_Date_H