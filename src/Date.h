#pragma once
#include<iostream>
#include<ctime>
class Date {
private:
	time_t sTime;
public:
	Date();
	Date(const Date&) = default;
	Date(time_t);
	Date(const char*);
	time_t getTime();
	friend std::ostream& operator<<(std::ostream&, Date&);
};