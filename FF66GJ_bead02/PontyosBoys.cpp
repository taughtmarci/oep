#include "FishermEnor.h"
#include "PontyosBoys.h"

void Ponty::first() {
	_e.first();
	next();
}

void Ponty::next() {
	if (!(_end = _e.end())) {
		st = norm;
		t.horgasz = _e.current().horgasz;
		t.ossz = 0;

		for (; !_e.end() && _e.current().horgasz == t.horgasz; _e.next()) {
			t.ossz += _e.current().suly.size();
			//cout << _e.current().suly.size() << endl;
		}
	}
	else st = abnorm;
}