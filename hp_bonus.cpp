#include "hp_bonus.h"

HGE* hp_bonus::hge = 0;
hp_bonus::hp_bonus(hgeVector position, hgeVector velocity, HTEXTURE &Texture) : Position(position), Velocity(velocity)
{
	hge = hgeCreate(HGE_VERSION);

	Sprite = new hgeAnimation(Texture, 5, 5, 0, 0, 30, 40);

	Sprite->SetHotSpot(20, 15);
	Sprite->Play();

	Speed = 0.15;

	CenterY = 0;
	Radius = hge->Random_Float(50.0f, 80.0f);
	Angle = 0.0f;
	bCenterYSet = false;
	bOscillate = false;
}
hp_bonus::~hp_bonus()
{
	delete Sprite;

	hge->Release();
}

bool hp_bonus::Update(float delta)
{
	Velocity.x *= HP_BONUS_FRICTION;
	Velocity.y *= HP_BONUS_FRICTION;

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

	Velocity.y -= Speed;//X

	Sprite->GetBoundingBox(Position.x, Position.y, &BoundingBox);
	return false;
}

void hp_bonus::Render()
{
	Sprite->Render(Position.x, Position.y);
}
