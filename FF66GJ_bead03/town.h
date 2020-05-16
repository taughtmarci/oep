#pragma once
#include <iostream>
#include <string>
#include "tourist.h"

using namespace std;

class Tourist;
class Japanese;
class Modern;
class Waster;

enum Exception { ZERO, FILE_ERROR, SHORT_FILE, LONG_FILE, EMPTY_FILE };

class Town {
private:
protected:
	int points;
	int income = 0;
	string type;
	Town(int& _p, string _t) : points(_p), type(_t) {}
public:
	~Town() {}

	void setPoints(int _p) {
		points = _p;
		if (points < 1) points = 1;
		if (points > 100) points = 100;
	}
	int getPoints() const {
		return points;
	}

	void setIncome(int _i) {
		income = _i;
	}
	int getIncome() const {
		return income;
	}

	void setType(string _s) {
		type = _s;
	}
	string getType() const {
		return type;
	}

	virtual void charm(Tourist* _t) {}
};

class GoodState : public Town {
public:
	GoodState(int& _p) : Town(_p, "Good") {}
	void charm(Tourist* _t) override;
};

class DecentState : public Town {
public:
	DecentState(int& _p) : Town(_p, "Decent") {}
	void charm(Tourist* _t) override;
};

class BadState : public Town {
public:
	BadState(int& _p) : Town(_p, "Bad") {}
	void charm(Tourist* _t) override;
};