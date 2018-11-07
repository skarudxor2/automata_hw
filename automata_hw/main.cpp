#include "header.h"


#define MAX_SIZE 1000

const string PARSE_ERR = "parsing err!";
const string NO_INIT_IN_STATES = "initial state is not exists in states";
const string NO_FINAL_IN_STATES = "some final states are not exists in states";

std::string DirectoryContaining(const std::string &filename)
{
	// This code isn't tested but I believe it should work. Might need to add
	// some const_casts to make it compile though.
	char drive[_MAX_DRIVE];
	char dir[_MAX_DIR];
	char ext[_MAX_EXT];

	errno_t err = _splitpath_s(filename.c_str(), drive, _MAX_DRIVE, dir,
							   _MAX_DIR, nullptr, 0, ext, _MAX_EXT);
	if (err == 0)
	{
		char fullDir[_MAX_PATH];
		err = _makepath_s(fullDir, _MAX_PATH, drive, dir, nullptr, nullptr);
		if (err == 0) return std::string(fullDir);
	}
	return filename;
}


int main(int argc, char *argv[])
{
	if (argc != 2)
	{
		cout << "invalid number of input file. please excute with one input file" << endl;
		exit(1);
	}



	string filename = argv[1];
	cout << "input file name : " << filename << endl<<endl;
	ifstream in(filename);
	char inBuffer[MAX_SIZE];

	vector<char> sigma;
	vector<string> states;
	vector<string> finalStates;
	vector<string> delta;
	string initial;



	vector<string> stringVector;
	while (!in.eof())
	{
		in.getline(inBuffer, 500);
		string inString(inBuffer);
		char token = inString[0];

		stringVector = split(inString, '[');
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
					if(i!="")
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
					if(i!="")
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
	if (initCheck(states,initial))
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


	printInput(sigma, states, initial, finalStates, delta);


	Automaton automaton(sigma);

	return 0;
}