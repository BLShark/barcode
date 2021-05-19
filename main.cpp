#include <iostream>
#include <list>
#include <sstream>
#include <cmath>

#include "coding_numbers.h"

int main()
{
    std::cout << "Hello Chaos group!" << std::endl;

    uint16_t sensor_numbers = 0;
    std::cout << "Enter numbers of sensors: ";
    std::cin>> sensor_numbers;
    std::cin.ignore();

    std::cout << "\nEnter the data from them: ";
    std::string line, sensor_data;
    getline(std::cin, line);
    std::stringstream ss(line);
    barcode b1;
    while (getline(ss, sensor_data, ' ') && sensor_numbers--) {
        b1<<(std::round(std::stod(sensor_data) + 0.05));
    }

    std::cout<<"\nEnter numbers of tests: ";
    uint16_t number_of_tests = 0;
    std::cin>>number_of_tests;

    b1.DecryptBarcode();
    return 0;
}
