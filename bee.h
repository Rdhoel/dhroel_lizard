#ifndef BEE_H
#define BEE_H
#pragma once

#include <hge.h>
#include <hgevector.h>
#include <hgeanim.h>

#define BEE_FRICTION 0.95

class bee
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
	bee(hgeVector Position, hgeVector Velocity, HTEXTURE &Texture);
	~bee();

	bool Update(float delta);
	void Render();
	void		SetOscillate(bool Value) { bOscillate = Value; };
	float		GetSpeed() { return Speed; };
	void		SetSpeed(float speed) { Speed = speed; };
	hgeRect		GetBoundingBox() { return BoundingBox; };
	hgeVector	GetPosition() { return Position; };
};

#endif
