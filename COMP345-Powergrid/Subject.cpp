#include "Subject.h"
#include "Observer.h"

Subject::Subject() {
	_observers = new list<Observer*>;
}

Subject::~Subject() {
	delete _observers;
}

void Subject::Attach(Observer* o) {
	_observers->push_back(o);
}

void Subject::Detach(Observer* o) {
	_observers->remove(o);
}

void Subject::NotifyPhase() {
	list<Observer *>::iterator i = _observers->begin();
	for (; i != _observers->end();++i) {
		(*i)->UpdatePhase();
	}
}

void Subject::NotifyStats() {
	list<Observer *>::iterator i = _observers->begin();
	for (; i != _observers->end();++i) {
		(*i)->UpdateStats();
	}
}