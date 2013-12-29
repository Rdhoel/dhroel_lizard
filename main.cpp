#include <hge.h>
#include <hgesprite.h>
#include <hgevector.h>
#include <list>
#include "player.h"
#include "insects.h"
#include "hgefont.h"
#include "bee.h"
#include "point_bonus.h"
#include "hp_bonus.h"
int count = 0;
int level = 1;
int ins = 0; //переменная отвечающая за количество насекомых
int beee = 0; //переменная отвечающая за количество пчел
int hpp = 0;
int hp = 5;
int messege = 0;
HGE*	hge	= NULL;

hgeFont *fnt=0;
hgeFont *fnt1 = 0;

//Insects
std::list<insects*> Insects;
HTEXTURE	g_tEColors[5] = { 0 };

//Bee
std::list<bee*> Bees;
HTEXTURE    g_bee[2] = { 0 };

//Point Bonus
std::list<point_bonus*> PB;
HTEXTURE g_pb[2] = { 0 };

//HP Bonus
std::list<hp_bonus*> HPB;
HTEXTURE g_hpb[2] = { 0 };

//Player
player*	Player1				= NULL;
HTEXTURE g_Player1=0;

//Background
HTEXTURE	g_tBackground		= 0;
hgeSprite*	g_sBackground		= NULL;

HTEXTURE	g_tBackground2      = 0;
hgeSprite*	g_sBackground2 = NULL;

HTEXTURE	g_tBackground3 = 0;
hgeSprite*	g_sBackground3 = NULL;


hgeSprite*	g_sStars			= NULL;

hgeVector	g_vBGPosition		= hgeVector(0,0);


//Sound
HEFFECT		g_eBGMusic			= 0;
HEFFECT		g_eBGMusic2			= 0;
HEFFECT		g_eBGMusic3			= 0;
bool FrameFunc()
{
	if (level == 1)
	{
		ins = 7;
		beee = 2;
		hpp = 1;
	}
	else if (level == 2)
	{
		ins = 5;
		beee = 3;
		hpp = 1;
	}
	else if (level == 3)
	{
		ins = 3;
		beee = 5;
		hpp = 3;
	}		float delta = hge->Timer_GetDelta();
	//Player1 = new player(hgeVector(300, 530), hgeVector(5, 0),g_Player1);
		//Insects
		if (Insects.size() < ins)
		{
			short Health = hge->Random_Int(50, 100);

			insects* Insect = new insects(hgeVector(hge->Random_Int(10, 800), 40), hgeVector(-hge->Random_Int(-4, 4), hge->Random_Int(1, 1)), g_tEColors[hge->Random_Int(0, 4)]);

			Insects.push_back(Insect);
		}

		for (auto i = Insects.begin(); i != Insects.end(); /**/)
		{
			if ((*i)->GetPosition().x < 0 || (*i)->GetPosition().y > 580 || (*i)->GetPosition().y < 20)
			{
				delete (*i);
				i = Insects.erase(i);
			}
			else
			{
				(*i)->Update(delta);
				i++;
			}
		}
		//Bee
		if (Bees.size() < beee)
		{
			short Health = hge->Random_Int(50, 100);
			bee* Bee = new bee(hgeVector(hge->Random_Int(10, 800), 40), hgeVector(-hge->Random_Int(-4, 4), hge->Random_Int(1, 1)), g_bee[hge->Random_Int(0, 1)]);
			Bees.push_back(Bee);
		}

		for (auto i = Bees.begin(); i != Bees.end(); /**/)
		{
			if ((*i)->GetPosition().x < 0 || (*i)->GetPosition().y > 580 || (*i)->GetPosition().y < 20)
			{
				delete (*i);
				i = Bees.erase(i);
			}
			else
			{
				(*i)->Update(delta);
				i++;
			}
		}

		//Player
		Player1->Update(delta);

		//PB
		if (count != 0 && count % 5 == 0 && PB.size() < 2)
		{
			short Health = hge->Random_Int(50, 100);
			point_bonus* point_bon = new point_bonus(hgeVector(hge->Random_Int(10, 800), 40), hgeVector(-hge->Random_Int(-4, 4), hge->Random_Int(1, 1)), g_pb[hge->Random_Int(0, 1)]);
			PB.push_back(point_bon);
		}

		for (auto i = PB.begin(); i != PB.end(); /**/)
		{
			if ((*i)->GetPosition().x < 0 || (*i)->GetPosition().y > 580 || (*i)->GetPosition().y < 20)
			{
				delete (*i);
				i = PB.erase(i);
			}
			else
			{
				(*i)->Update(delta);
				i++;
			}
		}
		//HPB
		if (HPB.size() < 2 && hp < 3 && count != 0 && count % 5 == 0)
		{
			short Health = hge->Random_Int(50, 100);
			hp_bonus* hp_bon = new hp_bonus(hgeVector(hge->Random_Int(10, 800), 40), hgeVector(-hge->Random_Int(-4, 4), hge->Random_Int(1, 1)), g_hpb[hge->Random_Int(0, 1)]);
			HPB.push_back(hp_bon);
		}

		for (auto i = HPB.begin(); i != HPB.end(); /**/)
		{
			if ((*i)->GetPosition().x < 0 || (*i)->GetPosition().y > 580 || (*i)->GetPosition().y < 20)
			{
				delete (*i);
				i = HPB.erase(i);
			}
			else
			{
				(*i)->Update(delta);
				i++;
			}
		}
		//Insects vs Player
		for (auto i = Insects.begin(); i != Insects.end(); /**/)
		{
			if ((*i)->GetBoundingBox().Intersect(&Player1->GetBoundingBox()))
			{
				delete (*i);
				i = Insects.erase(i);
				count++;
			}
			else i++;
		}

		//Bee vs Player
		for (auto i = Bees.begin(); i != Bees.end();)
		{
			if ((*i)->GetBoundingBox().Intersect(&Player1->GetBoundingBox()))
			{
				delete (*i);
				i = Bees.erase(i);
				hp = hp - hpp;
				if (hp == 0 || hp < 0 )
				{
					MessageBox(NULL, "GAME OVER! Your HP - 0", "Game Over", MB_OK);
					return true;
				}
			}
			else i++;
		}
		//PB vs PLayer
		for (auto i = PB.begin(); i != PB.end();)
		{
			if ((*i)->GetBoundingBox().Intersect(&Player1->GetBoundingBox()))
			{
				delete (*i);
				i = PB.erase(i);
				count = count + 10;
			}
			else i++;
		}
		//HPB vs PLayer
		for (auto i = HPB.begin(); i != HPB.end();)
		{
			if ((*i)->GetBoundingBox().Intersect(&Player1->GetBoundingBox()))
			{
				delete (*i);
				i = HPB.erase(i);
				if (hp<50)
					hp = hp + 1;
			}
			else i++;
		}
		if (count>50 && count<150)
			level = 2;
		if (count>150)
			level = 3;

		if (hge->Input_GetKeyState(HGEK_ESCAPE)) return true;
		return false;
}
bool RenderFunc()
{
	hge->Gfx_BeginScene();
	hge->Gfx_Clear(0);
	if (level == 1)
	{
		g_sBackground->Render(g_vBGPosition.x, g_vBGPosition.y);
		hge->Effect_Play(g_eBGMusic);
		
	}
	else if (level == 2)
	{
		if (messege == 0)
		{
			MessageBox(NULL, "LEVEL 2", "Level 2", MB_OK | MB_APPLMODAL);
			messege++;
			hge->Effect_Free(g_eBGMusic);
		}
		hge->Effect_Play(g_eBGMusic2);
		g_sBackground2->Render(g_vBGPosition.x, g_vBGPosition.y);
	}
	else if (level == 3)
	{
		if (messege == 1)
		{
			MessageBox(NULL, "LEVEL 3", "Level 3", MB_OK | MB_APPLMODAL);
			messege++;
			hge->Effect_Free(g_eBGMusic2);
		}
		hge->Effect_Play(g_eBGMusic3);
		g_sBackground3->Render(g_vBGPosition.x, g_vBGPosition.y);
	}
	//Player
	Player1->Render();

	//Enemies
	for(auto i = Insects.begin(); i != Insects.end(); i++)
	{
		(*i)->Render();
	}
	//Bee
	for (auto i = Bees.begin(); i != Bees.end(); i++)
	{
		(*i)->Render();
	}
	//PB
	for (auto i = PB.begin(); i != PB.end(); i++)
	{
		(*i)->Render();
	}
	//HPB
	for (auto i = HPB.begin(); i != HPB.end(); i++)
	{
		(*i)->Render();
	}
	fnt->printf(20, 20, HGETEXT_LEFT, "Insects eaten: %d", count);
	fnt1->printf(20, 40, HGETEXT_LEFT, "HP: %d", hp);
	hge->Gfx_EndScene();
	return false;
}

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	hge = hgeCreate(HGE_VERSION);
	hge->System_SetState(HGE_FRAMEFUNC, FrameFunc);
	hge->System_SetState(HGE_RENDERFUNC, RenderFunc);
	hge->System_SetState(HGE_WINDOWED, true);
	hge->System_SetState(HGE_USESOUND, true);
	hge->System_SetState(HGE_FPS, HGEFPS_VSYNC);
	hge->System_SetState(HGE_TITLE, "Lizard");

	if (hge->System_Initiate())
	{

		//Background
		g_tBackground = hge->Texture_Load("images/lvl1.jpg");
		g_sBackground = new hgeSprite(g_tBackground, 0, 0, 1782, 600);
		g_tBackground2 = hge->Texture_Load("images/lvl2.jpg");
		g_sBackground2 = new hgeSprite(g_tBackground2, 0, 0, 1782, 600);
		g_tBackground3 = hge->Texture_Load("images/lvl3.jpg");
		g_sBackground3 = new hgeSprite(g_tBackground3, 0, 0, 1782, 600);
		fnt=new hgeFont("font1.fnt");
		fnt1 = new hgeFont("font1.fnt");
		//Player
        //g_Player1         = hge->Texture_Load("images/main_9.png");
		Player1 = new player(hgeVector(300, 530), hgeVector(5, 0));
		//Insects
		g_tEColors[0] = hge->Texture_Load("images/Bonus_1.png");
		g_tEColors[1] = hge->Texture_Load("images/Bonus_2.png");
		g_tEColors[2] = hge->Texture_Load("images/Bonus_3.png");
		g_tEColors[3] = hge->Texture_Load("images/Bonus_4.png");
		g_tEColors[4] = hge->Texture_Load("images/Bonus_5.png");
		//Bee
		g_bee[0] = hge->Texture_Load("images/bee.png");
		g_bee[1] = hge->Texture_Load("images/bee.png");
		//PB
		g_pb[0] = hge->Texture_Load("images/pb.png");
		g_pb[1] = hge->Texture_Load("images/pb.png");
		//HPB
		g_hpb[0] = hge->Texture_Load("images/hpb.png");
		g_hpb[1] = hge->Texture_Load("images/hpb.png");
		//Sounds
	    g_eBGMusic  = hge->Effect_Load("sounds/lvl1.mp3");
		g_eBGMusic2 = hge->Effect_Load("sounds/lvl2.mp3");
		g_eBGMusic3 = hge->Effect_Load("sounds/lvl3.mp3");
			
		hge->System_Start();
		//Очищаем
		hge->Texture_Free(g_tBackground);
		hge->Effect_Free(g_eBGMusic3);
		
		delete g_sBackground;
		delete Player1;
		for(auto i = Insects.begin(); i != Insects.end(); /**/)
		{
			delete (*i);
			i = Insects.erase(i);
		}

		for (auto i = Bees.begin(); i != Bees.end(); /**/)
		{
			delete (*i);
			i = Bees.erase(i);
		}

		for (auto i = PB.begin(); i != PB.end(); /**/)
		{
			delete (*i);
			i = PB.erase(i);
		}

		for (auto i = HPB.begin(); i != HPB.end(); /**/)
		{
			delete (*i);
			i = HPB.erase(i);
		}

		//hge->Texture_Free(g_Player1);

		for (short b = 0; b < 2; b++) hge->Texture_Free(g_bee[b]);//удаляем 

		for (short i = 0; i < 5; i++) hge->Texture_Free(g_tEColors[i]);//удаляем

		for (short i = 0; i < 2; i++) hge->Texture_Free(g_pb[i]);

		for (short i = 0; i < 2; i++) hge->Texture_Free(g_hpb[i]);
	}
	else
	{
	  MessageBox(NULL, hge->System_GetErrorMessage(), "Error", MB_OK | MB_ICONERROR | MB_APPLMODAL);
	}
	
	hge->System_Shutdown();
	hge->Release();
 
	return 0;
}
