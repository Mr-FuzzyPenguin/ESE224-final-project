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
