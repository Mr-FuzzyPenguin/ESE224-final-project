#include "naturaldisasters.h"
#include <iostream>
#include <math.h>
using namespace std;

Outage::Outage(const int& y, const int& t, const int& m, const int& i)
{
    year = y;
    tree = t;
    motor = m;
    insulator = i;
    next = NULL;
};

Outages::Outages()
{
    tail = NULL;
    total_hours_out = 0;
    total_customers_hours_interrupted = 0;
};

void Outages::add_outage(Outage* new_outage)
{
    if (tail) {
        tail->next = new_outage;
    }
    tail = new_outage;
}

double Outages::predict_next_year_performance(const int& surgery_points, const int& interruption_hours)
{
    return (double)surgery_points / (interruption_hours + 1);
}

int predict_power_outage(const int& ticket_count, const int& hospital_hours_out)
{
    return ticket_count * hospital_hours_out;
}

void Outages::add_power_outage_time(const int& t)
{
    total_hours_out += t;
}

void Outages::reset_power_outage_time()
{
    total_hours_out = 0;
}

void Outages::add_customer_hr_interrupt(const int& t)
{
    total_customers_hours_interrupted += t;
}

void Outages::reset_customer_hr_interrupt()
{
    total_customers_hours_interrupted = 0;
}
