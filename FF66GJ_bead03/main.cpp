#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "town.h"
#include "tourist.h"

using namespace std;

Town* city;

vector<Japanese*> j;
vector<Modern*> m;
vector<Waster*> w;

int n = 0, years = 0, tenpoints;
ifstream _f;
string _name, tentype;

void selectState(int& pts) {
	if (pts <= 34) city = new BadState(pts);
	else if (pts <= 67) city = new DecentState(pts);
	else city = new GoodState(pts);
	//cout << city->getType() << endl;
}

void addPoints() {
	int result = (city->getIncome() - 10000) / 200;
	city->setPoints(city->getPoints() + result);
}

void readFile(ifstream &f, string fname) {
	f.open(fname.c_str());
	if (f.fail()) throw FILE_ERROR;
	
	f >> n;
	f >> years;
	cout << years << " tested years." << endl;

	for (int i = 0; i < years; ++i) {
		if (f.eof()) throw SHORT_FILE;
		int amount;
		f >> amount;
		cout << amount << " ";
		j.push_back(new Japanese(amount));
		f >> amount;
		cout << amount << " ";
		m.push_back(new Modern(amount));
		f >> amount;
		cout << amount << " " << endl;
		w.push_back(new Waster(amount));
	}

	if (!f.eof()) throw LONG_FILE;
	f.close();
	cout << endl;
}

void process() {
	for (int i = 0; i < years; ++i) {
		cout << "Year " << i + 1 << ":" << endl;

		selectState(n);
		city->charm(j[i]);
		cout << j[i] << endl;
		city->charm(m[i]);
		cout << m[i] << endl;
		city->charm(w[i]);
		cout << w[i] << endl;

		j[i]->affect(city);
		m[i]->affect(city);
		w[i]->affect(city);

		if (city->getIncome() >= 10200) addPoints();
		cout << "Income: " << city->getIncome() / 10 << " million forints, score: " << n << ", stance: " << city->getType() << endl;
		n = city->getPoints();
		cout << endl;

		if (i == 9) {
			selectState(n);
			tenpoints = city->getPoints();
			tentype = city->getType();
			cout << "According to the input data the expected state of town by the end of year 10:" << endl;
			cout << "Score: " << tenpoints << ", stance: " << tentype << "." << endl;
			cout << endl;
		}
	}
}

void tenYears() {
	if (years < 10) {
		selectState(n);
		tenpoints = city->getPoints();
		tentype = city->getType();
		cout << "According to the input data the expected state of town by the end of year 10:" << endl;
		cout << "Score: " << tenpoints << ", stance: " << tentype << "." << endl;
		cout << endl;
	}
}

void remove() {
	if (city != nullptr) delete city;
	for (Japanese* p : j)
		delete p;
	for (Modern* p : m)
		delete p;
	for (Waster* p : w)
		delete p;
	j.clear(); j.resize(0);
	m.clear(); m.resize(0);
	w.clear(); w.resize(0);
}

#define NORMAL_MODE
#ifdef NORMAL_MODE

int main() {
	//cout << "Name of the inputfile: ";
	//cin >> _name;
	//cout << endl;

	try {
		//FILE-T BEOLVAS
		readFile(_f, "t03.txt");

		//FELDOLGOZ
		cout << "Tourism's progress in town for the next " << years << " years: " << endl;
		process();
		tenYears();

		//TÖRÖL
		remove();
	} catch (Exception _err) {
		cout << "Error number " << _err << ".\n";
	}

	return 0;
}

#else
#define CATCH_CONFIG_MAIN
#include "catch.hpp"

TEST_CASE("Ures File", "t00.txt") {
	readFile(_f, "t00.txt");
	CHECK(n == 0);
	CHECK(years == 0);
	remove();
}

TEST_CASE("Kezdo pontszam es evszam input OK", "t01.txt") {
	readFile(_f,"t01.txt");
	CHECK(n == 25);
	CHECK(years == 1);
	remove();
}

TEST_CASE("Varos kezdo bevetele es pontszama OK", "t01.txt") {
	readFile(_f, "t01.txt");
	process();
	CHECK(city->getIncome() == 1100);
	CHECK(city->getPoints() == 6); //25-(16+3)
	remove();
}

TEST_CASE("Varos kesobbi bevetele es pontszama OK", "t02.txt") {
	readFile(_f, "t02.txt");
	process();
	CHECK(city->getIncome() == 1360); //Japánok nem mennek
	CHECK(city->getPoints() == 1); //16, -4
	remove();
}


TEST_CASE("Turistak jol vonzodnak Bad varoshoz", "t02.txt") {
	readFile(_f, "t02.txt");
	process();
	CHECK(j[0]->getPlanned() == 300);
	CHECK(j[0]->getWent() == 0);
	CHECK(m[0]->getPlanned() == 500);
	CHECK(m[0]->getWent() == 500);
	CHECK(w[0]->getPlanned() == 600);
	CHECK(w[0]->getWent() == 600);
	remove();
}

TEST_CASE("Turistak jol vonzodnak Decent varoshoz", "t03.txt") {
	readFile(_f, "t03.txt");
	process();
	CHECK(j[0]->getPlanned() == 1000);
	CHECK(j[0]->getWent() == 1000);
	CHECK(m[0]->getPlanned() == 4000);
	CHECK(m[0]->getWent() == 4400); //10%
	CHECK(w[0]->getPlanned() == 6000);
	CHECK(w[0]->getWent() == 6600); //10%
	remove();
}

TEST_CASE("10 eves allapot OK", "t03.txt") {
	readFile(_f, "t03.txt");
	process();
	tenYears();
	CHECK(tenpoints == 1);
	CHECK(tentype == "Bad");
	remove();
}

TEST_CASE("Turistak jol vonzodnak Good varoshoz", "t04.txt") {
	readFile(_f, "t04.txt");
	process();
	CHECK(j[0]->getPlanned() == 1000);
	CHECK(j[0]->getWent() == 1200); //10%
	CHECK(m[0]->getPlanned() == 2000);
	CHECK(m[0]->getWent() == 2600); //30%
	CHECK(w[0]->getPlanned() == 5000);
	CHECK(w[0]->getWent() == 5000);
	remove();
}

TEST_CASE("Varos kezdoallapota OK", "t04.txt") {
	readFile(_f, "t04.txt");
	process();
	CHECK(city->getType() == "Good");
	remove();
}

TEST_CASE("Varos megvaltozott allapota OK", "t05.txt") {
	readFile(_f, "t05.txt");
	process();
	CHECK(city->getType() == "Good");
	remove();
}

TEST_CASE("Bemeneti file tul kicsi/nagy pontszam korrigalasa", "t06.txt") {
	readFile(_f, "t06.txt");
	process();
	CHECK(city->getPoints() == 100);
	remove();
}

TEST_CASE("10 evnel nagyobb attekintes OK", "t7.txt") {
	readFile(_f, "t07.txt");
	process();
	tenYears();
	CHECK(city->getType() == "Good");
	remove();
}

TEST_CASE("10 eves allapot nagyobb attekintes utan is OK", "t7.txt") {
	readFile(_f, "t07.txt");
	process();
	tenYears();
	CHECK(tenpoints == 100);
	CHECK(tentype == "Good");
	remove();
}

#endif