#pragma once

enum class headers : char{
	ACK = 0x01, NAME = 0x10,
	NAME_IS = 0x11, MAP_IS = 0x12, CIRCULAR_TOKENS = 0x13, PLAY_WITH_DEV = 0x15, DEV_CARDS = 0x16, YOU_START = 0x17, I_START = 0x18,
	DICE_ARE = 0x20	, ROBBER_CARDS = 0x21, CARD_IS = 0x22, ROBBER_MOVE = 0x23,
	SETTLMENT = 0x24, ROAD = 0x25, CITY = 0x26, BANK_TRADE = 0x27, OFFER_TRADE = 0x28, PASS = 0x29,
	DEV_CARD = 0x30, MONOPOLY = 0x31, YEARS_OF_PLENTY = 0x32, ROAD_BUILDING = 0x33, KNIGHT = 0x34,
	YES = 0x40, NO = 0x41,
	I_WON = 0x50, PLAY_AGAIN_H = 0x51, GAME_OVER_H = 0x52,
	ERROR_ = 0xFE, QUIT_H = 0xFF
};

enum ResourceType : char {
	BOSQUE = 'M',
	COLINAS = 'L',
	MONTA�AS = 'P',
	CAMPOS = 'T',
	PASTOS = 'O',
	DESIERTO = 'N'
};

enum SeaType : char {
	ST_3X1 = 'N',
	ST_3X1_2TX1 = 'T',
	ST_3X1_2OX1 = 'O',
	ST_3X1_2LX1 = 'L',
	ST_2PX1 = 'P',
	ST_2MX1 = 'M'
};

enum DevCards : char {
	KNIGHT = 'K',
	VICTORY_POINTS = 'V',
	ROAD_BUILDING = 'C',
	MONOPOLY = 'M',
	YEARS_OF_PLENTY = 'P'
};

enum PortType : char {
	_4x1 = '0',
	_3x1 = 'N',
	_2Tx1 = 'T',
	_2Ox1 = 'O',
	_2Lx1 = 'L',
	_2Px1 = 'P',
	_2Mx1 = 'M'
};