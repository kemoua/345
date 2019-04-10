#pragma once

class PhaseObserver {
public:
	~PhaseObserver();
	virtual void UpdatePhase() = 0;

protected:
	PhaseObserver();
};