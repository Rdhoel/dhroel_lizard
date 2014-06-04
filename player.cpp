#include "player.h"
HGE* player::hge = 0;
player::player(hgeVector position, hgeVector velocity,int level/*,HTEXTURE &Texture*/) : Position(position), Velocity(velocity)
{
	hge = hgeCreate(HGE_VERSION);
	Texture = hge->Texture_Create(58, 77);
   if (level==1)
	{
		Texture = hge->Texture_Load("images/main_lvl1_1.png");
	    Sprite=new hgeAnimation(Texture,1,1,0,0,60,80);
	}
	else if(level==2)
	{
		Texture = hge->Texture_Load("images/main_lvl2_1.png");
		Sprite=new hgeAnimation(Texture,1,1,0,0,65,85);
	}
	else if(level==3)
	{
		Texture = hge->Texture_Load("images/main_lvl3_1.png");
		Sprite=new hgeAnimation(Texture,1,1,0,0,70,90);
	}
	else if(level==4)
	{
		Texture = hge->Texture_Load("images/main_boss_11.png");
		Sprite=new hgeAnimation(Texture,1,1,0,0,75,95);
	}
	else if(level==5)
	{
		Texture = hge->Texture_Load("images/main_boss_21.png");
		Sprite=new hgeAnimation(Texture,1,1,0,0,80,100);
	}
	else if(level==6)
	{
		Texture = hge->Texture_Load("images/main_boss_31.png");
		Sprite=new hgeAnimation(Texture,1,1,0,0,130,95);
	}
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
