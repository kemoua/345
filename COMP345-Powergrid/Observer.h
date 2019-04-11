#pragma once

class Observer {
public:
	~Observer();
	virtual void UpdatePhase() = 0;
	virtual void UpdateStats() = 0;

protected:
	Observer();
};