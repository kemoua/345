#pragma once
#include "PhaseObserver.h"
#include <list>
using namespace std;

class PhaseSubject {
public:
	virtual void Attach(PhaseObserver* o);
	virtual void Detach(PhaseObserver* o);
	virtual void NotifyPhase();
	PhaseSubject();
	~PhaseSubject();

private:
	list<PhaseObserver*> *_observers;
};