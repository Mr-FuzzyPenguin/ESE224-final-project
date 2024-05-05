#include <fstream>
#include <iostream>
#include <string>

// do not include utils. They are to be linked via project utils.
#include "tickethandler.h"

using namespace std;

int main()
{
    TicketList t;

    // adding more tests. Soon, we'll generalize.
    t.addTicket("tickets/EB04706280.csv");
    t.addTicket("tickets/EB05574047.csv");

    cout << *t.firstTicket;
    cout << *t.firstTicket->next;

    t.filterByTime(Time(2021, 1, 1, 1, 1, 1, 0), Time(2022, 05, 24, 02, 41, 01, 647934), "TM");
    return 0;
}
