#pragma once

/*This class is created in an attempt to avoid including <iostream> in more files than needed. Which also looks cleaner.*/
class Logger
{
public:
	void notify(const char* msg);
	void notify2(const char* msg1, const char* msg2);
	void errorPrint(const char* msg);
	void errorPrint2(const char* msg1, const char* msg);
};