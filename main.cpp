#include <iostream>

#include "ServiceCenter.h"

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Wrong number of arguments given. format: \n./main <input_file>" << std::endl;
        return 0;
    }
    std::string file = argv[1];

    ServiceCenter* center = new ServiceCenter();

    center->processInput(file);
    while (true) {
        center->updateCenter();
        if (center->isDone()) {
            break;
        }
    }
    center->displayMetrics();
    return 0;
}