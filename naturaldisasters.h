class Outage {
public:
    int year;
    int tree;
    int motor;
    int insulator;

    Outage* next;
    Outage(const int& y, const int& t, const int& m, const int& i);
};

class Outages {
public:
    Outage* tail;
    void add_outage(Outage* new_outage);
    Outages();
};
