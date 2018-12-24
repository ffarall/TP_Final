#pragma once

#include "allegro5/allegro.h"
#include "allegro5/allegro_image.h"
#include "GutenbergsPress.h"

using namespace std;

// This class simulates Gutenberg's movable types, to be moved around a matrix and then printed. Contains all the information needed regarding the characteristics of the bitmap.
class MovableType
{
public:
	MovableType(
		GutenbergsPress* press_,
		ALLEGRO_BITMAP* bitmap_, 
		ALLEGRO_COLOR tint_=al_map_rgb(255, 255, 255), 
		double coordinateX_=0, 
		double coordinateY_=0, 
		double difX_=0,
		double difY_=0,
		double scaleX_=1,
		double scaleY_=1,
		double angle_=0,
		int flags_=NULL);
	~MovableType();

	void printType();
	void redraw();

	void setPress(GutenbergsPress* press_);
	void setBitmap(ALLEGRO_BITMAP* bitmap_);
	void setTint(ALLEGRO_COLOR tint_);
	void setCX(double coordinateX_);
	void setCY(double coordinateY_);
	void setDX(double difX_);
	void setDY(double difY_);
	void setScaleX(double scaleX_);
	void setScaleY(double scaleY_);
	void setAngle(double angle_);
	void setFlags(int flags_);

private:
	GutenbergsPress* press;

	ALLEGRO_BITMAP* bitmap;
	ALLEGRO_COLOR tint;
	double coordinateX;
	double coordinateY;
	double difX;
	double difY;
	double scaleX;
	double scaleY;
	double angle;
	int flags;
};

