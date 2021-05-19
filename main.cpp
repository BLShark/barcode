#include <iostream>
#include <list>
#include <sstream>
#include <cmath>

#include "barcode_analyzer.h"

auto read_sensors = [](barcode& b1) {
    std::cout << "\nEnter the data from them: ";
    std::string line;
    getline(std::cin, line);
    std::stringstream ss(line);
    while (1)
    {
        double num;
        ss >> num;
        if (!ss)
            break;
        b1 << num;
    }
};

int main()
{
    std::cout << "Hello Chaos group!" << std::endl;

    uint16_t sensor_numbers = 0;
    std::cout << "Enter numbers of sensors: ";
    std::cin>> sensor_numbers;
    std::cin.ignore();

    std::vector<barcode> barcodes;
    {
        barcode b1;
        read_sensors(b1);
        barcodes.push_back(b1);
    }

    std::cout<<"\nEnter numbers of tests: ";
    uint16_t number_of_tests = 0;
    std::cin>>number_of_tests;

    while (number_of_tests)
    {
        barcode b;
        read_sensors(b);
        barcodes.emplace_back(b);
        number_of_tests--;
    }

    std::cout<<std::endl;
    for(auto& x : barcodes) {
        x.DecryptBarcode();
    }

    return 0;
}
