#include "StateManager.h"
#include <iostream>

void StateManager::AddState(std::string stateName, State* state)
{
	state->manager = this;
	states.push_back(state);
	stateNames.push_back(ToLower(stateName));
}

void StateManager::SwitchState(std::string nextStateName)
{
	State* result = GetStateFromName(nextStateName);
	if (result == nullptr)
		return;
	nextState = result;
}

void StateManager::SetStartingState(std::string nextStateName)
{
	startingState = GetStateFromName(nextStateName);
}

void StateManager::UpdateCurrentState()
{
	if (states.empty())
		return;
	if (startingState == nullptr)
	{
		std::cerr << "No explicit starting scene was found so the default (first one) was used" << std::endl;
		startingState = states[0];
	}
	if (currentState == nullptr)
	{
		startingState->OnEnter();
		nextState = currentState = startingState;
	}
	else
	{
		if (currentState != nextState)
		{
			currentState->OnExit();
			nextState->OnEnter();
			currentState = nextState;
		}
	}

	currentState->Update();
}

StateManager::~StateManager()
{
	if (states.empty())
		return;
	if (currentState != nullptr)
		currentState->OnExit();
	for (size_t i = 0; i < states.size(); i++)
		delete states[i];
}

std::string StateManager::ToLower(std::string str)
{
	for (auto& c : str)
		if ('A' <= c && c <= 'Z')
			c = c - 'A' + 'a';
	return str;
}

State* StateManager::GetStateFromName(std::string stateName)
{
	int i;
	stateName = ToLower(stateName);
	for (i = 0; i < stateNames.size(); i++)
		if (stateNames[i] == stateName)
			break;

	if (i == stateNames.size() || stateNames.empty())
	{
		std::cout << "Could not find state named: " << stateName << std::endl;
		return nullptr;
	}

	return states[i];
}
