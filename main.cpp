#include <fstream>
#include <iostream>
#include <string>

// do not include utils. They are to be linked via project utils.
#include "tickethandler.h"

using namespace std;

int main()
{
    TicketList t;

    t.addTicket("tickets/EB04706280.csv");
    return 0;
}
