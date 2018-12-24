#include "MovableType.h"



MovableType::MovableType(GutenbergsPress* press_, ALLEGRO_BITMAP * bitmap_, ALLEGRO_COLOR tint_, double coordinateX_, double coordinateY_, double difX_, double difY_, double scaleX_, double scaleY_, double angle_, int flags_)
{
	setPress(press_);
	setBitmap(bitmap_);
	setTint(tint_);
	setCX(coordinateX_);
	setCY(coordinateY_);
	setDX(difX_);
	setDY(difY_);
	setScaleX(scaleX_);
	setScaleY(scaleY_);
	setAngle(angle_);
	setFlags(flags_);
}

MovableType::~MovableType()
{
	al_destroy_bitmap(bitmap);
}

void MovableType::printType()
{
	al_draw_tinted_scaled_rotated_bitmap(bitmap, tint, coordinateX, coordinateY, difX, difY, scaleX, scaleY, angle, flags);
}

void MovableType::redraw()
{
	press->print();
}

void MovableType::setPress(GutenbergsPress * press_)
{
	press = press_;
}

void MovableType::setBitmap(ALLEGRO_BITMAP * bitmap_)
{
	bitmap = bitmap_;
}

void MovableType::setTint(ALLEGRO_COLOR tint_)
{
	tint = tint_;
}

void MovableType::setCX(double coordinateX_)
{
	coordinateX = coordinateX_;
}

void MovableType::setCY(double coordinateY_)
{
	coordinateY = coordinateY_;
}

void MovableType::setDX(double difX_)
{
	difX = difX_;
}

void MovableType::setDY(double difY_)
{
	difY = difY_;
}

void MovableType::setScaleX(double scaleX_)
{
	scaleX = scaleX_;
}

void MovableType::setScaleY(double scaleY_)
{
	scaleY = scaleY_;
}

void MovableType::setAngle(double angle_)
{
	angle = angle_;
}

void MovableType::setFlags(int flags_)
{
	flags = flags_;
}
