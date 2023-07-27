#ifndef WINDOW_H
#define WINDOW_H

#include "Customer.h"

class Window {

   public:
    Window() = default;
    Window(office_name office);
    ~Window() = default;
    void assignCustomer(Customer customerEntered);
    void updateWindow();
    time_tick getTotalIdleTime();
    bool isDone();
    Customer returnDoneCustomer();

   private:
    time_tick idleTime, maxIdleTime, totalIdleTime;
    office_name office;
    bool finished;
    Customer customer;
};

#endif
