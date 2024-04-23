class Time {
private:
    int year;
    int month;
    int day;

    int hour;
    int minute;
    int seconds;
    long sub_second;

    Time(int y, int m, int d, int h, int min, int s, long ss);
    friend class Ticket;
};
