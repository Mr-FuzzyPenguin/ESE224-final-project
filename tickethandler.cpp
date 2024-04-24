#include "tickethandler.h"
#include <fstream>
#include <iostream>
#include <string>
using namespace std;

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
        }
        // newline detected. Decide what to do
        else {
            // increment line number just to know what to do
            // based on the REAL line number
            linenumber++;
            if (linenumber == 2) {
                line2 = line;
            }
            // line number was 3. Go and initialize the ticket based on line2 and line3
            else if (linenumber == 3) {
                line3 = line;
                newTicket = new Ticket(line2, line3);
            }
            // not the (VERY FIRST) line.
            else if (line[0] != 'L') {
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
        // make the new ticket point "backwards"
        newTicket->prev = lastTicket;
        // make the last ticket point "forwards"
        lastTicket->next = newTicket;
    }
    return;
}

void Ticket::addLine(string data)
{
    cout << data << '\n';

    // TODO @Pete Aptenodytes Forsteri please write a better parser
    // - Fuzzy Penguin
}

//
// void Ticket::addLine(string data)
// {
//     // let the Line constructor handle the data processing.
//     // we are assuming the Line() object gathered the metadata
//     // already, because of the parser in the constructor.
//     Line* newLine = new Ticket::Line(data);
//
//     // first line is null.
//     // make both equal to the new line object.
//     if (firstLine == NULL) {
//         firstLine = newLine;
//         lastLine = newLine;
//     }
//     // make the lines point correctly.
//     else {
//         // make new line point "backwards"
//         newLine->prev = lastLine;
//         // make the last line point "forwards"
//         lastLine->next = newLine;
//     }
// }
//
// make sure it's only run during lines in which have "line #s"
Ticket::Ticket::Line::Line(string line)
{
    // defaults:
    address = "";
    substation = "";

    line_num = 0;
    int mode = 0;
    bool quotes = false;

    // recording devices
    int temp_int = 0;
    string temp_string;
    int time_recorder = 0;

    int year, month, day, hour, minute, seconds;
    // long sub_second;

    // TODO parser goes here.
    for (int i = 0; i < line.length(); i++) {
        // check for quotes.
        if (line[i] == '"') {
            quotes = !quotes;
        }

        // check for commas, and then increment mode.
        if (!quotes && line[i] == ',') {

            // if mode was 1, create the time object
            if (mode == 1) {
                time = Time(year, month, day, hour, minute, seconds, temp_int);
            }
            // if mode was 2, create the remark.
            else if (mode == 2) {
                remark = temp_string;
            }
            // ignore mode 3

            // if mode was 4, set the address.
            else if (mode == 4) {
                address = temp_string;
            }

            else if (mode == 5) {
                substation = temp_string;
            }
            temp_string = "";
            temp_int = 0;
            mode++;
        }

        // mode is 0, for line number.
        else if (mode == 0) {
            line_num = line_num * 10 + line[i] - 48;
            continue;
        }

        // mode is 1, for time.
        else if (mode == 1) {
            if (line[i] == '_' || line[i] == ':' || line[i] == '.' || line[i] == ' ') {

                // assign to individual variables.
                switch (time_recorder) {
                case 0:
                    year = temp_int;
                    break;
                case 1:
                    month = temp_int;
                    break;
                case 2:
                    day = temp_int;
                    break;
                case 3:
                    hour = temp_int;
                    break;
                case 4:
                    minute = temp_int;
                    break;
                case 5:
                    seconds = temp_int;
                    break;
                }

                // reset the temp_int for time recording
                temp_int = 0;
                // switch the time_recorder.
                // time_recorder is a mode to record hour, minute, seconds, etc.
                time_recorder++;
                continue;
            }
            // convert from string to int.
            temp_int = temp_int * 10 + line[i] - 48;
        }

        // start recording into the string.
        // dump the "ENE" string for mode==3
        // continue reading when mode == 4.
        // when the mode is 4, start to record Address.
        // at the last second, only trim the relevant part
        // of address.
        else if (mode == 2 || mode == 4 || mode == 5) {
            temp_string += line[i];
        }
    }
    substation = temp_string;

    // special lines
    if (mode > 2) {
        // outside of for loop. Fix address, and fix substation and sector.
        temp_int = 0;
        temp_string = "";

        // merely here for helping decode address.
        for (int i = 0; i < address.length(); i++) {
            if (address[i] >= '0' && address[i] <= '9') {
                temp_int = temp_int * 10 + address[i] - 48;
            }
        }

        // set real_address to temp_int
        real_address = temp_int;

        temp_int = 0;
        // iterate through substation and add temp_int
        for (int i = 0; i < substation.length(); i++) {
            if (substation[i] >= '0' && substation[i] <= '9') {
                temp_int = temp_int * 10 + substation[i] - 48;
            } else {
                if (substation[i] == ' ') {
                    break;
                }
                temp_string += substation[i];
            }
        }
        substation = temp_string;
    }
    return;
}

Ticket::Ticket(string initTime, string metadata)
{
    firstLine = new Line(initTime);
    lastLine = firstLine;

    // manipulate these guys based on initTime and metadata
    address = firstLine->real_address;
    substation = firstLine->substation;
    sector = firstLine->sector;

    // structure; //=ASPHALT,
    // voltage; //=68.3,
    // ground; //=METAL FENCE,
    // msplate; //=00P,
    // harmonic; //=29.3,
    // v_non_shunt; //=84.3,
    // status; // PASSIVE SITE SAFETY

    Line* log_start = NULL;
    Line* log_end = NULL;
}
