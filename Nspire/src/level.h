
Enemy_order EOStruct(Uint32 time,Enemy *enemy)
{
	Enemy_order t;
	t.time=time;
	t.enemy=enemy;
	return t; 
}

void LoadLevel(Uint8 level,std::vector<Enemy_order> & enemy_order)
{
	while(enemy_order.empty()==false)
		enemy_order.pop_back();
		
	
	switch(level)
	{
		case 1:
		{
			
			Enemy *t;
			
			double v0=8,vt=1,x=75,a=(v0*v0-vt*vt)/2.0/x,time=(v0-vt)/a;
			
		 	
			for(int i=0;i<3;++i)
			{
				t=new Enemy_Snipe01(0,30,3,5,0,10,5,ImageList(YAOJING1),ImageList(BULLET2),2,4);
				t->AddMovingOrder(0,CHANGE_SPEED,v0);
				t->AddMovingOrder(0,CHANGE_ACCELERATION,-a);
				t->AddMovingOrder(time,CHANGE_ACCELERATION,0);
				t->AddMovingOrder(time+40,CHANGE_ACCELERATION,a);
				enemy_order.push_back(EOStruct(120+i*15,t));
			}
			for(int i=9;i<12;++i)
			{
				t=new Enemy_Snipe01(320,30,3,5,0,10,5,ImageList(YAOJING1),ImageList(BULLET2),2,4);
				t->AddMovingOrder(0,CHANGE_SPEED,-v0);
				t->AddMovingOrder(0,CHANGE_ACCELERATION,a);
				t->AddMovingOrder(time,CHANGE_ACCELERATION,0);
				t->AddMovingOrder(time+40,CHANGE_ACCELERATION,-a);
				enemy_order.push_back(EOStruct(120+i*15,t));
			}
			for(int i=15;i<18;++i)
			{
				t=new Enemy_Snipe01(0,30,3,5,0,10,5,ImageList(YAOJING1),ImageList(BULLET2),2,4);
				t->AddMovingOrder(0,CHANGE_SPEED,v0);
				t->AddMovingOrder(0,CHANGE_ACCELERATION,-a);
				t->AddMovingOrder(time,CHANGE_ACCELERATION,0);
				t->AddMovingOrder(time+40,CHANGE_ACCELERATION,a);
				enemy_order.push_back(EOStruct(120+i*15,t));
				t=new Enemy_Snipe01(320,55,3,5,0,10,5,ImageList(YAOJING1),ImageList(BULLET2),2,4);
				t->AddMovingOrder(0,CHANGE_SPEED,-v0);
				t->AddMovingOrder(0,CHANGE_ACCELERATION,a);
				t->AddMovingOrder(time,CHANGE_ACCELERATION,0);
				t->AddMovingOrder(time+40,CHANGE_ACCELERATION,-a);
				enemy_order.push_back(EOStruct(120+i*15,t));
			}
			
			v0=4,x=55,a=(-v0*v0)/2/x,time=-v0/a;
			t=new Enemy_Snipe02(100,-32,7,40,time,3,5,PI/12,ImageList(DAHUDIE1),ImageList(BULLET3),3,3);
			t->AddMovingOrder(0,CHANGE_VY,v0);
			t->AddMovingOrder(0,CHANGE_AY,a);
			t->AddMovingOrder(time,CHANGE_A,0);
			t->AddMovingOrder(time,CHANGE_SPEED,0);
			t->AddMovingOrder(time+50,CHANGE_A_A,3*PI/4);
			t->AddMovingOrder(time+50,CHANGE_A,1);
			enemy_order.push_back(EOStruct(120+22*15,t));
			t=new Enemy_Snipe02(210,-32,7,40,time,3,5,PI/12,ImageList(DAHUDIE1),ImageList(BULLET3),3,3);
			t->AddMovingOrder(0,CHANGE_VY,v0);
			t->AddMovingOrder(0,CHANGE_AY,a);
			t->AddMovingOrder(time,CHANGE_A,0);
			t->AddMovingOrder(time,CHANGE_SPEED,0);
			t->AddMovingOrder(time+50,CHANGE_A_A,PI/4);
			t->AddMovingOrder(time+50,CHANGE_A,1);
			enemy_order.push_back(EOStruct(120+22*15,t));
			
			v0=4,x=35,a=(-v0*v0)/2/x,time=-v0/a;
			t=new Enemy_Snipe02(50,-32,7,40,time,3,5,PI/12,ImageList(DAHUDIE1),ImageList(BULLET3),3,3);
			t->AddMovingOrder(0,CHANGE_VY,v0);
			t->AddMovingOrder(0,CHANGE_AY,a);
			t->AddMovingOrder(time,CHANGE_A,0);
			t->AddMovingOrder(time,CHANGE_SPEED,0);
			t->AddMovingOrder(time+50,CHANGE_A_A,PI*3/4);
			t->AddMovingOrder(time+50,CHANGE_A,1);
			enemy_order.push_back(EOStruct(120+28*15,t));
			t=new Enemy_Snipe02(260,-32,7,40,time,3,5,PI/12,ImageList(DAHUDIE1),ImageList(BULLET3),3,3);
			t->AddMovingOrder(0,CHANGE_VY,v0);
			t->AddMovingOrder(0,CHANGE_AY,a);
			t->AddMovingOrder(time,CHANGE_A,0);
			t->AddMovingOrder(time,CHANGE_SPEED,0);
			t->AddMovingOrder(time+50,CHANGE_A_A,PI/4);
			t->AddMovingOrder(time+50,CHANGE_A,1);
			enemy_order.push_back(EOStruct(120+28*15,t));
			
			
			
			
			
			v0=4,x=55,a=(-v0*v0)/2/x,time=-v0/a;
			
			t=new Enemy_Snipe02(100,-32,7,40,time+30,15,20,PI/6,ImageList(DAHUDIE1),ImageList(BULLET3),3,3);
			t->AddMovingOrder(0,CHANGE_VY,v0);
			t->AddMovingOrder(0,CHANGE_AY,a);
			t->AddMovingOrder(time,CHANGE_A,0);
			t->AddMovingOrder(time,CHANGE_SPEED,0);
			t->AddMovingOrder(time+30+15*20,CHANGE_ANGLE,3*PI/4);
			t->AddMovingOrder(time+30+15*20,CHANGE_SPEED,3);
			enemy_order.push_back(EOStruct(120+36*15,t));
			t=new Enemy_Snipe02(210,-32,7,40,time+30,15,20,PI/6,ImageList(DAHUDIE1),ImageList(BULLET3),3,3);
			t->AddMovingOrder(0,CHANGE_VY,v0);
			t->AddMovingOrder(0,CHANGE_AY,a);
			t->AddMovingOrder(time,CHANGE_A,0);
			t->AddMovingOrder(time,CHANGE_SPEED,0);
			t->AddMovingOrder(time+30+15*20,CHANGE_ANGLE,PI/4);
			t->AddMovingOrder(time+30+15*20,CHANGE_SPEED,3);
			enemy_order.push_back(EOStruct(120+36*15,t));
			
			v0=4,x=55,a=(-v0*v0)/2/x,time=-v0/a;
			t=new Enemy_Snipe02(50,-62,7,40,time+30,15,20,PI/6,ImageList(DAHUDIE1),ImageList(BULLET3),3,3);
			t->AddMovingOrder(0,CHANGE_VY,v0);
			t->AddMovingOrder(0,CHANGE_AY,a);
			t->AddMovingOrder(time,CHANGE_A,0);
			t->AddMovingOrder(time,CHANGE_SPEED,0);
			t->AddMovingOrder(time+30+15*20,CHANGE_ANGLE,3*PI/4);
			t->AddMovingOrder(time+30+15*20,CHANGE_SPEED,3);
			enemy_order.push_back(EOStruct(120+36*15,t));
			t=new Enemy_Snipe02(260,-62,7,40,time+30,15,20,PI/6,ImageList(DAHUDIE1),ImageList(BULLET3),3,3);
			t->AddMovingOrder(0,CHANGE_VY,v0);
			t->AddMovingOrder(0,CHANGE_AY,a);
			t->AddMovingOrder(time,CHANGE_A,0);
			t->AddMovingOrder(time,CHANGE_SPEED,0);
			t->AddMovingOrder(time+30+15*20,CHANGE_ANGLE,PI/4);
			t->AddMovingOrder(time+30+15*20,CHANGE_SPEED,3);
			enemy_order.push_back(EOStruct(120+36*15,t));
			
			
		
			
			
			for(int i=42;i<48;++i)
			{
				t=new Enemy_Snipe03(-10,150,3,5,15,5,5,ImageList(YAOJING1),ImageList(BULLET2),2,4);
				t->AddMovingOrder(0,CHANGE_SPEED,2);
				t->AddMovingOrder(0,CHANGE_ANGLE,-PI/4);
				enemy_order.push_back(EOStruct(120+i*15,t));
				
				t=new Enemy_Snipe03(330,150,3,5,15,5,5,ImageList(YAOJING1),ImageList(BULLET2),2,4);
				t->AddMovingOrder(0,CHANGE_SPEED,2);
				t->AddMovingOrder(0,CHANGE_ANGLE,-3*PI/4);
				enemy_order.push_back(EOStruct(120+i*15,t));
			}
			
			v0=4,x=55,a=(-v0*v0)/2/x,time=-v0/a;
			t=new Enemy_Level1_Special(160,-32,3,1400,time,ImageList(YAOJING1));
			t->AddMovingOrder(0,CHANGE_VY,v0);
			t->AddMovingOrder(0,CHANGE_AY,a);
			t->AddMovingOrder(time,CHANGE_A,0);
			t->AddMovingOrder(time,CHANGE_SPEED,0);
			t->AddMovingOrder(time+12*30,CHANGE_SPEED,2);
			t->AddMovingOrder(time+12*30,CHANGE_ANGLE,-PI/2);
			enemy_order.push_back(EOStruct(120+65*15,t));
			
			t=new Boss_Level1(160,-16,6,ImageList(BOSS_LUNA));
			t->AddMovingOrder(0,CHANGE_VY,3);
			t->AddMovingOrder(22,CHANGE_VY,0);
			enemy_order.push_back(EOStruct(1800,t));
			
			std::sort(enemy_order.begin(),enemy_order.end());
			
		}
	}
}
