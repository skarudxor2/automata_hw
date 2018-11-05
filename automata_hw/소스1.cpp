#include "Çì´õ.h"


State::State(int id, bool isFinal)
	: id(id), isFinal(isFinal)
{

	
}

Automaton::Automaton(set<char> sigma)
	: sigma(sigma), number_of_states(0)
{
	initial_state = new State(0);
	internal_states.push_back(initial_state);
}

void Automaton::create_state(int *transition)
{


}