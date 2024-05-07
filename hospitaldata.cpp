#include "hospitaldata.h"
#include <fstream>
#include <iostream>

using namespace std;

HospitalDatabase::HospitalDatabase()
{
    head = NULL;
}

HospitalDatabase::Hospital::Hospital()
{
    team_head = NULL;
    team_tail = NULL;
}

HospitalDatabase::Hospital::Team::Team(string team)
{
    next = NULL;
    prev = NULL;
    surgery_head = NULL;
    surgery_tail = NULL;
    surgeon_head = NULL;
    surgeon_tail = NULL;
    averageTime = 0;
    averageDifficulty = 0;
    points = 0;
    teamNumber = 0;
}

void HospitalDatabase::Hospital::Team::addSurgery() { }
void HospitalDatabase::Hospital::Team::addSurgeon() { }

HospitalDatabase::Hospital::Team::Surgery::Surgery(const int& d, const int& m, const string& t, const string& start_time, const string& end_time)
{
}

void HospitalDatabase::Hospital::addTeam(string team)
{
    // put team name into new team
    Team* newTeam = new Team(team);
    if (team_head == NULL) {
        team_head = newTeam;
    } else {
        newTeam->next = newTeam;
    }
}

void HospitalDatabase::Hospital::removeTeam(string team)
{
    Team* temp;
    Team* traverse;

    while (traverse != NULL) {
        // found surgeon team to remove.
        if (traverse->next && traverse->next->trueTeamName == team) {
            temp = traverse->next;
            traverse->next = temp->next;
            delete temp;
            return;
        }
        // did not find it, and did not reach end.
        traverse = traverse->next;
    }
    // finished going through the entire list, and the surgeon team was still not found.
    cout << "Team was not found";
}

void HospitalDatabase::readFile(string file)
{
    ifstream hospitalFile;
    char temp;
    string line = "";
    int line_num = 1;
    hospitalFile.open(file, ifstream::in);
    while (hospitalFile.good()) {
        temp = (char)hospitalFile.get();
        if (temp != '\n') {
            line += temp;
        } else {
            if (line_num >= 2) {
                readLine(line);
            }
            line_num++;
            line = "";
        }
    }
}
void HospitalDatabase::readLine(string line)
{
    cout << line << '\n';

    int time_step = 0;

    // variables to be sorted later
    int start_month;
    int start_day;
    int start_year;

    int end_month;
    int end_day;
    int end_year;

    string substation_name;
    string team_name;
    string hospital;
    string surgery_type;
    int surgery_time;
    int difficulty_level;

    int temp_int = 0;
    string temp_string = "";

    bool start = true;

    Time start_time;
    Time end_time;

    string substation;

    // read up to a comma.
    int i = 0;

    // read the first date:
    while (i < line.length() && line[i] != ',') {
        if (line[i] == '/') {
            switch (time_step) {
            case 0:
                start_month = temp_int;
                break;
            case 1:
                start_day = temp_int;
                break;
            }
            time_step++;
            temp_int = 0;
        } else if (line[i] != ',') {
            temp_int = temp_int * 10 + line[i] - '0';
        }
        i++;
    }
    start_year = temp_int;

    // reset everything again before running.
    time_step = 0;
    temp_int = 0;
    i++;

    // read the second date:
    while (i < line.length() && line[i] != ',') {
        if (line[i] == '/') {
            switch (time_step) {
            case 0:
                end_month = temp_int;
                break;
            case 1:
                end_day = temp_int;
                break;
            }
            time_step++;
            temp_int = 0;
        } else if (line[i] != ',') {
            temp_int = temp_int * 10 + line[i] - '0';
        }
        i++;
    }
    end_year = temp_int;

    // set the start ane end times based on what was already parsed. Continue parsing.
    start_time = Time(start_year, start_month, start_day);
    end_time = Time(end_year, end_month, end_day);

    // parser goes here.. parser go brr..
    // reset everything again before running
    i++;
    while (i < line.length() && line[i] != ',') {
        temp_string += line[i];
        i++;
    }
    substation = temp_string;

    // reset everything again before running
    temp_string = "";
    i++;
    while (i < line.length() && line[i] != ',') {
        temp_string += line[i];
        i++;
    }
    hospital = temp_string;

    // reset everything again before running
    // dang it man, DRY programming much? This should be in project utils. do better smh - Pete Aptenodytes Forsteri
    i++;
    temp_string = "";
    while (i < line.length() && line[i] != ',') {
        temp_string += line[i];
        i++;
    }
    team_name = temp_string;

    i++;
    temp_string = "";
    while (i < line.length() && line[i] != ',') {
        temp_string += line[i];
        i++;
    }
    surgery_type = temp_string;

    // for surgery time
    temp_int = 0;
    i++;
    while (i < line.length() && line[i] != ',') {
        temp_int = temp_int * 10 + line[i] - '0';
        i++;
    }
    surgery_time = temp_int;

    // for surgery difficulty
    temp_int = 0;
    i++;
    while (i < line.length() && line[i] != ',') {
        temp_int = temp_int * 10 + line[i] - '0';
        i++;
    }
    difficulty_level = temp_int;
}
