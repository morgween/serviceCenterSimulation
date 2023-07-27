#include "Customer.h"
Customer::Customer(time_tick remainingRegistrarOffice, time_tick remainingCashierOffice, time_tick remainingFinancialAidOffice, time_tick startingTime, char *offices_array) {
    this->remainingRegistrarOffice = remainingRegistrarOffice;
    this->remainingCashierOffice = remainingCashierOffice;
    this->remainingFinancialAidOffice = remainingFinancialAidOffice;
    this->currentOffice = 'n';
    this->startingTime = startingTime;
    this->offices = new ListQueue<char>();
    this->active = false;
    setOfficesQueue(offices_array);
}
Customer::Customer(bool active) {
    this->remainingRegistrarOffice = 0;
    this->remainingCashierOffice = 0;
    this->remainingFinancialAidOffice = 0;
    this->currentOffice = 'n';
    this->startingTime = 0;
    this->active = active;
    this->offices = nullptr;
}

time_tick Customer::getWaitTime() {
    return (active == true) ? 0 : waitTime;
}

time_tick Customer::getArrivalTime() {
    return startingTime;
}

void Customer::updateCustomer() {
    if (finished() || isactive()) {
        return;
    }
    if (currentOffice == 'n') {
        waitTime++;
        return;
    } else {
        switch (currentOffice) {
            case REGISTRAR:
                remainingRegistrarOffice--;
                if (remainingRegistrarOffice <= 0) {
                    currentOffice = 'n';
                }
                break;
            case CASHIER:
                remainingCashierOffice--;
                if (remainingCashierOffice <= 0) {
                    currentOffice = 'n';
                }
                break;
            case FINANCIAL_AID:
                remainingFinancialAidOffice--;
                if (remainingFinancialAidOffice <= 0) {
                    currentOffice = 'n';
                }
                break;
        }
    }
}
void Customer::setOfficesQueue(char *offices) {
    for (int i = 0; i < 3; i++) {
        this->offices->add(offices[i]);
    }
}
void Customer::changeCurrentOffice(office_name office) {
    waitTime = 0;
    currentOffice = office;
}

office_name Customer::getNext() {
    if (offices->isEmpty()) {
        return 'n';
    }
    return offices->remove();
}

bool Customer::isWaiting() {
    return currentOffice == 'n';
}

bool Customer::finished() {
    return remainingRegistrarOffice == 0 && remainingCashierOffice == 0 && remainingFinancialAidOffice == 0;
}

bool Customer::isactive() {
    return active;
}