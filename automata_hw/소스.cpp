#include "Çì´õ.h"

using namespace std;

int main()
{
	char alphabet;
	char ch;
	set<char> sigma;

	bool loop = true;
	while (loop)
	{
		cout << "input alphabet : ";
		cin >> alphabet;
		sigma.insert(alphabet);
		cout << "press enter to continue, escape to end" << endl;
		ch = getch();
		if (ch == 27)
			loop = false;
	}
	cout << "loop terminated." << endl;
	cout << "alphabets are ";
	for (auto i : sigma)
	{
		cout << i << " ";
	}
	cout <<"size : "<<endl<<sigma.size()<< endl;

	Automaton automaton(sigma);

	return 0;
}