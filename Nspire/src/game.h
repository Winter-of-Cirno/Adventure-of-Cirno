
const double PI=3.14159265;

enum GAMEEVENT_TYPE
{
	Clean_up_bullets,
	Pause_bullets
};

class GAMEEVENT
{
	public:
	virtual GAMEEVENT_TYPE type()=0;
	
};

class GAMEEVENT_Clean_up_bullets : public GAMEEVENT
{
	public:
	virtual GAMEEVENT_TYPE type()
	{
		return Clean_up_bullets;	
	}	
};
class GAMEEVENT_PAUSE_BULLETS : public GAMEEVENT
{
	public:
	virtual GAMEEVENT_TYPE type()
	{
		return Pause_bullets;	
	}	
};

class TextPage
{
	public:
		TextPage()
		{
			t1[0]=t2[0]=t3[0]='\0';
		}
		
		TextPage(const char* t1,const char * t2,const char* t3)
		{
			strcpy(this->t1,t1);	
			strcpy(this->t2,t2);
			strcpy(this->t3,t3);
		}
	
		char t1[50];
		char t2[50];
		char t3[50];
};

queue<TextPage*>* p_Queue_pText;
queue<GAMEEVENT*>* Pointer_of_pGAMEEVENT_Queue;

class Bullet;

void BlitGraphics(SDL_Surface *pSRC,SDL_Rect image,SDL_Surface *pDST,Sint16 x,Sint16 y)
{
	SDL_Rect t;
	t.x=x;
	t.y=y;
	SDL_BlitSurface(pSRC,&image,pDST,&t);	
}

struct HitBox
{
	double x;
	double y;
	double r;
};
bool Hit(HitBox h1,HitBox h2)
{
	return (h1.x-h2.x)*(h1.x-h2.x)+(h1.y-h2.y)*(h1.y-h2.y)<(h1.r+h2.r)*(h1.r+h2.r);
}

typedef SDL_Rect Image;

const unsigned int NUM0=100;
const unsigned int NUM1=101;
const unsigned int NUM2=102;
const unsigned int NUM3=103;
const unsigned int NUM4=104;
const unsigned int NUM5=105;
const unsigned int NUM6=106;
const unsigned int NUM7=107;
const unsigned int NUM8=108;
const unsigned int NUM9=109;
const unsigned int LIFE=110;
const unsigned int BOMB=111;
const unsigned int PLAYERPOINT=112;
const unsigned int CRACKEFFECT=113;
const unsigned int CRACKEFFECT2=114;

const unsigned int BULLET1=200;
const unsigned int BULLET2=201;
const unsigned int BULLET3=203;
const unsigned int BULLET_TRIANGLE=204;

const unsigned int PLAYER=0;
const unsigned int YAOJING1=1;
const unsigned int DAHUDIE1=2;
const unsigned int BOSS_LUNA=3;

const unsigned int NOTHING=999;


Image ImageList(Uint16 id)
{
	Image t;
	switch(id)
	{
		case PLAYER:
			t.x=0,t.y=0,t.w=32,t.h=32;
			return t;
		case YAOJING1:
			t.x=32,t.y=0,t.w=32,t.h=32;
			return t;
		case DAHUDIE1:
			t.x=16*17,t.y=0,t.w=16*3,t.h=16*3;
			return t;	
		case BOSS_LUNA:
			t.x=64,t.y=0,t.w=32,t.h=32;	
			return t;
		case NUM0:
			t.x=0,t.y=224,t.w=16,t.h=16;
			return t;
		case NUM1:
			t.x=16,t.y=224,t.w=16,t.h=16;
			return t;
		case NUM2:
			t.x=16*2,t.y=224,t.w=16,t.h=16;
			return t;
		case NUM3:
			t.x=16*3,t.y=224,t.w=16,t.h=16;
			return t;
		case NUM4:
			t.x=16*4,t.y=224,t.w=16,t.h=16;
			return t;
		case NUM5:
			t.x=16*5,t.y=224,t.w=16,t.h=16;
			return t;
		case NUM6:
			t.x=16*6,t.y=224,t.w=16,t.h=16;
			return t;
		case NUM7:
			t.x=16*7,t.y=224,t.w=16,t.h=16;
			return t;
		case NUM8:
			t.x=16*8,t.y=224,t.w=16,t.h=16;
			return t;
		case NUM9:
			t.x=16*9,t.y=224,t.w=16,t.h=16;
			return t;
		case LIFE:
			t.x=16*10,t.y=224,t.w=16*2,t.h=16;
			return t;
		case BOMB:
			t.x=16*12,t.y=224,t.w=16*2,t.h=16;
			return t;
		
		case BULLET1:
			t.x=0,t.y=224-16,t.w=16,t.h=16;
			return t;
		case BULLET2:
			t.x=16,t.y=224-16,t.w=16,t.h=16;
			return t;
		case BULLET3:
			t.x=32,t.y=224-16,t.w=16,t.h=16;
			return t;
		case BULLET_TRIANGLE:
			t.x=48,t.y=224-16,t.w=16,t.h=16;
			return t;
		
		case PLAYERPOINT:
			t.x=16*14,t.y=224,t.w=16,t.h=16;
			return t;
		case CRACKEFFECT:
			t.x=16*15,t.y=224,t.w=16,t.h=16;
			return t;
		case CRACKEFFECT2:
			t.x=16*16,t.y=224,t.w=16,t.h=16;
			return t;
		case NOTHING:
			t.x=304,t.y=224,t.w=16,t.h=16;
			return t;
	}
}

class VisualObject 
{
	public:
		VisualObject()
		{
			
		}

		VisualObject(double x,double y,Image image)
		:x(x),y(y),image(image),died(false)
		{
			
		}
	
		SDL_Rect * Get_Image_Pos()
		{
			Image_pos.x=(int)x-image.w/2;
			Image_pos.y=(int)y-image.h/2;	
			return &Image_pos;
		}
		
		virtual void draw()
		{
			SDL_BlitSurface(pGraphics,&image,pScreen,Get_Image_Pos());
		}
		
		bool IsDied()
		{
			return died;
		}
		
		double Get_X()
		{
			return x;
		}
		
		double Get_Y()
		{
			return y;
		}
		
		
		
	protected:	
		bool died;
	
		Image image;
		SDL_Rect Image_pos;
	
		double x;
		double y;
};

class UIobject : public VisualObject
{
	public:
		UIobject(double x,double y,Image image,Sint16 LifeTime)
		:VisualObject(x,y,image),LifeTime(LifeTime),time(0)
		{
		}
		virtual void Act()
		{
			if(!died)
			{
				++time;
				if(time>LifeTime)
					died=true;		
			}
		}
	
	private:
		Uint32 time;	
		Uint32 LifeTime;
};

class MovingObject : public VisualObject
{
	public:	
		MovingObject()
		{
			
		}
		
		MovingObject(double x,double y,Image image,double r)
		:VisualObject(x,y,image),r(r)
		{}
		
		
		virtual void Move(){
			
		}
		
		
		
		const HitBox GetHitBox() const 
		{
			HitBox t;
			t.x=x;
			t.y=y;
			t.r=r;
			return t;
		}
		
		
	protected:

		double r;

				
};

class Player : public MovingObject
{
	public:
		Player()
		{
			
		}
		
	
		Player(double x,double y,double r,double speed,double power,Uint8 life,Uint8 bomb,Image image,Image playerpoint,Image bullet_img)
		:MovingObject(x,y,image,r),playerpoint(playerpoint),bullet_img(bullet_img)
		{
			this->bornX=x;
			this->bornY=y;
			this->bornbomb=this->bomb=bomb;
			this->speed=speed;
			this->life=life;
			this->power=power;
			
			vx=vy=0;
			dirL=dirR=dirU=dirD=SlowMode=false;
			
			
			GodModeTime=100;
			UsingBombTime=0;
			WaitingForMissBombTime=-1;
		}
		
		~Player();
		
		double Get_Power()
		{
			return power;
		}
	
		Sint8 GetLife(){
			return life;
		}
		
		Sint8 GetBomb(){
			return bomb;
		}
		
		void Bomb()
		{
			
				
			if(UsingBombTime<=0 && bomb>0)
			{
				WaitingForMissBombTime=-1;
				UsingBombTime=50;
				GodModeTime=50;
				
				--bomb;
			}
		
		}
		void Miss()
		{
			if(GodModeTime<=0  && WaitingForMissBombTime<0)
			{
				WaitingForMissBombTime=10;
			} 
		}
		
		double Get_Speed()
		{
			if(SlowMode)
				return speed*0.35;
			else return speed;
		}	
		
		void ReBirth()
		{
			x=bornX;
			y=bornY;
			bomb=bornbomb;
			died=false;
		}
	
		virtual void Act()
		{
			if(!died)
			{
				if(!SlowMode)
				{
					playerpoint=ImageList(NOTHING);
				} else 
					playerpoint=ImageList(PLAYERPOINT);
				
				if(GodModeTime>1)
				{
					image=GodModeTime%2==0?ImageList(PLAYER):ImageList(NOTHING);
					--GodModeTime;
				} else if(GodModeTime==1)
				{
					image=ImageList(PLAYER);
					--GodModeTime;
				}
				
				
				if(WaitingForMissBombTime>0)
				{
					image=ImageList(CRACKEFFECT);
					--WaitingForMissBombTime;
				} else if(WaitingForMissBombTime==0)
				{
					image=ImageList(PLAYER);
					--life;
					--WaitingForMissBombTime;
					GodModeTime=100;
					died=true;
					Pointer_of_pGAMEEVENT_Queue->push(new GAMEEVENT_Clean_up_bullets);
				} else Move();
				
				if(UsingBombTime==1)
				{
					Pointer_of_pGAMEEVENT_Queue->push(new GAMEEVENT_Clean_up_bullets);
				}
				
				if(UsingBombTime>=1)
				{
					Pointer_of_pGAMEEVENT_Queue->push(new GAMEEVENT_PAUSE_BULLETS);
					--UsingBombTime;
				}
				
			}
			
		}
		
		
		virtual void Move()
		{
			int tx,ty;
			tx=x+vx;
			ty=y+vy;
			
			if(tx>320)
				x=320;
			else if(tx<0)
				x=0;
			else x=tx;
			
			if(ty>240)
		 		ty=240;
 			else if(ty<0)
 				ty=0;
			else y=ty;
		}
		
		void Shoot();

		Image * Get_PlayerPointPos()
		{
			playerpointpos.x=(int)x-playerpoint.w/2;
			playerpointpos.y=(int)y-playerpoint.h/2;
			return &playerpointpos;
		}
		
		void control(Uint8* keystate)
		{
			if(p_Queue_pText->empty()==true)
			{
				#ifdef PC
				if(keystate[SDLK_z])
					Shoot();
					
				if(keystate[SDLK_x])
					Bomb();
				#endif
				
				
				#ifdef CALC
					Shoot();
				
				if(keystate[SDLK_LSHIFT])
					Bomb();
				#endif
				
			}

			
			dirR=keystate[SDLK_RIGHT]||keystate[SDLK_6]?true:false;
			dirL=keystate[SDLK_LEFT]||keystate[SDLK_4]?true:false;
			dirU=keystate[SDLK_UP]||keystate[SDLK_8]?true:false;
			dirD=keystate[SDLK_DOWN]||keystate[SDLK_5]?true:false;
			
			
			#ifdef PC
			SlowMode=keystate[SDLK_LSHIFT]?true:false;
			#endif
			
			#ifdef CALC
			SlowMode=keystate[SDLK_TAB]?true:false;
			#endif
			
			if(dirR)
			{
				if(dirU)
					vx=Get_Speed()/1.4 , vy=-Get_Speed()/1.4;
				else if (dirD)
					vx=Get_Speed()/1.4 , vy=Get_Speed()/1.4;
				else vx=Get_Speed();
			} else if (dirL)
			{
				if(dirU)
					vx=-Get_Speed()/1.4 , vy=-Get_Speed()/1.4;
				else if (dirD)
					vx=-Get_Speed()/1.4 , vy=Get_Speed()/1.4;
				else vx=-Get_Speed();
			} else 
			{
			  vx=0;
			  if (dirU)
					vy=-Get_Speed();
			  else if (dirD)
			  		vy=Get_Speed();
  			  else vy=0;
			}
		}
		
		Image playerpoint;
		Image playerpointpos;	
		

		
		
		
		static std::list<Bullet*>* p_List_pBullet;
	private:
		double vx;
		double vy;
		double speed;
		bool dirL;
		bool dirR;
		bool dirU;
		bool dirD;
		bool SlowMode;
		
		double bornX;
		double bornY;
		Uint8 bornbomb;
		
		Sint8 life;
		Sint8 bomb;		
		
		Sint8 GodModeTime;
		Sint8 UsingBombTime;
		Sint8 WaitingForMissBombTime;
		
		double power;
		Image bullet_img;
		

};
std::list<Bullet*>* Player::p_List_pBullet;

class MovingOrder
{
	public:
		MovingOrder()
		{
			
		}
	
		MovingOrder(Uint32 t,Uint8 ct,double data)
		{
			this->time=t;
			this->changetype=ct;
			this->data=data;	
		}
		
		Uint32 time;
		Uint8 changetype;
		double data;	
};

const int CHANGE_SPEED=1;
const int CHANGE_ANGLE=2;
const int CHANGE_ANGULAR_RATE=3;
const int CHANGE_ACCELERATION=4;
const int CHANGE_ROLLING_CENTER_X=5;
const int CHANGE_ROLLING_CENTER_Y=6;
const int CHANGE_A=7;
const int CHANGE_AX=8;
const int CHANGE_AY=9;
const int CHANGE_VX=10;
const int CHANGE_VY=11;
const int CHANGE_A_A=12;

class AutoMovingObject : public MovingObject
{
	public:
	AutoMovingObject(double x,double y,Image image,double r)
	:MovingObject(x,y,image,r)
	{
		time=speed=angle=Angular_rate=RollingCenterX=RollingCenterY=acceleration=vx=vy=ax=ay=AccelerationAngle=0;
		move_pause=false;
		died=false;
	}
	
		
	void AddMovingOrder(Uint32 time,Uint8 ct,double data)
	{
		MovingOrder t(time,ct,data);
		MovingOrderQueue.push(t);	
	}
	
	void ChangeSpeed(double speed)
	{
		this->speed=speed;
		vx=speed*cos(angle);
		vy=speed*sin(angle);
	}
	
	void ChangeAngle(double angle)
	{
		this->angle=angle;
		vx=speed*cos(angle);
		vy=speed*sin(angle);
	}
	
	void ChangeA(double acceleration)
	{
		this->acceleration=acceleration;
		ax=acceleration*cos(AccelerationAngle);
		ay=acceleration*sin(AccelerationAngle);
	}
	
	void ChangeVX(double vx)
	{
		this->vx=vx;
		angle=atan2(vy,vx);
		speed=sqrt(vx*vx+vy*vy);
	}
	
	void ChangeVY(double vy)
	{
		this->vy=vy;
		angle=atan2(vy,vx);
		speed=sqrt(vx*vx+vy*vy);
	}
	
	void ChangeAX(double AX)
	{
		this->ax=ax;
		AccelerationAngle=atan2(ay,ax);
		acceleration=sqrt(ax*ax+ay*ay);
	}
	void ChangeAY(double AY)
	{
		this->ay=ay;
		AccelerationAngle=atan2(ay,ax);
		acceleration=sqrt(ax*ax+ay*ay);
	}
	
	void Change_A_Angle(double AA)
	{
		this->AccelerationAngle=AA;
		ax=acceleration*cos(AccelerationAngle);
		ay=acceleration*sin(AccelerationAngle);
	}
	
	virtual void Act()
	{
		
	}
	
	virtual bool CheckIfDied()
	{
		
	}
	
	virtual void die()
	{
		died=true;
	}
	
	virtual void Move()
	{
		while(MovingOrderQueue.empty()==false && MovingOrderQueue.front().time<=time)
		{
			MovingOrder t=MovingOrderQueue.front();
			MovingOrderQueue.pop();
			switch(t.changetype)
			{
				case CHANGE_SPEED:
					ChangeSpeed(t.data);
					break;
				
				case CHANGE_ANGLE:
					ChangeAngle(t.data);
					break;
					
				case CHANGE_ANGULAR_RATE:
					Angular_rate=t.data;
					break;
					
				case CHANGE_ACCELERATION: 
					ChangeA(t.data);
					break;
				
				case CHANGE_ROLLING_CENTER_X:
					RollingCenterX=t.data;
					break;
				
				case CHANGE_ROLLING_CENTER_Y:
					RollingCenterY=t.data;
					break;
				
				case CHANGE_VX:
					ChangeVX(t.data);
					break;
				
				case CHANGE_VY:
					ChangeVY(t.data);
					break;
				
				case CHANGE_AX:
					ChangeAX(t.data);
					break;
					
				case CHANGE_AY:
					ChangeAY(t.data);
					break;
					
				case CHANGE_A:
					ChangeA(t.data);
					break;
				
				case CHANGE_A_A:
					Change_A_Angle(t.data);
					break;
				
				default:
					break;
			}
		}
		
		if(Angular_rate!=0)
		{
			x=(x-RollingCenterX)*cos(Angular_rate)-(y-RollingCenterY)*sin(Angular_rate)+RollingCenterX;
			y=(y-RollingCenterY)*cos(Angular_rate)+(x-RollingCenterX)*sin(Angular_rate)+RollingCenterY;
		}
		
		ChangeVX(vx+ax);
		ChangeVY(vy+ay);
		x+=vx;
		y+=vy;
		
	}
	
	
		bool move_pause;
		
	protected:
		queue<MovingOrder> MovingOrderQueue;
		Uint32 time;

		double speed;
		double angle;
		double Angular_rate;
		double RollingCenterX;
		double RollingCenterY;	
		double acceleration;
		
		double vx;
		double vy;
		double ax;
		double ay;
		
		double AccelerationAngle;
};

class Enemy : public AutoMovingObject
{
	public:

	
		Enemy(double x,double y,double r,Uint32 hp,Sint32 StartShootingTime,int ShootingTimes,int ShootingInterval, Image image,Image bullet_img,double bullet_r)
		:AutoMovingObject(x,y,image,r),bullet_img(bullet_img)
		{
			this->hp=hp;
			this->StartShootingTime=StartShootingTime;
			this->ShootingTimes=ShootingTimes;
			this->ShootingInterval=ShootingInterval;
			this->bullet_r=bullet_r;
			
			
			ShootingCount=0;
		}
		
		virtual ~Enemy();
		
		virtual void Showing_Up()
		{
			
		}
		
		
		
		virtual bool CheckIfDied()
		{
			return x+image.w<-32 || x>360 || y>290 || y+image.h<-32;
		}
		
		virtual void Act()
		{
			if(!died && !move_pause)
			{
				Shoot();
				Move();
				
				if(CheckIfDied())
					die();
				++time;
			}
		}
		
		virtual void Get_Damage(Uint32 damage)
		{
			hp-=damage;
			if(hp<=0)
				die();
		} 
		
		virtual void Shoot()=0;
		
		
		virtual void die()
		{
			died=true;
		}
		
		static Player *pPlayer;
		static std::list<Bullet*>* p_List_pBullet;
	protected:
		Sint32 hp;
		Sint32 StartShootingTime;
		Sint32 ShootingInterval;
		Sint16 ShootingCount;
		int ShootingTimes;
		Image bullet_img;
		double bullet_r;

};
Player* Enemy::pPlayer = 0;
std::list<Bullet*>* Enemy::p_List_pBullet;

class Bullet : public AutoMovingObject
{
	public:
	
	Bullet(double r,Image image,Sint32 DeathTime)
	:AutoMovingObject(0,0,image,r)
	{
		this->DeathTime=DeathTime;
	}
	
	virtual ~Bullet()
	{
		
	}
	
	Bullet(double x,double y,double r,Image image,Sint32 DeathTime)
	:AutoMovingObject(x,y,image,r)
	{
		this->DeathTime=DeathTime;
	}
	
	virtual bool CheckIfDied()
	{
		if(DeathTime==-1)
		{
			if(x+image.w<0 || x>320 || y>240 || y+image.h<0)
				return true;
			else return false;
		} else if(DeathTime==time)
				return true;
		else return false;
		
	}
	
	virtual void Act()
	{
		if(!died && !move_pause)
			{
				Move();
				
				if(CheckIfDied())
					die();
					
				++time;
			}
	}
	
	
	
	private:
		Sint32 DeathTime; // -1 means the object died when out of the screen.
};

Enemy::~Enemy()
{
}

Player::~Player()
{
}

void Player::Shoot()
{
	Bullet* pbullet=new Bullet(x-5,y-8,5,ImageList(BULLET1),-1);
	pbullet->AddMovingOrder(0,CHANGE_ANGLE,-3.14/2);
	pbullet->AddMovingOrder(0,CHANGE_SPEED,10);
	
	p_List_pBullet->push_back(pbullet);
	pbullet=new Bullet(x+4,y-8,5,ImageList(BULLET1),-1);
	pbullet->AddMovingOrder(0,CHANGE_ANGLE,-3.14/2);
	pbullet->AddMovingOrder(0,CHANGE_SPEED,10);
	p_List_pBullet->push_back(pbullet);

	
}

class Enemy_Snipe01 : public Enemy
{
	
	public:
		
		Enemy_Snipe01(double x,double y,double r,Uint32 hp,Sint32 StartShootingTime,int ShootingTimes,int ShootingInterval, Image image,Image bullet_img,double bullet_r,double Bullet_speed)
		 :Enemy(x,y,r,hp,StartShootingTime,ShootingTimes,ShootingInterval,image,bullet_img,bullet_r) , Bullet_speed(Bullet_speed)
        {}
		
		
		virtual void Shoot()
		{
			if(time>=StartShootingTime)
				if(ShootingTimes==-1 || ShootingCount<ShootingTimes)
					{
						if((time-StartShootingTime)%ShootingInterval==0)
						{
							Bullet *pbullet=new Bullet(x,y,bullet_r,bullet_img,-1);
							pbullet->AddMovingOrder(0,CHANGE_SPEED,Bullet_speed);
							pbullet->AddMovingOrder(0,CHANGE_ANGLE,atan2(pPlayer->Get_Y()-y,pPlayer->Get_X()-x));
							p_List_pBullet->push_back(pbullet);
								
							++ShootingCount;	
						}
						
							
						
					}			
	
		}
		
	protected:
		double Bullet_speed;
};

class Enemy_Snipe02 : public Enemy
{
	
	public:
		
		Enemy_Snipe02(double x,double y,double r,Uint32 hp,Sint32 StartShootingTime,int ShootingTimes,int ShootingInterval, double Shoot_Angle_Range,Image image,Image bullet_img,double bullet_r,double Bullet_speed)
		 :Enemy(x,y,r,hp,StartShootingTime,ShootingTimes,ShootingInterval,image,bullet_img,bullet_r) , Shoot_Angle_Range(Shoot_Angle_Range) , Bullet_speed(Bullet_speed)
        {}
		
		
		virtual void Shoot()
		{
			if(time>=StartShootingTime)
				if(ShootingTimes==-1 || ShootingCount<ShootingTimes)
					{
						if((time-StartShootingTime)%ShootingInterval==0)
						{
							double tAngle=atan2(pPlayer->Get_Y()-y,pPlayer->Get_X()-x);
							Bullet *pbullet=new Bullet(x,y,bullet_r,bullet_img,-1);
							pbullet->AddMovingOrder(0,CHANGE_SPEED,Bullet_speed);
							pbullet->AddMovingOrder(0,CHANGE_ANGLE,tAngle);
							p_List_pBullet->push_back(pbullet);
							
							pbullet=new Bullet(x,y,bullet_r,bullet_img,-1);
							pbullet->AddMovingOrder(0,CHANGE_SPEED,Bullet_speed);
							pbullet->AddMovingOrder(0,CHANGE_ANGLE,tAngle+Shoot_Angle_Range);
							p_List_pBullet->push_back(pbullet);
							
							pbullet=new Bullet(x,y,bullet_r,bullet_img,-1);
							pbullet->AddMovingOrder(0,CHANGE_SPEED,Bullet_speed);
							pbullet->AddMovingOrder(0,CHANGE_ANGLE,tAngle-Shoot_Angle_Range);
							p_List_pBullet->push_back(pbullet);
								
							++ShootingCount;	
						}
						
							
						
					}			
	
		}
		
	protected:
		double Shoot_Angle_Range;
		double Bullet_speed;
};

class Enemy_Snipe03 : public Enemy
{
	
	public:
		
		Enemy_Snipe03(double x,double y,double r,Uint32 hp,Sint32 StartShootingTime,int ShootingTimes,int ShootingInterval, Image image,Image bullet_img,double bullet_r,double Bullet_speed)
		 :Enemy(x,y,r,hp,StartShootingTime,ShootingTimes,ShootingInterval,image,bullet_img,bullet_r) , Bullet_speed(Bullet_speed) ,Angle_SET(false)
        {}
		
		
		virtual void Shoot()
		{
			if(time>=StartShootingTime)
			{
				if(!Angle_SET)
				{
					Angle_SET=true;
					tAngle=atan2(pPlayer->Get_Y()-y,pPlayer->Get_X()-x);
				}
				
				if(ShootingTimes==-1 || ShootingCount<ShootingTimes)
					{
						if((time-StartShootingTime)%ShootingInterval==0)
						{
							Bullet *pbullet=new Bullet(x,y,bullet_r,bullet_img,-1);
							pbullet->AddMovingOrder(0,CHANGE_SPEED,Bullet_speed);
							pbullet->AddMovingOrder(0,CHANGE_ANGLE,tAngle);
							p_List_pBullet->push_back(pbullet);
								
							++ShootingCount;	
						}
						
							
						
					}			
			}
		}
		
	protected:
		double Bullet_speed;
		double tAngle;
		bool Angle_SET;
};

class Enemy_Level1_Special : public Enemy
{
	
	public:
		
		Enemy_Level1_Special(double x,double y,double r,Uint32 hp,Sint32 StartShootingTime,Image image)
		 :Enemy(x,y,r,hp,StartShootingTime,0,0,image,ImageList(NOTHING),0) 
        {
			tAngle1=PI/2;
		}
        
        // 构造函数中有用的参数仅有 x,y,r,hp,image,StartShootingTime
		// 其余为多余参数 
		
		
		virtual void Shoot()
		{

			
			if((time-StartShootingTime) % 2==0)
			{
				Bullet *tb=new Bullet(x,y,2,ImageList(BULLET2),-1);
				tb->AddMovingOrder(0,CHANGE_SPEED,1);
				tb->AddMovingOrder(0,CHANGE_ANGLE, ((tAngle1+=PI/8)>(2*PI))?(tAngle1-=2*PI):tAngle1 );
				p_List_pBullet->push_back( tb );
			}
			
			if((time-StartShootingTime) % 18==0)
			{
				double Angle=atan2(pPlayer->Get_Y()-y,pPlayer->Get_X()-x);
				int max=12;
				for(int i=0;i<max;i++)
				{
					Bullet *pbullet=new Bullet(x,y,3,ImageList(BULLET3),-1);
					pbullet->AddMovingOrder(0,CHANGE_SPEED,2);
					pbullet->AddMovingOrder(0,CHANGE_ANGLE,Angle+2*PI/max*i);
					p_List_pBullet->push_back(pbullet);
				}
			}
			
		}
		
	private:
		double tAngle1;
		
		
};

class Boss_Spell_Card
{
	public:
		Boss_Spell_Card(const char* name,int id,int MaxTime,int MaxHp) 
		: time(0), MaxTime(MaxTime) , hp(MaxHp) ,MaxHp(MaxHp), id(id) 
		{
			strcpy(this->name,name) ;
		}
		
		char name[50];
		int time;
		const int MaxTime; // -1 means forever
		int hp;
		const int MaxHp;
		int id;
};

class Enemy_Boss : public Enemy
{
	public:
		Enemy_Boss(double x,double y,double r,Image image)
		 :Enemy(x,y,r,0,0,0,0,image,ImageList(NOTHING),0) 
        {
			
		}
        
        // 构造函数中有用的参数仅有 x,y,r,image
		// 其余为多余参数
		
		
		
		virtual ~Enemy_Boss()
		{
			while(Queue_of_pointers_of_spell_cards.empty()==false)
			{
				delete Queue_of_pointers_of_spell_cards.front();
				Queue_of_pointers_of_spell_cards.pop();
			}
		}
		
		virtual void draw() 
		{
			
			if(p_Queue_pText->empty())
				if(Queue_of_pointers_of_spell_cards.empty()==false)
				{
					SDL_Rect tRect;
					tRect.x=15;
					tRect.y=10;
					tRect.h=5;
					tRect.w= Queue_of_pointers_of_spell_cards.front()->hp *1.0 / Queue_of_pointers_of_spell_cards.front()->MaxHp *260.0;
					
					SDL_FillRect(pScreen,&tRect,SDL_MapRGB(pScreen->format,255,0,0));
					
					
					if(Queue_of_pointers_of_spell_cards.front()->MaxTime!=-1)
					{
						int mytime=(Queue_of_pointers_of_spell_cards.front()->MaxTime-Queue_of_pointers_of_spell_cards.front()->time)/FPS;
						BlitGraphics(pGraphics,ImageList(mytime/10+100),pScreen,15+260+16,7);
						BlitGraphics(pGraphics,ImageList(mytime%10+100),pScreen,15+260+16+8,7);
					} 
					
					
					if(Queue_of_pointers_of_spell_cards.front()->time <= 2*FPS)
					{
						if(Queue_of_pointers_of_spell_cards.front()->time % 2==0)
							Font_DrawString(pScreen,100,120,Queue_of_pointers_of_spell_cards.front()->name,SDL_MapRGB(pScreen->format,0,0,255));
					} else
						Font_DrawString(pScreen,15,10+7,Queue_of_pointers_of_spell_cards.front()->name,SDL_MapRGB(pScreen->format,0,0,255));
					
				}
			
			SDL_BlitSurface(pGraphics,&image,pScreen,Get_Image_Pos());
		}
		
		virtual void Act()
		{
			if(died)
				return;
			
			if(p_Queue_pText->empty())	
			{
				if(Queue_of_pointers_of_spell_cards.empty()==false)
				{
					++Queue_of_pointers_of_spell_cards.front()->time;
					
					if(Queue_of_pointers_of_spell_cards.front()->MaxTime !=-1 )
						if(Queue_of_pointers_of_spell_cards.front()->time 
							> Queue_of_pointers_of_spell_cards.front()->MaxTime)
						{
							Spell_Card_Finish();
						} 
					
					
						
				} 
			
				if(Queue_of_pointers_of_spell_cards.empty())
				{
					die();
				}
			}
			
			
			if(!died && !move_pause)
			{
				if(p_Queue_pText->empty())
				{
					Shoot();
				}
				Move();
				++time;
			}
			
		}
		
		virtual void Get_Damage(Uint32 damage)
		{	
			if(p_Queue_pText->empty())
				if(Queue_of_pointers_of_spell_cards.empty()==false)
				{
					
					if(Queue_of_pointers_of_spell_cards.front()->hp >0 )
					{
						Queue_of_pointers_of_spell_cards.front()->hp-=damage;
						
					}
					
					if(Queue_of_pointers_of_spell_cards.front()->hp <=0 )
					{
						Spell_Card_Finish();
					}
					
				}
			
		
		}
		
	protected:
		
	
	
		
		
		virtual void Spell_Card_Finish()
		{
			Pointer_of_pGAMEEVENT_Queue->push(new GAMEEVENT_Clean_up_bullets);
			
			delete Queue_of_pointers_of_spell_cards.front();
			Queue_of_pointers_of_spell_cards.pop();
		}
		
		
		queue<Boss_Spell_Card*> Queue_of_pointers_of_spell_cards;
};

class Bullet_Of_Level1_Boss_SC4 : public Bullet
{
	public:
	Bullet_Of_Level1_Boss_SC4(double x,double y,double r,Image image,double sign) : 
	x0(x),y0(y),theta(0),sign(sign),
	t1(1*FPS),t2(160),
	x1(160),y1(120),
	Bullet(x,y,r,image,0)
	{
		
	}
	
	
	virtual bool CheckIfDied()
	{
		return (x-x1)*(x-x1)+(y-y1)*(y-y1) < 4;
	}
	
	
	virtual void Move()
	{
		if(time <= t1)
		{
			double k=(1-(1-0.75)/t1*time);
			x= k*(x0-x1)+x1;
			y= k*(y0-y1)+y1;
			
			if(time==t1)
				x0=x,y0=y;
			
		} else {
		
		if(time > t1 )//&& time < t1+t2)	
		{
			double k=1-(1-0.25)/t2*(time-t1);
			x= k*(x0-x1)*cos(theta) - k*(y0-y1)*sin(theta) + x1;
			y= k*(x0-x1)*sin(theta) + k*(y0-y1)*cos(theta) + y1;
			theta+= sign * PI/128;
		}
			
		}
		
		
	}

	private:
	double x0,y0,theta,t1,t2,x1,y1,sign;	
};

class Boss_Level1 : public Enemy_Boss
{
	public: 
	
		Boss_Level1(double x,double y,double r,Image image)
		 : Enemy_Boss(x,y,r,image)
		{
			Queue_of_pointers_of_spell_cards.push(new Boss_Spell_Card("　",1,30*FPS,3000));
			Queue_of_pointers_of_spell_cards.push(new Boss_Spell_Card("月符【流动的月光】",2,48*FPS,8000));
			Queue_of_pointers_of_spell_cards.push(new Boss_Spell_Card("　",3,30*FPS,4000));
			Queue_of_pointers_of_spell_cards.push(new Boss_Spell_Card("声符【静默空间】",4,33*FPS,8000));
			
		}	
		
		virtual void Showing_Up()
		{
			
		}
		
		
		virtual void die()
		{
			died=true;
	
		}
		
		virtual void Shoot()
		{
			
			if(Queue_of_pointers_of_spell_cards.empty()==false)
			{
				Boss_Spell_Card* pSC=Queue_of_pointers_of_spell_cards.front();
				switch(pSC->id)
				{
					
					
					case 1:
					{
						if(pSC->time % 14==0)
						{
							double Angle=atan2(pPlayer->Get_Y()-y,pPlayer->Get_X()-x);
							int max=36;
							for(int i=0;i<max;i++)
							{
								Bullet *pbullet=new Bullet(x,y,3,ImageList(BULLET3),-1);
								pbullet->AddMovingOrder(0,CHANGE_SPEED,2);
								pbullet->AddMovingOrder(0,CHANGE_ANGLE,Angle+2*PI/max*i);
								p_List_pBullet->push_back(pbullet);
							}
						}
					}
					break;
					
					
					case 2:
					{
						int tx;
								
						if(pSC->time >45)
						{
							if(pSC->time %16==0)
							{
								tx=0;
								tx+=rand()%35+30;
								
								while(tx<320)
								{
									Bullet *tb;
									tb=new Bullet(tx,0,2,ImageList(BULLET2),-1);
									tb->AddMovingOrder(0,CHANGE_VY,2);
									p_List_pBullet->push_back(tb);
									
									tx+=rand()%35+30;
								}
							}
							
							if(pSC->time %96==0)
							{
								tx=0;
								for(int i=0;i<12;i+=2)
								{
									Bullet *tb;
									for(int j=0;j<3;j++)
									{
										tb=new Bullet(tx,j*14,2,ImageList(BULLET_TRIANGLE),-1);
										tb->AddMovingOrder(0,CHANGE_VY,1.5+i*0.2);
										p_List_pBullet->push_back(tb);
									}
									tx+=23;	
								}
								
								for(int i=8;i>=0;i-=2)
								{
									Bullet *tb;
									for(int j=0;j<3;j++)
									{
										tb=new Bullet(tx,j*14,2,ImageList(BULLET_TRIANGLE),-1);
										tb->AddMovingOrder(0,CHANGE_VY,1.5+i*0.2);
										p_List_pBullet->push_back(tb);
									}
									tx+=23;	
								}
							}
							
							if(pSC->time>48 && (pSC->time-48)%96==0)
							{
								tx=120;
								for(int i=0;i<12;i+=2)
								{
									Bullet *tb;
									for(int j=0;j<3;j++)
									{
										tb=new Bullet(tx,j*14,2,ImageList(BULLET_TRIANGLE),-1);
										tb->AddMovingOrder(0,CHANGE_VY,1.5+i*0.2);
										p_List_pBullet->push_back(tb);
									}
									tx+=23;	
								}
								
								for(int i=8;i>=0;i-=2)
								{
									Bullet *tb;
									for(int j=0;j<3;j++)
									{
										tb=new Bullet(tx,j*14,2,ImageList(BULLET_TRIANGLE),-1);
										tb->AddMovingOrder(0,CHANGE_VY,1.5+i*0.2);
										p_List_pBullet->push_back(tb);
									}
									tx+=23;	
								}
							}
						}
						
					
					}
					break;
					
					case 3:
					{
						int n=30;
						if(pSC->time % 14==0)
						{
							double Angle = double(pSC->time / 14 % (n+1)) / n * 2 * PI;
							int max=36;
							for(int i=0;i<max;i++)
							{
								Bullet *pbullet=new Bullet(x,y,3,ImageList(BULLET3),-1);
								pbullet->AddMovingOrder(0,CHANGE_SPEED,2);
								pbullet->AddMovingOrder(0,CHANGE_ANGLE,Angle+2*PI/max*i);
								p_List_pBullet->push_back(pbullet);
							}
						}
					}
					break;
					
					case 4:
					{
						if((pSC->time-1)%(4*FPS)==0)
						{
							double sign=(rand()%2?1:-1);
							Bullet *pbullet;
							for(int tx=0;tx<=320;tx+=40)
							{
								pbullet=new Bullet_Of_Level1_Boss_SC4(tx,-40,2,ImageList(BULLET3),sign);
								p_List_pBullet->push_back(pbullet);
								
								pbullet=new Bullet_Of_Level1_Boss_SC4(tx,280,2,ImageList(BULLET3),sign);
								p_List_pBullet->push_back(pbullet);
							}
							
							for(int ty=0;ty<=240;ty+=40)
							{
								
								pbullet=new Bullet_Of_Level1_Boss_SC4(0,ty,2,ImageList(BULLET3),sign);
								p_List_pBullet->push_back(pbullet);
								
								
								pbullet=new Bullet_Of_Level1_Boss_SC4(320,ty,2,ImageList(BULLET3),sign);
								p_List_pBullet->push_back(pbullet);
							}
							
						} 
					}
					break;
					
				}
				
			}
			
		}
		
	protected:
	
		
};

struct Enemy_order
{
	bool operator<(const Enemy_order & t)
	{
		return time > t.time;
	}
		
	Uint32 time;
	Enemy* enemy;
};
