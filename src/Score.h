#pragma once
#include"Date.h"
#include<ostream>

class Score {
private:
	char name[16];
	int score;
	Date date;
public:
	Score() {}
	Score(const char*);
	char* getName();
	int getScore();
	Date getDate();
	void setName(const char*);
	void setScore(int);
	void setDate();
	friend bool operator<(Score&, Score&);
	friend bool operator>(Score&, Score&);
	friend std::ostream& operator<<(std::ostream&, Score&);
};