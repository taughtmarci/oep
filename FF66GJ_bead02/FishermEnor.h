#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

using namespace std;

struct Versenyzo {
	string horgasz;
	string verseny;
	string hal;
	double suly;
};

struct Pontyos {
	string horgasz;
	string verseny;
	vector<double> suly;
};

enum Status { abnorm, norm };

class Bajnoksag {
private:
	ifstream f;
	Status st;
	Versenyzo e;
	Pontyos t;
	bool _end;

public:
	Bajnoksag(string fname);
	~Bajnoksag() { f.close(); }

	void first();
	void next();
	Pontyos current() { return t; }
	bool end() { return (st == abnorm); }
};


