#pragma warning(disable : 4996)
#include<cstring>
#include<cstdio>
#include"Date.h"

Date::Date() {
	sTime = std::time(0);
}

Date::Date(time_t input) {
	sTime = input;
}


Date::Date(const char* fDate) {
	int day, mon, year;
	char monTemp[4];
	monTemp[3] = '\0';

	if (fDate[2] == '/' || fDate[2] == '-') {
		sscanf(fDate, "%2d %*c %2d %*c %2d", &mon, &day, &year);
	}
	else if ((int)fDate[2] >= 65 && (int)fDate[2] <= 90) {
		sscanf(fDate, "%2d %3s %2d", &day, monTemp, &year);
		if (strcmp(monTemp, "Jan") == 0) {
			mon = 1;
		}
		else if (strcmp(monTemp, "Feb") == 0) {
			mon = 2;
		}
		else if (strcmp(monTemp, "Mar") == 0) {
			mon = 3;
		}
		else if (strcmp(monTemp, "Apr") == 0) {
			mon = 4;
		}
		else if (strcmp(monTemp, "May") == 0) {
			mon = 5;
		}
		else if (strcmp(monTemp, "Jun") == 0) {
			mon = 6;
		}
		else if (strcmp(monTemp, "Jul") == 0) {
			mon = 7;
		}
		else if (strcmp(monTemp, "Aug") == 0) {
			mon = 8;
		}
		else if (strcmp(monTemp, "Sep") == 0) {
			mon = 9;
		}
		else if (strcmp(monTemp, "Oct") == 0) {
			mon = 10;
		}
		else if (strcmp(monTemp, "Nov") == 0) {
			mon = 11;
		}
		else {
			mon = 12;
		}
	}
	struct tm* tTime = new tm;
	tTime->tm_sec = 0;
	tTime->tm_min = 0;
	tTime->tm_hour = 0;
	tTime->tm_mday = day;
	tTime->tm_mon = mon - 1;
	tTime->tm_year = year + 100;

	sTime = mktime(tTime);
	delete tTime;
}

time_t Date::getTime() {
	return sTime;
}

std::ostream& operator<<(std::ostream& out, Date& nDate) {
	if (nDate.getTime() == NULL) {
		return out;
	}
	time_t temp = nDate.getTime();
	struct tm* tTime = localtime(&temp);
	char buffer[60];
	strftime(buffer, 60, "%D", tTime);

	return out << buffer;
}