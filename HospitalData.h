#include <iostream>
#include "projectutils.h"
#include <string>
using namespace std;

class HospitalData 
{
    class Substation
    {
        class Team
            {
                
                class Surgery
                {
                    //Making it a node
                    Surgery *next;
                    Surgery *prev;
                    //metadata
                    string name;
                    string date;
                    string time;
                    string room;
                    string surgeon;
                    string anesthesiologist;
                    string nurse;
                    string patient;
                    string status;
                };
                public: 
                int avergaeTime;
                int averageDifiiulty;
                string name; 
                //ensure that each team is a doublylinked list of surgeries
                private: 
                Surgery *head; 
                Surgery *tail;
                public: 
                Team *next; 
                Team *prev;
            };
            private: 
            Team *head; 
            Team *tail; 
            public: 
            string bestTeam; 
            string worstTeam;
            
    };
    Substation EB; 
    Substation RL; 
    Substation OF;
    Substation TM; 
    Substation HD; 
    //yea ask me if you have any questions
};