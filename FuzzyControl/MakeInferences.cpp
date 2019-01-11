// MakeInferences.cpp: implementation of the MakeInferences class.
//
//////////////////////////////////////////////////////////////////////

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

#include "stdafx.h"
#include "versionone.h"
#include "MakeInferences.h"
#include "MakeRelations.h"
#include "MakeMapping.h"
#include "FzyRelation.h"
#include "Infer.h"
#include "Math.h"
#include "Robot.h"

#include "conio.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

MakeInferences::MakeInferences()
{
	Relations.build();
	Mappings.build();
}

void MakeInferences::Build()
{
	pi = 3.1415926535;

	int NumRule = 10;
	int i;
	rules = new InFer *[NumRule];
	for(i=0;i<NumRule;i++)
		rules[i]=new InFer;

	FzyRelation *RelA;
	FzyRelation *RelB;
	FzyRelation *Out;
	Matrix *Mx;
//---------------------------------------------------------------
//	stearing control
	RelA = Relations.Rels[6];		//	Target following behaviour
	RelB = Relations.Rels[14];		//	obstacle avoid behaviour
	Out = Relations.Rels[15];		//	steering control
	Mx = Mappings.Mats[0];			//
	rules[0]->Build(RelA, RelB, Out, Mx);
//---------------------------------------------------------------
//	Target speed control
	RelA = Relations.Rels[7];		//	target distance
	RelB = Relations.Rels[0];		//	Maximum vehicle speed
	Out = Relations.Rels[18];		//	vehicle speed
	Mx = Mappings.Mats[1];			//
	rules[1]->Build(RelA, RelB, Out, Mx);
//---------------------------------------------------------------
//	Target follow behaviour
	RelA = Relations.Rels[5];		//direction error
	RelB = Relations.Rels[7];		//distance to target
	Out = Relations.Rels[6];		//target follow
	Mx = Mappings.Mats[2];			//
	rules[2]->Build(RelA, RelB, Out, Mx);
//---------------------------------------------------------------
//	Left wheel speed
	RelA = Relations.Rels[15];		//stearing direction
	RelB = Relations.Rels[18];		//vehicle speed
	Out = Relations.Rels[3];		//Left wheel speed
	Mx = Mappings.Mats[3];			//
	rules[3]->Build(RelA, RelB, Out, Mx);
//---------------------------------------------------------------
//	Right wheel speed
	RelA = Relations.Rels[15];		//stearing direction
	RelB = Relations.Rels[18];		//vehicle speed
	Out = Relations.Rels[4];		//Right wheel speed
	Mx = Mappings.Mats[4];			//
	rules[4]->Build(RelA, RelB, Out, Mx);
//---------------------------------------------------------------
//	Vehicle Speed
	RelA = Relations.Rels[15];		//steering angle
	RelB = Relations.Rels[8];		//obstacle proximity
	Out = Relations.Rels[0];		//Maximum vehicle speed
	Mx = Mappings.Mats[5];			//
	rules[5]->Build(RelA, RelB, Out, Mx);
//---------------------------------------------------------------
//	Fuzzy map to Gray Map convertion rule
	RelA = Relations.Rels[9];		//
	RelB = Relations.Rels[10];		//
	Out = Relations.Rels[11];		//
	Mx = Mappings.Mats[6];			//
	rules[6]->Build(RelA, RelB, Out, Mx);
//---------------------------------------------------------------
//	Obstacle avoidance behaviour
	RelA = Relations.Rels[12];		//	Left proximity
	RelB = Relations.Rels[13];		//	Right proximity
	Out = Relations.Rels[14];		//	Obstacle avoidance
	Mx = Mappings.Mats[7];			//
	rules[7]->Build(RelA, RelB, Out, Mx);
//---------------------------------------------------------------
//	Averaging obstacle avoidance behaviour
	RelA = Relations.Rels[14];		//	min obstacle avoidance
	RelB = Relations.Rels[16];		//	average obstacle avoidance
	Out = Relations.Rels[17];		//	Obstacle avoidance
	Mx = Mappings.Mats[8];			//
	rules[8]->Build(RelA, RelB, Out, Mx);
//---------------------------------------------------------------
//	Speed restriction on direction error to target.
	RelA = Relations.Rels[5];		//	target direction error
	RelB = Relations.Rels[18];		//	vehicle speed
	Out = Relations.Rels[1];		//	Final vehicle speed
	Mx = Mappings.Mats[9];			//
	rules[9]->Build(RelA, RelB, Out, Mx);
}

int MakeInferences::Exe(Robot *ref)
{

	static float t_speed, t_Maxspeed, t_speed_final, t_steer, t_steer_pre, t_obs_avoid, t_Tfollow;
	static float t_Lwheel, t_Rwheel;
	int possibility=0;
	
//---------------------------------------------------------------
//	MUST DO A LITTLE MATH FIRST
//---------------------------------------------------------------
//	Direction error and distance to target -> Required corrective steering
	float err=0,dist=0;
//
	float Rx = ref->pos_x;
	float Ry = ref->pos_y;
	float Tx = ref->target.x;
	float Ty = ref->target.y;
//
	float dX= Rx - Tx;
	float dY= Ry - Ty;
	dist=pow(pow(dX,2)+pow(dY,2),0.5);
	if(dist>100)
		dist=100;						//LIMIT INPUT TO MATRIX
//
	float ori = ref->Orient;
//
	if(Ty<Ry)										//East
	{
		if(Tx<Rx)		
			err= atan(dY/dX)/(2*pi)+0.25;			//North //////////
		else
			err= -0.25-(-(atan(dY/dX)/(2*pi)));		//South	/////O.K.//////
	}
//
	else											//West
	{
		if(Tx<Rx)
			err= atan(dY/dX)/(2*pi)+0.25;			//North
		else
			err= -0.25-(-(atan(dY/dX)/(2*pi)));		//South//////O.K.//////
	}
//
	err -= ori;
	if(err>0.5)
		err -= 1;
	if(err<-0.5)
		err += 1;	//Maintain -0.5 -> +0.5 range
//
	err *= 100;		//convert to integer relation range -50 -> +50
//---------------------------------------------------------------
//	Direction error and distance to target -> Required corrective steering
//printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
//printf("\nTarget is at %f and distance %f",err,dist);
//
	t_Tfollow /= 2;
	float Tfollow= rules[2]->Exe(float(err),float(dist)) + t_Tfollow;
	Tfollow /= 2;
	t_Tfollow = Tfollow;
//
	if(Tfollow>50)
		Tfollow = 50;
	if(Tfollow<-50)
		Tfollow=-50;
//printf("\nT follow = %f",Tfollow); 
//---------------------------------------------------------------
//	Obstacle avoidance behaviour
	float Ldist = ref->Laz->scan(Rx,Ry,ori+0.170);	//Just a slight gap in front
	float Lave = ref->Laz->average;
	float Rdist = ref->Laz->scan(Rx,Ry,ori-0.170);	//Means different sensor readings
	float Rave = ref->Laz->average;
//printf("\n\nLdist= %f // Rdist = %f",Ldist,Rdist);
//printf("\nLaverage= %f // Raverage = %f",Lave,Rave);
	float obs_min = rules[7]->Exe(Ldist,Rdist);
	float obs_ave = rules[7]->Exe(Lave,Rave);
//
	t_obs_avoid /= 2;
	float obs_avoid = rules[8]->Exe(obs_min,obs_ave) + t_obs_avoid;
	obs_avoid /= 2;
	t_obs_avoid = obs_avoid;
//
	if(obs_avoid>50)
		obs_avoid = 50;
	if(obs_avoid<-50)
		obs_avoid=-50;
//printf("\n\tObstacle avoid = %f",obs_avoid);
//---------------------------------------------------------------
//	Pre processing Steering control, Winner takes all function
//
	t_steer_pre /= 2;
	float steer_pre = rules[0]->Exe(float(Tfollow),float(obs_avoid)) + t_steer_pre;
	steer_pre /= 2;
	t_steer_pre = steer_pre;
//
	if(steer_pre>50)
		steer_pre = 50;
	if(steer_pre<-50)
		steer_pre=-50;
//
//---------------------------------------------------------------
//	Stearing angle and obstacle presence -> Vehicle speed
//	Must calculate distance to obstacle in desired direction of travel
	float closest = ref->Laz->scan(Rx,Ry,ori);		//Max`ed in Laser
	if(!closest)
		closest=ref->Laz->MaxRange;
//
	t_Maxspeed /= 2;
	float Maxspeed = rules[5]->Exe(float(steer_pre),float(closest)) + t_Maxspeed;
	Maxspeed /= 2;
	t_Maxspeed = Maxspeed;
//
//printf("\n\nObstacle forward(%f)= %f hence Maxspeed = %f",ori,closest,Maxspeed);
//---------------------------------------------------------------
//  Reduce from maximum safe speed to slowing for destination
	t_speed /= 2;
	float speed = rules[1]->Exe(float(dist),float(Maxspeed)) + t_speed;
	speed /= 2;
	t_speed = speed;
//printf("\n\nSpeedadjusted for target = %f",speed);
//	speed = Maxspeed;
//---------------------------------------------------------------
//  Reduce maximum speed to slow to corner for target
//printf("\nSpeed = %f",speed);
	t_speed_final /= 2;
	float speed_final = rules[9]->Exe(float(err),float(speed)) + t_speed_final;	speed_final /= 2;
	t_speed_final = speed_final;
//printf(" err = %f final speed = %f",err,speed_final);
//printf("\n\nSpeedadjusted for target = %f",speed);
//	speed = Maxspeed;
//---------------------------------------------------------------
	static int FRUST = 0;
	static int pre_FRUST=0;
	float steer;
//printf("\nsteer_pre=%f speed=%f dist=%f closest=%f pre_FRUST= %d and FRUST=%d",float(steer_pre),float(speed),float(dist),float(closest),pre_FRUST,FRUST);

	if((steer_pre>-5) && (steer_pre<5) && (!FRUST) && (speed>-5) && (speed<5) && (dist*3>closest) && (closest<15))
	{
		pre_FRUST++;
		if(pre_FRUST>=10)
		{
			pre_FRUST = 0;
			FRUST = 10;
			possibility = -1;
		}
	}
	else
	{
		steer = steer_pre;
	}
//
//	Steering control, Final ( target track + obs_avoid^2)
//
	if(FRUST)
	{
//printf("Ignoring target due to Frustration");
		t_steer /= 2;
		steer = rules[0]->Exe(float(0),float(obs_avoid)) + t_steer;
		steer /= 2;
		t_steer = steer;
	//
		if(steer>50)
			steer = 50;
		if(steer<-50)
			steer=-50;
//
		FRUST--;
	}
//printf("\n\nTarget follow = %f, Obsacle avoid = %f",Tfollow,obs_avoid);
//printf("\n\tStearing is = %f",steer);	
//---------------------------------------------------------------	
//	Vehicle speed and stearing angle -> Left wheel speed
	t_Lwheel /= 2;
	t_Lwheel += rules[3]->Exe(float(steer),float(speed_final));
	t_Lwheel /= 2;
//---------------------------------------------------------------
//	Vehicle speed and stearing angle -> Right wheel speed
	t_Rwheel /= 2;
	t_Rwheel += rules[4]->Exe(float(steer),float(speed_final)); //+=!!!
	t_Rwheel /= 2;
//printf("\n\nLeft wheel = %f // Right wheel = %f",Lwheel,Rwheel);
//
// Copy wheel speeds to visable variables
	Lwheel = t_Lwheel;
	Rwheel = t_Rwheel;
//getch();
//---------------------------------------------------------------
	return(possibility);
}

MakeInferences::~MakeInferences()
{

}
