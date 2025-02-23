#include<Windows.h>
#include<string>
#include<iostream>
#include<fstream>
#include"employee.h"

void printBinary(const char* fileName) {
	std::ifstream file(fileName, std::ios::binary);
	if (!file) {
		throw "binary file not opened";
	}
	std::cout << "\nContents of binary file " << fileName << ":\n";
	employee emp;
	while (file.read(reinterpret_cast<char*>(&emp), sizeof(employee))) {
		std::cout << "ID: " << emp.num << ", Name: " << emp.name
			<< ", Working hours: " << emp.hours << "\n";
	}
	file.close();
}

void printReport(const char* filename) {
	std::ifstream file(filename);
	if (!file) {
		throw "report file not opened";
	}
	std::cout << "\nContents of report file " << filename << ":\n";
	std::string line;
	while (std::getline(file, line)) {
		std::cout << line << "\n";
	}
	file.close();
}

int main()
{
	char binaryFile[256];
	int recordCount;
	std::cout << "\nEnter binary file name:\n";
	std::cin >> binaryFile;
	std::cout << "Enter record count:\n";
	std::cin >> recordCount;
	STARTUPINFO si;
	ZeroMemory(&si, sizeof(STARTUPINFO));
	si.cb = sizeof(STARTUPINFO);
	PROCESS_INFORMATION pi;
	std::string cmdLine = "Creator.exe " + static_cast<std::string>(binaryFile) + " " + std::to_string(recordCount);
	if (!CreateProcess(NULL, (LPSTR)cmdLine.c_str(), NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi))
	{
		std::cerr << "Fatal error: could not execute creator process.";
		return 1;
	}
	WaitForSingleObject(pi.hProcess, INFINITE);
	CloseHandle(pi.hProcess);
	CloseHandle(pi.hThread);
	try
	{
		printBinary(binaryFile);
	}
	catch (...)
	{
		std::cerr << "Error: could not open binary file.";
	}
	char reportFile[256];
	double payRate;
	std::cout << "\nEnter report file name:\n";
	std::cin >> reportFile;
	std::cout << "Enter pay rate: ";
	std::cin >> payRate;
	std::string reporterCmd = "Reporter.exe " + static_cast<std::string>(binaryFile) + " " + static_cast<std::string>(reportFile) + " " + std::to_string(payRate);
	if (!CreateProcess(NULL, (LPSTR)reporterCmd.c_str(), NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi)) {
		std::cerr << "Fatal error: could not execute reporter process.\n";
		return 1;
	}
	WaitForSingleObject(pi.hProcess, INFINITE);
	CloseHandle(pi.hProcess);
	CloseHandle(pi.hThread);
	try
	{
		printReport(reportFile);
	}
	catch (...)
	{
		std::cerr << "Error: could not open report file.";
	}
	system("pause");
	return 0;
}