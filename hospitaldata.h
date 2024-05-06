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

            public:
                Surgery();
            };

        public:
            int averageTime;
            int averageDificiulty;
            int points;
            string part;
            // ensure that each team is a doublylinked list of surgeries
        private:
            string trueTeamName;
            Surgery* head;
            Surgery* tail;
            Team* next;
            Team* prev;

            void addSurgery();
        };

    private:
        Team* head;
        Team* tail;

    public:
        void addTeam(string team);
        void removeTeam(string team);

        int CAP;
    };
};
