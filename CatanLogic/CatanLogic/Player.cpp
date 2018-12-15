#include "Player.h"
#include <algorithm>
#include <vector>
#include <functional>

#define TX(x) (static_cast<void (Player::* )()>(&Player::x))
#define MAX_SETTLEMENTS 5
#define MAX_ROADS 15
#define MAX_CITIES 4

Player::Player()
{
	init();
}

Player::Player(string name_, BasicGUI* GUI_)
{
	init();
	name = name_;
	setGUI(GUI_);
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

void Player::setGUI(BasicGUI* GUI_)
{
	GUI = GUI_;
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

	remainingSettlements = MAX_SETTLEMENTS;
	remainingRoads = MAX_ROADS;
	remainingCities = MAX_CITIES;

	longestRoadCard = false;
	longestRoad = 0;
	largestArmyCard = false;
	army = 0;

	resources[BOSQUE] = 0;
	resources[COLINAS] = 0;
	resources[MONTAÑAS] = 0;
	resources[CAMPOS] = 0;
	resources[PASTOS] = 0;
	resources[DESIERTO] = 0;

	devCards[KNIGHT] = { 0, useKnight };
	devCards[VICTORY_POINTS] = { 0, useVictoryPoint };
	devCards[MONOPOLY] = { 0, useMonopoly };
	devCards[YEARS_OF_PLENTY] = { 0, useYearsOfPlenty };
	devCards[ROAD_BUILDING] = { 0, useRoadBuilding };
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
	size_t totalVictoryPoints = victoryPoints + cardVictoryPoints;
	if (hasLongestRoad())
	{
		totalVictoryPoints++;
	}
	if (hasLargestArmy())
	{
		totalVictoryPoints++;
	}
	if (totalVictoryPoints >= 10)
	{
		iWon = true;
	}
	else
	{
		iWon = false;
	}

	return iWon;
}

void Player::addResource(ResourceType resource, int amount)
{
	resources[resource] += amount;

	notifyAllObservers();
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

	notifyAllObservers();
}

size_t Player::totalResourcesAmount()
{
	size_t total = 0;
	for (auto res : resources)
	{
		total += res.second;
	}
	return total;
}

size_t Player::getResourceAmount(ResourceType resource)
{
	return resources[resource];
}

void Player::addToMySettlements(string position)
{
	Settlement* newSettlement = new Settlement(position);
	mySettlements.insert(pair< string, Settlement* >(position, newSettlement));

	useResource(COLINAS);
	useResource(BOSQUE);
	useResource(CAMPOS);
	useResource(PASTOS);

	incVictoryPoints();
	remainingSettlements--;

	updateAvailability();

	notifyAllObservers();
}

void Player::addToRivalsSettlements(string position)
{
	Settlement* newSettlement = new Settlement(position);
	rivalsSettlements.insert(pair< string, Settlement* >(position, newSettlement));

	updateAvailability();

	notifyAllObservers();
}

void Player::addToMyRoads(string position)
{
	Road* newRoad = new Road(position, getAdjacentVertexes(position));
	myRoads.insert(pair< string, Road* >(position, newRoad));

	useResource(COLINAS);
	useResource(BOSQUE);

	updateAvailability();
	updateLongestRoad(position);
	remainingRoads--;

	notifyAllObservers();
}

void Player::addToRivalsRoads(string position)
{
	Road* newRoad = new Road(position, getAdjacentVertexes(position));
	rivalsRoads.insert(pair< string, Road* >(position, newRoad));

	updateAvailability();

	notifyAllObservers();
}

void Player::promoteToMyCity(string position)
{
	if (mySettlements.find(position) != mySettlements.end())
	{
		delete mySettlements[position];
		Settlement* newCity = new City(position);
		mySettlements[position] = newCity;

		useResource(CAMPOS, 2);
		useResource(MONTAÑAS, 3);

		incVictoryPoints();
		incVictoryPoints();
		remainingCities--;
		remainingSettlements++;

		notifyAllObservers();
	}
}

void Player::promoteToRivalsCity(string position)
{
	if (rivalsSettlements.find(position) != rivalsSettlements.end())
	{
		delete rivalsSettlements[position];
		Settlement* newCity = new City(position);
		rivalsSettlements[position] = newCity;

		notifyAllObservers();
	}
}

size_t Player::getRemainingSettlements()
{
	return remainingSettlements;
}

size_t Player::getRemainingRoads()
{
	return remainingRoads;
}

size_t Player::getRemainingCities()
{
	return remainingCities;
}

list<string> Player::getMySettlements()
{
	list<string> ret;
	for (auto building : mySettlements)
	{
		if (building.second->whatAmI().compare("Settlement"))
		{
			ret.push_back(building.first);
		}
	}
	return ret;
}

list<string> Player::getMyCities()
{
	list<string> ret;
	for (auto building : mySettlements)
	{
		if (building.second->whatAmI().compare("City"))
		{
			ret.push_back(building.first);
		}
	}
	return ret;
}

list<string> Player::getMyRoads()
{
	list<string> ret;
	for (auto building :myRoads)
	{
		ret.push_back(building.first);
	}
	return ret;
}

bool Player::checkSettlementAvailability(string position)
{
	bool ret = (find(availableForSettlement.begin(), availableForSettlement.end(), position) == availableForSettlement.end());	// Check if position is available.
	ret &= checkSettlementResources();																							// Check if player has resources.
	ret &= getRemainingSettlements();																							// Check if player has Settlements left to put.

	return ret;
}

bool Player::checkRoadAvailability(string position)
{
	bool ret = (find(availableForRoad.begin(), availableForRoad.end(), position) == availableForRoad.end());					// Check if position is available.
	ret &= checkRoadResources();																								// Check if player has resources.
	ret &= getRemainingRoads();																									// Check if player has remaining Roads to put.

	return ret;
}

bool Player::checkPromotionOfCity(string position)
{
	bool ret = (mySettlements.find(position) != mySettlements.end());		// Check if there's a Settlement in that position.
	ret &= checkCityResources();											// Check if player has resources.
	ret &= getRemainingCities();											// Check if player has Cities left to put.

	return ret;
}

bool Player::checkResourcesForBankTrade(PortType type)
{
	switch (type)
	{
	case _4x1:
	{
		bool ret = false;
		for (auto res : resources)
		{
			ret |= getResourceAmount(res.first) >= 4;
		}
		return ret;
	}
		break;
	case _3x1:
	{
		bool ret = false;
		for (auto res : resources)
		{
			ret |= getResourceAmount(res.first) >= 3;
		}
		return ret;
	}
		break;
	case _2Tx1: return (getResourceAmount(CAMPOS) >= 2);
		break;
	case _2Ox1: return (getResourceAmount(PASTOS) >= 2);
		break;
	case _2Lx1: return (getResourceAmount(COLINAS) >= 2);
		break;
	case _2Px1: return (getResourceAmount(MONTAÑAS) >= 2);
		break;
	case _2Mx1: return (getResourceAmount(BOSQUE) >= 2);
		break;
	default:
		break;
	}
}

void Player::getNewDevCard(Board * board)
{
	devCards[board->pickDevCard()].amount++;

	useResource(CAMPOS);
	useResource(PASTOS);
	useResource(MONTAÑAS);
}

void Player::useDevCard(DevCards card)
{
	if (devCards[card].amount)
	{
		auto f = bind(devCards[card].useDevCard, this);
		f();

		notifyAllObservers();
	}
}

size_t Player::getDevCardAmount(DevCards card)
{
	return devCards[card].amount;
}

bool Player::checkResourcesForDevCard()
{
	if (resources[PASTOS] >= 1 && resources[CAMPOS] >= 1 && resources[MONTAÑAS] >= 1)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool Player::isThereDevCard(DevCards card)
{
	if (devCards[card].amount)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool Player::hasLongestRoad()
{
	return longestRoadCard;
}

void Player::setLongestRoadCard(bool doesItHaveTheCard)
{
	longestRoadCard = doesItHaveTheCard;
}

size_t Player::getLongestRoad()
{
	return longestRoad;
}

void Player::updateLongestRoad(string startingEdge)
{
	roadsVisited.clear();															// Clears any residue from previous calculations.
	vector< string > startingVertexes = getAdjacentVertexes(startingEdge);

	for (auto vertex : startingVertexes)
	{
		followRoad(vertex);															// Follows Road to both sides, filling roadsVisited.
	}

	size_t roadLength = roadsVisited.size();										// Length of road calculated.
	if (roadLength > longestRoad)
	{
		longestRoad = roadLength;													// Updates if there's a new longestRoad.
	}

	notifyAllObservers();
}

bool Player::hasLargestArmy()
{
	return largestArmyCard;
}

void Player::setLargestArmyCard(bool doesItHaveTheCard)
{
	largestArmyCard = doesItHaveTheCard;
}

size_t Player::getArmySize()
{
	return army;
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
		vector<string> posibles = getAdjacentEdges(vertx.first);
		for (string a : posibles)
		{
			availableForRoad.push_back(a);
		}
	}
	availableForRoad.unique(); // filtro los que puedan estar repetidos
	//ahora que ya tengo todas las disponibles, tengo que sacar las ocupadas
	for (vertex = availableForRoad.begin(); vertex != availableForRoad.end(); vertex++)
	{
		if (myRoads.find(*vertex) != myRoads.end() || rivalsRoads.find(*vertex) != rivalsRoads.end())
		{
			availableForRoad.erase(vertex); // creo que se rompe el for con esto
		}
	}
	
	notifyAllObservers();
}

bool Player::checkSettlementResources()
{
	bool ret = true;
	ret &= resources[COLINAS] >= 1;																								// Using brick.
	ret &= resources[BOSQUE] >= 1;																								// Using wood.
	ret &= resources[CAMPOS] >= 1;																								// Using wheat.
	ret &= resources[PASTOS] >= 1;																								// Using wool.

	return ret;
}

bool Player::checkRoadResources()
{
	bool ret = true;
	ret &= resources[COLINAS] >= 1;																								// Using brick.
	ret &= resources[BOSQUE] >= 1;																								// Using wood.

	return ret;
}

bool Player::checkCityResources()
{
	bool ret = true;
	ret &= resources[CAMPOS] >= 2;											// Using wheat.
	ret &= resources[MONTAÑAS] >= 3;										// Using rock.

	return ret;
}

bool Player::isThereSetOrCity(char token)
{
	for (auto set : mySettlements)
	{
		if (set.first.find(token) != string::npos)
		{
			return true;
		}
	}
	return false;
}

bool Player::checkIfIsPort(string position, Board* board)
{
	if (board->checkIfIsPort(position))
	{
		if (checkResourcesForBankTrade(board->getPortType(position)))
		{
			return true;
		}
	}
	return false;
}

bool Player::checkForAnyPort(Board * board, PortType port_)
{
	for (auto settlement : mySettlements)
	{
		if (board->checkIfIsPort(settlement.first))
		{
			if (board->getPortType(settlement.first) == port_)
			{
				return true;
			}
		}
	}
	return false;
}

void Player::makeBankTrade(PortType type, ResourceType resourceAsked, ResourceType resourcesOffered)
{
	switch (type)
	{
	case _4x1: { useResource(resourcesOffered, 4); addResource(resourceAsked); }
		break;
	case _3x1: { useResource(resourcesOffered, 3); addResource(resourceAsked); }
		break;
	case _2Tx1: { useResource(CAMPOS, 2); addResource(resourceAsked); }
		break;
	case _2Ox1: { useResource(PASTOS, 2); addResource(resourceAsked); }
		break;
	case _2Lx1: { useResource(COLINAS, 2); addResource(resourceAsked); }
		break;
	case _2Px1: { useResource(MONTAÑAS, 2); addResource(resourceAsked); }
		break;
	case _2Mx1: { useResource(BOSQUE, 2); addResource(resourceAsked); }
		break;
	default:
		break;
	}

	notifyAllObservers();
}

void Player::incVictoryPoints()
{
	victoryPoints++;

	hasWon();
	notifyAllObservers();
}

vector< string > Player::getAdjacentVertexes(string edge)
{
	vector< string > adVert;
	
	if (edge.size() == 2)																		// For edges nominated by two tokens.
	{
		for (auto vert : allVertexes)
		{
			if (vert.find(edge[0]) != string::npos && vert.find(edge[1]) != string::npos)		// If the vertex coordinate contains both tokens of the edge coordinate...
			{
				adVert.push_back(vert);															// Is one of the two adjacent vertexes.
			}
		}
	}
	else if (edge.size() == 3)																	// For edges nominated by three tokens.
	{
		for (auto vert : allVertexes)
		{
			if (vert.find(edge[0]) != string::npos && vert.find(edge[1]) != string::npos && vert.find(edge[2]) != string::npos)		// If the vertex coordinate contains all three tokens of the edge coordinate...
			{
				adVert.push_back(vert);																								// Is one of the two adjacent vertexes.
			}
		}

		string auxEdge = edge;
		auxEdge.pop_back();
		for (auto vert : allVertexes)
		{
			if (vert.size() == 2)																									// The other vertex must be of size 2.
			{
				if (vert.find(auxEdge[0]) != string::npos && vert.find(auxEdge[1]) != string::npos)									// If the vertex coordinate contains both tokens of the auxEdge coordinate...
				{
					adVert.push_back(vert);																							// Is the other adjacent vertexes.
				}
			}
		}
	}
	return adVert;
}

void Player::useKnight()
{
	devCards[KNIGHT].amount--;
	army++;
}

void Player::useVictoryPoint()
{
	cardVictoryPoints = devCards[VICTORY_POINTS].amount;
}

void Player::useMonopoly()
{
	devCards[MONOPOLY].amount--;
}

void Player::useYearsOfPlenty()
{
	devCards[YEARS_OF_PLENTY].amount--;
}

void Player::useRoadBuilding()
{
	devCards[ROAD_BUILDING].amount--;
}

vector<string> Player::getAdjacentEdges(string vertex)
{
	vector<string> adyacentes;
	adyacentes.clear();
	if (vertex[0] >= '0' && vertex[0] <= '9')
	{
		if (vertex.length() == 3) // si es la de 2 num + 1 letra
		{
			if (!vertex.compare("05A")) // el unico de los 6 que es distinto
			{
				adyacentes.push_back("5A");
				adyacentes.push_back("0A5");
			}
			else
			{
				string aux_ = vertex;
				aux_.erase(aux_.begin() + 1);
				adyacentes.push_back(aux_);
				aux_ = vertex;
				aux_.erase(aux_.begin());
				aux_.push_back(vertex[0]);
				adyacentes.push_back(aux_);
			}
		}
		else
		{
			for (string str : allEdges)
			{
				if (str.find(vertex[0]) != str.end && str.find(vertex[1]) != str.end) // las aristas que contengan ambos caracteres
				{
					adyacentes.push_back(str);
				}
			}
		}
	}
	else // los edge aledaños son combinaciones de las letras, easy to solve(?
	{
		string temp;
		temp.push_back(vertex[0]);
		temp.push_back(vertex[1]);
		adyacentes.push_back(temp);
		temp[1] = vertex[2];
		availableForRoad.push_back(temp);
		temp[0] = vertex[1];
		adyacentes.push_back(temp);
	}
	return adyacentes;
}

void Player::followRoad(string vertex)
{
	vector< string > adjacentEdges = getAdjacentEdges(vertex);

	for (auto edge : adjacentEdges)
	{
		if (myRoads.find(edge) != myRoads.end() && find(roadsVisited.begin(), roadsVisited.end(), edge) != roadsVisited.end())		// If the edge has a Road and it's not yet visited...
		{
			roadsVisited.push_back(edge);																							// Visiting this Road.
			for (auto newVertex : getAdjacentVertexes(edge))																		// This new Road has two vertexes.
			{
				if (newVertex != vertex)																							// Ignores the vertex that was the parameter of this function.
				{
					followRoad(newVertex);
				}
			}
		}
	}
}
