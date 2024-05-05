#include "projectutils.h"
#include "string"

using namespace std;

Time::Time(int y, int m, int d, int h, int min, int s, int ss)
{
    year = y;
    month = m;
    day = d;
    hour = h;
    minute = m;
    seconds = s;
    sub_second = ((double)ss) / 1000000;
}

Time::Time() { }

ostream& operator<<(ostream& out, Time& a)
{
    // yikes. We have to have a deterministic first three lines
    out << a.month << '/' << a.day << '/' << a.year << " " << pad_zeroes(a.hour) << ':' << pad_zeroes(a.minute) << ':' << pad_zeroes(a.seconds) << to_string(a.sub_second).substr(1);

    return out;
}

bool Time::operator<(Time& t)
{
    if (year < t.year) {
        return true;
    } else if (month < t.month) {
        return true;
    } else if (day < t.day) {
        return true;
    } else if (hour < t.hour) {
        return true;
    } else if (minute < t.minute) {
        return true;
    } else if (seconds < t.seconds) {
        return true;
    } else if (sub_second < t.sub_second) {
        return true;
    }
    return false;
}

bool Time::operator>(Time& t)
{
    if (year > t.year) {
        return true;
    } else if (month > t.month) {
        return true;
    } else if (day > t.day) {
        return true;
    } else if (hour > t.hour) {
        return true;
    } else if (minute > t.minute) {
        return true;
    } else if (seconds > t.seconds) {
        return true;
    } else if (sub_second > t.sub_second) {
        return true;
    }
    return false;
}

string pad_zeroes(int number)
{
    string output;
    if (number <= 9) {
        output += '0';
        output += '0' + number;
    } else {
        output = to_string(number);
    }
    return output;
}
