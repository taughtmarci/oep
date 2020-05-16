#include "town.h"

void GoodState::charm(Tourist* _t) {
	if (_t->getType() == "Japanese") _t->setWent(_t->getPlanned() * 1.2);
	if (_t->getType() == "Modern") _t->setWent(_t->getPlanned() * 1.3);
	if (_t->getType() == "Waster") _t->setWent(_t->getPlanned());
}

void DecentState::charm(Tourist* _t) {
	if (_t->getType() == "Japanese") _t->setWent(_t->getPlanned());
	if (_t->getType() == "Modern") _t->setWent(_t->getPlanned() * 1.1);
	if (_t->getType() == "Waster") _t->setWent(_t->getPlanned() * 1.1);
}

void BadState::charm(Tourist* _t) {
	if (_t->getType() == "Japanese") _t->setWent(0);
	if (_t->getType() == "Modern") _t->setWent(_t->getPlanned());
	if (_t->getType() == "Waster") _t->setWent(_t->getPlanned());
}
