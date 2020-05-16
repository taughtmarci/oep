#include "FishermEnor.h"

Bajnoksag::Bajnoksag(string fname) {
	f.open(fname.c_str());
	if (f.fail()) throw "Could not open the file.";
}

void Bajnoksag::first() {
	t.horgasz = "0";
	t.verseny = "0";
	next();
}

void Bajnoksag::next() {
	string line;
	getline(f, line);

	if (!(_end = f.fail())) {
		st = norm;
		t.suly.clear();

		istringstream in(line);
		in >> e.horgasz >> e.verseny;
		while (!in.eof()) {
			in >> e.hal >> e.suly;
			if (e.hal == "Ponty") {
				t.suly.push_back(e.suly);
				//cout << e.suly << " " << endl;
			}
		}
		t.horgasz = e.horgasz;
		t.verseny = e.verseny;
	}
	else st = abnorm;
}