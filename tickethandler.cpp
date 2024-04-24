#include "tickethandler.h"
#include <fstream>
#include <string>

TicketList::TicketList()
{
    firstTicket = NULL;
    lastTicket = NULL;
}

void TicketList::addTicket(string filename)
{
    ifstream ticketFile;

    Ticket* newTicket;
    string line;
    string line2;
    string line3;
    string substation;
    int linenumber = 0;
    char temp;
    ticketFile.open(filename, ifstream::in);
    while (ticketFile.good()) {
        temp = (char)ticketFile.get();
        if (temp != '\n') {
            line += temp;
        } else {
            linenumber++;
            if (linenumber == 2) {
                line2 = line;
            } else if (linenumber == 3) {
                line3 = line;
            } else {
                newTicket->addLine(line);
            }
            line = "";
        }
    }
    ticketFile.close();

    // the first ticket has been added onto the list
    if (firstTicket == NULL) {
        firstTicket = newTicket;
        lastTicket = newTicket;
    } else {
        // make the new point "backwards"
        newTicket->prev = lastTicket;
        // make the last point "forwards"
        lastTicket->next = newTicket;
    }
    return;
}

/*
Ticket::Ticket(string str2parse)
{

    bool recording;
    int mode;
    for (int i=0; i<str2parse.length(); i++)
    {
        if (str2parse[i] == '=')
        {
            recording =true;
        }
        else if (str2parse[i] == ',')
        {
            recording=false;
        }

        switch (mode)
        {

        }
    }

    // manipulate these guys based on the str2parse
    string remark;

    string structure; //=ASPHALT,
    float voltage; //=68.3,
    string ground; //=METAL FENCE,
    string msplate; //=00P,
    float harmonic; //=29.3,
    float v_non_shunt; //=84.3,
    string status; // PASSIVE SITE SAFETY



    Line* log_start = NULL;
    Line* log_end = NULL;
}*/
