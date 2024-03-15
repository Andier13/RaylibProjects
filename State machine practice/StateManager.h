#pragma once

#include "State.h"
#include <vector>
#include <string>

class StateManager
{
	std::vector<State*> states = {};
	std::vector<std::string> stateNames = {};
	State* startingState = nullptr;
	State* currentState = nullptr;
	State* nextState = nullptr;

public:

	StateManager() = default;
	void AddState(std::string stateName, State* state);
	void SwitchState(std::string nextStateName);
	void SetStartingState(std::string nextStateName);
	void UpdateCurrentState();
	~StateManager();

private:
	std::string ToLower(std::string str);
	State* GetStateFromName(std::string stateName);
};

