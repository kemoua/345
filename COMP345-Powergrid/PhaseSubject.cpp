#include "PhaseSubject.h"
#include "PhaseObserver.h"

PhaseSubject::PhaseSubject() {
	_observers = new list<PhaseObserver*>;
}

PhaseSubject::~PhaseSubject() {
	delete _observers;
}

void PhaseSubject::Attach(PhaseObserver* o) {
	_observers->push_back(o);
}

void PhaseSubject::Detach(PhaseObserver* o) {
	_observers->remove(o);
}

void PhaseSubject::NotifyPhase() {
	list<PhaseObserver *>::iterator i = _observers->begin();
	for (; i != _observers->end();++i) {
		(*i)->UpdatePhase();
	}
}