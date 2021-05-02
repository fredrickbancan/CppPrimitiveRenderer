#include "Logger.h"
#include <iostream>
using namespace std;

void Logger::notify(const char* msg)
{
	cout << "[CPPPR] " << msg << endl;
}

void Logger::notify2(const char* msg1, const char* msg2)
{
	cout << "[CPPPR] " << msg1 << " " << msg2 << endl;
}

void Logger::errorPrint(const char* msg)
{
	cout << "[CPPPR] Error!: " << msg << endl;
	system("PAUSE");
}

void Logger::errorPrint2(const char* msg1, const char* msg2)
{
	cout << "[CPPPR] Error!: " << msg1 << " " << msg2 << endl;
	system("PAUSE");
}