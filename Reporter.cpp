#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include "employee.h"
#include <windows.h>

int main(int argc, char* argv[]) {
    if (argc != 4) {
        std::cerr << "Fatal error: Wrong argument amount, example: <report file> <payrate>\n";
        return 1;
    }

    const char* inputFilename = argv[1];
    const char* reportFilename = argv[2];
    double payRate = std::stod(argv[3]);

    std::ifstream inputFile(inputFilename, std::ios::binary);
    if (!inputFile) {
        std::cerr << "Fatal error: could not open binary file.\n";
        return 1;
    }

    std::ofstream reportFile(reportFilename);
    if (!reportFile) {
        std::cerr << "Fatal error: could not create report file\n";
        return 1;
    }

    reportFile << "Report using file \"" << inputFilename << "\"\n";

    employee emp;
    while (inputFile.read(reinterpret_cast<char*>(&emp), sizeof(employee))) {
        double salary = emp.hours * payRate;
        reportFile << "ID: " << emp.num << ", "
            << "Worker's name: " << emp.name << ", "
            << "Hours of work: " << emp.hours << ", "
            << "Salary: " << salary << "\n";
    }

    inputFile.close();
    reportFile.close();
    std::cout << "Report file " << reportFilename << " created.\n";
    return 0;
}
