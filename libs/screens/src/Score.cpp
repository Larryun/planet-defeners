#pragma warning(disable : 4996)
#include<iomanip>
#include<cstdlib>
#include<cstring>
#include"Score.h"


Score::Score(const char* line) {
	char nameTemp[15], dateTemp[11], scoreTemp[8];
	nameTemp[14] = '\0', dateTemp[10] = '\0', scoreTemp[7] = '\0';
	int end = strlen(line);
	for (int i = 0; i < end; i++) {
		if (i <= 14) {
			if (line[i] == ' ' && line[i + 1] == ' ') {
				nameTemp[i] = '\0';
			}
			else {
				nameTemp[i] = line[i];
			}
		}
		else if (i >= 16 && i <= 25) {
			if (line[i] == ' ') {
				dateTemp[i - 16] = '\0';
			}
			else {
				dateTemp[i - 16] = line[i];
			}
		}
		else if (i >= 29) {
			if (i == end) {
				scoreTemp[i - 29] = '\0';
			}
			scoreTemp[i - 29] = line[i];
		}
	}
	score = atoi(scoreTemp);

	strcpy(name, nameTemp);
	if (dateTemp[9] >= 48 && dateTemp[9] <= 57) {
		time_t dateTransfer(atoi(dateTemp));
		date = dateTransfer;
	}
	else if (dateTemp[0] == '\0') {
		Date dateTransfer;
		date = dateTransfer;
	}
	else {
		Date dateTransfer(dateTemp);
		date = dateTransfer;
	}
}

char* Score::getName() {
	return name;
}

void Score::setName(const char* input) {
	int i = 0;
	while (input[i] != '\0') {
		name[i] = input[i];
		i++;
	}
	name[i] = input[i];
}

int Score::getScore() {
	return score;
}

void Score::setScore(int input) {
	score = input;
}

Date Score::getDate() {
	return date;
}

void Score::setDate() {
	time_t now = time(0);
}

bool operator<(Score& obj1, Score& obj2) {
	if (obj1.getScore() < obj2.getScore()) {
		return true;
	}
	else {
		return false;
	}
}

bool operator>(Score& obj1, Score& obj2) {
	if (obj1.getScore() > obj2.getScore()) {
		return true;
	}
	else {
		return false;
	}
}

std::ostream& operator<<(std::ostream& out, Score& nScore) {
	Date temp = nScore.getDate();

	return out << std::setw(16) << std::left << nScore.getName()
		<< std::setw(8) << std::left << temp
		<< std::setw(5) << " " << nScore.getScore();
}