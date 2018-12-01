#include "Player.h"
#include <algorithm>
#include <vector>

Player::Player()
{
	init();
}

Player::Player(string name_)
{
	name = name_;
	init();
}


Player::~Player()
{
	for (auto settlement : mySettlements)	// Deletes mySettlement
	{
		delete settlement.second;
	}
	for (auto settlement : rivalsSettlements)	// Deletes rivalsSettlement
	{
		delete settlement.second;
	}
	for (auto road : myRoads)	// Deletes myRoads
	{
		delete road.second;
	}
	for (auto road : rivalsRoads)	// Deletes rivalsRoads
	{
		delete road.second;
	}
}

void Player::init()
{
	victoryPoints = 0;
	iWon = false;
	mySettlements.clear();
	myRoads.clear();
	rivalsRoads.clear();
	rivalsSettlements.clear();
	availableForRoad.clear();
	allVertexesAvailable();

	resources[M] = 0;
	resources[L] = 0;
	resources[P] = 0;
	resources[T] = 0;
	resources[O] = 0;
	resources[N] = 0;

}

size_t Player::getVictoryPoints()
{
	return victoryPoints;
}

string Player::getName()
{
	return name;
}

bool Player::hasWon()
{
	return iWon;
}

void Player::addResource(ResourceType resource, int amount)
{
	resources[resource] += amount;
}

bool Player::useResource(ResourceType resource, int amount)
{
	if (resources[resource] > amount)
	{
		resources[resource] -= amount;
		return true;
	}
	else
	{
		return false;
	}
}

void Player::addToMySettlements(string position)
{
	Settlement* newSettlement = new Settlement(position);
	mySettlements.insert(pair< string, Settlement* >(position, newSettlement));
	updateAvailability();
}

void Player::addToRivalsSettlements(string position)
{
	Settlement* newSettlement = new Settlement(position);
	rivalsSettlements.insert(pair< string, Settlement* >(position, newSettlement));
	updateAvailability();
}

void Player::addToMyRoads(string position)
{
	Road* newRoad = new Road(position);
	myRoads.insert(pair< string, Road* >(position, newRoad));
	updateAvailability();
}

void Player::addToRivalsRoads(string position)
{
	Road* newRoad = new Road(position);
	rivalsRoads.insert(pair< string, Road* >(position, newRoad));
	updateAvailability();
}

void Player::promoteToMyCity(string position)
{
	if (mySettlements.find(position) != mySettlements.end())
	{
		delete mySettlements[position];
		Settlement* newCity = new City(position);
		mySettlements[position] = newCity;
	}
}

void Player::promoteToRivalsCity(string position)
{
	if (rivalsSettlements.find(position) != rivalsSettlements.end())
	{
		delete rivalsSettlements[position];
		Settlement* newCity = new City(position);
		rivalsSettlements[position] = newCity;
	}
}

bool Player::checkSettlementAvailability(string position)
{
	return (find(availableForSettlement.begin(), availableForSettlement.end(), position) == availableForSettlement.end());
}

bool Player::checkRoadAvailability(string position)
{
	return (find(availableForRoad.begin(), availableForRoad.end(), position) == availableForRoad.end());
}

void Player::allVertexesAvailable()
{
	availableForSettlement = allVertexes;
}

void Player::updateAvailability()
{
	/* Primero veo los settlements */
	availableForSettlement.clear();

	if (mySettlements.size() >= 2)
	{
		map<string, Road*>::iterator itr;
		for (itr = myRoads.begin(); itr != myRoads.end(); itr++)
		{
			/*agrego todos los posibles lugrares disponibles*/
			string edge = itr->first;
			if (edge[0] >= '0' && edge[0] <= '9')
			{
				if (edge.size() == 3) // eston son los casos especiales que se especifica el final
				{
					availableForSettlement.push_back(edge.substr(0, 2)); // este es uno de los vertices
					char aux = edge[2];
					edge.pop_back();
					if (aux <= edge[0])
						edge.insert(edge.begin(), aux);
					else if (aux <= edge[1])
						edge.insert(edge.begin() + 1, aux);
					else
						edge.push_back(aux);
					availableForSettlement.push_back(edge);
				}
				else //son las 1 numero + 1letra
				{
					string aux = edge;
					char a = edge[0] - '0';
					aux.insert((a == 5 ? aux.begin() : aux.begin() + 1), (a == 5 ? '0' : '0' + a + 1)); //rancio pero funcional
					availableForSettlement.push_back(aux);
					aux = edge;
					aux.insert(aux.begin() + (a < 3 ? 1 : 2), edge[1] + (a < 3 ? -1 : 1) * ((a % 3) % 2 ? a % 3 + 1 : a % 3 + 4));
					availableForSettlement.push_back(aux);
				}
			}
			else
			{
				for (string a : allVertexes)
				{
					// si este vertice tiene las dos letras de la arista, lo agrego como posible
					if ((a.find(edge[0]) != a.npos) && (a.find(edge[1]) != a.npos))
					{
						availableForSettlement.push_back(a);
					}
				}
			}
		} // aca tengo las posibles todas, ahora tengo que sacar por la regla de 2 vertices
	}
	else // estoy en el principio
	{
		availableForSettlement = allVertexes;
	}
	//ahora saco los ocupados o los de la regla de dos espacios

	list<string>::iterator vertex;
	for (vertex = availableForSettlement.begin(); vertex != availableForSettlement.end();vertex++)
	{
		int row=0, colum=0;
		while (boardInStrings[row][colum] != *vertex) // encueltro el vertice en la super matriz
		{
			row++;
			if (row == 14)
			{
				row = 0;
				colum++;
			}
		}

		vector<string> tempVert;
		tempVert.push_back(boardInStrings[row - 1][colum - 1]);
		tempVert.push_back(boardInStrings[row - 1][colum]);
		tempVert.push_back(boardInStrings[row - 1][colum + 1]);
		tempVert.push_back(boardInStrings[row][colum - 1]);
		tempVert.push_back(boardInStrings[row][colum + 1]);
		tempVert.push_back(boardInStrings[row + 1][colum - 1]);
		tempVert.push_back(boardInStrings[row + 1][colum]);
		tempVert.push_back(boardInStrings[row + 1][colum + 1]);

		for (bool fin = false, int i = 0; i < 8 && !fin; i++)
		{
			if ((mySettlements.find(tempVert[i]) != mySettlements.end()) || (rivalsSettlements.find(tempVert[i]) != rivalsSettlements.end()) )
			{
				availableForSettlement.erase(vertex); // esto hay que ver si funciona pq se corre el itertor y me puede cagar el for
				fin = false;
			}
		}
	}
	/* Fin del chaequeo de los vertices para los settlements */

	/* Turno de los vertices disponibles */
	availableForRoad.clear();

	for (pair<string,Settlement*> vertx : mySettlements)
	{
		if (vertx.first[0] >= '0' && vertx.first[0] <= '9')
		{
			if (vertx.first.length() == 3) // si es la de 2 num + 1 letra
			{
				if (!vertx.first.compare("05A")) // el unico de los 6 que es distinto
				{
					availableForRoad.push_back("5A");
					availableForRoad.push_back("0A5");
				}
				else
				{
					string aux_ = vertx.first;
					aux_.erase(aux_.begin() + 1);
					availableForRoad.push_back(aux_);
					aux_ = vertx.first;
					aux_.erase(aux_.begin());
					aux_.push_back(vertx.first[0]);
					availableForRoad.push_back(aux_);
				}
			}
			else
			{
				for (string str : allEdges)
				{
					if (str.find(vertx.first[0]) != str.end && str.find(vertx.first[1]) != str.end) // las aristas que contengan ambos caracteres
					{
						availableForRoad.push_back(str);
					}
				}
			}
		}
		else // los edge aledaños son combinaciones de las letras, easy to solve(?
		{
			string temp;
			temp.push_back(vertx.first[0]);
			temp.push_back(vertx.first[1]);
			availableForRoad.push_back(temp);
			temp[1] = vertx.first[2];
			availableForRoad.push_back(temp);
			temp[0] = vertx.first[1];
			availableForRoad.push_back(temp);
		}
	}
	//ahora que ya tengo todas las disponibles, tengo que sacar las ocupadas
	for (vertex = availableForRoad.begin(); vertex != availableForRoad.end(); vertex++)
	{
		if (myRoads.find(*vertex) != myRoads.end() || rivalsRoads.find(*vertex) != rivalsRoads.end())
		{
			availableForRoad.erase(vertex); // creo que se rompe el for con esto
		}
	}
	
}
