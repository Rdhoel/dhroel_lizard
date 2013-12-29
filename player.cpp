#include "player.h"
HGE* player::hge = 0;
player::player(hgeVector position, hgeVector velocity/*,HTEXTURE &Texture*/) : Position(position), Velocity(velocity)
{
	hge = hgeCreate(HGE_VERSION);
	Texture = hge->Texture_Create(58, 77);
	Texture = hge->Texture_Load("images/main_9.png");
	Sprite=new hgeAnimation(Texture,4,4,0,0,58,77);
	Sprite->SetHotSpot(32,14.5);
	Sprite->Play();

	Speed		= 0.2;
}

player::~player()
{
	hge->Texture_Free(Texture);
	delete Sprite;

	hge->Release();
}

bool player::Update(float delta)
{
	Velocity.x *= PLAYER_FRICTION;
	Position.x += Velocity.x;

	Velocity.y *= PLAYER_FRICTION;
	Position.y += Velocity.y;

	if(hge->Input_GetKeyState(HGEK_A) || hge->Input_GetKeyState(HGEK_LEFT)	 && Position.x > 32) Velocity.x -= (Speed * M_PI) /2;
	if(hge->Input_GetKeyState(HGEK_D) || hge->Input_GetKeyState(HGEK_RIGHT)  && Position.x < 800) Velocity.x += (Speed * M_PI) /2;

	if(Position.x > 800) {Position.x=0;};
	if(Position.x < 0)   {Position.x=800;};
	Sprite->Update(delta);

	Sprite->GetBoundingBox(Position.x, Position.y, &BoundingBox);
	return false;
}

void player::Render()
{
	Sprite->Render(Position.x,Position.y);
}
