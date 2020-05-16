//FF66GJ's mighty felsoroló beadandó xd

#include "FishermEnor.h"
#include "PontyosBoys.h"

struct LegnagyobbPonty {
	string horgasz;
	string verseny;
	double suly;
};

void first(const string& name, LegnagyobbPonty& y) {
	Bajnoksag x(name);
	y.horgasz = "0";
	y.verseny = "0";
	y.suly = 0;

	for (x.first(); !x.end(); x.next()) {
		for (unsigned int i = 0; i < x.current().suly.size(); ++i) {
			if (x.current().suly[i] > y.suly) {
				y.horgasz = x.current().horgasz;
				y.verseny = x.current().verseny;
				y.suly = x.current().suly[i];
			}
		}
	}

	if (y.horgasz != "0" && y.verseny != "0" && y.suly != 0) {
		cout << y.horgasz << " fogta ki a " << y.verseny << " azonositoju versenyen a " << y.suly << " sulyu legnagyobb pontyot." << endl;
	}
	else {
		cout << "Senki nem fogott pontyot a megadott horgaszversenyen!" << endl;
	}
}

void second(const string& name, PontyokSzama& y) {
	Ponty x(name);
	y.horgasz = "0";
	y.ossz = 0;

	for (x.first(); !x.end(); x.next()) {
		if (x.current().ossz > y.ossz) {
			y.horgasz = x.current().horgasz;
			y.ossz = x.current().ossz;
		}
	}

	if (y.horgasz != "0" && y.ossz != 0) {
		cout << y.horgasz << " szerezte a legtobb pontyot, szam szerint ennyit: " << y.ossz << "." << endl;
	}
	else {
		cout << "Senki nem fogott pontyot a megadott horgaszversenyen!" << endl;
	}
}

//#define NORMAL_MODE
#ifdef NORMAL_MODE

int main() {
	try {
		LegnagyobbPonty y1;
		PontyokSzama y2;
		first("t06.txt",y1);
		second("t06.txt",y2);
	}
	catch (const char* exc) {
		cout << "ERROR: " << exc << endl;
	}
	return 0;
}

#else
#define CATCH_CONFIG_MAIN
#include "catch.hpp"

TEST_CASE("Üres fájl", "t00.txt") {
	LegnagyobbPonty y1;
	PontyokSzama y2;
	CHECK_THROWS(first("t0.txt", y1));
	CHECK_THROWS(second("t0.txt", y2));
}

TEST_CASE("Egy sor, van ponty", "t01.txt") {
	LegnagyobbPonty y1;
	PontyokSzama y2;
	first("t01.txt", y1);
	second("t01.txt", y2);

	CHECK(y1.horgasz == "JANIBA");
	CHECK(y1.verseny == "Kiliti0512");
	CHECK(y1.suly == 4.5);

	CHECK(y2.horgasz == "JANIBA");
	CHECK(y2.ossz == 1);
}

TEST_CASE("Egy sor, nincs ponty", "t02.txt") {
	LegnagyobbPonty y1;
	PontyokSzama y2;
	first("t02.txt", y1);
	second("t02.txt", y2);

	CHECK(y1.horgasz == "0");
	CHECK(y1.verseny == "0");
	CHECK(y1.suly == 0);

	CHECK(y2.horgasz == "0");
	CHECK(y2.ossz == 0);
}

TEST_CASE("Több sor, többen fogtak pontyot", "t03.txt") {
	LegnagyobbPonty y1;
	PontyokSzama y2;
	first("t03.txt", y1);
	second("t03.txt", y2);

	CHECK(y1.horgasz == "KARIBA");
	CHECK(y1.verseny == "Kiliti0512");
	CHECK(y1.suly == 145.3);

	CHECK(y2.horgasz == "JANIBA");
	CHECK(y2.ossz == 5);
}

TEST_CASE("Több sor, senki nem fogott pontyot", "t04.txt") {
	LegnagyobbPonty y1;
	PontyokSzama y2;
	first("t04.txt", y1);
	second("t04.txt", y2);

	CHECK(y1.horgasz == "0");
	CHECK(y1.verseny == "0");
	CHECK(y1.suly == 0);

	CHECK(y2.horgasz == "0");
	CHECK(y2.ossz == 0);
}

TEST_CASE("Több sor, két maximum mindkét feladatban", "t05.txt") {
	LegnagyobbPonty y1;
	PontyokSzama y2;
	first("t05.txt", y1);
	second("t05.txt", y2);

	CHECK(y1.horgasz == "JANIBA");
	CHECK(y1.verseny == "Kiliti0512");
	CHECK(y1.suly == 145.3);

	CHECK(y2.horgasz == "JANIBA");
	CHECK(y2.ossz == 2);
}

TEST_CASE("Több sor, változó mennyiségû fogások, két maximum mindkét feladatban", "t06.txt") {
	LegnagyobbPonty y1;
	PontyokSzama y2;
	first("t06.txt", y1);
	second("t06.txt", y2);

	CHECK(y1.horgasz == "ZSOLTIKA");
	CHECK(y1.verseny == "Gesztes0906");
	CHECK(y1.suly == 3434);

	CHECK(y2.horgasz == "JANIBA");
	CHECK(y2.ossz == 4);
}

#endif