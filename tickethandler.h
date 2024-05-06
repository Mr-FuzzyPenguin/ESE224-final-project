#include "projectutils.h"
#include <string>
using namespace std;

class Ticket {
public:
    // This should be a doubly linked list implementation with all of the lines.
    // Lines should be parsed and numbered.
    class Line {
        friend ostream& operator<<(ostream& out, Time& a);

    public:
        // metadata
        int line_num;
        Time time;
        string remark;

        // next and previous line in the logs.
        Line* next;
        Line* prev;

        // Line constructor.
        Line(string line);
        friend class Ticket;

        // defaults. helper for Ticket
        string address;
        int real_address;
        string substation;
        int sector;
    };

    // add metadata for query later.
    int address;

    string structure; //=ASPHALT,
    double voltage; //=68.3,
    string ground; //=METAL FENCE,
    string msplate; //=00P,
    double harmonic; //=29.3,
    double v_non_shunt; //=84.3,
    string status; // PASSIVE SITE SAFETY

    // what substation each ticket is associated with.
    // found after address and part
    string substation;
    int sector;

    // this just has the head of the lines.
    // This ticket class is a wrapper for a linked list of type: (Line)
    // and also contains metadata.
    Line* firstLine;
    // this is for adding at the end of the doubly linked list.
    Line* lastLine;

    // for doubly linked list implementation
    Ticket* next;
    Ticket* prev;

private:
    void generateWordList();
    friend class TicketList;
    friend ostream& operator<<(ostream& out, Ticket& a);
    friend istream& operator>>(istream& in, Ticket& a);
    Ticket(string initTime, string metadata);

public:
    // this should be privat'ed soon because comparisons should only be run by tickets themselves, who compares other tickets. This is because compare will call the compare method of the WordList anyway (which is private.)
    WordList* wordFreq;
    // ^^ private

    bool compare(Ticket* t);
    void addLine(string data);
};

// TODO doubly linked list implementation
class TicketList {
public:
    Ticket* firstTicket;
    Ticket* lastTicket;

    void filterByTime(Time start, Time end, string substation);

    // TicketList is a class (which is a wrapper) for a linked list of type: (Ticket)
    // part of DataBase

    // to search and filter for strings.
    // have a large chain of if statements that
    // check for the constraint == value
    void filterBySubstation(const int& y, const string& file) const;

    void filterByComments(const int& z, const string& file) const;

    void mostFrequentWord(const string& file) const;

    void addTicket(string file);

    TicketList();
};

// TODO decide implementation
// DISCUSSED: Doubly linked list?
// Implement hospital?
// add other metadata?
class Database {
    // Contain Ticket List
    // Hospital Data
    // Customer Interruptions
};
