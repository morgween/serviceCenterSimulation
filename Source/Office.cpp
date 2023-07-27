#include "Office.h"

Office::Office() {
    customersServed = 0;
    maxWindowIdleTime = 0;
    totalWindowIdleTime = 0;
    maxCustomerWaitTime = 0;
    totalCustomerWaitTime = 0;
    windows = new DblList<Window>();
    customersWaitList = new ListQueue<Customer>();
    customersDoneList = new ListQueue<Customer>();
}
Office::Office(int numWindows, office_name office) {
    customersServed = 0;
    maxWindowIdleTime = 0;
    totalWindowIdleTime = 0;
    maxCustomerWaitTime = 0;
    totalCustomerWaitTime = 0;
    windows = new DblList<Window>();
    customersWaitList = new ListQueue<Customer>();
    customersDoneList = new ListQueue<Customer>();
    for (int i = 0; i < numWindows; i++) {
        windows->addFront(Window(office));
    }
    windowsNum = numWindows;
    this->office = office;
}

void Office::updateOffice() {
    if (windows->isEmpty() && customersWaitList->isEmpty()) {
        return;
    }
    int windowsActiveSize = windows->size();
    for (int i = 0; i < windowsActiveSize; i++) {
        Window &window = windows->at(i);
        if (window.isDone() && !customersWaitList->isEmpty()) {
            Customer newCustomer = customersWaitList->remove();
            time_tick waitTime = newCustomer.getWaitTime();
            if (waitTime > 10) waitedMoreThanTen++;
            if (waitTime > maxCustomerWaitTime) maxCustomerWaitTime = waitTime;
            totalCustomerWaitTime += waitTime;
            window.assignCustomer(newCustomer);
        }

        window.updateWindow();

        if (window.isDone()) {
            Customer customer = window.returnDoneCustomer();
            if (!customer.isactive()) {
                customersDoneList->add(customer);
                customersServed++;
            }
        }
    }

    ListQueue<Customer> *temp = new ListQueue<Customer>();
    while (!customersWaitList->isEmpty()) {
        Customer customer = customersWaitList->remove();
        customer.updateCustomer();
        temp->add(customer);
    }
    while (!temp->isEmpty()) {
        customersWaitList->add(temp->remove());
    }
}

void Office::addCustomer(Customer *customer) {
    customersWaitList->add(*customer);
}

void Office::calculateIdleTime() {
    for (int i = 0; i < windows->size(); i++) {
        Window window = windows->get(i);
        time_tick idleTime = window.getTotalIdleTime();
        totalWindowIdleTime += idleTime;
        if (idleTime > 5) idledMoreThanFive++;
        if (maxWindowIdleTime < idleTime) maxWindowIdleTime = idleTime;
    }
}

time_tick Office::getMaxIdleTime() {
    return maxWindowIdleTime;
}

time_tick Office::getMaxWaitTime() {
    return maxCustomerWaitTime;
}

float Office::getMeanIdleTime() {
    if (windowsNum == 0) {
        return 0;
    }
    return static_cast<float>(totalWindowIdleTime) / windowsNum;
}

float Office::getMeanWaitTime() {
    if (customersServed == 0) {
        return 0;
    }
    return static_cast<float>(totalCustomerWaitTime) / customersServed;
}

int Office::getWindowsNum() {
    return windowsNum;
}

int Office::sizeOfReturnCustomers() {
    return customersDoneList->size();
}

int Office::getWaitedMoreThanTen() {
    return waitedMoreThanTen;
}

int Office::getIdledMoreThanFive() {
    return idledMoreThanFive;
}

Customer *Office::returnReadyCustomer() {
    if (customersDoneList->isEmpty()) return nullptr;
    Customer *array_of_customers = new Customer[customersDoneList->size()];
    for (int i = 0; i < customersDoneList->size(); i++) {
        array_of_customers[i] = customersDoneList->remove();
    }
    return array_of_customers;
}

bool Office::isDone() {
    if (!customersWaitList->isEmpty()) return false;
    size_t windowsSize = windows->size();
    for (int i = 0; i < windowsSize; i++) {
        Window window = windows->get(i);
        if (!window.isDone()) return false;
    }
    return true;
}