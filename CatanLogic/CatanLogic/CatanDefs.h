#pragma once

enum class headers : char{
	ACK = 0x01, NAME = 0x10,
	NAME_IS = 0x11, MAP_IS = 0x12, CIRCULAR_TOKENS = 0x13, PLAY_WITH_DEV = 0x15, DEV_CARDS = 0x16, YOU_START = 0x17, I_START = 0x18,
	DICE_ARE = 0x20	, ROBBER_CARDS = 0x21, CARD_IS = 0x22, ROBBER_MOVE = 0x23,
	SETTLMENT = 0x24, ROAD = 0x25, CITY = 0x26, BANK_TRADE = 0x27, OFFER_TRADE = 0x28, PASS = 0x29,
	DEV_CARD = 0x30, MONOPOLY = 0x31, YEARS_OF_PLENTY = 0x32, ROAD_BUILDING = 0x33, KNIGHT = 0x34,
	YES = 0x40, NO = 0x41,
	I_WON = 0x50, PLAY_AGAIN = 0x51, GAME_OVER = 0x52,
	ERROR = 0xFE, QUIT = 0xFF
};

enum ResourceType : char {
	BOSQUE = 'M',
	COLINAS = 'L',
	MONTAÑAS = 'P',
	CAMPOS = 'T',
	PASTOS = 'O',
	DESIERTO = 'N'
};

enum SeaType : char {
	_3X1 = 'N',
	_3X1_2TX1 = 'T',
	_3X1_2OX1 = 'O',
	_3X1_2LX1 = 'L',
	_2PX1 = 'P',
	_2MX1 = 'M'
};

enum DevCards : char {
	CABALLERO = 'K',
	VICTORY_POINTS = 'V',
	ROAD_CONSTRUCTION = 'C',
	MONOPOLY = 'M',
	YEARS_OF_PLENTY = 'P'
};