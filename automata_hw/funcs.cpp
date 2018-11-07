#include "header.h"

void printInput(vector<char> sigma, vector<string>states, string initial, vector<string>finalStates, vector<string>delta)
{
	cout << "sigma : " << sigma.size() << "->";
	for (auto i : sigma)
		cout << i << " ";
	cout << endl;

	cout << "states : " << states.size() << "->";
	for (auto i : states)
		cout << i << " ";
	cout << endl;

	cout << "initial : " << initial << endl;

	cout << "final : " << finalStates.size() << "->";
	for (auto i : finalStates)
		cout << i << " ";
	cout << endl;

	cout << "delta : " << delta.size() << "->";
	for (auto i : delta)
		cout << i << " ";
	cout << endl;
}

//return true if err
bool initCheck(vector<string> states, string initial)
{
	bool flag = true;
	for (auto i : states)
	{
		if (i == initial)
			flag = false;
	}

	return flag;
}

//return true if err
bool finalCheck(vector<string>states, vector<string>finalStates)
{
	for (auto i : finalStates)
	{
		bool flag = true;

		for (auto j : states)
		{
			if (i == j)
				flag = false;
		}

		if (flag == true)
			return true;

	}

	return false;
}

std::vector<std::string> split(const std::string& s, char delimiter)
{
	std::vector<std::string> tokens;
	std::string token;
	std::istringstream tokenStream(s);
	while (std::getline(tokenStream, token, delimiter))
	{
		tokens.push_back(token);
	}
	return tokens;
}
