#include "header.h"

int main(int argc, char *argv[])
{

	if (argc != 3)
	{
		cout << "invalid number of files. please excute with one input file and one output file" << endl;
		exit(1);
	}


	bool debug = true;

	string filename = argv[1];
	string fileOutput = argv[2];
	cout << "input file name : " << filename << endl << endl;
	ifstream in(filename);
	char inBuffer[MAX_SIZE];

	vector<char> sigma;
	vector<string> states;
	vector<string> finalStates;
	vector<string> delta;
	string initial;
	string input;

	//parsing
	while (!in.eof())
	{
		in.getline(inBuffer, 500);
		string inString(inBuffer);
		char token = inString[0];
		vector<string> stringVector;

		stringVector = split(inString, '[');
		if (stringVector.size() <= 1)
		{
			continue;
		}
		stringVector = split(stringVector[1], ']');
		inString = stringVector[0];
		stringVector = split(inString, ' ');

		switch (token)
		{
			//alphabet
			case 'a':
				for (auto i : stringVector)
					if (i != "")
						sigma.push_back(i.c_str()[0]);
				break;
				//states
			case 's':
				for (auto i : stringVector)
					if (i != "")
						states.push_back(i);
				break;
				//initial state
			case 'i':
				if (stringVector.size() != 1)
				{
					cout << PARSE_ERR << endl;
					exit(1);
				}
				initial = stringVector[0];
				break;
				//final states
			case 'f':
				for (auto i : stringVector)
					if (i != "")
						finalStates.push_back(i);
				break;
				//delta
			case 'd':
				for (auto i : stringVector)
					if (i != "")
						delta.push_back(i);
				break;
			default:
				break;
		}
	}

	//check whether initial is  in internal states
	if (initCheck(states, initial))
	{
		cout << NO_INIT_IN_STATES << endl;
		cout << "initial = " << initial << endl;
		cout << "but internal states = ";
		for (auto i : states)
			cout << i << " ";
		cout << endl;
		exit(1);
	}

	//check whether all final states are in internal states
	if (finalCheck(states, finalStates))
	{
		cout << NO_FINAL_IN_STATES << endl;
		cout << "final states = ";
		for (auto i : finalStates)
			cout << i << " ";
		cout << endl;
		cout << "but internal states = ";
		for (auto i : states)
			cout << i << " ";
		cout << endl;
		exit(1);
	}

	Automaton automaton(sigma, states, initial, finalStates, delta);

	if (debug)
	{
		cout << "*********************************DEBUG*********************************"<<endl;
		printInput(sigma, states, initial, finalStates, delta);
		automaton.showStatus();
		cout << "*********************************DEBUG*********************************"<<endl<<endl;

	}
	automaton.makeMinimal(fileOutput);

	cout << "enter input string : ";
	cin >> input;

	string initialLabel = automaton.getCurrentState()->getLabel();
	string isFinal, isAcc;
	string::iterator iter;

	cout << "initial state = " << initialLabel << endl;
	cout << initialLabel;
	for (iter = input.begin(); iter != input.end(); ++iter)
	{
		string curLabel;
		automaton.transition(*iter);
		curLabel = automaton.getCurrentState()->getLabel();
		cout << " -> "<<curLabel;
	}
	cout << endl;

	isFinal = automaton.getCurrentState()->isFinalState() ? "final" : "not a final";
	isAcc = automaton.isAccepted() ? "accpted" : "not accepted";
	cout << "current state " << automaton.getCurrentState()->getLabel() << " is " + isFinal + " state.";
	cout << " thus input string is " + isAcc << "." << endl;

	return 0;
}
