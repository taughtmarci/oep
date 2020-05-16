#pragma once
#include "FishermEnor.h"

struct PontyokSzama {
	string horgasz;
	unsigned int ossz;
};

class Ponty {
private:
	Status st;
	Bajnoksag _e;
	PontyokSzama t;
	bool _end;

public:
	Ponty(string fname) : _e(fname) {}
	~Ponty() {}

	void first();
	void next();
	PontyokSzama current() { return t; }
	bool end() { return (st == abnorm); }
};