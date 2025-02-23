#include<iostream>
#include<fstream>
#include<string>
#include<Windows.h>
#include"employee.h"

int main(int argc, char* argv[])
{
	if (argc != 3)
	{
		std::cerr << "Fatal error: Wrong argument amount, example: <filename> <record count>";
		return 1;
	}
	const char* fileName = argv[1];
	int recordCount = std::atoi(argv[2]);
	if (recordCount < 1)
	{
		std::cerr << "Fatal error: There is less than one record in a file, or the number is invalid.";
		return 3;
	}
	std::ofstream file(fileName, std::ios::binary);
	if (!file)
	{
		std::cerr << "Fatal error: cannot open binary file.";
		return 2;
	}
	int i = 0;
	for (; i < recordCount; i++)
	{
		employee emp;
		std::cout << "Enter employee ID, name (no more than 10 symbols) and work hours:\n";
		std::cin >> emp.num >> emp.name >> emp.hours;
		file.write(reinterpret_cast<char*>(&emp), sizeof(employee));
	}
	file.close();
	std::cout << "File " << fileName << " created.";
	return 0;
}