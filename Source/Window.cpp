#include "Window.h"

Window::Window(office_name office) {
    idleTime = 0;
    totalIdleTime = 0;
    maxIdleTime = 0;
    finished = true;
    this->office = office;
    customer = Customer(true);
}

void Window::assignCustomer(Customer customerEntered) {
    if (idleTime > maxIdleTime) {
        maxIdleTime = idleTime;
    }
    totalIdleTime += idleTime;
    idleTime = 0;
    customerEntered.changeCurrentOffice(office);
    this->customer = customerEntered;
    finished = false;
}

void Window::updateWindow() {
    if (customer.isactive() || isDone()) {
        idleTime++;
    } else {
        customer.updateCustomer();
        if (customer.isWaiting()) finished = true;
    }
}

time_tick Window::getTotalIdleTime() {
    if(idleTime!=0) totalIdleTime += idleTime;
    return totalIdleTime;
}

bool Window::isDone() {
    return finished;
}

Customer Window::returnDoneCustomer() {
    Customer tmp = customer;
    customer = Customer(true);
    finished = true;
    return tmp;
}
