#define CALC

#ifdef PC
#include <stdlib.h> 
#include <stdio.h>
#include <cstring>
#endif

#include "SDL/SDL.h"  
SDL_Surface *pScreen;
SDL_Surface *pGraphics;
const int FPS=30;
FILE * fileFont;

#include <cmath>
#include "myqueue.h"
#include <vector>
#include <algorithm>
#include <list>
#include "puts.h"
#include "game.h"
#include "level.h"


void DropDeadEnemy(std::list<Enemy*>& pEnemyList,std::list<UIobject*>& pITEMList)
{
	for(auto it=pEnemyList.begin();it!=pEnemyList.end();)
	{	
		Enemy* t=*it;
		if(t->IsDied())
			{
				UIobject *pUIO=new UIobject(t->Get_X(),t->Get_Y(),ImageList(CRACKEFFECT),2);
				pITEMList.push_back(pUIO);
							
				delete t;
				it=pEnemyList.erase(it);
			}
			else it++;
	}
}

void DropDeadITEM(std::list<UIobject*>& pITEMList)
{
	for(auto it=pITEMList.begin();it!=pITEMList.end();)
	{	
		UIobject* t=*it;
		if(t->IsDied())
		{
			delete t;
			it=pITEMList.erase(it);
		}
		else it++;
	}

}

template<typename T>
void DropDeadBullet(T& pList)
{
			
	for(auto it=pList.begin();it!=pList.end();)
	{
		auto t=(*it);
		if(t->IsDied())
		{
			delete t;
			it=pList.erase(it);
		} else {
			it++;
		}
		
	}
}


void GameMain()
{
	Uint8 level=1;
	bool gameover,stageclear;
	Uint32 gametime;
	Uint32 SDLtime=0,SDLtime2=0;
	SDL_Event sdl_event;
	Uint8* keystate;
	Uint32 showFPS=30;
	
	Player player;
	Enemy::pPlayer=&player;
	
	std::vector<Enemy_order> enemy_order;
	queue<TextPage*> pTextQueue;
	queue<GAMEEVENT*> pGAMEEVENTqueue;
	
	Pointer_of_pGAMEEVENT_Queue=&pGAMEEVENTqueue;
	p_Queue_pText=&pTextQueue;

	
	std::list<Enemy*> pEnemyList;
	std::list<Bullet*> pEnemyBulletList;
	std::list<Bullet*> pPlayerBulletList;
	std::list<UIobject*> pITEMList;
	
	
	Player::p_List_pBullet=&pPlayerBulletList;
	Enemy::p_List_pBullet=&pEnemyBulletList;
	
	bool debug_mode;
		
	while(1)
	{
		gameover=false,stageclear=false;
		LoadLevel(level,enemy_order);
		gametime=0;
	
		
		pEnemyBulletList.clear();
		pEnemyList.clear();
		pPlayerBulletList.clear();
		pITEMList.clear();
		player=Player(160,200,3,6,5,3,3,ImageList(PLAYER),ImageList(PLAYERPOINT),ImageList(BULLET1));
		
		while(!gameover && !stageclear)
		{
			
			SDLtime=SDL_GetTicks();
			debug_mode=false;
			
			
			while ( SDL_PollEvent(&sdl_event))
			{
				switch(sdl_event.type)
	             {
	             case SDL_KEYDOWN:
	                 switch( sdl_event.key.keysym.sym )
	                    {
	                    	case SDLK_z:
	                    		if(pTextQueue.empty()==false)
	                    		{
		                    		delete pTextQueue.front();
		                    		pTextQueue.pop();
		                    	}	
	                    	break;
	                    	
	                    }
		        break;
	                 
	                 
	             default:
	                 break;
	             } 
			}
			
			// handle game events
			
			while(pGAMEEVENTqueue.empty()==false)
			{
				switch(pGAMEEVENTqueue.front()->type())
				{
					case Clean_up_bullets:
						
						while(!pEnemyBulletList.empty())
						{
							delete pEnemyBulletList.back();
							pEnemyBulletList.pop_back();
							
						}
						
					break;
					
					case Pause_bullets:
					
						for(auto& t:pEnemyBulletList)
						{
							t->move_pause=true;
						}
					
					
					default:
					break;
				}
				
				pGAMEEVENTqueue.pop();
			}
			
			
			
			
			
			//drop dead objs...
			
			if(player.IsDied())		
				player.ReBirth();
			
			if(pTextQueue.empty())	
			{
				DropDeadEnemy(pEnemyList,pITEMList);
			}
			DropDeadBullet(pEnemyBulletList);
			DropDeadBullet(pPlayerBulletList);
			DropDeadITEM(pITEMList);
			
			
			
			//get keys...
			keystate = SDL_GetKeyState(NULL);
			if(keystate[SDLK_q])
				return;
			
			if(keystate[SDLK_LCTRL])
			{
				while(pTextQueue.empty()==false)
					pTextQueue.pop();
			}
			debug_mode=keystate[SDLK_g]?true:false;
			gameover=keystate[SDLK_r]?true:false;
			
			player.control(keystate);
			
			
			
			//add objs...
			

			while(enemy_order.empty()==false && enemy_order.back().time <=gametime)
			{

				pEnemyList.push_back( enemy_order.back().enemy );
				pEnemyList.back()->Showing_Up();
				enemy_order.pop_back();
			}

			
			//objects Act...
			for(auto &t:pEnemyList)
				t->Act();
			for(auto &t:pEnemyBulletList)
				t->Act();
			for(auto &t:pPlayerBulletList)
				t->Act();	
			for(auto &t:pITEMList)
				t->Act();	
			player.Act();
			
			
			
			
			//check collision...
			
			
			
			for(auto& b:pPlayerBulletList)
			{
				for(auto& e:pEnemyList)
				{
					if(  Hit( b->GetHitBox() , e->GetHitBox() ) )
					{
						e->Get_Damage(player.Get_Power());
					
						UIobject* t=new UIobject(b->Get_X(),b->Get_Y(),ImageList(CRACKEFFECT2),2);
						pITEMList.push_back(t);
					}
				}
				
			}
			
			
			 if(pTextQueue.empty())
			 {
			 	for(auto &t:pEnemyList)
					 	if(Hit(player.GetHitBox(),t->GetHitBox()))
					 	{
			 				if(!debug_mode)
						 		player.Miss();
			 			}
				 
				 for(auto& eb:pEnemyBulletList)
					if(Hit(player.GetHitBox(),eb->GetHitBox()))
					{
						if(!debug_mode)
							player.Miss();
					}
			 }
			 
		 	
			if(player.GetLife()<=0)
				gameover=true;
			
			
			
			
			
			//draw objects...
			
			
			SDL_FillRect(pScreen,NULL,SDL_MapRGB(pScreen->format,255,255,255));

			for(auto &t:pPlayerBulletList)
				t->draw();
							
			player.draw();
			
			for(auto &t:pEnemyList)
				t->draw();
			
			for(auto &t:pEnemyBulletList)
				t->draw();
					
			for(auto &t:pITEMList)
				t->draw();
					
			SDL_BlitSurface(pGraphics,&player.playerpoint,pScreen,player.Get_PlayerPointPos());
			//show UI
			
			BlitGraphics(pGraphics,ImageList(LIFE),pScreen,260,16);
			BlitGraphics(pGraphics,ImageList(player.GetLife()+100),pScreen,260+32,16);
			BlitGraphics(pGraphics,ImageList(BOMB),pScreen,260,16*2);
			BlitGraphics(pGraphics,ImageList(player.GetBomb()+100),pScreen,260+32,16*2);
			 
			 //show FPS...
			if(!debug_mode) 
			{
				BlitGraphics(pGraphics,ImageList(showFPS/10+100),pScreen,295,220); 
		 		BlitGraphics(pGraphics,ImageList(showFPS%10+100),pScreen,295+8,220); 
		 	}

			//draw Text
			
			if(pTextQueue.empty()==false)
			{
				put_chs(pScreen,0,176,pTextQueue.front()->t1);
				put_chs(pScreen,0,192,pTextQueue.front()->t2);
				put_chs(pScreen,0,208,pTextQueue.front()->t3);
			}
			
			
	 		
			SDL_Flip(pScreen);
			
			

			
			//hold fps...
			
			SDLtime2=SDL_GetTicks();
			
			if(SDLtime2-SDLtime<1000/FPS)
				if(!debug_mode)
				{
					SDL_Delay(1000/FPS-(SDLtime2-SDLtime));
				} else {
					SDL_Delay(1);
				}
				
			
				
			showFPS=1000/(SDL_GetTicks()-SDLtime);
			
			++gametime;
		}
	}
}

void ShowLogo()
{
	SDL_Rect t;
	t.x=0;
	t.y=241;
	t.w=320;
	t.h=240;
	SDL_BlitSurface(pGraphics,&t,pScreen,0);
	SDL_Flip(pScreen);
	SDL_Delay(6000);
}

int main(int argc, char *argv[])  
{  	
	#ifdef PC
	fileFont = fopen("HZK12","rb");
	SDL_Init(SDL_INIT_VIDEO);
	pScreen=SDL_SetVideoMode(320,240,8,SDL_HWSURFACE);
	SDL_Surface *pt=SDL_LoadBMP("graphics.bmp");
	#endif
	
	
	#ifdef CALC
	fileFont = fopen("/Documents/game/HZK12.tns","rb");
	SDL_Init(SDL_INIT_VIDEO);
	pScreen=SDL_SetVideoMode(320,240,8,SDL_SWSURFACE);	
	SDL_Surface *pt=SDL_LoadBMP("/Documents/game/graphics.bmp.tns");
	#endif
	
	pGraphics=SDL_DisplayFormat(pt);
	SDL_FreeSurface(pt);	
	
	ShowLogo();
	
	SDL_SetColorKey(pGraphics,SDL_SRCCOLORKEY,SDL_MapRGB(pGraphics->format,255,0,0));
	srand(SDL_GetTicks());
	GameMain();
	SDL_Quit();
	fclose(fileFont);
    return 0;
}  


