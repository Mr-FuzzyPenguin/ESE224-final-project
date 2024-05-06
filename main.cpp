#include "tickethandler.h"
#include <iostream>
#include <string>

// do not include utils. They are to be linked via project utils.

using namespace std;

int main()
{
    TicketList t;
    string file_list;
    cout << "Give me a list of all the files, separated by newlines. When done, put '#'";
    cin >> file_list;

    while (file_list != "#") {
        t.addTicket(file_list);
        cin >> file_list;
    }

    cout << *t.firstTicket;
    cout << *t.firstTicket->next;

    t.filterByTime(Time(2021, 1, 1, 1, 1, 1, 0), Time(2022, 05, 24, 02, 41, 01, 647934), "TM");
    return 0;
}
