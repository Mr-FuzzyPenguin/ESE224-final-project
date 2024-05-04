#include <iostream>
#include <string>
using namespace std;

class Time {
public:
    int year;
    int month;
    int day;

    int hour;
    int minute;
    int seconds;
    double sub_second;

    Time(int y, int m, int d, int h, int min, int s, int ss);
    Time();
    friend class Ticket;
};

class HospitalDates {
private:
    int startYear;
    int startMonth;
    int startDay;

    int endYear;
    int endMonth;
    int endDay;

    HospitalDates(int Sy, int Sm, int Sd, int Ey, int Em, int Ed)
    {
        startYear = Sy;
        startMonth = Sm;
        startDay = Sd;

        endYear = Ey;
        endMonth = Em;
        endDay = Ed;
    };
    HospitalDates();
    friend class Ticket;
};
string pad_zeroes(int number);
