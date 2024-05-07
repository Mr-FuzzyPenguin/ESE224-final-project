#include "projectutils.h"
#include <iostream>
#include <string>
using namespace std;

class HospitalDatabase {
    class Hospital {
        class Team {
            class Surgery {
            private:
                // Making it a node
                Surgery* next;
                Surgery* prev;

                int difficulty;
                int minutes;
                string type;
                Time start_day;
                Time end_day;

            public:
                Surgery(const int& d, const int& m, const string& t, const string& start_time, const string& end_time);
            };

            class Surgeon {
            private:
                Surgeon* next;

            public:
                string name;
                Surgeon(string n);
            };

        public:
            int averageTime;
            int averageDifficulty;
            int points;
            string part;
            int teamNumber;

            // ensure that each team is a doublylinked list of surgeries
            Team(string team);

        private:
            string trueTeamName;

            Surgery* surgery_head;
            Surgery* surgery_tail;

            Surgeon* surgeon_head;
            Surgeon* surgeon_tail;

            Team* next;
            Team* prev;

            void addSurgery();
            void addSurgeon();
            friend class HospitalDatabase;
        };

    private:
        Team* team_head;
        Team* team_tail;

    public:
        void addTeam(string team);
        void removeTeam(string team);
        string hospital_name;

        int CAP;
        Hospital();
        friend class HospitalDatabase;
    };

public:
    HospitalDatabase();
    Hospital* head;
    void readFile(string file);

private:
    void readLine(string line);
};
