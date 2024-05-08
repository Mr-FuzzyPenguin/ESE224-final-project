#include "projectutils.h"
#include <iostream>
#include <string>
using namespace std;

class HospitalDatabase {
    class Hospital {
        class Team {
            class Surgery {
            private:
                Surgery* next;
                Surgery* prev;

                int difficulty;
                int minutes;
                string type;
                Time start_day;
                Time end_day;

            public:
                Surgery();
                Surgery(const Time& st, const Time& et, const int& d, const int& min, const string& t);
                friend class HospitalDatabase;
            };

            class Surgeon {
            private:
                Surgeon* next;

            public:
                string name;
                Surgeon(string n);
                friend class HospitalDatabase;
            };

        public:
            double averageDifficulty;
            int averageTime;
            string part;

            // ensure that each team is a doublylinked list of surgeries
            Team(string team);

        private:
            // statistics
            int total_difficulty;
            int total_time;

            int number_of_surgeries;

            double points;

            // team info
            string trueTeamName;

            Surgery* surgery_head;
            Surgery* surgery_tail;

            Surgeon* surgeon_head;
            Surgeon* surgeon_tail;

            Team* next;
            Team* prev;

            void addSurgery(const Time& st, const Time& et, const int& d, const int& min, const string& t);
            void displaySurgery();

            void addSurgeon(string n);

            friend class HospitalDatabase;
        };

    private:
        Team* team_head;
        Team* team_tail;

    public:
        void addTeam(string team);
        void removeTeam(string team);

        string hospital_name;
        string substation;

        int CAP;
        Hospital(string name, string sub);
        friend class HospitalDatabase;

    private:
        Hospital* next;
    };

public:
    HospitalDatabase();
    Hospital* head;
    void displaySurgery(const string& hospital, const string& team);
    void listSurgeriesAtHospital(const string& h, Time s, Time e) const;
    void readFile(string file);

private:
    void readLine(string line);
};
