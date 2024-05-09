#include "hospitaldata.h"
#include <algorithm>
#include <cstddef>
#include <fstream>
#include <iostream>

using namespace std;

HospitalDatabase::HospitalDatabase()
{
    head = NULL;
}

HospitalDatabase::Hospital::Hospital(string name, string sub)
{
    hospital_name = name;
    substation = sub;
    next = NULL;
    team_head = NULL;
    team_tail = NULL;
}

HospitalDatabase::Hospital::Team::Surgeon::Surgeon(string n)
{
    full_name = n;
    next = NULL;
}

HospitalDatabase::Hospital::Team::Team(string team)
{
    trueTeamName = team;
    next = NULL;
    prev = NULL;
    surgery_head = NULL;
    surgery_tail = NULL;
    surgeon_head = NULL;
    surgeon_tail = NULL;

    total_difficulty = 0;
    total_time = 0;

    averageDifficulty = 0;
    averageTime = 0;

    number_of_surgeries = 0;

    points = 0;
}

void HospitalDatabase::Hospital::Team::addSurgery(const Time& st, const Time& et, const int& d, const int& min, const string& t)
{
    Surgery* newSurgery = new Surgery(st, et, d, min, t);
    newSurgery->next = surgery_head;
    if (surgery_head) {
        surgery_head->prev = newSurgery;
    }
    surgery_head = newSurgery;

    // add total difficulty
    total_difficulty += newSurgery->difficulty;

    // add total time.
    total_time += newSurgery->minutes;

    // increase number of surgeries for averages.
    number_of_surgeries++;

    // add total points.
    // using d^2/m algorithm (Multiplying by 100 to shift decimal spaces)
    points += 100 * ((double)newSurgery->difficulty * (double)newSurgery->difficulty) / (newSurgery->minutes);

    // change average values:
    averageDifficulty = (double)total_difficulty / number_of_surgeries;
    averageTime = total_time / number_of_surgeries;
}
void HospitalDatabase::Hospital::Team::addSurgeon(string n)
{
    Surgeon* newSurgeon = new Surgeon(n);
    newSurgeon->next = surgeon_head;
    surgeon_head = newSurgeon;
}

HospitalDatabase::Hospital::Team::Surgery::Surgery(const Time& st, const Time& et, const int& d, const int& min, const string& t)
{
    next = NULL;
    prev = NULL;

    difficulty = d;
    minutes = min;
    type = t;

    start_day = st;
    end_day = et;
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
    Team* traverse = team_head;

    while (traverse != NULL) {
        // found surgeon team to remove.
        // next to traverse is our target!
        if (traverse->next && traverse->next->trueTeamName == team) {
            // temp is our target.
            temp = traverse->next;

            // ([temp]) to be deleted
            // [traverse] ([temp]) [?temp->next]
            traverse->next = temp->next;

            // [traverse] ([temp]) [?temp->next]
            if (temp->next) {
                temp->next->prev = traverse;
            }
            cout << "Deleting: " << temp->trueTeamName;
            delete temp;
            return;
        } else if (traverse->trueTeamName == team) {
            // if this ever runs, then that means that it was the head!
            delete team_head;
            team_head = NULL;
        }
        // did not find it, and did not reach end.
        traverse = traverse->next;
    }
    // finished going through the entire list, and the surgeon team was still not found.
    cout << "Team was not found";
}

void HospitalDatabase::Hospital::sortTeams()
{
    bool sorted = false;
    while (!sorted) {
        sorted = true;
        Team* traverse = team_head;
        while (traverse != NULL) {
            // check that next exists and compare the points.
            if (traverse->next != NULL && traverse->next->points > traverse->points) {
                sorted = false;

                // do the swap

                // case where there are things in front and behind.
                 //WIlensky's Code
                if(traverse->next->next != NULL)
                {
                    traverse->prev->next = traverse->next;
                    traverse->prev = traverse->next;
                    traverse->next->prev = traverse->prev;
                    traverse->next = traverse->next->next;
                    traverse->next->prev->next = traverse;
                    traverse->next->prev = traverse;
                }
               
                
                //All of Stanley's Code
                // traverse->prev = traverse->prev->prev;
                // traverse->next->prev = traverse->prev->next;
                // traverse->prev->next->next = traverse->next;
                // traverse->prev->next->prev = traverse;
                // traverse->prev->next = traverse;
                // traverse->next = traverse->next->prev;

                // do case for where things are only in front

                // also do case for where things are only behind

                // also do case for where there are only two things.
            }
            else
                sorted = true;

            traverse = traverse->next;
        }
    }
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
void HospitalDatabase::displaySurgery(const string& hospital, const string& team)
{
    // find the hospital match.
    // then find the team in that hospital.
    // we do this because we might have a same team name across hospitals

    Hospital* hospital_traverse = head;
    while (hospital_traverse != NULL) {
        // check if we can find the hospital name!
        if (hospital_traverse->hospital_name == hospital) {
            break;
        }
        hospital_traverse = hospital_traverse->next;
    }

    if (hospital_traverse == NULL) {
        cout << "It seems that the hospital name " << hospital << " does not exist.\n";
        return;
    }

    // otherwise, we found the hospital. Next, search for the team
    Hospital::Team* team_traverse = hospital_traverse->team_head;
    while (team_traverse != NULL) {
        // check to see if we can find the team.
        if (team_traverse->trueTeamName == team) {
            break;
        }
        team_traverse = team_traverse->next;
    }

    // Search the team traverse. If it is blank, then it does not exist.
    if (team_traverse == NULL) {
        cout << "It seems that the team name " << team << " does not exist in hospital " << hospital << ".\n";
        return;
    }

    // now print everything. We know that it exists.
    Hospital::Team::Surgery* surgery_traverse = team_traverse->surgery_head;
    // 100*d^2/m
    cout << "Team: " << team << " which averages earning points around: " << 100 * team_traverse->averageDifficulty * team_traverse->averageDifficulty / team_traverse->averageTime << " points per hour.\n";
    while (surgery_traverse != NULL) {
        cout << surgery_traverse->start_day << " to " << surgery_traverse->end_day << " at " << hospital_traverse->hospital_name << " powered by " << hospital_traverse->substation << " with type: " << surgery_traverse->type << ", difficulty: " << surgery_traverse->difficulty << " taking time: " << surgery_traverse->minutes << "\n";

        surgery_traverse = surgery_traverse->next;
    }
}

void HospitalDatabase::readLine(string line)
{
    // debug
    // cout << line << '\n';

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

    // searching to see if the hospital exists.
    Hospital* hospital_traverse = head;
    while (hospital_traverse != NULL) {
        // Searching for hospital.
        if (hospital_traverse->hospital_name == hospital) {
            break;
        }
        hospital_traverse = hospital_traverse->next;
    }

    // check if hospital_traverse returned null. If it did, that means that the hospital was not found.
    // just add onto the database.
    if (!hospital_traverse) {
        Hospital* newHospital = new Hospital(hospital, substation);
        newHospital->next = head;
        head = newHospital;
        hospital_traverse = newHospital;
    }

    // at this point of the code, all we know for a fact is that the line that is read will be associated with the hospital that hospital_traverse is pointing to.

    // traverse through the hospital to see if you can find the team. If it cannot, then add a team to the hospital using the addTeam method.
    Hospital::Team* team_traverse = hospital_traverse->team_head;
    while (team_traverse != NULL) {
        if (team_name == team_traverse->trueTeamName) {
            break;
        }
        team_traverse = team_traverse->next;
    }

    // apparently we couldn't find the team, so we made the team.
    if (!team_traverse) {
        Hospital::Team* newTeam = new Hospital::Team(team_name);
        newTeam->next = hospital_traverse->team_head;
        hospital_traverse->team_head = newTeam;
        team_traverse = newTeam;
    }

    // at this point of the code, all we know for a fact is that the team_traverse pointer now holds the memory address of where the team associated with the surgery is, so we can just call addSurgery on it.

    // Anyways... I bet you that the addSurgery method will be called 100 % of the time, so figure out how to integrate that with reading lines. There's a reason why all of these methods are privated anyways. (I'm slowly losing my sanity)
    team_traverse->addSurgery(start_time, end_time, difficulty_level, surgery_time, surgery_type);

    // also worthy to note that the addSurgery method will be called within the team, so we're going to need to use team_traverse'
}

void HospitalDatabase::listSurgeriesAtHospital(const string& h, Time s, Time e) const
{
    if (e < s) {
        cout << "Check your bounds.";
    }

    Hospital* traverse = head;
    while (traverse != NULL) {
        if (traverse->hospital_name == h) {
            break;
        }
        traverse = traverse->next;
    }
    if (!traverse) {
        cout << "I could not find the hospital name: " << h << '\n';
        return;
    }
    cout << "Listing all surgeries at hospital " << h << " between " << s << " and " << e << '\n';

    // iterate through all team
    Hospital::Team* team_traverse = traverse->team_head;
    while (team_traverse != NULL) {
        cout << "Here is a list done by the team: " << team_traverse->trueTeamName << '\n';
        Hospital::Team::Surgery* surgery_traverse = team_traverse->surgery_head;
        int i = 1;
        while (surgery_traverse != NULL) {
            cout << i++ << ": " << surgery_traverse->start_day << " to " << surgery_traverse->end_day << " difficulty: " << surgery_traverse->difficulty << " time taken: " << surgery_traverse->minutes << " and type " << surgery_traverse->type << '\n';
            surgery_traverse = surgery_traverse->next;
        }
        team_traverse = team_traverse->next;
    }
    // iterate through the team sureries
}

void HospitalDatabase::removeSurgeon(const string& h, const string& t, const string& f)
{
    Hospital* traverse = head;
    while (traverse != NULL) {
        if (traverse->hospital_name == h) {
            break;
        }
        traverse = traverse->next;
    }
    if (!traverse) {
        cout << "I could not find the hospital name: " << h << '\n';
        return;
    }

    // iterate through all team
    Hospital::Team* team_traverse = traverse->team_head;
    while (team_traverse != NULL) {
        if (team_traverse->trueTeamName == t) {
            break;
        }
        team_traverse = team_traverse->next;
    }
    if (!team_traverse) {
        cout << "Team '" << t << "' was not found.\n";
        return;
    }

    Hospital::Team::Surgeon* surgeon_traverse = team_traverse->surgeon_head;
    while (surgeon_traverse != NULL) {
        if (surgeon_traverse->next && surgeon_traverse->next->full_name == f) {
            // [surgeon_traverse] ([surgeon_traverse->next]) [?surgeon_traverse->next->next]
            surgeon_traverse->next = surgeon_traverse->next->next;
            delete surgeon_traverse->next;
            break;
        }
        if (surgeon_traverse->full_name == f) {
            // if this runs then that means that it is the first (head) surgeon we want to remove.
            delete surgeon_traverse;
            team_traverse->surgeon_head = NULL;
        }
        surgeon_traverse = surgeon_traverse->next;
    }
    // insanity is repeating the same thing over and over. I think I'm going insane.
    // - Pete Aptenodytes Forsteri
    if (!surgeon_traverse) {
        cout << "Surgeon by name " << f << "  was not found in team " << t << '\n';
        return;
    }
}
