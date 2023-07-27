#ifndef CUSTOMER_H
#define CUSTOMER_H

#include <string.h>

#include "ListQueue.h"

#define REGISTRAR 'R'
#define CASHIER 'C'
#define FINANCIAL_AID 'F'

typedef int time_tick;
typedef char office_name;

class Customer {
   public:
    Customer() = default;
    Customer(time_tick remainingRegistrar, time_tick remainingCashier, time_tick remainingFinancialAid, time_tick starting, char *offices_array);
    Customer(bool active);
    ~Customer() = default;

    time_tick getWaitTime();
    time_tick getArrivalTime();

    void updateCustomer();
    void setOfficesQueue(char *offices);
    void changeCurrentOffice(office_name office);

    office_name getNext();

    bool isWaiting();
    bool finished();
    bool isactive();

   private:
    time_tick waitTime,
        startingTime;

    time_tick remainingRegistrarOffice,
        remainingCashierOffice,
        remainingFinancialAidOffice;

    office_name currentOffice;

    bool active;

    ListQueue<char> *offices;
};

#endif
