#ifndef OFFICE_H
#define OFFICE_H

#include "Customer.h"
#include "DblList.h"
#include "ListQueue.h"
#include "Window.h"

class Office {
   public:
    Office();
    Office(int numWindows, office_name officeName);
    ~Office()=default;

    void updateOffice();
    void addCustomer(Customer *customer);
    void calculateIdleTime();

    float getMeanIdleTime();
    float getMeanWaitTime();

    time_tick getMaxIdleTime();
    time_tick getMaxWaitTime();

    int getWindowsNum();
    int sizeOfReturnCustomers();
    int getWaitedMoreThanTen();
    int getIdledMoreThanFive();

    Customer *returnReadyCustomer();

    bool isDone();

   private:
    time_tick maxWindowIdleTime, totalWindowIdleTime, idledMoreThanFive;
    time_tick maxCustomerWaitTime, totalCustomerWaitTime, waitedMoreThanTen;
    int customersServed, windowsNum;
    DblList<Window> *windows;
    ListQueue<Customer> *customersWaitList;
    ListQueue<Customer> *customersDoneList;
    office_name office;
};

#endif
