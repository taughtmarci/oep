#include "tourist.h"

ostream& operator << (ostream& os, const Tourist* _t) {
	os << _t->getType() << " tourists - planned: " << _t->getPlanned() << ", went: " << _t->getWent();
	return os;
}

void Japanese::affect(Town* _t) {
	_t->setIncome(_t->getIncome() + getWent());
}

void Modern::affect(Town* _t) {
	_t->setPoints(_t->getPoints() - (getWent() / 100));
	_t->setIncome(_t->getIncome() + getWent());
}

void Waster::affect(Town* _t) {
	_t->setPoints(_t->getPoints() - (getWent() / 50));
	_t->setIncome(_t->getIncome() + getWent());
}