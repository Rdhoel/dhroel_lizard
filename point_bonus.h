#ifndef POINT_BONUS_H
#define POINT_BONUS_H
#pragma once

#include <hge.h>
#include <hgevector.h>
#include <hgeanim.h>

#define POINT_BONUS_FRICTION 0.95

class point_bonus
{
private:
	static HGE*		hge;
	hgeVector		Position;
	hgeVector		Velocity;
	hgeAnimation*	Sprite;
	hgeRect			BoundingBox;
	float			Speed;

	float			CenterY;
	float			Radius;
	float			Angle;
	bool			bCenterYSet;
	bool			bOscillate;
public:
	point_bonus(hgeVector Position, hgeVector Velocity, HTEXTURE &Texture);
	~point_bonus();

	bool Update(float delta);
	void Render();
	void		SetOscillate(bool Value) { bOscillate = Value; };
	float		GetSpeed() { return Speed; };
	void		SetSpeed(float speed) { Speed = speed; };
	hgeRect		GetBoundingBox() { return BoundingBox; };
	hgeVector	GetPosition() { return Position; };
};

#endif
