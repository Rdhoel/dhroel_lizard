#ifndef BONUS_H
#define BONUS_H
#pragma once

#include <hge.h>
#include <hgevector.h>
#include <hgeanim.h>

#define BONUS_FRICION 0.95
extern int count;
class bonus
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
	bonus();
	bonus(hgeVector Position, hgeVector Velocity, HTEXTURE &Texture);
	~bonus();
	virtual void Bonus()=0;
	void Render();
	bool Update(float delta);
	void		SetOscillate(bool Value) { bOscillate = Value; };
	float		GetSpeed() { return Speed; };
	void		SetSpeed(float speed) { Speed = speed; };
	hgeRect		GetBoundingBox() { return BoundingBox; };
	hgeVector	GetPosition() { return Position; };
};

#endif
