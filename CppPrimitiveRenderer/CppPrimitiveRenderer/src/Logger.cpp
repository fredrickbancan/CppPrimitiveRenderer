#include "Logger.h"
#include <iostream>
using namespace std;

template <typename T>
void Logger::notify(T o)
{
	cout << "[CPPPR] " << o << endl;
}

template <typename T, typename T2>
void Logger::notify2(T o, T2 o2)
{
	cout << "[CPPPR] " << o << " " << o2 << endl;
}

template <typename T>
void Logger::errorPrint(T o)
{
	cout << "[CPPPR] Error!: " << o << endl;
	cin.get();
}

template <typename T, typename T2>
void Logger::errorPrint2(T o, T2 o2)
{
	cout << "[CPPPR] Error!: " << o << " " << o2 << endl;
	cin.get();
}