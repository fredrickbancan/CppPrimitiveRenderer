#pragma once
class Logger
{
public:
	void notify(const char* msg);
	void notify2(const char* msg1, const char* msg2);
	void errorPrint(const char* msg);
	void errorPrint2(const char* msg1, const char* msg);
};