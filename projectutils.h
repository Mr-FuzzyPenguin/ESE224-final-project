class Time {
private:
    int year;
    int month;
    int day;

    int hour;
    int minute;
    int seconds;
    int sub_second;

    Time(int y, int m, int d, int h, int min, int s, int ss);
    Time();
    friend class Ticket;
};
