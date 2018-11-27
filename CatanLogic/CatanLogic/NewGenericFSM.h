#pragma once
#include "NewEventHandling.h"
#include<map>

class genericFSM;
using StateTypes = unsigned int;

struct FsmCell
{
	StateTypes nextState;
	void (genericFSM::*action)(genericEvent *);
};

struct StateMap
{
	std::map< eventTypes, FsmCell > acceptedEventsMap;		// Every state has a map of accepted events with their corresponding FsmCells.
	FsmCell defaultCell;									// And a cell that contains the information of what to do when the event that arrived is not in the current state's map.
};

using FsmMap = std::map< StateTypes, StateMap >;





class genericFSM : public eventGenerator
{
public:

	genericFSM( const FsmMap fsmMap_, StateTypes initState);
	genericEvent * getEvent();
	void cycle(genericEvent * ev);

private:
	StateTypes state;
	genericEvent * fsmEvent = nullptr;

	
	FsmMap fsmMap;
};


/******************       The fsm should be initialised like this       ********************/

/*
enum eventTypes { Ev0, Ev1, Ev2, Ev3, Ev4 };
enum implStates : StateTypes { State0, State1, State2, State3 };

class FSMImplementation : public genericFSM
{


private:

#define TX(x) (static_cast<void (genericFSM::* )(genericEvent *)>(&FSMImplementation::x))

	const FsmMap testFsmMap = {
		{ State0, { {	{ Ev0, { State1, TX(prueba1) } },
						{ Ev1, { State2, TX(prueba2) } }
					},
					{ State0, TX(default1) }}},

		{ State1, { {	{ Ev3, { State3, TX(prueba3) } },
						{ Ev4, { State2, TX(prueba4) } }
					},
					{ State1, TX(default2) }}},

		{ State2, { {	{ Ev3, { State3, TX(prueba3) } },
						{ Ev4, { State2, TX(prueba4) } },
						{ Ev0, { State0, TX(prueba1) } }
					},
					{ State2, TX(default3) }}},

		{ State3, { {	{ Ev1, { State3, TX(prueba3) } }
					},
					{ State3, TX(default4) }}}
	};

	//The action routines for the FSM
	//These actions should not generate fsmEvents

	void prueba1(genericEvent * ev)
	{
		cout << "prueba 1" << endl;
		return;
	}
	void prueba2(genericEvent * ev)
	{
		cout << "prueba 2" << endl;
		return;
	}
	void prueba3(genericEvent * ev)
	{
		cout << "prueba 3" << endl;
		return;
	}
	void prueba4(genericEvent * ev)
	{
		cout << "prueba 4" << endl;
		return;
	}

	void default1(genericEvent * ev)
	{
		cout << "default 1" << endl;
		return;
	}
	void default2(genericEvent * ev)
	{
		cout << "default 2" << endl;
		return;
	}
	void default3(genericEvent * ev)
	{
		cout << "default 3" << endl;
		return;
	}
	void default4(genericEvent * ev)
	{
		cout << "default 4" << endl;
		return;
	}

public:
	FSMImplementation() : genericFSM(testFsmMap, State0) {}
};*/