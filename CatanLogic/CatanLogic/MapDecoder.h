#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include "Pixel.h"
#include "Error.h"

using namespace std;

class MapDecoder
{
public:
	MapDecoder();
	MapDecoder(const char * filename);
	~MapDecoder();

	void init(char * dataArray, unsigned int x_, unsigned int y_);

	// For the given i and j pixel coordinates, returns the type of pixel (what it's used for in the MapCode: 64 for POSITIONING, 128 for TOKEN, 191 for EDGE and 255 for VERTEX).
	unsigned char getPixelType(unsigned int i, unsigned int j);
	// For the given i and j pixel coordinates, returns a string that represents the coordinate in the Catan map.
	string getCoordinateFromPixel(unsigned int i, unsigned int j);

	// Returns the coordinates in the board where a bitmap of the Road should be drawn.
	pair<unsigned int, unsigned int> getPositioningForEdge(string edge);
	// Returns the coordinates in the board where a bitmap of the Settlement or City should be drawn.
	pair<unsigned int, unsigned int> getPositioningForVertex(string vertex);
	// Returns the coordinates in the board where a bitmap of the Resource or sea should be drawn.
	pair<unsigned int, unsigned int> getPositioningForToken(string token);
	
	// True if everything is ok, false otherwise.
	bool isOk(void); 
	string getError(void);

private:
	bool setPixel(Pixel& pixel_, unsigned int i, unsigned int j);
	// Returns x and y coordinates of a pixel in pixelMatrix.
	pair< unsigned int, unsigned int > getCoordinatesInMatrix(Pixel& p);

	unsigned int x;
	unsigned int y;
	// Matrix containing x*y Pixels.
	vector< Pixel > pixelMatrix;
	// Map containing coordinates of Pixels for vertex positioning (eases finding positioning Pixels using the Catan coordinates for access).
	map< string, pair< unsigned int, unsigned int > > vertexPositioners;
	// Map containing coordinates of Pixels for edge positioning (eases finding positioning Pixels using the Catan coordinates for access).
	map< string, pair< unsigned int, unsigned int > > edgePositioners;
	// Map containing coordinates of Pixels for token positioning (eases finding positioning Pixels using the Catan coordinates for access).
	map< string, pair< unsigned int, unsigned int > > tokenPositioners;
	Error compressorError;
};

