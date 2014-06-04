#include "bonus.h"

HGE* bonus::hge = 0;
bonus::bonus()
{
}
bonus::bonus(hgeVector position, hgeVector velocity, HTEXTURE &Texture) : Position(position), Velocity(velocity)
{
	hge = hgeCreate(HGE_VERSION);
	Sprite	= new hgeAnimation(Texture,5,5,0,0,30,40);
	Sprite->SetHotSpot(20,15);
	Sprite->Play();
	Speed		= 0.15;
	CenterY		= 0;
	Radius		= hge->Random_Float(50.0f,80.0f);
	Angle		= 0.0f;
	bCenterYSet	= false;
	bOscillate	= false;
}

bonus::~bonus()
{
	delete Sprite;

	hge->Release();
}

bool bonus::Update(float delta)
{
	Velocity.x *= BONUS_FRICION;
	Velocity.y *= BONUS_FRICION;

	Position.y -= Velocity.y; //X
	if(!bOscillate) Position.x += Velocity.x;
	else
	{
		if(!bCenterYSet)
		{
			if(Velocity.x > -0.000001f && Velocity.x < 0.000001f)
			{
				CenterY = Position.x;
				bCenterYSet = true;
			}
		}

		Position.x = CenterY + sin(Angle) * Radius;
		Angle += 2 * delta;
	}

	Sprite->Update(delta);

	Velocity.y -= Speed;//X

	Sprite->GetBoundingBox(Position.x, Position.y, &BoundingBox);
	return false;
}
void bonus::Render()
{
	Sprite->Render(Position.x, Position.y);
}
