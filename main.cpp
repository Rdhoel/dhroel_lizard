#include <iostream>
#include <fstream>
#include <hge.h>
#include <hgesprite.h>
#include <hgevector.h>
#include <hgegui.h>
#include <hgefont.h>
#include <list>
#include "player.h"
#include "insects.h"
#include "hgefont.h"
#include "bee.h"
#include "point_bonus.h"
#include "hp_bonus.h"
#include "menu.h"
#include "Boss.h"
int about = 0;
int level = 1;
int lvl = 1;
int ins = 0; //переменная отвечающая за количество насекомых
int beee = 0; //переменная отвечающая за количество пчел
int hpp = 0;
int hp = 5;
int count = 0;
int play = 0;
int messege = 0;
int bs = 0;
int id;
int game_menu;
static int lastid=0;
//using namespace std;
HGE*	hge	= NULL;
hgeFont *fnt2 = 0;
hgeFont *fnt1 = 0;
//float dt1=hge->Timer_GetDelta();
//Insects
std::list<insects*> Insects;
HTEXTURE	g_tEColors[5] = { 0 };
//Bee
std::list<bee*> Bees;
HTEXTURE    g_bee[2] = { 0 };
//Boss
std::list<boss*> Bosses;
HTEXTURE    g_boss[2] = { 0 };
//boss* Boss = NULL;
//HTEXTURE g_boss = 0;
//Point Bonus
std::list<point_bonus*> PB;
HTEXTURE g_pb[2] = { 0 };
//HP Bonus
std::list<hp_bonus*> HPB;
HTEXTURE g_hpb[2] = { 0 };

//Player
player*	Player1 = NULL;
HTEXTURE g_Player1 = 0;

//Background
HTEXTURE	g_tBackground = 0;
hgeSprite*	g_sBackground = NULL;

HTEXTURE	g_tBackground2 = 0;
hgeSprite*	g_sBackground2 = NULL;

HTEXTURE	g_tBackground3 = 0;
hgeSprite*	g_sBackground3 = NULL;

HTEXTURE	g_tBackground4 = 0;
hgeSprite*	g_sBackground4 = NULL;

HTEXTURE    bg=0;
hgeSprite*	sbg = NULL;

HTEXTURE    surv_bg=0;
hgeSprite*	surv_sbg = NULL;

hgeVector	g_vBGPosition = hgeVector(0,0);


//Sound
HEFFECT		g_eBGMusic			= 0;
HEFFECT		g_eBGMusic2			= 0;
HEFFECT		g_eBGMusic3			= 0;
HEFFECT		g_eBGMusic4			= 0;

HEFFECT				snd;
HTEXTURE			tex;
hgeQuad				quad;

// Pointers to the HGE objects we will use
hgeGUI				*gui;
hgeFont				*fnt;
hgeSprite			*spr;
void Save()
{
	FILE *f;
	f = fopen("save.txt","w");
	fprintf(f,"%d\n",hp);
	fprintf(f, "%d\n", level);
	fprintf(f,"%d\n", count);
	fclose(f);
}
void Load()
{
	std::ifstream load("save.txt") ; 
	load >> hp;
	load >> level;
	load >> count;
}
bool ForTime()
{
	if (play == 4)
	{
		if (level == 1)
		{
			ins = 10;
			beee = 5;
			hpp = 1;
		}
		else if (level == 2)
		{
			ins = 10;
			beee = 7;
			hpp = 1;
		}
		else if (level == 3)
		{
			ins = 3;
			beee = 5;
			hpp = 3;
		}
		else if (level == 4)
		{
			ins = 5;
			beee = 10;
			hpp = 3;
		}
		float delta = hge->Timer_GetDelta();
		//Insects
		if (Insects.size() < ins)
		{
			short Health = hge->Random_Int(50, 100);

			insects* Insect = new insects(hgeVector(hge->Random_Int(10, 800), 40), hgeVector(-hge->Random_Int(-4, 4), hge->Random_Int(1, 1)), g_tEColors[hge->Random_Int(0, 4)]);

			Insects.push_back(Insect);
		}

		for (auto i = Insects.begin(); i != Insects.end();)
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

		for (auto i = Bees.begin(); i != Bees.end();)
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

		for (auto i = PB.begin(); i != PB.end();)
		{
			if ((*i)->GetPosition().x < 0 || (*i)->GetPosition().y > 580 || (*i)->GetPosition().y < 20)
			{
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

		for (auto i = HPB.begin(); i != HPB.end();)
		{
			if ((*i)->GetPosition().x < 0 || (*i)->GetPosition().y > 580 || (*i)->GetPosition().y < 20)
			{
				i = HPB.erase(i);
			}
			else
			{
				(*i)->Update(delta);
				i++;
			}
		}
		//Insects vs Player
		for (auto i = Insects.begin(); i != Insects.end();)
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
			}
			else i++;
		}
		if (hp == 0 || hp < 0 )
		{
			MessageBox(NULL, "GAME OVER! Your HP - 0", "Game Over", MB_OK);
			play = 0;
			gui->Enter();
			return true;
		}
		//PB vs PLayer
		for (auto i = PB.begin(); i != PB.end();)
		{
			if ((*i)->GetBoundingBox().Intersect(&Player1->GetBoundingBox()))
			{
				(*i)->Bonus();
				i = PB.erase(i);
			}
			else i++;
		}
		//HPB vs PLayer
		for (auto i = HPB.begin(); i != HPB.end();)
		{
			if ((*i)->GetBoundingBox().Intersect(&Player1->GetBoundingBox()))
			{
				if (hp<5)
					(*i)->Bonus();
				i = HPB.erase(i);
					
			}
			else i++;
		}
		if (count>30 && count<100)
		{
			lvl=1;
			level = 2;
		}
		if (count>100 && count<180)
		{
			level = 3;
		}
		if (count>180)
		{
			level = 4;
		}
		if (count>180)
		{
			level = 4;
		}
		if (count>200)
		{
			level = 4;
		}
		if(hge->Input_GetKeyState(HGEK_ESCAPE))
		{
			play = 0;
			game_menu = 3;
			gui->Enter();
		}
		if(hge->Input_GetKeyState(HGEK_ESCAPE))
		{
			play = 0;
			game_menu = 3;
			gui->Enter();
		}
		}
	return false;
}
bool FramePlay()
{
	if(play == 1)
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
		}
		else if (level == 4)
		{
			ins = 3;
			beee = 0;
			hpp = 3;
			bs = 1;
		}
		float delta = hge->Timer_GetDelta();
		//Insects
		if (Insects.size() < ins)
		{
			short Health = hge->Random_Int(50, 100);

			insects* Insect = new insects(hgeVector(hge->Random_Int(10, 800), 40), hgeVector(-hge->Random_Int(-4, 4), hge->Random_Int(1, 1)), g_tEColors[hge->Random_Int(0, 4)]);

			Insects.push_back(Insect);
		}

		for (auto i = Insects.begin(); i != Insects.end();)
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

		for (auto i = Bees.begin(); i != Bees.end();)
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
		//boss
		if (Bosses.size() < bs)
		{
			short Health = hge->Random_Int(50, 100);
			boss* Boss = new boss(hgeVector(hge->Random_Int(10, 800), 40), hgeVector(-hge->Random_Int(-4, 4), hge->Random_Int(1, 1)), g_boss[hge->Random_Int(0, 1)]);
			Bosses.push_back(Boss);
		}

		for (auto i = Bosses.begin(); i != Bosses.end();)
		{
			if ((*i)->GetPosition().x < 0 || (*i)->GetPosition().y > 580 || (*i)->GetPosition().y < 20)
			{
				delete (*i);
				i = Bosses.erase(i);
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

		for (auto i = PB.begin(); i != PB.end();)
		{
			if ((*i)->GetPosition().x < 0 || (*i)->GetPosition().y > 580 || (*i)->GetPosition().y < 20)
			{
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

		for (auto i = HPB.begin(); i != HPB.end();)
		{
			if ((*i)->GetPosition().x < 0 || (*i)->GetPosition().y > 580 || (*i)->GetPosition().y < 20)
			{
				i = HPB.erase(i);
			}
			else
			{
				(*i)->Update(delta);
				i++;
			}
		}
		//Insects vs Player
		for (auto i = Insects.begin(); i != Insects.end();)
		{
			if ((*i)->GetBoundingBox().Intersect(&Player1->GetBoundingBox()))
			{
				delete (*i);
				i = Insects.erase(i);
				count++;
			}
			else i++;
		}
		//BOSS vs Player
		for (auto i = Bosses.begin(); i != Bosses.end();)
		{
			if ((*i)->GetBoundingBox().Intersect(&Player1->GetBoundingBox()))
			{
				delete (*i);
				i = Bosses.erase(i);
				if (count>175 && count<185)
					hp=hp-2;
				else if(count>200)
				{
					count=count+200;
					MessageBox(NULL, "You're WIN!!!", "WIN", MB_OK);
					play = 0;
					gui->Enter();
				}
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
			}
			else i++;
		}
		if (hp == 0 || hp < 0 )
		{
			MessageBox(NULL, "GAME OVER! Your HP - 0", "Game Over", MB_OK);
			play = 0;
			gui->Enter();
			return true;
		}
		//PB vs PLayer
		for (auto i = PB.begin(); i != PB.end();)
		{
			if ((*i)->GetBoundingBox().Intersect(&Player1->GetBoundingBox()))
			{
				(*i)->Bonus();
				i = PB.erase(i);
			}
			else i++;
		}
		//HPB vs PLayer
		for (auto i = HPB.begin(); i != HPB.end();)
		{
			if ((*i)->GetBoundingBox().Intersect(&Player1->GetBoundingBox()))
			{
				if (hp<5)
					(*i)->Bonus();
				i = HPB.erase(i);

			}
			else i++;
		}
		if (count>50 && count<150)
		{
			lvl=2;
			level = 2;
		}
		if (count>150 && count<175)
		{
			level = 3;
			lvl=3;
		}
		if (count>175 && count<180)
		{
			level = 4;
			lvl=4;
		}
		if (count>180 && count<200)
		{
			lvl = 5;
			level = 4;
		}
		if (count>200)
		{
			lvl=6;
			level = 4;
		}
		if(hge->Input_GetKeyState(HGEK_ESCAPE))
		{
			play = 0;
			game_menu = 3;
			gui->Enter();
		}
	}
	return false;
}
bool FrameFunc()
{
	if(play == 0)
	{
		float dt=hge->Timer_GetDelta();
		static float t=0.0f;
		float tx,ty;
		// We update the GUI and take an action if
		// one of the menu items was selected
		id=gui->Update(dt);
		if(id == -1)
		{
			switch(lastid)
			{
			case 1:
				play=1;
				//id=gui->Update(dt);
				gui->Leave();
				break;
			case 2:
				play=1;
				Load();
				gui->Leave();
				break;
			case 3:
				Save();
				gui->Leave();
				gui->Enter();
				break;
			case 5: return true;
			case 4:
				about=2;
				gui->Leave();
				gui->Enter();
				break;
			case 6: 
				about=1;
			case 7:
				play=4;
				//id=gui->Update(dt);
				gui->Leave();
				break;
			}
		}
		else if(id) { lastid=id; gui->Leave(); }

		// Here we update our background animation
		t+=dt;
		tx=50*cosf(t/60);
		ty=50*sinf(t/60);

		quad.v[0].tx=tx;        quad.v[0].ty=ty;
		quad.v[1].tx=tx+800/64; quad.v[1].ty=ty;
		quad.v[2].tx=tx+800/64; quad.v[2].ty=ty+600/64;
		quad.v[3].tx=tx;        quad.v[3].ty=ty+600/64;
	}
	else if(play == 1)
		FramePlay();
	else if (play == 4)
		ForTime();
	return false;
}
bool RenderFunc()
{
	if(play == 0)
	{
		// Render graphics
		hge->Gfx_BeginScene();
		hge->Gfx_RenderQuad(&quad);
		if (about==0)
		{
			gui->Render();
		}
		if (about == 1)
		{
			fnt->SetColor(0xFFFFFFFF);
			fnt->printf(300, 200, HGETEXT_LEFT, "Powerd by R.Gavrilko\nGame Version 1.1\n2014\n\n\n\nPress ESC to return to Menu");
			if(hge->Input_GetKeyState(HGEK_ESCAPE))
			{
				play = 0;
				about = 0;
				gui->Enter();
			}

		}
		if (about == 2)
		{
			fnt->SetColor(0xFFFFFFFF);
			fnt->printf(50, 100, HGETEXT_LEFT, "To move, use the Left and Right or A and D\nCollect points for larger flies and movement levels\nDodge the bees, they take away your health points\n\nThere are 4 levels\nOn the first level, you need to dial 50 points\nOn the second level you will need to earn 150 points\nAt the third level, you need to dial 175 points\n\nAt the final level you will fight with the boss\ndodge the boss until you have 200 points\nand then attack him\n\n\nPress ESC to return to Menu");
			if(hge->Input_GetKeyState(HGEK_ESCAPE))
			{
				play = 0;
				about = 0;
				gui->Enter();
			}

		}
		hge->Gfx_EndScene();
	}
	else if(play == 1)
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
				play = 3;
			else if(messege == 1)
			{
				hge->Effect_Play(g_eBGMusic2);
				g_sBackground2->Render(g_vBGPosition.x, g_vBGPosition.y);
			}
		}
		else if (level == 3)
		{
			if (messege == 1)
				play = 3;
			else if(messege == 2)
			{
				hge->Effect_Play(g_eBGMusic3);
				g_sBackground3->Render(g_vBGPosition.x, g_vBGPosition.y);
			}
		}
		else if (level == 4)
		{
			if (messege == 2)
				play=3;
			else if(messege == 3)
			{
				hge->Effect_Play(g_eBGMusic4);
				g_sBackground4->Render(g_vBGPosition.x, g_vBGPosition.y);
			}
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
		//Boss
		for (auto i = Bosses.begin(); i != Bosses.end(); i++)
		{
			(*i)->Render();
		}
		/*if(bs>0)
		Boss->Render();*/
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
		fnt2->printf(20, 20, HGETEXT_LEFT, "Insects eaten: %d", count);
		fnt1->printf(20, 40, HGETEXT_LEFT, "HP: %d", hp);
		hge->Gfx_EndScene();
	}
	else if(play == 3)
	{
		if(messege == 0)
		{
			if(!hge->Input_GetKeyState(HGEK_ENTER))
			{
				hge->Gfx_BeginScene();
				sbg->Render(g_vBGPosition.x, g_vBGPosition.y);
				fnt->SetColor(0xFFFFFFFF);
				hge->Effect_Free(g_eBGMusic);
				fnt->printf(300, 200, HGETEXT_LEFT, "LEVEL 2\n\n\nPress ENTER to continue");
				hge->Gfx_EndScene();
			}
			else if(hge->Input_GetKeyState(HGEK_ENTER))
			{				
				hge->Effect_Free(g_eBGMusic);
				messege=1;
				play = 1;
			}
		}
		else if(messege == 1)
		{
			if(!hge->Input_GetKeyState(HGEK_ENTER))
			{
				hge->Gfx_BeginScene();
				sbg->Render(g_vBGPosition.x, g_vBGPosition.y);
				fnt->SetColor(0xFFFFFFFF);
				hge->Effect_Free(g_eBGMusic2);
				fnt->printf(300, 200, HGETEXT_LEFT, "LEVEL 3\n\n\nPress ENTER to continue");
				hge->Gfx_EndScene();
			}
			else if(hge->Input_GetKeyState(HGEK_ENTER))
			{				
				hge->Effect_Free(g_eBGMusic2);
				messege = 2;
				play = 1;
			}
		}
			else if(messege == 2)
		{
			if(!hge->Input_GetKeyState(HGEK_ENTER))
			{
				hge->Gfx_BeginScene();
				sbg->Render(g_vBGPosition.x, g_vBGPosition.y);
				fnt->SetColor(0xFFFFFFFF);
				hge->Effect_Free(g_eBGMusic3);
				fnt->printf(300, 200, HGETEXT_LEFT, "FINAL LEVEL\nFight with the BOSS!\n\n\nPress ENTER to continue");
				hge->Gfx_EndScene();
			}
			else if(hge->Input_GetKeyState(HGEK_ENTER))
			{				
				hge->Effect_Free(g_eBGMusic3);
				messege = 3;
				play = 1;
			}
		}
		}
	else if(play == 4)
	{
		hge->Gfx_BeginScene();
		hge->Gfx_Clear(0);
		surv_sbg->Render(g_vBGPosition.x, g_vBGPosition.y);
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
		//Boss
		for (auto i = Bosses.begin(); i != Bosses.end(); i++)
		{
			(*i)->Render();
		}
		/*if(bs>0)
		Boss->Render();*/
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
		fnt2->printf(20, 20, HGETEXT_LEFT, "Insects eaten: %d", count);
		fnt1->printf(20, 50, HGETEXT_LEFT, "SURV. MODE\nHP: %d", hp);
		hge->Gfx_EndScene();
	}
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
	hge->System_SetState(HGE_SCREENWIDTH, 800);
	hge->System_SetState(HGE_SCREENHEIGHT, 600);
	hge->System_SetState(HGE_SCREENBPP, 32);
	if (hge->System_Initiate())
	{			
		//quad.tex=hge->Texture_Load("bg.png");
		quad.tex=hge->Texture_Load("images/bg.png");
		tex=hge->Texture_Load("images/cursor.png");
		snd=hge->Effect_Load("sounds/menu.wav");
		if(!quad.tex || !tex || !snd)
		{
			//Проверяем загруженны ли все тектсуры и звуки меню игрі
			MessageBox(NULL, "Can't load BG.PNG, CURSOR.PNG or MENU.WAV ", "Error", MB_OK | MB_ICONERROR | MB_APPLMODAL);
			hge->System_Shutdown();
			hge->Release();
			return 0;
		}

		// Set up the quad we will use for background animation
		quad.blend=BLEND_ALPHABLEND | BLEND_COLORMUL | BLEND_NOZWRITE;
		for(int i=0;i<4;i++)
		{
			// Set up z-coordinate of vertices
			quad.v[i].z=0.5f;
			// Set up color. The format of DWORD col is 0xAARRGGBB
			quad.v[i].col=0xFFFFFFFF;
		}
		quad.v[0].x=0; quad.v[0].y=0; 
		quad.v[1].x=800; quad.v[1].y=0; 
		quad.v[2].x=800; quad.v[2].y=600; 
		quad.v[3].x=0; quad.v[3].y=600; 
		// Load the font, create the cursor sprite
		fnt=new hgeFont("font1.fnt");
		spr=new hgeSprite(tex,0,0,32,32);
		// Create and initialize the GUI
		gui=new hgeGUI();
		gui->AddCtrl(new hgeGUIMenuItem(6,fnt,snd,400,100,0.0f,"Lizard"));
		gui->AddCtrl(new hgeGUIMenuItem(1,fnt,snd,400,200,0.0f,"Play"));
		gui->AddCtrl(new hgeGUIMenuItem(2,fnt,snd,400,240,0.1f,"Load Game"));
		gui->AddCtrl(new hgeGUIMenuItem(3,fnt,snd,400,280,0.2f,"Save Game"));
		gui->AddCtrl(new hgeGUIMenuItem(7,fnt,snd,400,320,0.0f,"Surv.Mode"));
		gui->AddCtrl(new hgeGUIMenuItem(4,fnt,snd,400,360,0.3f,"How to Play"));
		gui->AddCtrl(new hgeGUIMenuItem(5,fnt,snd,400,400,0.4f,"Exit"));
		gui->SetNavMode(HGEGUI_UPDOWN | HGEGUI_CYCLED);
		gui->SetCursor(spr);
		gui->SetFocus(1);
		gui->Enter();
		//Background
		bg = hge->Texture_Load("images/bg_1.jpg");
		sbg = new hgeSprite(bg, 0, 0 ,1720, 600);
		surv_bg = hge->Texture_Load("images/surv_mode.jpg");
		surv_sbg = new hgeSprite(surv_bg, 0, 0 ,1920, 1200);
		g_tBackground = hge->Texture_Load("images/lvl1.jpg");
		g_sBackground = new hgeSprite(g_tBackground, 0, 0, 1782, 600);
		g_tBackground2 = hge->Texture_Load("images/lvl2.jpg");
		g_sBackground2 = new hgeSprite(g_tBackground2, 0, 0, 1782, 600);
		g_tBackground3 = hge->Texture_Load("images/lvl3.jpg");
		g_sBackground3 = new hgeSprite(g_tBackground3, 0, 0, 1782, 600);
		g_tBackground4 = hge->Texture_Load("images/lvl44.jpg");
		g_sBackground4 = new hgeSprite(g_tBackground4, 0, 0, 1782, 600);
		fnt2 = new hgeFont("font1.fnt");
		fnt1 = new hgeFont("font1.fnt");
		//Player
		Player1 = new player(hgeVector(300, 530), hgeVector(5, 0),lvl);
		//Insects
		g_tEColors[0] = hge->Texture_Load("images/bonus_1.png");
		g_tEColors[1] = hge->Texture_Load("images/bonus_2.png");
		g_tEColors[2] = hge->Texture_Load("images/bonus_3.png");
		g_tEColors[3] = hge->Texture_Load("images/bonus_4.png");
		g_tEColors[4] = hge->Texture_Load("images/bonus_5.png");
		//Bee
		g_bee[0] = hge->Texture_Load("images/bee.png");
		g_bee[1] = hge->Texture_Load("images/bee.png");
		//Boss
		//Boss = new boss(hgeVector(300, 30), hgeVector(5, 0));
		g_boss[0] = hge->Texture_Load("images/boss.png");
		g_boss[1] = hge->Texture_Load("images/boss.png");
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
		g_eBGMusic4 = hge->Effect_Load("sounds/lvl1.mp3");
		if(!g_tBackground || !g_tBackground2 || !g_tBackground3 || !g_tBackground4 || !g_tEColors || !g_bee || /*!g_boss ||*/ !g_pb || !g_hpb || !g_eBGMusic || !g_eBGMusic2 || !g_eBGMusic3)
		{
			//Проверяем загруженны ли все тектсуры и звуки основной игры
			MessageBox(NULL, "Can't load LVL1(2,3,4).PNG, bonus(1,2,3,4,5).PNG, BEE.PNG, HPB.PNG, PB.PNG or LVL1(2,3,4).MP3 ", "Error", MB_OK | MB_ICONERROR | MB_APPLMODAL);
			hge->System_Shutdown();
			hge->Release();
			return 0;
		}
		hge->System_Start();
		//Очищаем
		hge->Texture_Free(g_tBackground);
		hge->Texture_Free(g_tBackground2);
		hge->Texture_Free(g_tBackground3);
		hge->Texture_Free(g_tBackground4);
		hge->Effect_Free(g_eBGMusic);
		hge->Effect_Free(g_eBGMusic2);
		hge->Effect_Free(g_eBGMusic3);
		hge->Effect_Free(g_eBGMusic4);
		// Delete created objects and free loaded resources
		delete gui;
		delete fnt;
		delete spr;
		hge->Effect_Free(snd);
		hge->Texture_Free(tex);
		hge->Texture_Free(quad.tex);
	};
	delete g_sBackground;
	delete Player1;
	//delete Boss;
	for(auto i = Bosses.begin(); i != Bosses.end();)
	{
		delete (*i);
		i = Bosses.erase(i);
	}
	for(auto i = Insects.begin(); i != Insects.end();)
	{
		delete (*i);
		i = Insects.erase(i);
	}
	for (auto i = Bees.begin(); i != Bees.end();)
	{
		delete (*i);
		i = Bees.erase(i);
	}

	for (auto i = PB.begin(); i != PB.end();)
	{
		delete (*i);
		i = PB.erase(i);
	}

	for (auto i = HPB.begin(); i != HPB.end();)
	{
		delete (*i);
		i = HPB.erase(i);
	}

	//hge->Texture_Free(g_Player1);

	for (short b = 0; b < 2; b++) hge->Texture_Free(g_bee[b]);//удаляем 

	for (short b = 0; b < 1; b++)hge->Texture_Free(g_boss[b]);

	for (short i = 0; i < 5; i++) hge->Texture_Free(g_tEColors[i]);//удаляем

	for (short i = 0; i < 2; i++) hge->Texture_Free(g_pb[i]);

	for (short i = 0; i < 2; i++) hge->Texture_Free(g_hpb[i]);
	hge->System_Shutdown();
	hge->Release();
	// Clean up and shutdown
	return 0;
}
