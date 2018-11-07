#include "header.h"

State::State(int id, bool isFinal)
	: id(id), isFinal(isFinal)
{


}

State::State(string label, bool isFinal)
	: label(label), isFinal(isFinal)
{

}

Automaton::Automaton(vector<char>sigma, vector<string>states, string initial, vector<string>finalStates, vector<string>delta)
{

}

void Automaton::create_state(int *transition)
{


}

Automaton::~Automaton()
{

}

