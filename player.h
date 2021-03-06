#ifndef PLAYER_H
#define PLAYER_H
#pragma once

#include <hge.h>
#include <hgevector.h>
#include <hgeanim.h>

#define PLAYER_FRICTION 0.95

class player
{
private:
	static HGE*		hge;
	hgeVector		Position;
	hgeVector		Velocity;
	HTEXTURE		Texture;
	hgeAnimation*	Sprite;
	hgeRect			BoundingBox;
	float			Speed;

public:
	player(hgeVector Position, hgeVector Velocity, int level/*,HTEXTURE &Texture*/);
	~player();

	bool Update(float delta);
	void Render();
	void		ReverseVelocity() { Velocity = hgeVector(-Velocity.x,-Velocity.y); };
	void		SetVelocity(hgeVector velocity) { Velocity = velocity; };
	void		SetPosition(hgeVector position) { Position = position; };
	hgeRect		GetBoundingBox() { return BoundingBox; };
	hgeVector	GetPosition() { return Position; };
};

#endif
