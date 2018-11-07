#include "header.h"
State::State(string label, int id, bool isFinal)
	: label(label), id(id), isFinal(isFinal)
{

}

Automaton::Automaton(vector<char>sigma, vector<string>states, string initial, vector<string>finalStates, vector<string>delta)
	: sigma(sigma), number_of_states(0)
{
	//create states as inputfile
	for (int i = 0; i < states.size(); ++i)
	{
		string str = states[i];
		internal_states.push_back(new State(str, number_of_states++));
		//if the state is initial,
		if (str == initial)
			initial_state = internal_states[i];
		//if the state is elem of final states
		if (elem(finalStates, str))
		{
			internal_states[i]->setFinal(true);
			final_states.push_back(internal_states[i]);
		}
	}
	current_state = initial_state;

	for (auto i : delta)
	{

		vector<string> temp = split(i, '(');
		string str = temp[1];
		temp = split(str, ')');
		str = temp[0];			//before  input   after
		temp = split(str, ','); //temp[0] temp[1] temp[2]  where internal states index = id
		transition_rules.push_back(temp);


	}

}

void Automaton::transition(char input)
{
	string currentLabel = current_state->getLabel();
	string nextLabel = "failed";

	for (auto delta : transition_rules)
		if (delta[0] == currentLabel && delta[1][0] == input)
			nextLabel = delta[2];

	

	if (nextLabel == "failed")
	{
		cout <<endl<< TRANSITION_ERROR << endl;
		cout << "no transitions would happen" << endl;
		current_state = findWithLabel(currentLabel);
		return;
	}
	else
		current_state = findWithLabel(nextLabel);
	

}

State *Automaton::findWithLabel(string label)
{
	for (auto i : internal_states)
		if (i->getLabel() == label)
			return i;
}


void Automaton::showStatus()
{
	cout << "automaton.showStatus()" << endl;
	cout << "number of states : " << number_of_states << endl;
	cout << "sigma : ";
	for (auto i : sigma)
		cout << i << ' ';
	cout << endl;

	cout << "internal states : " << endl;
	for (auto i : internal_states)
		cout << i->getLabel() << "(" << i->getId() << ")" << endl;

	cout << "initial state : " << initial_state->getLabel() << "(" << initial_state->getId() << ")" << endl;

	cout << "final states : " << endl;
	for (auto i : final_states)
		cout << i->getLabel() << "(" << i->getId() << ")" << endl;

	cout << "transiton rules : " << endl;
	for (auto i : transition_rules)
	{
		cout << GREEK_DELTA + "(" << i[0]<<"," << i[1] << ") = " << i[2];
		cout << endl;
	}
}

Automaton::~Automaton()
{
	for (auto i : internal_states)
		delete i;
}

