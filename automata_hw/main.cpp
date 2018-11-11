#include "header.h"
void parsing(string filename, vector<char>* sigma, vector<string>* states, vector<string>* finalstates, vector<string>* delta, string* initial);

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


	vector<char> sigmaIn, sigmaOut;
	vector<string> statesIn, statesOut;
	vector<string> finalStatesIn, finalStatesOut;
	vector<string> deltaIn, deltaOut;
	string initialIn, initialOut;
	string input;
	parsing(filename, &sigmaIn, &statesIn, &finalStatesIn, &deltaIn, &initialIn);
	Automaton automatonIn(sigmaIn, statesIn, initialIn, finalStatesIn, deltaIn);

	if (debug)
	{
		cout << "*********************************DEBUG*********************************"<<endl;
		printInput(sigmaIn, statesIn, initialIn, finalStatesIn, deltaIn);
		automatonIn.showStatus();
		cout << "*********************************DEBUG*********************************"<<endl<<endl;

	}

	automatonIn.makeMinimal(fileOutput);

	parsing(fileOutput, &sigmaOut, &statesOut, &finalStatesOut, &deltaOut, &initialOut);

	Automaton automaton(sigmaOut, statesOut, initialOut, finalStatesOut, deltaOut);

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

void parsing(string filename, vector<char>* sigma, vector<string>* states, vector<string>* finalStates, vector<string>* delta, string* initial)
{
	ifstream in(filename);
	char inBuffer[MAX_SIZE];


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
					sigma->push_back(i.c_str()[0]);
			break;
			//states
		case 's':
			for (auto i : stringVector)
				if (i != "")
					states->push_back(i);
			break;
			//initial state
		case 'i':
			if (stringVector.size() != 1)
			{
				cout << PARSE_ERR << endl;
				exit(1);
			}
			*initial = stringVector[0];
			break;
			//final states
		case 'f':
			for (auto i : stringVector)
				if (i != "")
					finalStates->push_back(i);
			break;
			//delta
		case 'd':
			for (auto i : stringVector)
				if (i != "")
					delta->push_back(i);
			break;
		default:
			break;
		}
	}

	//check whether initial is  in internal states
	if (initCheck(*states, *initial))
	{
		cout << NO_INIT_IN_STATES << endl;
		cout << "initial = " << initial << endl;
		cout << "but internal states = ";
		for (auto i : *states)
			cout << i << " ";
		cout << endl;
		exit(1);
	}

	//check whether all final states are in internal states
	if (finalCheck(*states, *finalStates))
	{
		cout << NO_FINAL_IN_STATES << endl;
		cout << "final states = ";
		for (auto i : *finalStates)
			cout << i << " ";
		cout << endl;
		cout << "but internal states = ";
		for (auto i : *states)
			cout << i << " ";
		cout << endl;
		exit(1);
	}

}