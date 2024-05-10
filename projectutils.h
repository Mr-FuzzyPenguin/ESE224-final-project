#include <iostream>
#include <string>

// Necessary to "cause the current header file to be included only once in a single compilation".
// Otherwise you'll get an error about redefining Time in two different places.
// for more information visit: https://en.wikipedia.org/wiki/Pragma_once
#pragma once

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
    Time operator-(Time& a);
    Time operator/(int a);
    Time operator+(Time& a);
    // helpful for automatically formatting time and printing
    friend ostream& operator<<(ostream& out, Time& t);

    Time(int y, int m, int d, int h, int min, int s, int ss);
    Time(int y, int m, int d);
    Time();
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
    WordList();

    void sort();
    bool compare(WordList* w);

private:
    Word* head;
};

string pad_zeroes(int number);
