#pragma once

class StateManager;

class State
{
	friend class StateManager;
public:

	State() = default;
	virtual ~State() = default;

protected:
	StateManager* manager = nullptr;
	virtual void OnEnter() = 0;
	virtual void OnExit() = 0;
	virtual void Update() = 0;
};

