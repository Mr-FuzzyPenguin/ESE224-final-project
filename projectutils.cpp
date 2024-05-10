#include "projectutils.h"
#include <iostream>
#include <string>
#include <cmath>

using namespace std;

Time::Time(int y, int m, int d, int h, int min, int s, int ss)
{
    year = y;
    month = m;
    day = d;
    hour = h;
    minute = min;
    seconds = s;
    sub_second = ((double)ss) / 1000000;
}

Time::Time(int y, int m, int d)
{
    year = y;
    month = m;
    day = d;
    hour = 0;
    minute = 0;
    seconds = 0;
    sub_second = 0;
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

Time Time::operator-(Time& a){
        Time result = *this;  // Start with a copy of the current object

        // Subtract sub_seconds
        result.sub_second -= a.sub_second;
        if (result.sub_second < 0) {
            result.sub_second += 1.0;
            result.seconds -= 1;
        }

        // Subtract seconds
        result.seconds -= a.seconds;
        if (result.seconds < 0) {
            result.seconds += 60;
            result.minute -= 1;
        }

        // Subtract minutes
        result.minute -= a.minute;
        if (result.minute < 0) {
            result.minute += 60;
            result.hour -= 1;
        }

        // Subtract hours
        result.hour -= a.hour;
        if (result.hour < 0) {
            result.hour += 24;
            result.day -= 1;
        }

        // Subtraction for days, months, and years is more complex due to varying month lengths and leap years
        // This basic implementation does not handle those and needs a more robust date management approach

        return result;
    }
Time Time::operator/(int a)
{
    if (a == 0)
    {
        throw std::logic_error("Division by zero is not allowed"); //indicates that an exception has occured
    }

    // Convert time to total seconds + microseconds
    double totalSeconds = hour * 3600 + minute * 60 + seconds + sub_second;
    
    // Divide the total seconds by the divisor
    totalSeconds /= a;

    Time result(0, 0, 0, 0, 0, 0, 0);
    result.sub_second = fmod(totalSeconds, 1.0); // Get fractional part
    totalSeconds = (int)totalSeconds; // Remove fractional part
    
    result.seconds = (int)totalSeconds % 60;
    totalSeconds /= 60;

    result.minute = (int)totalSeconds % 60;
    totalSeconds /= 60;

    result.hour = (int)totalSeconds % 24;
    totalSeconds /= 24;

    result.day = (int)totalSeconds; // The remaining part is considered as days

    return result;
}


Time Time::operator+(Time& a)  {
        Time result(0, 0, 0, 0, 0, 0, 0); // Initialize result Time object

        // Add sub_seconds and handle overflow
        double totalSubSeconds = this->sub_second + a.sub_second;
        if (totalSubSeconds >= 1.0) {
            result.seconds = 1; // Increment seconds if total sub_seconds are more than or equal to one second
            result.sub_second = fmod(totalSubSeconds, 1.0); // Keep only the fractional part
        } else {
            result.sub_second = totalSubSeconds;
        }

        // Add seconds and handle overflow
        int totalSeconds = this->seconds + a.seconds + result.seconds; // Include any overflow from sub_seconds
        result.seconds = totalSeconds % 60;
        int overflowMinutes = totalSeconds / 60;

        // Add minutes and handle overflow
        int totalMinutes = this->minute + a.minute + overflowMinutes;
        result.minute = totalMinutes % 60;
        int overflowHours = totalMinutes / 60;

        // Add hours and handle overflow (assuming overflow does not convert to days)
        int totalHours = this->hour + a.hour + overflowHours;
        result.hour = totalHours % 24;
        int overflowDays = totalHours / 24;

        // Simple handling of days (not accounting for month or year overflow)
        result.day = this->day + a.day + overflowDays;

        return result;
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
    int colons = 0;
    string query = "";
    bool ignore;

    for (int i = 0; i < add_freq.length(); i++) {
        if (add_freq[i] == ':') {
            colons++;
        }

        if (colons >= 2 && add_freq[i] == ' ') {
            i++;
            // read until you get a space
            while (add_freq[i] != ' ' && add_freq[i] != '\r') {
                query += add_freq[i];
                // make sure it is a valid word.
                if ((add_freq[i] >= '0' && add_freq[i] <= '9') || add_freq[i] == '%' || add_freq[i] == '&') {
                    ignore = true;
                }
                i++;
            }
            if (ignore) {
                ignore = false;
                query = "";
                i--;
                continue;
            }
            // not ignoring. Handle the word, then reset the query string
            else {
                // go through list, see if word matches, if it does, increment.
                Word* traverse = head;
                while (traverse != NULL) {
                    if (query == traverse->content) {
                        traverse->inc();
                        break;
                    }
                    traverse = traverse->next;
                }

                // if traverse is NULL then that means that the word did not exist. Add the word to the head.
                if (traverse == NULL) {
                    Word* newWord = new Word(query);
                    newWord->next = head;
                    head = newWord;
                    head->inc();
                }

                query = "";
            }
            // move back so next time i gets incremented, it'll hit space
            if (add_freq[i] != '\r')
                i--;
        }
    }
}
void WordList::display()
{
    cout << "DISPLAYING FREQUENCY OF WORDS:\n\n";
    Word* traverse = head;
    while (traverse != NULL) {
        cout << traverse->content << ": " << traverse->frequency << '\n';
        traverse = traverse->next;
    }
}

bool WordList::compare(WordList* w)
{
    // iterate through current word list
    // Compare with other word list. Use nested for loop
    for (Word* traverse = head; traverse != NULL; traverse = traverse->next) {
        for (Word* other_traverse = w->head; other_traverse != NULL; other_traverse = other_traverse->next) {
            // explanation:
            // content must match content (duh)
            // frequency must also match (for a strong(er) correlation)
            // frequency must be greater than 1 (so it doesn't include outliers.)
            if (other_traverse->content == traverse->content && other_traverse->frequency == traverse->frequency && other_traverse->frequency > 1) {
                cout << "Similar: " << traverse->content << " with " << traverse->frequency << " occurences and " << other_traverse->content << " with " << other_traverse->frequency << '\n';
                return true;
            }
        }
    }

    return false;
}

void WordList::sort()
{
    Word* traverse = head;
    bool changed = true;
    while (changed) {
        changed = false;
        traverse = head;
        while (traverse) {
            if (traverse->next && traverse->frequency < traverse->next->frequency) {
                changed = true;

                // swap in place.
                int temp_int = traverse->next->frequency;
                string temp_string = traverse->next->content;

                traverse->next->frequency = traverse->frequency;
                traverse->next->content = traverse->content;

                traverse->frequency = temp_int;
                traverse->content = temp_string;
            } else {
                traverse = traverse->next;
            }
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
