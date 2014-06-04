#include "bee.h"
HGE* bee::hge = 0;
bee::bee(hgeVector position, hgeVector velocity, HTEXTURE &Texture) : Position(position), Velocity(velocity)
{
	hge = hgeCreate(HGE_VERSION);

	Sprite = new hgeAnimation(Texture, 5, 5, 0, 0, 40, 50);

	Sprite->SetHotSpot(20, 15);
	Sprite->Play();
	Speed = 0.15;
	CenterY = 0;
	Radius = hge->Random_Float(50.0f, 80.0f);
	Angle = 0.0f;
	bCenterYSet = false;
	bOscillate = false;
}
bee::~bee()
{
	delete Sprite;
	hge->Release();
}

bool bee::Update(float delta)
{
	Velocity.x *= BEE_FRICTION;
	Velocity.y *= BEE_FRICTION;

	Position.y -= Velocity.y; //X
	if (!bOscillate) Position.x += Velocity.x;
	else
	{
		if (!bCenterYSet)
		{
			if (Velocity.x > -0.000001f && Velocity.x < 0.000001f)
			{
				CenterY = Position.x;
				bCenterYSet = true;
			}
		}

		Position.x = CenterY + sin(Angle) * Radius;
		Angle += 2 * delta;
	}

	Sprite->Update(delta);

	Velocity.y -= Speed;

	Sprite->GetBoundingBox(Position.x, Position.y, &BoundingBox);
	return false;
}
void bee::Render()
{

	Sprite->Render(Position.x, Position.y);

}
