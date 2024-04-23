#include "projectutils.h"

Time::Time(int y, int m, int d, int h, int min, int s, long ss)
{
    year = y;
    month = m;
    day = d;
    hour = h;
    minute = m;
    seconds = s;
    sub_second = ss;
}
