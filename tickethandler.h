#include "projectutils.h"
#include <string>
using namespace std;

class Ticket {
public:
    // This should be a doubly linked list implementation with all of the lines.
    // Lines should be parsed and numbered.
    class Line {
        // metadata
        int line_num;
        Time time;
        string remark;
        string comment;

        // next line in the logs.
        Line* next;

        // Line constructor.
        Line(string line);
    };

    // add metadata for query later.
    string remark;

    string structure; //=ASPHALT,
    float voltage; //=68.3,
    string ground; //=METAL FENCE,
    string msplate; //=00P,
    float harmonic; //=29.3,
    float v_non_shunt; //=84.3,
    string status; // PASSIVE SITE SAFETY

    // what substation each ticket is associated with.
    string substation;

    // this just has the head of the lines.
    // This ticket class is a wrapper for a linked list of type: (Line)
    // and also contains metadata.
    Line* log_start;
    // this is for adding at the end of the doubly linked list.
    Line* log_end;

    // for doubly linked list implementation
    Ticket* next;
    Ticket* prev;

private:
    friend class TicketList;
    Ticket(string initTime, string metadata);

public:
    void addLine(string data);
};

// TODO doubly linked list implementation
class TicketList {
    Ticket* firstTicket;
    Ticket* lastTicket;
    // TicketList is a class (which is a wrapper) for a linked list of type: (Ticket)
    // part of DataBase

    // to search and filter for strings.
    // have a large chain of if statements that
    // check for the constraint == value
    void query(string constraint, string value, string type);
    void addTicket(string filename);

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
