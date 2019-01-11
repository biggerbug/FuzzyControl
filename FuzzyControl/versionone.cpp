// versionone.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "versionone.h"
#include "conio.h"

//#include "GrayMap.h"
#include "BoolMap.h"
//#include "FuzzyMap.h"

//#include "MembFunc.h"
//#include "FzyRelation.h"
//#include "InFer.h"
//#include "MakeRelations.h"
//#include "MakeMapping.h"
//#include "MakeInferences.h"
//#include "Matrix.h"

//#include "Laser.h"
#include "Robot.h"

#include "Math.h"

#include <windows.h>
#include <gl/glut.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// Behaviour constants
#define EXPLORE	0
#define TARGET	1
#define STOP	2
/*
#define SPEEDlow	0
#define	SPEEDmedium	1
#define	SPEEDhigh	2
*/
/////////////////////////////////////////////////////////////////////////////
// The one and only application object

CWinApp theApp;

using namespace std;

double pi = 3.1415926535;

// Step size in x and y directions
// (number of pixels to move each time)
GLfloat xstep = 1.0f;
GLfloat ystep = 1.0f;

// Keep track of windows changing width and height
GLfloat windowWidth;
GLfloat windowHeight;
GLfloat ACTUAL_windowWidth;
GLfloat ACTUAL_windowHeight;

BoolMap BMap;
Robot Fred(&BMap);

int old_x;	//old wall drawing position
int old_y;	// and y
bool draw;	//(1 Draw / 0 Erase) Wall
bool color;
bool Tmove;
bool Rmove;

// Called to draw scene
void RenderScene(void)
	{
	// Clear the window with current clearing color
	glClear(GL_COLOR_BUFFER_BIT);

//---------------------------------------------------------------------
   	int i,j;
	float x_div,y_div;
	x_div= windowWidth/BMap.x_size;
	y_div= windowHeight/BMap.y_size;
//---------------------------------------------------------------------
//	Draw real known boolean map
	float lev;
	//			R	 G	   B
	glColor3f(0.0f, 0.0f, 0.0f);
	for(i=0;i<BMap.x_size;i++)
	{
		for(j=0;j<BMap.y_size;j++)
		{
			if(BMap.GetPos(i,j))
			{
				glRectf(i*x_div, j*y_div, i*x_div+x_div, j*y_div+y_div);	
			}
		}
	}
//---------------------------------------------------------------------
//	Draw Robots Gray scale Global map	
//	x_div= windowWidth/Fred.GMap.x_size;
//	y_div= windowHeight/Fred.GMap.y_size;
	for(i=0;i<Fred.GMap.x_size;i++)
	{
		for(j=0;j<Fred.GMap.y_size;j++)
		{
			if((lev=float(Fred.GMap.GetPos(i,j))/100)!=0)	//Only draw colored squares
			{
				//			R		 G	   B
				glColor3f(1.0f, 1.0f-lev, 1.0f-lev);
				glRectf(i*x_div, j*y_div, i*x_div+x_div*2/3, j*y_div+y_div*2/3);	
			}
		}
	}
//---------------------------------------------------------------------
	//Draw Fred on the map
//	x_div= windowWidth/Fred.GMap.x_size;
//	y_div= windowHeight/Fred.GMap.y_size;

	float x_= Fred.pos_x;
	float y_= Fred.pos_y;
	float o_=Fred.Orient;
	float hyp_=pow(8,0.5);	//calc hypo_moose root sum squares assuming robot width and length to be 2 units;
	
	glColor3f(1.0f, 0.0f, 0.0f);	
	glLineWidth(3.0f);
	glBegin(GL_LINE_STRIP);
		glVertex2f( x_div*( x_+(hyp_*cos(2*pi*(o_+0.125)))),y_div*( y_+(hyp_*sin(2*pi*(o_+0.125)))) );
		glVertex2f( x_div*( x_+(hyp_*cos(2*pi*(o_+0.375)))),y_div*( y_+(hyp_*sin(2*pi*(o_+0.375)))) );
		glVertex2f( x_div*( x_+(hyp_*cos(2*pi*(o_+0.625)))),y_div*( y_+(hyp_*sin(2*pi*(o_+0.625)))) );
		glVertex2f( x_div*( x_+(hyp_*cos(2*pi*(o_+0.875)))),y_div*( y_+(hyp_*sin(2*pi*(o_+0.875)))) );
		glVertex2f( x_div*( x_+(hyp_*cos(2*pi*(o_+0.125)))),y_div*( y_+(hyp_*sin(2*pi*(o_+0.125)))) );
	glEnd();
	glBegin(GL_LINE_STRIP);
		glVertex2f( x_div*( x_+(hyp_*cos(2*pi*(o_+0.625)))),y_div*( y_+(hyp_*sin(2*pi*(o_+0.625)))) );

		glVertex2f( x_div*( x_+(hyp_*cos(2*pi*(o_+0.25)))),y_div*( y_+(hyp_*sin(2*pi*(o_+0.25)))) );
		
		glVertex2f( x_div*( x_+(hyp_*cos(2*pi*(o_+0.875)))),y_div*( y_+(hyp_*sin(2*pi*(o_+0.875)))) );
	glEnd();

//	printf("Fred`s Rotation is %f of a full turn",Fred.Orient);
//---------------------------------------------------------------------
//	Draw final goal
	// Set current drawing color to green
	//		   R	 G	   B
	glColor3f(0.0f, 1.0f, 0.0f);
	glRectf((Fred.goal.x-2)*x_div,(Fred.goal.y-2)*y_div,(Fred.goal.x+2)*x_div,(Fred.goal.y+2)*y_div);
//
//	Mark goal inactive,... if it is.
	if(Fred.behave == EXPLORE)
	{
		// Set current drawing color to red
		//		   R	 G	   B
		glColor3f(1.0f, 0.0f, 0.0f);
//
		glLineWidth(3.0f);
//
		glBegin(GL_LINE_STRIP);
			glVertex2f( (Fred.goal.x-2)*x_div,(Fred.goal.y-2)*y_div );
			glVertex2f( (Fred.goal.x+2)*x_div,(Fred.goal.y+2)*y_div );
		glEnd();
		glBegin(GL_LINE_STRIP);
			glVertex2f( (Fred.goal.x+2)*x_div,(Fred.goal.y-2)*y_div );
			glVertex2f( (Fred.goal.x-2)*x_div,(Fred.goal.y+2)*y_div );
		glEnd();
	}
//---------------------------------------------------------------------
//	Draw Fuzzy Local Map
//	Clear in Green and Wall in Blue?
	int Wx,Wy;							//World coordinates
//
	glLineWidth(1.0f);
//
	float belief;
	for(i=0;i<Fred.FMap.x_size;i++)
	{
		for(j=0;j<Fred.FMap.y_size;j++)
		{
			Wx=Fred.pos_x-Fred.FMap.x_size/2+i;
			Wy=Fred.pos_y-Fred.FMap.y_size/2+j;
			//
			if(belief= float(Fred.FMap.GetClear(i,j))/100.0 )
			{
		//		printf("\nBelief=%f",belief);
				glColor3f(0.0f, belief, 0.0f);
				//
				glBegin(GL_LINE_STRIP);
					glVertex2f( x_div*(Wx-0.5) , y_div*(Wy-0.5) );
					glVertex2f( x_div*(Wx+0.5) , y_div*(Wy+0.5) );
				glEnd();
			}
			if(belief= float(Fred.FMap.GetWall(i,j))/100.0 )
			{
				glColor3f(0.0f, 0.0f, belief);
				//
				glBegin(GL_LINE_STRIP);
					glVertex2f( x_div*(Wx-0.5) , y_div*(Wy+0.5) );
					glVertex2f( x_div*(Wx+0.5) , y_div*(Wy-0.5) );
				glEnd();
			}
		}
	}
//---------------------------------------------------------------------
//	Draw Known nodes and links
//	Draws links in both directions, kinda a waist of processor.
	int ii,jj,x,y,x_lnk,y_lnk;
	glColor3f(0.0f, 0.0f, 1.0f);
	for(ii=0;ii<Fred.NMap->NumNodes;ii++)
	{
		x=Fred.NMap->Nodes[ii]->x_x+Fred.NMap->off_x;
		y=Fred.NMap->Nodes[ii]->y_y+Fred.NMap->off_y;
//
		for(jj=0;jj<8;jj++)
		{
			if(Fred.NMap->Nodes[ii]->DirFlag[jj]==1)
			{
//printf("\nLink exists at Node %d direction %d",ii,jj);
				x_lnk=(Fred.NMap->Nodes[ii]->link[jj])->x_x+Fred.NMap->off_x;
				y_lnk=(Fred.NMap->Nodes[ii]->link[jj])->y_y+Fred.NMap->off_y;
				glBegin(GL_LINE_STRIP);
					glVertex2f( x_div*(x) , y_div*(y) );
					glVertex2f( x_div*(x_lnk) , y_div*(y_lnk) );
				glEnd();
			}
		}
	}
// Draw last rout workings
	for(ii=0;ii<Fred.NMap->NumNodes;ii++)
	{
		x=Fred.NMap->Nodes[ii]->x_x+Fred.NMap->off_x;
		y=Fred.NMap->Nodes[ii]->y_y+Fred.NMap->off_y;
//
		for(jj=0;jj<8;jj++)
		{
			if(Fred.NMap->Nodes[ii]->routeDir == jj)
			{
				glColor3f(1.0f, 0.0f, 0.0f);
				x_lnk=(Fred.NMap->Nodes[ii]->link[jj])->x_x+Fred.NMap->off_x;
				y_lnk=(Fred.NMap->Nodes[ii]->link[jj])->y_y+Fred.NMap->off_y;
				glBegin(GL_LINE_STRIP);
					glVertex2f( x_div*(x) , y_div*(y) );
					glVertex2f( x_div*(x_lnk) , y_div*(y_lnk) );
				glEnd();
				glColor3f(0.0f, 0.0f, 1.0f);
			}
		}
		glRectf((x-1)*x_div,(y-1)*y_div,(x+1)*x_div,(y+1)*y_div);
	}	
//
	for(ii=0;ii<Fred.NMap->NumNodes;ii++)
	{
//	Mark all un-completed nodes
		if(!(Fred.NMap->Nodes[ii]->explored))
		{
			x=Fred.NMap->Nodes[ii]->x_x+Fred.NMap->off_x;
			y=Fred.NMap->Nodes[ii]->y_y+Fred.NMap->off_y;
//
			glColor3f(1.0f, 1.0f, 1.0f);	// Set to white
			glRectf((x-0.5)*x_div,(y-0.5)*y_div,(x+0.5)*x_div,(y+0.5)*y_div);
			glColor3f(0.0f, 0.0f, 1.0f);	// Set back to blue
		}
//
	}
		
//---------------------------------------------------------------------
//	Draw sub target
	// Set current drawing color to green
	//		   R	 G	   B
	glColor3f(0.0f, 1.0f, 0.0f);
	glRectf((Fred.target.x-1)*x_div,(Fred.target.y-1)*y_div,(Fred.target.x+1)*x_div,(Fred.target.y+1)*y_div);
//---------------------------------------------------------------------
//	Draw current node,  start and end for route
	x = Fred.NMap->Nodes[Fred.Cur_node]->x_x+Fred.NMap->off_x;
	y = Fred.NMap->Nodes[Fred.Cur_node]->y_y+Fred.NMap->off_y;
	// Set current drawing color to red
	//		   R	 G	   B
	glColor3f(1.0f, 0.0f, 0.0f);
	glRectf((x-1)*x_div,(y-1)*y_div,(x+1)*x_div,(y+1)*y_div);
//printf("\nCurent Node is number %d",Fred.Cur_node);
//
	x = Fred.NMap->Nodes[Fred.startAt]->x_x+Fred.NMap->off_x;
	y = Fred.NMap->Nodes[Fred.startAt]->y_y+Fred.NMap->off_y;
	// Set current drawing color to black
	//		   R	 G	   B
	glColor3f(0.0f, 0.0f, 0.0f);
	glRectf((x-1)*x_div,(y-1)*y_div,(x)*x_div,(y)*y_div);
//
	x = Fred.NMap->Nodes[Fred.endAt]->x_x+Fred.NMap->off_x;
	y = Fred.NMap->Nodes[Fred.endAt]->y_y+Fred.NMap->off_y;
	// Set current drawing color to black
	//		   R	 G	   B
	glColor3f(0.0f, 0.0f, 0.0f);
	glRectf((x)*x_div,(y)*y_div,(x+1)*x_div,(y+1)*y_div);

//---------------------------------------------------------------------
	// Flush drawing commands
    glutSwapBuffers();
//---------------------------------------------------------------------
}


// Setup the rendering state
void SetupRC(void)
{
	// Set clear color to white
	// totally pointless as whole map is covered by grid anyway.
	// But seams to be good practice.
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
}

// Called by GLUT library when the window has chanaged size
void ChangeSize(GLsizei w, GLsizei h)
{
	// Prevent a divide by zero
	if(h == 0)
		h = 1;

	// Set Viewport to window dimensions
    glViewport(0, 0, w, h);
	// And store actual new window size in pixels
	ACTUAL_windowHeight = h;
	ACTUAL_windowWidth = w;

	// Reset coordinate system
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	// Keep the square square, this time, save calculated
	// width and height for later use
	if (w <= h) 
	{
		windowHeight = 250.0f*h/w;
		windowWidth = 250.0f;
	}
    else 
	{
		windowWidth = 250.0f*w/h;
		windowHeight = 250.0f;
	}

	// Set the clipping volume
	glOrtho(0.0f, windowWidth, 0.0f, windowHeight, 1.0f, -1.0f);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}
void idle()
{
//	CAll fred`s routines
	Fred.runinfer();	//
	Fred.implement();	// Drive to wheels forward
	Fred.MakeScan();	// Perform one 360 degree panaramic scan
	Fred.updateMap();	// Update Fuzzy belief maps from scan data
	Fred.buildNodes();	//
//
    glutPostRedisplay();
//	
//	getch();
}

void Motion(int x, /* I - Mouse X position */
       int y) /* I - Mouse Y position */
{
	//	printf("\nMouseMotion (%d,%d)",x,y);
	float x_div= ACTUAL_windowWidth / float(BMap.x_size);
	float y_div= ACTUAL_windowHeight / float(BMap.y_size);
	int BM_x = int(float(x)/x_div);
	int BM_y = BMap.y_size -1- int(float(y)/y_div);
	//
	if(Rmove)
	{
		Fred.pos_x=BM_x;
		Fred.pos_y=BM_y;
		Fred.FMap.clearMap();
		Fred.Infer.Lwheel=0;
		Fred.Infer.Rwheel=0;
	}
	if(Tmove)
	{
		Fred.goal.x=BM_x;
		Fred.goal.y=BM_y;
		Fred.behave = TARGET;
		Fred.ROUTE =0;
	}
	if(draw)
	{
		BMap.drawWall(old_x,old_y,BM_x,BM_y,color);
		old_x=BM_x;
		old_y=BM_y;
	}
}

void mouse(int button, int state, int x, int y)
{
	if(button==GLUT_LEFT_BUTTON && 
		state==GLUT_DOWN)
	{
		float x_div= ACTUAL_windowWidth / float(BMap.x_size);
		float y_div= ACTUAL_windowHeight / float(BMap.y_size);
		old_x = int(float(x)/x_div);
		old_y = BMap.y_size -1- int(float(y)/y_div);
		//
		if( (old_x>=Fred.pos_x-2) &&	// find if clicked on robot
			(old_x<=Fred.pos_x+2) &&
			(old_y>=Fred.pos_y-2) &&
			(old_y<=Fred.pos_y+2) )
		{// Then move target
//			printf("\nHit the Robot");
			Rmove = 1;
			draw=0;
			Tmove=0;
		}
		else if( (old_x>=Fred.goal.x-2) &&	// find if clicked on target
			(old_x<=Fred.goal.x+2) &&
			(old_y>=Fred.goal.y-2) &&
			(old_y<=Fred.goal.y+2) )
		{// Then move target
//			printf("\nHit the target");
			Tmove = 1;
			draw =0;
			Rmove =0;
		}
		else
		{//	Draw wall
			draw = 1;
			color=1;
			Tmove=0;
			Rmove=0;
		}
	}
	//
	if(button==GLUT_LEFT_BUTTON && 
		state==GLUT_UP)
	{
		Tmove = 0;
		Rmove = 0;
		draw = 0;
	}
	//
	if(button==GLUT_RIGHT_BUTTON && 
		state==GLUT_DOWN)
	{
		float x_div= ACTUAL_windowWidth / float(BMap.x_size);
		float y_div= ACTUAL_windowHeight / float(BMap.y_size);
		old_x = int(float(x)/x_div);
		old_y = BMap.y_size -1- int(float(y)/y_div);
		//
		draw =1;
		color = 0;
		Tmove=0;
		Rmove=0;
	}
}

int _tmain(int argc, TCHAR* argv[], TCHAR* envp[])
{
	int nRetCode = 0;
	// initialize MFC and print and error on failure
	if (!AfxWinInit(::GetModuleHandle(NULL), NULL, ::GetCommandLine(), 0))
	{
		// TODO: change error code to suit your needs
		cerr << _T("Fatal Error: MFC initialization failed") << endl;
		nRetCode = 1;
	}
	else
	{
		printf("\n\n\n\n\tUse the Left Mouse Button to Draw Walls");
		printf("\n\t\tRight mouse Button to Erase Walls");
		printf("\n\n\tBoth the Robot and Green Goal can be moved");
		printf("\n\t\tby Dragging with the Left Mouse Button");
		printf("\n\n\tThe Goal will Appear Crossed-Out when Inactive");
		printf("\n\t\tDrag the Goal to activate");
		printf("\n\n\n\tPress any key to start simulation\n\n");
		getch();
		//
		BMap.Build(100,100);	// must size BoolMap before calling
		Fred.Build(5,5,0.45);	// fred.Build as size used to build GrayMap
		Fred.goal.x=50;
		Fred.goal.y=50;
		Fred.target.x=50;		//Remove???
		Fred.target.y=50;		//Remove???
		//
		glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
		glutInitWindowPosition(50, 50);
		glutInitWindowSize(800, 600);
		glutCreateWindow("Fuzzy Logic Based Autonomous Vehicle Navigation. Campbell Hooper 2002");
		glutDisplayFunc(RenderScene);
		glutReshapeFunc(ChangeSize);
		glutIdleFunc(idle);
		glutMouseFunc(mouse);
		glutMotionFunc(Motion);
		//
		SetupRC();
		//
		glutMainLoop();
	}
	//
	return nRetCode;
}


