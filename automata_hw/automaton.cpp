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
		cout << endl << TRANSITION_ERROR << endl;
		cout << "no transitions would happen" << endl;
		current_state = findWithLabel(currentLabel);
		return;
	}
	else
		current_state = findWithLabel(nextLabel);


}

State *Automaton::transitionWithState(State *iState, char input)
{
	string currentLabel = iState->getLabel();
	string nextLabel = "failed";

	for (auto delta : transition_rules)
		if (delta[0] == currentLabel && delta[1][0] == input)
			nextLabel = delta[2];



	if (nextLabel == "failed")
	{
		cout << endl << TRANSITION_ERROR << endl;
		cout << "no transitions would happen" << endl;
		return iState;
	}
	else
		return findWithLabel(nextLabel);


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
		cout << GREEK_DELTA + "(" << i[0] << "," << i[1] << ") = " << i[2];
		cout << endl;
	}
}

void Automaton::makeMinimal(string filename)
{
	int isDFA;
	for (auto i : internal_states)
	{
		isDFA = 0;
		for (auto j : sigma)
		{
			for (auto delta : transition_rules)
				if (delta[0] == i->getLabel() && delta[1][0] == j)
				{
					isDFA++;
					break;
				}
		}
		if (isDFA != sigma.size())
		{
			cout << "This Automata is not DFA" << endl;
			return;
		}
	}
	ofstream output(filename);
	int *Mark, *MarkNext, MarkNum, NOS = getNumberOfStates(), number_of_alphabets = (int) (sigma.size()), isDiff = 1;
	bool isSame = 0;
	Mark = new int[getNumberOfStates()];
	MarkNext = new int[getNumberOfStates()];
	if (NOS == 1)
	{
		cout << "one state only" << endl;
		return;
	}

	for (int i = 0; i < NOS; i++) Mark[i] = internal_states[i]->isFinalState();

	cout << "Making minimal DFA..." << endl;

	cout << "****************************************************************" << endl;
	while (isDiff)
	{
		MarkNext[0] = 0; MarkNum = 0, isDiff = 0;

		for (int i = 1; i < NOS; i++)
		{
			isSame = 0;
			for (int j = 0; j < i; j++)
			{
				if (isSame) break;
				if (Mark[i] == Mark[j])
					for (int k = 0; k < number_of_alphabets; k++)
					{
						if (Mark[transitionWithState(internal_states[i], sigma[k])->getId()] != Mark[transitionWithState(internal_states[j], sigma[k])->getId()])
						{
							isDiff++;
							break;
						}

						if (k == number_of_alphabets - 1)
						{
							MarkNext[i] = MarkNext[j];
							isSame = true;
						}
					}

				if (j == i - 1 && isSame != true)
				{
					MarkNum++;
					MarkNext[i] = MarkNum;
				}
			}
		}

		for (int i = 0; i < NOS; i++)
			cout << internal_states[i]->getLabel() << " : Marked with " << Mark[i] << endl;

		if (isDiff)
		{
			cout << "************бщ************" << endl;
		}

		for (int i = 0; i < NOS; i++)
			Mark[i] = MarkNext[i];


	}
	cout << "****************************************************************" << endl;
	MarkNum++;

	output << "alphabet [";
	for (int i = 0; i < sigma.size(); i++)
	{
		output << sigma[i];
		if (i != sigma.size() - 1) output << " ";
	}
	output << "]" << endl;

	output << "state [";
	for (int i = 0; i < MarkNum; i++)
	{
		output << "S" << i;
		if (i != MarkNum - 1) output << " ";
	}
	output << "]" << endl;

	output << "initial [S" << Mark[initial_state->getId()] << "]" << endl;

	output << "final [";
	for (int i = 0; i < MarkNum; i++)
	{
		for (int j = 0; j < NOS; j++)
		{
			if (Mark[j] == i && internal_states[j]->isFinalState() == 1)
			{
				output << "S" << i;
				if (i != MarkNum - 1) output << " ";
				break;
			}
		}
	}
	output << "]" << endl;

	output << "delta [";
	for (int i = 0; i < MarkNum; i++)
		for (int j = 0; j < NOS; j++)
			if (Mark[j] == i)
			{
				for (int k = 0; k < sigma.size(); k++)
				{
					output << "(S" << i << "," << sigma[k] << "," << "S" << Mark[transitionWithState(internal_states[j], sigma[k])->getId()] << ")";
					if (!(i == MarkNum - 1 && j == NOS - 1 && k == sigma.size() - 1)) output << " ";
				}
				break;
			}

	output << "]" << endl;

	cout << "The output file for minimalDFA " << filename << " is made!" << endl;

}

Automaton::~Automaton()
{
	for (auto i : internal_states)
		delete i;
}

