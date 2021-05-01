#pragma once
class Logger
{
public:
	template <typename T>
	void notify(T o);
	template <typename T, typename T2>
	void notify2(T o, T2 o2);
	template <typename T>
	void errorPrint(T o);
	template <typename T, typename T2>
	void errorPrint2(T o, T2 o2);
};
