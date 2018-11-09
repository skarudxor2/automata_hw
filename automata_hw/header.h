#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <conio.h>
#include <fstream>
#include <sstream>

#define MAX_SIZE 1000

using namespace std;

const string PARSE_ERR = "parsing err!";
const string NO_INIT_IN_STATES = "initial state is not exists in states";
const string NO_FINAL_IN_STATES = "some final states are not exists in states";
const string TRANSITION_ERROR = "err while transition";
const string GREEK_DELTA = "\u03B4";

class State
{
	std::string label;
	int id;
	bool isFinal;


public:
	State(string label, int id, bool isFinal = false);

	int getId()
	{
		return id;
	}
	int isFinalState()
	{
		return isFinal;
	}
	string getLabel()
	{
		return label;
	}
	void setFinal(bool isFinal)
	{
		this->isFinal = isFinal;
	}


};

class Automaton
{
	int number_of_states;
	vector<char> sigma; // set of alphabet
	vector<State*> internal_states;
	vector<State*> final_states;
	vector<vector<string> > transition_rules; //or int[][]

	State *current_state;
	State *initial_state;

	
	State *findWithLabel(string label);

public:
	Automaton(vector<char>sigma, vector<string>states, string initial, vector<string>finalStates, vector<string>delta);
	void showStatus();
	void transition(char input);
	void makeMinimal(string filename);
	int getNumberOfStates()
	{
		return number_of_states;
	}
	//is input string accepted
	bool isAccepted()
	{
		return current_state->isFinalState();
	}
	State *transitionWithState(State *iState, char input);
	State *getCurrentState()
	{
		return current_state;
	}
	~Automaton();
};



vector<string> split(const string& s, char delimiter);
void printInput(vector<char> sigma, vector<string>states, string initial, vector<string>finalStates, vector<string>delta);
bool finalCheck(vector<string>states, vector<string>finalStates);
bool initCheck(vector<string> states, string initial);
bool elem(vector<string>vec, string str);
