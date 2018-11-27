#include <iostream>
#include "NewEventHandling.h"
#include "NewGenericFSM.h"
#include "simpleEventGenerator.h"

enum implStates : stateTypes { State0, State1, State2, State3 };

using namespace std;
class FSMImplementation : public genericFSM
{
	void deleteTable()
	{
		for (auto const& x : MyFSMTable)
		{
			for (auto const& y : x.second)
			{
				delete y.second;
			}
		}
	}

private:
	fsmCell cell1;
#define TX(x) (static_cast<void (genericFSM::* )(genericEvent *)>(&FSMImplementation::x))
#define CELL(x,y,z) x,new fsmCell(y,TX(z))
	const fsmTable MyFSMTable = {
		
		{State0,{
			{CELL(EventA,State0,prueba1)},
			{CELL(EventB,State1,prueba2)},//CELL(EventB,State2,prueba2)}
			{CELL(EventC,State2,prueba3)},
			{CELL(EventD,State3,prueba4)}
				}
		},
		{State1,{
			{CELL(EventA,State1,prueba1)},
			{CELL(EventB,State2,prueba2)},//CELL(EventB,State2,prueba2)}
			{CELL(EventC,State3,prueba3)},
			{CELL(EventD,State0,prueba4)}
			
				}

		},
		{State2,{
			{CELL(EventA,State2,prueba1)},
			{CELL(EventB,State3,prueba2)},//CELL(EventB,State2,prueba2)}
			{CELL(EventC,State0,prueba3)},
			{CELL(EventD,State1,prueba4)}
				}
		},
		{State3,{
			{CELL(EventA,State3,prueba1)},
			{CELL(EventB,State0,prueba2)},//CELL(EventB,State2,prueba2)}
			{CELL(EventC,State1,prueba3)},
			{CELL(EventD,State2,prueba4)}
				}
		}
		
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

public:
	FSMImplementation() : genericFSM((auxFsmTable)&MyFSMTable, State0) {}
};


int main(int argc, char** argv)
{
	FSMImplementation fsm;
	simpleEventGenerator s;
	mainEventGenerator eventGen;

	eventGen.attach(&s);

	bool quit = false;
	do
	{
		genericEvent * ev;
		ev = eventGen.getNextEvent();
		if (ev->getType() == EventQuit)
		{
			quit = true;
			delete ev;
		}
		else
			fsm.cycle(ev);
	} while (!quit);

	system("pause");
	return 0;
}



