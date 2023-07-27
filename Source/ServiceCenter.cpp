#include "ServiceCenter.h"

ServiceCenter::~ServiceCenter() {
    delete registrarOffice;
    delete cashierOffice;
    delete financialAidOffice;
};

void ServiceCenter::setupOffices() {
    if (students.isEmpty()) {
        return;
    }

    ListQueue<Customer> tempQueue{};
    while (!students.isEmpty()) {
        Customer student = students.remove();
        if (student.getArrivalTime() <= currentTick) {
            office_name office = student.getNext();
            switch (office) {
                case REGISTRAR:
                    registrarOffice->addCustomer(&student);
                    break;
                case CASHIER:
                    cashierOffice->addCustomer(&student);
                    break;
                case FINANCIAL_AID:
                    financialAidOffice->addCustomer(&student);
                    break;
                default:
                    if (student.finished())
                        continue;
            }
        } else
            tempQueue.add(student);
    }
    while (!tempQueue.isEmpty()) {
        students.add(tempQueue.remove());
    }
}

void ServiceCenter::initializeOffices() {
    this->registrarOffice = new Office(numberOfRegistrarWindows, REGISTRAR);
    this->cashierOffice = new Office(numberOfCashierWindows, CASHIER);
    this->financialAidOffice = new Office(numberOfFinancialAidWindows, FINANCIAL_AID);
}

void ServiceCenter::processInput(const std::string filePath) {
    try {
        currentTick = 1;

        Customer student;

        int student_count;
        time_tick registrar_time, cashier_time, financial_aid_time, starting_time;

        std::ifstream file(filePath);

        std::string line;

        if (!file.is_open()) {
            std::cerr << "Failed to open the file: " << filePath << std::endl;
            exit(-1);
        }

        if (std::getline(file, line)) {
            numberOfRegistrarWindows = std::stoi(line);
        }
        if (std::getline(file, line)) {
            numberOfCashierWindows = std::stoi(line);
        }
        if (std::getline(file, line)) {
            numberOfFinancialAidWindows = std::stoi(line);
        }

        initializeOffices();

        while (true) {
            std::getline(file, line);
            if (line == "END") {
                break;
            }

            starting_time = std::stoi(line);

            std::getline(file, line);

            student_count = std::stoi(line);
            office_name offices[3];
            time_tick requiredTime[3];

            for (int i = 0; i < student_count; ++i) {
                std::getline(file, line);
                std::stringstream iss(line);
                int tokenI;
                char tokenC;

                for (int j = 0; j < 3; j++) {
                    iss >> tokenI;
                    requiredTime[j] = tokenI;
                }
                for (int k = 0; k < 3; k++) {
                    iss >> tokenC;
                    offices[k] = tokenC;
                }

                switch (offices[0]) {
                    case REGISTRAR:
                        registrar_time = requiredTime[0];
                        break;
                    case CASHIER:
                        cashier_time = requiredTime[0];
                        break;
                    case FINANCIAL_AID:
                        financial_aid_time = requiredTime[0];
                        break;
                }
                switch (offices[1]) {
                    case REGISTRAR:
                        registrar_time = requiredTime[1];
                        break;
                    case CASHIER:
                        cashier_time = requiredTime[1];
                        break;
                    case FINANCIAL_AID:
                        financial_aid_time = requiredTime[1];
                        break;
                }
                switch (offices[2]) {
                    case REGISTRAR:
                        registrar_time = requiredTime[2];
                        break;
                    case CASHIER:
                        cashier_time = requiredTime[2];
                        break;
                    case FINANCIAL_AID:
                        financial_aid_time = requiredTime[2];
                        break;
                }
                student = Customer(registrar_time, cashier_time, financial_aid_time, starting_time, offices);
                students.add(student);
            }
        }
        file.close();
    } catch (std::exception& e) {
        std::cerr << "Wrong input file given " << std::endl;
        exit(-1);
    }
}

void ServiceCenter::updateCenter() {
    setupOffices();

    cashierOffice->updateOffice();
    financialAidOffice->updateOffice();
    registrarOffice->updateOffice();

    currentTick++;

    size_t sizeOfReturnedCustomers = cashierOffice->sizeOfReturnCustomers();
    Customer* returnedCustomers = cashierOffice->returnReadyCustomer();

    if (returnedCustomers != nullptr) {
        for (int i = 0; i < sizeOfReturnedCustomers; i++) {
            if (!returnedCustomers[i].finished()) {
                students.add(returnedCustomers[i]);
                delete &returnedCustomers[i];
            }
        }
    }
    sizeOfReturnedCustomers = financialAidOffice->sizeOfReturnCustomers();
    returnedCustomers = financialAidOffice->returnReadyCustomer();
    if (returnedCustomers != nullptr) {
        for (int i = 0; i < sizeOfReturnedCustomers; i++) {
            if (!returnedCustomers[i].finished()) {
                students.add(returnedCustomers[i]);
                delete &returnedCustomers[i];
            }
        }
    }
    sizeOfReturnedCustomers = registrarOffice->sizeOfReturnCustomers();
    returnedCustomers = registrarOffice->returnReadyCustomer();
    if (returnedCustomers != nullptr) {
        for (int i = 0; i < sizeOfReturnedCustomers; i++) {
            if (!returnedCustomers[i].finished()) {
                students.add(returnedCustomers[i]);
                delete &returnedCustomers[i];
            }
        }
    }
}

void ServiceCenter::displayMetrics() {
    cashierOffice->calculateIdleTime();
    registrarOffice->calculateIdleTime();
    financialAidOffice->calculateIdleTime();
    std::cout << "Cashier's Office:" << std::endl;
    std::cout << "Mean student waitime: " << cashierOffice->getMeanWaitTime() << " tick(s)" << std::endl;
    std::cout << "Mean window idle time: " << cashierOffice->getMeanIdleTime() << " tick(s)" << std::endl;
    std::cout << "Longest student wait time: " << cashierOffice->getMaxWaitTime() << " tick(s)" << std::endl;
    std::cout << "Longest window idle time: " << cashierOffice->getMaxIdleTime() << " tick(s)" << std::endl;
    std::cout << "=============" << std::endl;

    std::cout << "Financial Aid Office:" << std::endl;
    std::cout << "Mean student waitime: " << financialAidOffice->getMeanWaitTime() << " tick(s)" << std::endl;
    std::cout << "Mean window idle time: " << financialAidOffice->getMeanIdleTime() << " tick(s)" << std::endl;
    std::cout << "Longest student wait time: " << financialAidOffice->getMaxWaitTime() << " tick(s)" << std::endl;
    std::cout << "Longest window idle time: " << financialAidOffice->getMaxIdleTime() << " tick(s)" << std::endl;
    std::cout << "=============" << std::endl;

    std::cout << "Registrar's Office:" << std::endl;
    std::cout << "Mean student waitime: " << registrarOffice->getMeanWaitTime() << " tick(s)" << std::endl;
    std::cout << "Mean window idle time: " << registrarOffice->getMeanIdleTime() << " tick(s)" << std::endl;
    std::cout << "Longest student wait time: " << registrarOffice->getMaxWaitTime() << " tick(s)" << std::endl;
    std::cout << "Longest window idle time: " << registrarOffice->getMaxIdleTime() << " tick(s)" << std::endl;
    std::cout << "=============" << std::endl;

    std::cout << "Number of students waiting over 10 minutes across all offices: " << cashierOffice->getWaitedMoreThanTen() + financialAidOffice->getWaitedMoreThanTen() + registrarOffice->getWaitedMoreThanTen()
              << " tick(s)" << std::endl;
    std::cout << "Number of windows idle for over 5 minutes across all offices: " << cashierOffice->getIdledMoreThanFive() + financialAidOffice->getIdledMoreThanFive() + registrarOffice->getIdledMoreThanFive()
              << " tick(s)" << std::endl;
}

bool ServiceCenter::isDone() {
    if (!students.isEmpty()) return false;
    return registrarOffice->isDone() && cashierOffice->isDone() && financialAidOffice->isDone();
}