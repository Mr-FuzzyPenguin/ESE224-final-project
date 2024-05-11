#include "naturaldisasters.h"
#include <cstddef>

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
};

void Outages::add_outage(Outage* new_outage)
{
    if (tail) {
        tail->next = new_outage;
    }
    tail = new_outage;
}
