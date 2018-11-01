#pragma once
#include <iostream>
#include <vector>

using namespace std;

class state
{
	int id;
	bool isFinal;

};

class automaton
{
	char *sigma; // set of alphabet
	vector<state> internal_states;
	vector<state> final_states;
	vector<vector<state>> transition_rules;

	state *current_state;
	state *initial_state;

	void create_state(int *transtion);
	void transition(char input);

};
