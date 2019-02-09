#include "MapDecoder.h"
#include "Image.h"
#include "lodepng.h"
#include <cmath>
#include <fstream>


MapDecoder::MapDecoder() : pixelMatrix() , compressorError()
{
	x = 0;
	y = 0;
}

MapDecoder::MapDecoder(const char * filename) : pixelMatrix()
{
	Image png(filename);
	
	unsigned char * tempArray; //si es un png estas las utilizo en lodepng functios

	if (png.getFormat() == "png")
	{
		unsigned error = lodepng_decode32_file(&tempArray, &x, &y, filename);
		if ( error != 0)
		{
			compressorError.setErrType(ErrType::ERROR_PNG);
			compressorError.setErrDetail(string(lodepng_error_text(error)));
		}
		else
		{
			init((char *)tempArray, x, y);
		}
	}
	
}


MapDecoder::~MapDecoder()
{
}

void MapDecoder::init(char * dataArray, unsigned int x_, unsigned int y_)
{
	x = x_;
	y = y_;
	for (unsigned int i = 0; i < x * y; i++)
	{
		Pixel newPixel(*(dataArray + i*4 ), *(dataArray + i*4 + 1), *(dataArray + i*4 + 2), *(dataArray + i*4 + 3));	// Add x*y Pixels initialised with (red, green, blue, alfa).
		pixelMatrix.push_back(newPixel);

		if (newPixel.getAlpha() == E_POSITIONING)
		{
			string catanCoordinates;
			catanCoordinates += newPixel.getR();
			if (char G = newPixel.getG())						// If it's not 0, it means it is part of the coordinate.
			{
				catanCoordinates += G;
			}
			if (char B = newPixel.getB())						// If it's not 0, it means it is part of the coordinate.
			{
				catanCoordinates += B;
			}

			edgePositioners[catanCoordinates] = getCoordinatesInMatrix(newPixel);
		}
		else if (newPixel.getAlpha() == V_POSITIONING)
		{
			string catanCoordinates;
			catanCoordinates += newPixel.getR();
			if (char G = newPixel.getG())						// If it's not 0, it means it is part of the coordinate.
			{
				catanCoordinates += G;
			}
			if (char B = newPixel.getB())						// If it's not 0, it means it is part of the coordinate.
			{
				catanCoordinates += B;
			}

			vertexPositioners[catanCoordinates] = getCoordinatesInMatrix(newPixel);
		}
		else if ((newPixel.getAlpha()) == T_POSITIONING)
		{
			string catanCoordinates;
			catanCoordinates += newPixel.getR(); // just one character defines de color 
			tokenPositioners[catanCoordinates] = getCoordinatesInMatrix(newPixel);
		}
	}
}

unsigned char MapDecoder::getPixelType(unsigned int i, unsigned int j)
{
	if (i < x && j < y)
	{
		int element = j * x + i;
		return pixelMatrix[element].getAlpha();
	}
	return 0; // para que no tire warning, el 0 no lo usamos en ningun alpha
}

string MapDecoder::getCoordinateFromPixel(unsigned int i, unsigned int j)
{
	if (i < x && j < y)
	{
		int element = j * x + i;
		Pixel temp = pixelMatrix[element];
		string ret;
		ret += temp.getR();
		if (char G = temp.getG())						// If it's not 0, it means it is part of the coordinate.
		{
			ret += G;
		}
		if (char B = temp.getB())						// If it's not 0, it means it is part of the coordinate.
		{
			ret += B;
		}

		return ret;
	}
	return string(); // error
}

pair<unsigned int, unsigned int> MapDecoder::getPositioningForEdge(string edge)
{
	return edgePositioners[edge];
}

pair<unsigned int, unsigned int> MapDecoder::getPositioningForVertex(string vertex)
{
	return vertexPositioners[vertex];
}

pair<unsigned int, unsigned int> MapDecoder::getPositioningForToken(string token)
{
	return tokenPositioners[token];
}

bool MapDecoder::setPixel(Pixel& pixel_, unsigned int i, unsigned int j)
{
	int element;
	if (i < x && j < y) //compruebo que el pixel este dentro de la matriz
	{
		element = j * x + i;
		pixelMatrix[element] = pixel_;
	}
	return false; // no se pudo escribir el pixel
}

pair<unsigned int, unsigned int> MapDecoder::getCoordinatesInMatrix(Pixel & p)
{
	vector< Pixel >::iterator it = find(pixelMatrix.begin(), pixelMatrix.end(), p);
	unsigned int index = distance(pixelMatrix.begin(), it);
	unsigned int j = index / x;
	unsigned int i = index % x;
	return pair<unsigned int, unsigned int>(i, j);
}

bool MapDecoder::isOk(void)
{
	return (compressorError.getErrType() == ErrType::NO_ERR);
}

string MapDecoder::getError(void)
{
	return compressorError.getErrDetail();
}

