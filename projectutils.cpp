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

Word::Word(string c)
{
    content = c;
    frequency = 0;
    next = NULL;
}

void Word::inc()
{
    frequency++;
}

WordList::WordList()
{
    head = NULL;
}
void WordList::addRemark(string add_freq)
{
    // search for a ':' and count to 2 (because we're ignoring the "Comment:" string)
    int colons;
    string query = "";
    bool ignore;

    for (int i = 0; i < add_freq.length(); i++) {
        if (add_freq[i] == ':') {
            colons++;
        }

        if (colons >= 2 && add_freq[i] == ' ') {
            i++;
            // read until you get a space
            while (add_freq[i] != ' ') {
                query += add_freq[i];
                // make sure it is a valid word.
                if ((add_freq[i] >= '0' && add_freq[i] <= '9') || add_freq[i] == '%' || add_freq[i] == '&') {
                    ignore = true;
                }
            }
            if (ignore) {
                continue;
            } else {
                // go through list, see if word matches, if it does, increment.
                Word* traverse = head;
                while (traverse != NULL) {
                    if (query == traverse->content) {
                        traverse->inc();
                        break;
                    }
                }

                // if traverse is NULL then that means that the word did not exist. Add the word to the head.
                if (traverse == NULL) {
                    Word* newWord = new Word(query);
                    newWord->next = head;
                    head = newWord;
                }
            }
            // move back so next time i gets incremented, it'll hit space
            i--;
        }
    }
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
