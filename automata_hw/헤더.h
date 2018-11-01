#pragma once
#include <iostream>
#include <vector>

using namespace std;

class State
{
	int id;
	bool isFinal;


	State();
};

class Automaton
{
	int number_of_states;
	char *sigma; // set of alphabet
	vector<State> internal_states;
	vector<State> final_states;
	vector<vector<State>> transition_rules;

	State *current_state;
	State *initial_state;

	Automaton(char *sigma);
	void create_state(int *transtion);
	void transition(char input);


	~Automaton();
};
