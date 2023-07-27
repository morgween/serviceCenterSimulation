#ifndef SERVICE_CENTER_H
#define SERVICE_CENTER_H

#include <fstream>
#include <sstream>
#include <string>

#include "ListQueue.h"
#include "Office.h"
#include "Window.h"
#include "Customer.h"

class ServiceCenter {
   public:
    ServiceCenter() = default;
    ~ServiceCenter();

    void processInput(const std::string inputFile);
    void updateCenter();
    void displayMetrics();
    
    bool isDone();

   private:

    int numberOfRegistrarWindows;
    int numberOfCashierWindows;
    int numberOfFinancialAidWindows;

    int currentTick;

    Office* registrarOffice;
    Office* cashierOffice;
    Office* financialAidOffice;

    ListQueue<Customer> students;

    void initializeOffices();
    void setupOffices();
};

#endif
