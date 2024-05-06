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

    // time comparisons for filtering by time.
    bool operator<(Time& a);
    bool operator>(Time& a);
    // helpful for automatically formatting time and printing
    friend ostream& operator<<(ostream& out, Time& t);

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

// Linked List to help search words
class Word {
public:
    string content;
    int frequency;

private:
    Word(string c);
    Word* next;
    void inc();
    friend class WordList;
};

class WordList {
public:
    void addRemark(string add_freq);
    void display();
    // returns true if similar
    bool compare(WordList& w);
    WordList();

    void sort();

private:
    Word* head;
};

string pad_zeroes(int number);
