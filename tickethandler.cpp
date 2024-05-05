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

        // update last ticket.
        lastTicket = newTicket;
    }
    return;
}

void Ticket::addLine(string data)
{
    Line* newLine = new Ticket::Line(data);

    // make new line point "backwards"
    newLine->prev = lastLine;
    // make the last line point "forwards"
    lastLine->next = newLine;
    // shift the lastLine.
    lastLine = newLine;
}

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
    // check the ending. If mode == 3, it's a normal log.
    // therefore: return early
    if (mode == 2) {
        remark = temp_string;
        return;
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

    // write another parser here. this time, parse metadata string
    bool recording = false;
    int part = 0;
    string temp_string;
    for (int i = 0; i < metadata.length(); i++) {

        // detected ',' stop recording.
        // also decide where to route temp_string
        if (metadata[i] == ',' && recording) {
            recording = false;

            switch (part) {
            case 0:
                structure = temp_string;
                break;
            case 1:
                voltage = stod(temp_string);
                break;
            case 2:
                ground = temp_string;
                break;
            case 3:
                msplate = temp_string;
                break;
            case 4:
                harmonic = stod(temp_string);
                break;
            case 5:
                v_non_shunt = stod(temp_string);
                break;
            case 6:
                status = temp_string;
                break;
            }

            // reset temp_string
            temp_string = "";

            // increase part;
            part++;
        }
        // not comma, but recording. Add to temp_string
        else if (recording)
            temp_string += metadata[i];

        // detected '=' start recording.
        else if (metadata[i] == '=') {
            recording = true;
        }
    }

    status = temp_string.substr(0, temp_string.length() - 2);
    Line* log_start = NULL;
    Line* log_end = NULL;
}

// A note to my partner:
// thanks mate :D
void TicketList::filterByTime(Time start, Time end, string substation)
{
    cout << "#######################\n#  Filtering by time. #\n#######################\n\nWe are searching in substation " << substation << " and between: " << start << " to " << end << "\n\nHere's what we found:\n.\n.\n";

    Ticket* traverse = firstTicket;
    while (traverse != NULL) {
        // within our time range and also matches substation
        if (traverse->firstLine->time > start && traverse->firstLine->time < end && traverse->substation == substation) {
            cout << *traverse;
        }
        traverse = traverse->next;
    }
}

// "For this question we assumed that we would be comparing this "similar tickets" relative to a ticket that an operator would already be looking at. And so in our function will pass the parameter Y as the number of similar tickets that we want to find, alongside another parameter which will contain the name of a file of a ticket that we want to compare to. And so this output of this function will output a Y number of similar tickets to ticket X."
void TicketList::filterBySubstation(string y, string X)
{
    // so in this case, we look at the substation name from string x. We don't actually have to look at the file itself, the filename will already tell us what to compare.

    // In this case, ticket X is our filename. We know the filename by looking at the Ticket.firstLine.remark comparisons.
}

void TicketList::filterByIssue(string searchMetadata, string z)
{
    double doubleQuery;
    int intQuery;
    // check what type it should be that we're looking for.
    if (searchMetadata == "voltage" || searchMetadata == "harmonic" || searchMetadata == "v_non_shunt") {
        doubleQuery = stod(z);
    } else if (searchMetadata == "address" || searchMetadata == "sector") {
        intQuery = stoi(z);
    }

    // massive if statement goes here. It just checks if the ticket that it's iterating is (within reasonable limits) similar to the constraint, and the searchMetadata parameter dictates which piece of metadata we are comparing to our baseline z (another parameter)
}

// this is a little more tricky to implement. Implement a way to search key words in the string. I think I'll need some testing in a separate file (test.cpp) or something.
void TicketList::filterByRemark(string k) { }

ostream& operator<<(ostream& out, Ticket& a)
{
    // yikes. We have to have a deterministic first three lines
    out << "Line,Time,Remark\n1," << a.firstLine->time.year << '_' << a.firstLine->time.month << '_' << a.firstLine->time.day << ' ' << pad_zeroes(a.firstLine->time.hour) << ':' << pad_zeroes(a.firstLine->time.minute) << ':' << pad_zeroes(a.firstLine->time.seconds) << '.' << to_string(a.firstLine->time.sub_second).substr(2) << ',' << a.firstLine->remark << ",ENE," << a.firstLine->address << ' ' << a.firstLine->substation << ' ' << a.firstLine->real_address << "\n,,\"STRUCTURE=" << a.structure << ", VOLTAGE=" << a.voltage << ", GROUND=" << a.ground << ", MSPLATE=" << a.msplate << ", HARMONIC=" << a.harmonic << ", V NON-SHUNT=" << a.v_non_shunt << ", STATUS=" << a.status << '\n';

    Ticket::Line* traverse = a.firstLine;
    while (traverse != NULL) {
        cout << traverse->line_num << ',' << traverse->time.year << '_' << traverse->time.month << '_' << traverse->time.day << ' ' << pad_zeroes(traverse->time.hour) << ':' << pad_zeroes(traverse->time.minute) << ':' << pad_zeroes(traverse->time.seconds) << '.' << to_string(traverse->time.sub_second).substr(2) << ',' << traverse->remark << '\n';
        traverse = traverse->next;
    }

    return out;
}
