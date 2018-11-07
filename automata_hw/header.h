#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <conio.h>
#include <fstream>
#include <sstream>

using namespace std;

class State
{
	std::string label;
	int id;
	bool isFinal;


public:
	State(int id,bool isFinal=false);
	int getId()
	{
		return id;
	}
	int isFinalState()
	{
		return isFinal;
	}
};

class Automaton
{
	int number_of_states;
	vector<char> sigma; // set of alphabet
	vector<State*> internal_states;
	vector<State*> final_states;
	vector<vector<State>> transition_rules; //or int[][]

	State *current_state;
	State *initial_state;

	
	void create_state(int *transtion);
	void transition(char input);

public:
	Automaton(vector<char> sigma);
	void showCur()
	{
		int curId = current_state->getId();
		cout << "Id of current state is " << curId << endl;
	}
	~Automaton();
};



vector<string> split(const string& s, char delimiter);
void printInput(vector<char> sigma, vector<string>states, string initial, vector<string>finalStates, vector<string>delta);
bool finalCheck(vector<string>states, vector<string>finalStates);
bool initCheck(vector<string> states, string initial);