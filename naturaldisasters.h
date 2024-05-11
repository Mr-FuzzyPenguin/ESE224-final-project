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
    double predict_next_year_performance(const int& surgery_points, const int& interruption_hours);
    int predict_power_outage();

    void add_power_outage_time(const int& t);
    void reset_power_outage_time();

    void add_customer_hr_interrupt(const int& t);
    void reset_customer_hr_interrupt();

private:
    int total_hours_out;
    int total_customers_hours_interrupted;
    Outages();
};
