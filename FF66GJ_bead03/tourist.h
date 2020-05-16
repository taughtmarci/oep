#pragma once
#include "town.h"

using namespace std;

class Town;
class GoodState;
class DecentState;
class BadState;

class Tourist {
private:
protected:
	int planned;
	int went;
	string type;
	Tourist(const int &_p, string _t) : planned(_p), type(_t) {}
public:
	~Tourist() {}

	void setPlanned(int _p) {
		planned = _p;
	}
	int getPlanned() const {
		return planned;
	}

	void setWent(int _w) {
		went = _w;
	}
	int getWent() const {
		return went;
	}

	void setType(string _s) {
		type = _s;
	}
	string getType() const {
		return type;
	}

	virtual void affect(Town* _t) {}
	friend ostream& operator << (ostream& os, const Tourist* _t);
};

class Japanese : public Tourist {
public:
	Japanese(const int& _p) : Tourist(_p, "Japanese") {}
	void affect(Town* _t) override;
};

class Modern : public Tourist {
public:
	Modern(const int& _p) : Tourist(_p, "Modern") {}
	void affect(Town* _t) override;
};

class Waster : public Tourist {
public:
	Waster(const int& _p) : Tourist(_p, "Waster") {}
	void affect(Town* _t) override;
};