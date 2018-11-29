#pragma once
#include "Token.h"
#include <iostream>
#include <map>

using namespace std;

class Board
{
public:
	Board();
	virtual ~Board();

private:
	map< char, Token > board;
};

