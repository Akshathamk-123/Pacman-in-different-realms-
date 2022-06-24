#include<stdio.h>           //standard input and output
#include<stdlib.h>          //contains exit() function
#include<dos.h>             //producing sound, date and time functions; contains sound(), nosound(),delay();
#include<conio.h>           //getch(),textcolor()
#include<graphics.h>        //includes c grphics
#include<math.h>            //includes maths functions
char ch, sc[10];                //ch=getch();   sc is an array of score
int maxx, maxy, gridx, gridy;   //Maximum x and y coordinate for current graphics mode and driver
                                //gridx and gridy are variables
int gd=DETECT, gm;      // gm is Graphics mode which is a computer display mode that generates image using pixels.
                        // DETECT is a macro defined in "graphics.h" header file
 
int score, rep=0, death, dir, dark=0, t=300;    //rep is to start new game; t is the speed of level in time(milli seconds)
int map[20][19];        //function for the outlook of themes
int x=16, y=6, x1=7, y1=8, x2=11, y2=8, x3= 7, y3=10, dir=0, st=120, end=60, sfish=210, efish=150, sjfish=190, ejfish=10;
    //x,y is for pacman position
    //x1,y1 is for ghost1 position
    //x2,y2 is for ghost2
    //x3,y3 is for  ghost3
    //st is the start angle(slice())-> pacman
    //end is endangle(slice())-> pacman
    //sfish, efish,sjfish,ejfish --> angles respectively
    //dir is the direction of the pacman moves
int tx2, ty2, tx3, ty3, r3;         //P speed of the ghosts
char c;
float offset, octave[7]={130.81,146.83,164.81,174.61,196,220,246.94};
int g;

void kill_ocean();//kill will remain the same for all of them 
void kill_space();//kill will remain the same for all of them 
void kill_forest();//kill will remain the same for all of them 

int returning_function(char choice)
{
	if(choice=='1')
		return 1;
	else if(choice=='2')
		return 2;
	else 
		return 3;
}
void first_page()//FIRST PAGE
{
    int i, n;
    initgraph(&gd, &gm, "C:\\TURBOC3\\BGI");
    maxx=getmaxx();
    maxy=getmaxy();
    setcolor(YELLOW);       //sets boundary colour
    setfillstyle(SOLID_FILL, YELLOW);       //inside filling
    //setfillstyle(int pattern,int colour)
    sector(maxx/2, maxy/2-50, 330, 30, 20, 20);     //shape
    /*void sector(int x, int y, int s_angle, int e_angle, int x_radius, int y_radius);
 
    where,
    (x, y) is center of the sector. (s_angle, e_angle) are starting and ending angles.
    (x_radius, y_radius) are x and y radius of sector.
    */
    setcolor(WHITE);
    outtextxy(maxx/2-25, maxy/2, "Pacman");
    outtextxy(maxx/2-84, maxy-50, "Press any key to start");
    /*
    void outtextxy(int x, int y, char *string);
 
        where, x, y are coordinates of the point and, third argument contains the address of string to be displayed.
     This is used for text in the output screen
    */
    for(i=0;i<30;i++)
    {
        n=random(6);
        sound(octave[n]*4);
        delay(50);
    }
    nosound();
    getch();
    sound(octave[6]*2);
    delay(15);
    nosound();
    cleardevice();          //clears the screen
    outtextxy(maxx/2-42, 120, "CHOOSE ANY REALM");
    
	setcolor(LIGHTBLUE);
    setfillstyle(SOLID_FILL,CYAN);
    outtextxy(maxx/2-130, 180, "[1] Ocean");
    setcolor(MAGENTA);
    outtextxy(maxx/2-130, 200, "[2] Space");
	setcolor(LIGHTGREEN);
    setfillstyle(SOLID_FILL,LIGHTGREEN);
    outtextxy(maxx/2-130, 220, "[3] Forest");
    setcolor(WHITE);
    outtextxy(maxx/2-116, 300, "Use WASD to change directions");
	c=getch();
	g=returning_function(c);
	if(c=='1')
    {
		setcolor(LIGHTBLUE);
        outtextxy(maxx/2-58, 280, "LEVEL: OCEAN");
    }
    else if(c=='2')
    {
		setcolor(MAGENTA);
        outtextxy(maxx/2-64, 280, "LEVEL: SPACE");
    }
    else if(c=='3')
    {
		setcolor(LIGHTGREEN);
		setcolor(LIGHTGREEN);
        outtextxy(maxx/2-58, 280, "LEVEL: FOREST");
    }
	outtextxy(maxx/2-96, maxy-50, "Press any key to continue");
    getch();
    sound(octave[6]*2);
    delay(15);// delays by 15 ms
    nosound();
    
	/*if(c=='1')
        OCEAN();
    else if(c=='2')
        //main function call
    else if(c=='3')
	{ } //main function call
 */
} 

void initialize_ocean()
{
    int i, j;
	//if statement required 
    int m[20][19]={
{2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,1,1,3,0,1,1,1,3,1,1,1,1,1,0,1,1,1,0},
{0,1,0,1,0,1,1,0,1,1,1,0,1,1,0,1,0,1,0},
{0,1,0,1,1,2,0,0,0,2,0,0,0,2,1,1,0,1,0},
{0,1,1,1,0,2,2,2,2,2,2,2,2,2,0,1,1,1,0},
{0,1,1,1,0,2,2,2,0,0,0,2,2,2,0,1,1,1,0},
{0,1,0,0,0,0,0,2,2,3,2,2,0,0,0,0,0,1,0},
{0,1,1,3,0,2,2,2,0,0,0,2,2,3,0,1,1,1,0},
{0,3,1,1,1,2,0,2,2,2,2,2,0,2,1,1,1,1,0},
{0,1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,1,0},
{0,1,1,1,1,1,2,2,3,0,2,2,2,2,3,1,1,1,0},
{0,1,1,0,1,0,2,0,0,0,0,0,2,2,0,1,1,3,0},
{0,1,0,0,1,0,2,2,2,2,2,2,2,2,0,1,0,0,0},
{0,1,3,0,1,0,0,1,0,2,0,0,1,1,0,3,1,1,0},
{0,1,1,1,1,1,1,1,0,1,3,0,0,1,1,1,1,1,0},
{0,1,0,0,1,1,1,3,1,1,1,1,1,1,1,0,0,1,0},
{0,1,1,1,1,0,1,0,0,0,0,0,1,0,1,1,1,1,0},
{0,1,1,0,3,0,1,1,1,3,1,1,1,0,4,0,1,1,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}};
       
       
    for (i=0; i<20; i++)
        for (j=0; j<19; j++)
            map[i][j]= m[i][j];
   
    score= 0, death=0, dark=0;
    initgraph(&gd, &gm, "C:\\TURBOC3\\BGI");
    /* initgraph(int graphic driver,int graphic mode,char path)
    initgraph initializes the graphics system by loading a graphics driver from disk*/
 
    maxx=getmaxx();
    //gives the maximum X coordinate for the current graphics mode and driver
   
    maxy=getmaxy();
    //gives the maximum Y coordinate for the current graphics mode and driver
   
    setviewport(0,0,maxx,maxy,1);// restricts drawing in a particular area
    gridx=ceil(maxx/19);//ceil function  rounds up the nearest integer
    gridy=ceil(maxy/20);
    offset=(maxx%19)/2;// extremely small <1
}

void initialize_space()
{
    int i, j;
    int m[20][19]={//            //
{2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2},
{0,0,0,3,6,0,0,3,6,0,0,3,0,6,0,3,0,6,0},
{0,7,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,3},
{0,1,3,0,1,3,1,0,0,0,3,0,1,0,1,3,5,1,6},   // 5  coordinates are 3 row 16th col
{3,1,1,1,1,0,1,1,1,0,1,1,1,3,1,1,1,1,3},
{6,3,0,3,1,0,6,0,2,0,2,0,3,0,1,0,0,0,0},
{0,1,1,1,1,0,2,2,2,2,2,2,2,0,1,1,1,1,3},
{3,1,0,0,1,3,2,0,3,5,0,3,2,0,1,0,3,1,0},   // 5  coordinates are 7 row 9th col
{0,1,1,1,1,0,2,2,2,2,2,2,2,0,1,1,1,1,0},
{3,1,0,0,1,0,2,3,2,0,2,0,2,0,1,0,0,1,3},
{0,1,1,1,1,3,2,2,2,2,2,2,2,3,1,1,1,1,0},
{6,0,0,6,1,3,2,0,3,0,3,0,2,6,1,3,0,3,0},
{0,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,6},
{3,1,6,0,1,6,3,0,1,3,1,6,3,0,1,3,6,1,0},
{0,1,1,0,1,1,1,1,1,2,1,1,1,1,1,0,1,1,0},
{6,0,1,0,1,0,1,0,3,0,0,3,1,0,1,0,1,0,6},
{0,1,1,1,1,0,1,1,1,0,1,1,1,0,1,1,1,1,0},
{3,1,0,3,0,3,0,0,1,0,1,0,3,0,0,3,0,1,3},
{0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,6},
{6,3,0,6,3,0,6,0,3,0,6,0,6,0,3,6,6,0,0}};
    for (i=0; i<20; i++)
        for (j=0; j<19; j++)
            map[i][j]= m[i][j];
   
    score= 0, death=0, dark=0;
    initgraph(&gd, &gm, "C:\\TURBOC3\\BGI");
    maxx=getmaxx();
    maxy=getmaxy();
    setviewport(0,0,maxx,maxy,1);
    gridx=ceil(maxx/19);
    gridy=ceil(maxy/20);
    offset=(maxx%19)/2;
}

void initialize_forest()
{
    int i, j;
    int m[20][19]={
{2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,3,1,1,1,1,1,1,3,1,1,1,1,1,1,1,1,4,0},
{0,1,0,0,1,0,0,0,0,0,0,0,0,1,1,0,3,1,0},
{0,1,0,3,1,1,1,3,0,1,1,1,1,1,1,0,0,1,0},
{0,1,0,3,1,0,0,1,1,1,1,3,1,1,1,0,1,1,0},
{0,1,0,0,1,1,1,2,0,0,0,0,0,3,1,0,3,1,0},
{0,1,1,1,1,3,0,2,2,2,2,2,2,2,2,0,0,1,0},
{0,1,3,1,1,1,0,2,2,2,0,0,2,0,1,0,3,1,0},
{0,1,1,1,0,0,0,0,0,2,2,2,2,0,1,1,1,1,0},
{0,1,1,1,1,1,1,2,2,2,0,2,2,0,0,0,1,1,0},
{0,1,0,0,3,1,1,2,2,2,0,0,2,0,3,1,1,1,0},
{0,1,3,0,1,0,1,2,2,0,2,0,2,0,1,0,1,1,0},
{0,1,1,0,1,0,1,0,0,0,2,2,2,1,1,0,3,1,0},
{0,1,1,0,1,0,1,1,1,0,0,0,0,1,0,0,0,1,0},
{0,1,1,1,1,0,2,1,1,1,3,1,1,1,1,1,1,1,0},
{0,1,3,0,1,0,0,0,0,1,1,1,0,3,1,1,1,1,0},
{0,1,0,0,1,1,1,3,1,1,0,0,0,0,0,0,1,1,0},
{0,1,1,3,1,1,1,1,1,3,1,1,1,1,3,1,1,1,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}
	};
    for (i=0; i<20; i++)
        for (j=0; j<19; j++)
            map[i][j]= m[i][j];
   
    score= 0, death=0, dark=0;
    initgraph(&gd, &gm, "C:\\TURBOC3\\BGI");
    maxx=getmaxx();
    maxy=getmaxy();
    setviewport(0,0,maxx,maxy,1);
    gridx=ceil(maxx/19);
    gridy=ceil(maxy/20);
    offset=(maxx%19)/2;
}



void initpos_ocean()
{
    x=16, y=6, x1=7, y1=8, x2=11, y2=8, x3= 7, y3=10, dir=0, st=120, end=60, sfish=210, efish=150, sjfish=190, ejfish=10;
    tx2=14, ty2=14, r3=0;
    //x,y is for pacman
    //x1,y1 is for red ghost
    //x2,y2 is for blue ghost
    //x3,y3 is for green ghost
    //st is the start angle(slice())-> smiley
    //end is endangle(slice())-> smiley
    //dir is the direction of the smiley moves
}

void initpos_forest()
{
    x=16, y=6, x1=7, y1=8, x2=11, y2=8, x3= 7, y3=10, dir=0, st=120, end=60, sfish=210, efish=150, sjfish=190, ejfish=10;
    tx2=14, ty2=14, r3=0;
    //x,y is for pacman
    //x1,y1 is for red ghost
    //x2,y2 is for blue ghost
    //x3,y3 is for green ghost
    //st is the start angle(slice())-> smiley
    //end is endangle(slice())-> smiley
    //dir is the direction of the smiley moves
}

void initpos_space()
{
    x=9, y=14, x1=7, y1=8, x2=11, y2=8, x3= 7, y3=10, dir=0, st=120, end=60, sfish=210, efish=150, sjfish=190, ejfish=10;
    tx2=14, ty2=14, r3=0;
    //x,y is for pacman
    //x1,y1 is for red ghost
    //x2,y2 is for blue ghost
    //x3,y3 is for green ghost
    //st is the start angle(slice())-> smiley
    //end is endangle(slice())-> smiley
    //dir is the direction of the smiley moves
}
 
void start_ocean()//FIRST PAGE
{	
    int i, n;
    cleardevice();          //clears the screen
	setcolor(YELLOW);
    outtextxy(maxx/2-55, 120, "INSTRUCTIONS");
    outtextxy(maxx/2-90, 180, "Your aim is to collect");
	outtextxy(maxx/2-180, 200, "fishes(orange triangles) carrying 1 point");
    outtextxy(maxx/2-180, 220, "Jelly fish(purple cloud) carrying 2 points");
    outtextxy(maxx/2-180, 240, "pearl(white pearl) carrying 50 points");
	outtextxy(maxx/2-120, 300, "But be careful! You must avoid");
    outtextxy(maxx/2-123, 320, "the sharks trying to catch you!");
    outtextxy(maxx/2-116, 360, "Use WASD to change directions");
    outtextxy(maxx/2-96, maxy-50, "Press any key to continue");
    getch();
    sound(octave[6]*2);
    delay(15);// delays by 15 ms
    nosound();//stop the system's sound
}



void start_space()
{
    int i, n;
	cleardevice();
	setcolor(YELLOW);
    outtextxy(maxx/2-55, 120, "INSTRUCTIONS");
    outtextxy(maxx/2-90, 180, "Your aim is to collect");
	outtextxy(maxx/2-150, 200, "stars(white circles) carrying 1 point");
    outtextxy(maxx/2-150, 220, "galaxy (purple) carrying 50 points");
    outtextxy(maxx/2-150, 240, "The purple circle is for teleporting");
	outtextxy(maxx/2-120, 300, "But be careful! You must avoid");
    outtextxy(maxx/2-123, 320, "the sharks trying to catch you!");
    outtextxy(maxx/2-116, 360, "Use WASD to change directions");
    outtextxy(maxx/2-96, maxy-50, "Press any key to continue");
    getch();
    sound(octave[6]*2);
    delay(15);
    nosound();      
}


void start_forest()
{
	int i, n;
	cleardevice();
	setcolor(YELLOW);
	outtextxy(maxx/2-55, 120, "INSTRUCTIONS");
    outtextxy(maxx/2-90, 180, "Your aim is to collect");
	outtextxy(maxx/2-150, 200, "fruits(red circles) carrying 1 point");
    outtextxy(maxx/2-150, 220, "dry wood(brown bar) carrying 2 points");
    outtextxy(maxx/2-150, 240, "tresure(brown box) carrying 50 points");
	outtextxy(maxx/2-120, 300, "But be careful! You must avoid");
    outtextxy(maxx/2-123, 320, "the sharks trying to catch you!");
    outtextxy(maxx/2-116, 360, "Use WASD to change directions");
    outtextxy(maxx/2-96, maxy-50, "Press any key to continue");
	getch();
	sound(octave[6]*2);
	delay(15);// delays by 15 ms 
	nosound();//stop the system's sound
}

 
void dif()  // choosing the speed
{
    char c='M';
    while(c!=' ')       // space takes to the next page
    {
    setcolor(YELLOW);
    cleardevice();
    outtextxy(maxx/2-70, 100, "LEVEL THE WAY YOU WANT");
    outtextxy(maxx/2-180, 130, "Choose the speed at which the game progresses");
    outtextxy(maxx/2-42, 170, "[S] Slow");
    outtextxy(maxx/2-42, 190, "[M] Medium");
    outtextxy(maxx/2-42, 210, "[F] Fast");
    outtextxy(maxx/2-42, 240, "[X] Xtreme");
    if(c=='s'||c=='S')
    {
        outtextxy(maxx/2-58, 280, "Current: Slow");
    }
    else if(c=='m'||c=='M')
    {
        outtextxy(maxx/2-64, 280, "Current: Medium");
    }
    else if(c=='f'||c=='F')
    {
        outtextxy(maxx/2-58, 280, "Current: Fast");
    }
    else if(c=='x'||c=='X')
    {
        outtextxy(maxx/2-64, 280, "The Xtreme Limited Edition");
    }
    outtextxy(maxx/2-96, maxy-50, "Press Spacebar to continue");
    c=getch();
    sound(octave[6]*2);
    delay(15);
    nosound();
    if(c=='s'||c=='S')
        t=400;                  //time(milli seconds)
    else if(c=='m'||c=='M')
        t=300;
    else if(c=='f'||c=='F')
        t=200;
    else if(c=='x'||c=='X')
        dark=1;
    }
}
 
void slice(int p, int q, int sangle, int eangle, int rad)       //pacman
    {
    int i,j;
    if(sangle>eangle){
    circle(p,q,rad);                    //circle(int x, int y, radius)
    floodfill(p,q,YELLOW);              //floodfill(int x, int y, int border_color) for the shape
    setcolor(CYAN);                     //set the current drawing color to the new color.  (background)
    setfillstyle(SOLID_FILL,CYAN);      //setfillstyle(int pattern, int color)    (background)
    pieslice(p,q,eangle,sangle,rad);    //pieslice(int x, int y, int s_angle, int e_angle, int r);
    setcolor(YELLOW);
    }
    else{
    setfillstyle(SOLID_FILL, YELLOW);
    sector(p,q,sangle,eangle,rad,rad);
    }
    }
 
void show_ocean()//DEFINING DESIGN IN THE GAME PLATFORM
{
    int i,j;
    clrscr();
    cleardevice();
    for (i=0; i<20; i++)
    {   for (j=0; j<19; j++)
        {
		switch(map[i][j])
        {
			case 0://Blue WALL
			setfillstyle(SOLID_FILL, BLUE);
			bar(j*gridx+1+offset, i*gridy+1, (j+1)*gridx+offset, (i+1)*gridy);
			//bar(int left_from the left screen, int top_from the top of the screen , int right_ from the left screen , int bottom_from the bottom of the screen)
			break;
 
			case 1:
			setcolor(BROWN);//points(fish)
			setfillstyle(SOLID_FILL, CYAN);
			bar(j*gridx+1+offset, i*gridy+1, (j+1)*gridx+offset, (i+1)*gridy);
			setfillstyle(SOLID_FILL, BROWN);
			sector(j*gridx+gridx/2+offset, i*gridy+gridy/2,sfish,efish,7, 7);
			//sector(int x, int y, int s_angle, int e_angle, int x_radius, int y_radius);
			//circle(j*gridx+gridx/2+offset, i*gridy+gridy/2, 3);
			floodfill(j*gridx+gridx/2+offset, i*gridy+gridy/2,BROWN);
			break;
 
			case 2://space
			setfillstyle(SOLID_FILL, CYAN);
			bar(j*gridx+1+offset, i*gridy+1, (j+1)*gridx+offset, (i+1)*gridy);
			break;
 
			case 3://points(jelly fish)
			setcolor(LIGHTBLUE);
			setfillstyle(SOLID_FILL,CYAN);
			bar(j*gridx+1+offset, i*gridy+1, (j+1)*gridx+offset, (i+1)*gridy);
			setfillstyle(SOLID_FILL, LIGHTBLUE);
			sector(j*gridx+gridx/2+offset, i*gridy+gridy/2,sjfish,ejfish,5, 5);
			//circle(j*gridx+gridx/2+offset, i*gridy+gridy/2, 4);
			floodfill(j*gridx+gridx/2+offset, i*gridy+gridy/2,LIGHTBLUE);
			break;
 
			case 4://points(pearl)
			setcolor(WHITE);
			setfillstyle(SOLID_FILL, CYAN);
			bar(j*gridx+1+offset, i*gridy+1, (j+1)*gridx+offset, (i+1)*gridy);
			setfillstyle(SOLID_FILL, WHITE);
			//setcolor(WHITE);
			circle(j*gridx+gridx/2+offset, i*gridy+gridy/2, 4);
			floodfill(j*gridx+gridx/2+offset, i*gridy+gridy/2,WHITE);
			break;
			/*setcolor(WHITE);//points
			circle(j*gridx+gridx/2+offset, i*gridy+gridy/2, 5);
			//bar(j*gridx+1+offset, i*gridy+1, (j+1)*gridx+offset, (i+1)*gridy);*/
        }
		}
    }
    //pacman
    setfillstyle(SOLID_FILL, YELLOW);
    setcolor(YELLOW);
    slice(gridx*x+gridx/2+offset, gridy*y+gridy/2, st, end, gridy/2-2);//x,y is for pacman initial position
    /* GHOST 1*/
    setcolor(RED);
    setfillstyle(SOLID_FILL, RED);
    circle(gridx*x1+gridx/2+offset, gridy*y1+gridy/2, gridy/2-2);
    //circle(int x,int y, int radius) x and y are coordinates of the center.
    floodfill(gridx*x1+gridx/2+offset, gridy*y1+gridy/2, RED);
   
    /*GHOST 2*/
    setcolor(RED);
    setfillstyle(SOLID_FILL, RED);
    circle(gridx*x2+gridx/2+offset, gridy*y2+gridy/2, gridy/2-2);
    floodfill(gridx*x2+gridx/2+offset, gridy*y2+gridy/2, RED);
   
    /*GHOST 3 */
    setcolor(RED);
    setfillstyle(SOLID_FILL, RED);
    circle(gridx*x3+gridx/2+offset, gridy*y3+gridy/2, gridy/2-2);
    floodfill(gridx*x3+gridx/2+offset, gridy*y3+gridy/2, RED);
    printf("\t\t\t\tPress Esc to Pause\t\tLives left: %2d", (3-death)); //Instruction when the game is paused
}
 
void show_space()//DEFINING DESIGN IN THE GAME PLATFORM
{
	 int i,j;
    clrscr();
    cleardevice();
    for (i=0; i<20; i++)
    {   for (j=0; j<19; j++)
        {
        switch(map[i][j])
        {
        case 0: // planet 1
        //setfillstyle(SOLID_FILL, CYAN);
        //bar(j*gridx+1+offset, i*gridy+1, (j+1)*gridx+offset, (i+1)*gridy);
        setcolor(CYAN);
        setfillstyle(SOLID_FILL, CYAN);
        circle(j*gridx+gridx/2+offset, i*gridy+gridy/2, 12);
        floodfill(j*gridx+gridx/2+offset, i*gridy+gridy/2, CYAN);
        break;
        case 1:
        setcolor(WHITE);
        circle(j*gridx+gridx/2+offset, i*gridy+gridy/2, 2);
        //floodfill(j*gridx+gridx/2+offset, i*gridy+gridy/2,WHITE)
        break;
        case 2:
        setfillstyle(SOLID_FILL, BLACK);
        bar(j*gridx+1+offset, i*gridy+1, (j+1)*gridx+offset, (i+1)*gridy);
        break;
        case 3: // planet 2
        //setfillstyle(SOLID_FILL, LIGHTMAGENTA);
        //bar(j*gridx+1+offset, i*gridy+1, (j+1)*gridx+offset, (i+1)*gridy);
        setcolor(LIGHTMAGENTA);
        setfillstyle(SOLID_FILL, LIGHTMAGENTA);
        circle(j*gridx+gridx/2+offset, i*gridy+gridy/2, 12);
        floodfill(j*gridx+gridx/2+offset, i*gridy+gridy/2, LIGHTMAGENTA);
        break;
        case 5:
        //setcolor(GREEN);
        setfillstyle(SOLID_FILL, GREEN);
        circle(j*gridx+gridx/2+offset, i*gridy+gridy/2, 11);
        //setfillstyle(SOLID_FILL, GREEN);
        break;
        case 6: // planet 3
        setcolor(LIGHTGRAY);
        setfillstyle(SOLID_FILL, LIGHTGRAY);
        circle(j*gridx+gridx/2+offset, i*gridy+gridy/2, 12);
        floodfill(j*gridx+gridx/2+offset, i*gridy+gridy/2, LIGHTGRAY);
        break;
        case 7: // galaxy
        setcolor(LIGHTBLUE);
        setfillstyle(SOLID_FILL, LIGHTBLUE);
        ellipse(j*gridx+gridx/2+offset, i*gridy+gridy/2,0,360,11,7);
        floodfill(j*gridx+gridx/2+offset, i*gridy+gridy/2, LIGHTBLUE);
        break;
 
        }
    }
    }
    setfillstyle(SOLID_FILL, YELLOW);
    setcolor(YELLOW);
    slice(gridx*x+gridx/2+offset, gridy*y+gridy/2, st, end, gridy/2-2); // userdefined function slice()
    setcolor(GREEN);
    setfillstyle(SOLID_FILL, GREEN);// it fills the circle inside
    circle(gridx*x1+gridx/2+offset, gridy*y1+gridy/2, gridy/2-2);
    floodfill(gridx*x1+gridx/2+offset, gridy*y1+gridy/2, GREEN); // this fills the border color
    setcolor(GREEN);
    setfillstyle(SOLID_FILL, GREEN);//
    circle(gridx*x2+gridx/2+offset, gridy*y2+gridy/2, gridy/2-2);
    floodfill(gridx*x2+gridx/2+offset, gridy*y2+gridy/2, GREEN);
    setcolor(GREEN);
    setfillstyle(SOLID_FILL, GREEN);//
    circle(gridx*x3+gridx/2+offset, gridy*y3+gridy/2, gridy/2-2);
    floodfill(gridx*x3+gridx/2+offset, gridy*y3+gridy/2, GREEN);
    printf("\t\t\t\tPress Esc to Pause\t\tLives left: %2d", (3-death));
}

void show_forest()//DEFINING DESIGN IN THE GAME PLATFORM 
{
	int i,j;
	clrscr();
	cleardevice();
	for (i=0; i<20; i++)
	{	for (j=0; j<19; j++)
		{
		switch(map[i][j])
		{
		case 0://GREEN WALL
		setfillstyle(SOLID_FILL, GREEN);
		bar(j*gridx+1+offset, i*gridy+1, (j+1)*gridx+offset, (i+1)*gridy);
		//bar(int left_from the left screen, int top_from the top of the screen , int right_ from the left screen , int bottom_from the bottom of the screen)
		break;
		case 1:
		setcolor(RED);//points
		setfillstyle(SOLID_FILL, LIGHTGREEN);
		bar(j*gridx+1+offset, i*gridy+1, (j+1)*gridx+offset, (i+1)*gridy);
		setfillstyle(SOLID_FILL, RED);
		circle(j*gridx+gridx/2+offset, i*gridy+gridy/2, 3);
		floodfill(j*gridx+gridx/2+offset, i*gridy+gridy/2,RED);
		break;
		case 2:
		setfillstyle(SOLID_FILL, LIGHTGREEN);
		bar(j*gridx+1+offset, i*gridy+1, (j+1)*gridx+offset, (i+1)*gridy);
		break;
		case 3://check
		setcolor(BROWN);
		setfillstyle(SOLID_FILL,LIGHTGREEN);
		bar(j*gridx+1+offset, i*gridy+1, (j+1)*gridx+offset, (i+1)*gridy);
		setfillstyle(SOLID_FILL, BROWN);
		circle(j*gridx+gridx/2+offset, i*gridy+gridy/2, 4);
		floodfill(j*gridx+gridx/2+offset, i*gridy+gridy/2,BROWN);
		case 4:
		setcolor(YELLOW);//points
		bar(j*gridx+1+offset, i*gridy+1, (j+1)*gridx+offset, (i+1)*gridy);
		}
	}
	}
	setfillstyle(SOLID_FILL, YELLOW);
	setcolor(YELLOW);
	slice(gridx*x+gridx/2+offset, gridy*y+gridy/2, st, end, gridy/2-2);//x,y is for pacman initial position 
	/* GHOST RED*/
	setcolor(LIGHTGRAY);
	setfillstyle(SOLID_FILL, LIGHTGRAY);
	circle(gridx*x1+gridx/2+offset, gridy*y1+gridy/2, gridy/2-2);
	//circle(int x,int y, int radius x and y are coordinates of the center.
	floodfill(gridx*x1+gridx/2+offset, gridy*y1+gridy/2, LIGHTGRAY);
	
	/*GHOST BLUE*/
	setcolor(LIGHTGRAY);
	setfillstyle(SOLID_FILL, LIGHTGRAY);
	circle(gridx*x2+gridx/2+offset, gridy*y2+gridy/2, gridy/2-2);
	floodfill(gridx*x2+gridx/2+offset, gridy*y2+gridy/2, LIGHTGRAY);
	
	/*GHOST GREEN */
	setcolor(LIGHTGRAY);
	setfillstyle(SOLID_FILL, LIGHTGRAY);
	circle(gridx*x3+gridx/2+offset, gridy*y3+gridy/2, gridy/2-2);
	floodfill(gridx*x3+gridx/2+offset, gridy*y3+gridy/2, LIGHTGRAY);
	printf("\t\t\t\tPress Esc to Pause\t\tLives left: %2d", (3-death)); //Instruction when the game is paused
}

void update_ocean(int l, int m)       //passing index positions of the 2d array(outlook)
{
    int i,j,r=1;
    sprintf(sc,"%d", score);        //sprintf(char *str, const char *string,...);
    //String print. Instead of printing on console, it store output on char buffer which are specified in sprintf.
    setcolor(WHITE);
    setviewport(offset,0,offset+120,gridy,1);       //setviewport(int left, int top, int right, int bottom, int clip);
        //is used to restrict drawing to a particular portion on the screen.
    clearviewport();                                //clearviewport(void);
    outtextxy(offset,5,"Score: ");      //function which displays the text or string at a specified point (x, y) on the screen.
    outtextxy(offset+60,5,sc);
    setviewport(0,0,maxx,maxy,1);
    if (dark==1)
    {
        cleardevice();
        r=2;
    }
    for (i=(m-r); i<=(m+r); i++)
    {   for (j=(l-r); j<=(l+r); j++)
        {
        switch(map[i][j])
        {
        default:
        setfillstyle(SOLID_FILL, BLUE);
        bar(j*gridx+1+offset, i*gridy+1, (j+1)*gridx+offset, (i+1)*gridy);
        break;
 
        case 1:
        setfillstyle(SOLID_FILL, CYAN);
        bar(j*gridx+1+offset, i*gridy+1, (j+1)*gridx+offset, (i+1)*gridy);
        setcolor(BROWN);
        //circle(j*gridx+gridx/2+offset, i*gridy+gridy/2, 2);
        sector(j*gridx+gridx/2+offset, i*gridy+gridy/2,sfish,efish,7, 7);
        break;
 
        case 2:
        setfillstyle(SOLID_FILL, CYAN);
        bar(j*gridx+1+offset, i*gridy+1, (j+1)*gridx+offset, (i+1)*gridy);
        break;
 
        case 3:
        setfillstyle(SOLID_FILL, CYAN);
        bar(j*gridx+1+offset, i*gridy+1, (j+1)*gridx+offset, (i+1)*gridy);
        setcolor(LIGHTBLUE);
        //setfillstyle(SOLID_FILL, LIGHTBLUE);
        //circle(j*gridx+gridx/2+offset, i*gridy+gridy/2, 2);
        sector(j*gridx+gridx/2+offset, i*gridy+gridy/2,sjfish,ejfish,5, 5);
        break;
        case 4:
        setfillstyle(SOLID_FILL, CYAN);
        //circle(j*gridx+gridx/2+offset, i*gridy+gridy/2, 4);
        bar(j*gridx+1+offset, i*gridy+1, (j+1)*gridx+offset, (i+1)*gridy);
        setcolor(WHITE);
        circle(j*gridx+gridx/2+offset, i*gridy+gridy/2, 4);
        break;
        }
    }
    }
        setfillstyle(SOLID_FILL, YELLOW);
        setcolor(YELLOW);
        slice(gridx*x+gridx/2+offset, gridy*y+gridy/2, st, end, gridy/2-2);
       
        setcolor(RED);
        setfillstyle(SOLID_FILL, RED);
        circle(gridx*x1+gridx/2+offset, gridy*y1+gridy/2, gridy/2-2);
        floodfill(gridx*x1+gridx/2+offset, gridy*y1+gridy/2, RED);
        setcolor(RED);
        setfillstyle(SOLID_FILL, RED);
        circle(gridx*x2+gridx/2+offset, gridy*y2+gridy/2, gridy/2-2);
        floodfill(gridx*x2+gridx/2+offset, gridy*y2+gridy/2, RED);
        setcolor(RED);
        setfillstyle(SOLID_FILL, RED);
        circle(gridx*x3+gridx/2+offset, gridy*y3+gridy/2, gridy/2-2);
        floodfill(gridx*x3+gridx/2+offset, gridy*y3+gridy/2, RED);
       
        setcolor(YELLOW);
}
 
void update_space(int l, int m)
{
    int i,j,r=1;
    sprintf(sc,"%d", score);
    setcolor(WHITE);
    setviewport(offset,0,offset+120,gridy,1);
    clearviewport();
    outtextxy(offset,5,"Score: ");
    outtextxy(offset+60,5,sc);
    setviewport(0,0,maxx,maxy,1);
    if (dark==1)
    {
        cleardevice();
        r=2;
    }
    for (i=(m-r); i<=(m+r); i++)
    {   for (j=(l-r); j<=(l+r); j++)
        {
        switch(map[i][j])
        {
        default:
        setfillstyle(SOLID_FILL, BLACK);
        bar(j*gridx+1+offset, i*gridy+1, (j+1)*gridx+offset, (i+1)*gridy);
        setcolor(CYAN);
        setfillstyle(SOLID_FILL, CYAN);
        circle(j*gridx+gridx/2+offset, i*gridy+gridy/2, 12);
        floodfill(j*gridx+gridx/2+offset, i*gridy+gridy/2, CYAN);
        break;
        case 1:
        setfillstyle(SOLID_FILL, BLACK);
        bar(j*gridx+1+offset, i*gridy+1, (j+1)*gridx+offset, (i+1)*gridy);
        setcolor(WHITE);
        circle(j*gridx+gridx/2+offset, i*gridy+gridy/2, 2);
        //floodfill(j*gridx+gridx/2+offset, i*gridy+gridy/2,WHITE)
        break;
        case 2:
        setfillstyle(SOLID_FILL, BLACK);
        bar(j*gridx+1+offset, i*gridy+1, (j+1)*gridx+offset, (i+1)*gridy);
        break;
        case 3:
        setfillstyle(SOLID_FILL, BLACK);
        bar(j*gridx+1+offset, i*gridy+1, (j+1)*gridx+offset, (i+1)*gridy);
        setcolor(LIGHTMAGENTA);
        setfillstyle(SOLID_FILL, LIGHTMAGENTA);
        circle(j*gridx+gridx/2+offset, i*gridy+gridy/2, 12);
        floodfill(j*gridx+gridx/2+offset, i*gridy+gridy/2, LIGHTMAGENTA);
        break;
        case 5:
        setfillstyle(SOLID_FILL, BLACK);
        bar(j*gridx+1+offset, i*gridy+1, (j+1)*gridx+offset, (i+1)*gridy);
        //setcolor(GREEN);
        setfillstyle(SOLID_FILL, GREEN);
        circle(j*gridx+gridx/2+offset, i*gridy+gridy/2, 11);
        //setfillstyle(SOLID_FILL, GREEN);
        break;
        case 6:
        setfillstyle(SOLID_FILL, BLACK);
        bar(j*gridx+1+offset, i*gridy+1, (j+1)*gridx+offset, (i+1)*gridy);
        setcolor(LIGHTGRAY);
        setfillstyle(SOLID_FILL, LIGHTGRAY);
        circle(j*gridx+gridx/2+offset, i*gridy+gridy/2, 12);
        floodfill(j*gridx+gridx/2+offset, i*gridy+gridy/2, LIGHTGRAY);
        break;
        case 7:
        setfillstyle(SOLID_FILL, BLACK);
        bar(j*gridx+1+offset, i*gridy+1, (j+1)*gridx+offset, (i+1)*gridy);
        setcolor(LIGHTBLUE);
        setfillstyle(SOLID_FILL, LIGHTBLUE);
        ellipse(j*gridx+gridx/2+offset, i*gridy+gridy/2,0,360,10,8);
        floodfill(j*gridx+gridx/2+offset, i*gridy+gridy/2, LIGHTBLUE);
        break;
        }
    }
    }
    setfillstyle(SOLID_FILL, YELLOW);
    setcolor(YELLOW);
    slice(gridx*x+gridx/2+offset, gridy*y+gridy/2, st, end, gridy/2-2); // userdefined function slice()
    setcolor(GREEN);
    setfillstyle(SOLID_FILL, GREEN);//
    circle(gridx*x1+gridx/2+offset, gridy*y1+gridy/2, gridy/2-2);
    floodfill(gridx*x1+gridx/2+offset, gridy*y1+gridy/2, GREEN);
    setcolor(GREEN);
    setfillstyle(SOLID_FILL, GREEN);//
    circle(gridx*x2+gridx/2+offset, gridy*y2+gridy/2, gridy/2-2);
    floodfill(gridx*x2+gridx/2+offset, gridy*y2+gridy/2, GREEN);
    setcolor(GREEN);
    setfillstyle(SOLID_FILL, GREEN);//
    circle(gridx*x3+gridx/2+offset, gridy*y3+gridy/2, gridy/2-2);
    floodfill(gridx*x3+gridx/2+offset, gridy*y3+gridy/2, GREEN);
       
        setcolor(YELLOW); // is for the text that appears when u pause the game if this setolor is not mentioned then the text will apper in green as default as the letest selcolor is green
}

void update_forest(int l, int m)
{
	int i,j,r=1;
	sprintf(sc,"%d", score);
	setcolor(WHITE);
	setviewport(offset,0,offset+120,gridy,1);
	clearviewport();
	outtextxy(offset,5,"Score: ");
	outtextxy(offset+60,5,sc);
	setviewport(0,0,maxx,maxy,1);
	if (dark==1)
	{
		cleardevice();
	    r=2;
	}
	for (i=(m-r); i<=(m+r); i++)
	{	for (j=(l-r); j<=(l+r); j++)
		{
		switch(map[i][j])
		{
		default:
		setfillstyle(SOLID_FILL, GREEN);
		bar(j*gridx+1+offset, i*gridy+1, (j+1)*gridx+offset, (i+1)*gridy);
		break;
		case 1:
		setfillstyle(SOLID_FILL, LIGHTGREEN);
		bar(j*gridx+1+offset, i*gridy+1, (j+1)*gridx+offset, (i+1)*gridy);
		setcolor(RED);
		circle(j*gridx+gridx/2+offset, i*gridy+gridy/2, 2);
		break;
		case 2:
		setfillstyle(SOLID_FILL, LIGHTGREEN);
		bar(j*gridx+1+offset, i*gridy+1, (j+1)*gridx+offset, (i+1)*gridy);
		break;
		case 3:
		setfillstyle(SOLID_FILL, LIGHTGREEN);
		bar(j*gridx+1+offset, i*gridy+1, (j+1)*gridx+offset, (i+1)*gridy);
		setcolor(BROWN);
		setfillstyle(SOLID_FILL,LIGHTGREEN);
		circle(j*gridx+gridx/2+offset, i*gridy+gridy/2, 2);
		case 4:
		setfillstyle(SOLID_FILL, LIGHTGREEN);
		bar(j*gridx+1+offset, i*gridy+1, (j+1)*gridx+offset, (i+1)*gridy);
		setcolor(YELLOW);
		circle(j*gridx+gridx/2+offset, i*gridy+gridy/2, 2);
		}
	}
	}
		setfillstyle(SOLID_FILL, YELLOW);
		setcolor(YELLOW);
		slice(gridx*x+gridx/2+offset, gridy*y+gridy/2, st, end, gridy/2-2);
		
		setcolor(LIGHTGRAY);
		setfillstyle(SOLID_FILL, LIGHTGRAY);
		circle(gridx*x1+gridx/2+offset, gridy*y1+gridy/2, gridy/2-2);
		floodfill(gridx*x1+gridx/2+offset, gridy*y1+gridy/2, LIGHTGRAY);
		setcolor(LIGHTGRAY);
		setfillstyle(SOLID_FILL, LIGHTGRAY);
		circle(gridx*x2+gridx/2+offset, gridy*y2+gridy/2, gridy/2-2);
		floodfill(gridx*x2+gridx/2+offset, gridy*y2+gridy/2, LIGHTGRAY);
		setcolor(LIGHTGRAY);
		setfillstyle(SOLID_FILL, LIGHTGRAY);
		circle(gridx*x3+gridx/2+offset, gridy*y3+gridy/2, gridy/2-2);
		floodfill(gridx*x3+gridx/2+offset, gridy*y3+gridy/2, LIGHTGRAY);
		
		setcolor(YELLOW);
}

void ghost1_ocean()
{
    int k, r=0;
    while(1)
    {
        if(r==2||(abs(y1-y)>=abs(x1-x)&&r==0)) // x1=7 y1=8 position of ghost 1 x=9 and y=14 is for pacman
        {                                   //abs  gives the absolute value
            if (r==2||y1>y)
            {
                if (map[y1-1][x1]!=0)
                {
                    y1=y1-1;
                    break;
                }
            }
            else if (r==2||y1<=y)
            {
                if (map[y1+1][x1]!=0)
                {
                    y1=y1+1;
                    break;
                }
            }
        }
        else
        {
            if (r==2||x1>x)
            {
                if (map[y1][x1-1]!=0)
                {
                    x1=x1-1;
                    break;
                }  
            }
            else if (r==2||x1<=x)
            {
                if (map[y1][x1+1]!=0) // not block
                {
                    x1=x1+1;
                    break;
                }
            }
        }
    r++;
    if(r>3)
        break;
    }
        if(dark==0)
        update_ocean(x1,y1);
        if (x1==x&&y1==y)
        {
            death++;
            for(k=6;k>=0;k--)
            {
                sound(octave[k]);
                delay(50);
            }
            nosound();
            delay(750);
            if(death==3)
                kill_ocean();
            else
            {
                initpos_ocean();
                show_ocean();
            }
        }
}
 
void ghost2_ocean()
{
    int k, r=0;
    while(1)
    {
    if(r==2||(abs(y2-ty2)>=abs(x2-tx2)&&r==0))
    {
        if (r==2||y2>ty2)
        {
            if (map[y2-1][x2]!=0)
            {
                y2=y2-1;
                break;
            }
        }
        else if (r==2||y2<=ty2)
        {
            if (map[y2+1][x2]!=0)
            {
                y2=y2+1;
                break;
            }
        }
    }
    else
    {
        if (r==2||x2>tx2)
        {
            if (map[y2][x2-1]!=0)
            {
                x2=x2-1;
                break;
            }
        }
        else if (r==2||x2<=tx2)
        {
            if (map[y2][x2+1]!=0)
            {
                x2=x2+1;
                break;
            }
        }
    }
    r++;
    if(r>3)
        break;
    }
        if(dark==0)
        update_ocean(x2,y2);
        if (x2==x&&y2==y)
        {
            death++;
            for(k=6;k>=0;k--)
            {
                sound(octave[k]);
                delay(50);
            }
            nosound();
            delay(750);
            if(death==3)
                kill_ocean();
            else
            {
                initpos_ocean();
                show_ocean();
            }
        }
        if (x2==tx2&&y2==ty2)
        {
            if(tx2==14&&ty2==14)
                tx2=4;
            else if(tx2==4&&ty2==14)
                ty2=2;
            else if(tx2==4&&ty2==2)
                tx2=14;
            else if(tx2==14&&ty2==2)
                ty2=14;
        }  
}
 
void ghost3_ocean()
{
    int k, r=0, f=0;
    if((abs(x3-x)<=8&&abs(y3-y)<=8)&&r3<=8&&f==0)
    {
        tx3=x;
        ty3=y;
        r3++;
        if(r3==8)
        f=1;
    }
    else
    {
        tx3=19-x;
        ty3=20-y;
        if(f==1)
            r3++;
    }
    if(r3==16)
    {
        r3=0;
        f=0;
    }
    while(1)
    {
    if(r==2||(abs(y3-ty3)>=abs(x3-tx3)&&r==0))
    {
        if (r==2||y3>ty3)
        {
            if (map[y3-1][x3]!=0)
            {
                y3=y3-1;
                break;
            }
        }
        else if (r==2||y3<=ty3)
        {
            if (map[y3+1][x3]!=0)
            {
                y3=y3+1;
                break;
            }
        }
    }
    else
    {
        if (r==2||x3>tx3)
        {
            if (map[y3][x3-1]!=0)
            {
                x3=x3-1;
                break;
            }
        }
        else if (r==2||x3<=tx3)
        {
            if (map[y3][x3+1]!=0)
            {
                x3=x3+1;
                break;
            }
        }
    }
    r++;
    if(r>3)
        break;
    }
        if(dark==0)
        update_ocean(x3,y3);
        if (x3==x&&y3==y)
        {
            death++;
            for(k=6;k>=0;k--)
            {
                sound(octave[k]);
                delay(50);
            }
            nosound();
            delay(750);
            if(death==3)
                kill_ocean();
            else
            {
                initpos_ocean();
                show_ocean();
            }
        }  
}

void ghost1_space()
{
    int k, r=0;
    while(1)
    {
    if(r==2||(abs(y1-y)>=abs(x1-x)&&r==0))
    {
        if (r==2||y1>y)
        {
            if (map[y1-1][x1]!=0 && map[y1-1][x1]!=3 && map[y1-1][x1]!=6)
            {
                y1=y1-1;
                break;
            }
        }
        else if (r==2||y1<=y)
        {
            if (map[y1+1][x1]!=0 && map[y1+1][x1]!=3 && map[y1+1][x1]!=6)
            {
                y1=y1+1;
                break;
            }
        }
    }
    else
    {
        if (r==2||x1>x)
        {
            if (map[y1][x1-1]!=0 && map[y1][x1-1]!=3 && map[y1][x1-1]!=6)
            {
                x1=x1-1;
                break;
            }
        }
        else if (r==2||x1<=x)
        {
            if (map[y1][x1+1]!=0 && map[y1][x1+1]!=3 && map[y1][x1+1]!=6)
            {
                x1=x1+1;
                break;
            }
        }
    }
    r++;
    if(r>3)
        break;
    }
        if(dark==0)
        update_space(x1,y1);
        if (x1==x&&y1==y)
        {
            death++;
            for(k=6;k>=0;k--)
            {
                sound(octave[k]);
                delay(50);
            }
            nosound();
            delay(750);
            if(death==3)
                kill_space();
            else
            {
                initpos_space();
                show_space();
            }
        }
}
 
void ghost2_space()
{
    int k, r=0;
    while(1)
    {
    if(r==2||(abs(y2-ty2)>=abs(x2-tx2)&&r==0))
    {
        if (r==2||y2>ty2)
        {
            if (map[y2-1][x2]!=0 && map[y2-1][x2]!=3 && map[y2-1][x2]!=6)
            {
                y2=y2-1;
                break;
            }
        }
        else if (r==2||y2<=ty2)
        {
            if (map[y2+1][x2]!=0 && map[y2+1][x2]!=3 && map[y2+1][x2]!=6)
            {
                y2=y2+1;
                break;
            }
        }
    }
    else
    {
        if (r==2||x2>tx2)
        {
            if (map[y2][x2-1]!=0 && map[y2][x2-1]!=3 && map[y2][x2-1]!=6)
            {
                x2=x2-1;
                break;
            }
        }
        else if (r==2||x2<=tx2)
        {
            if (map[y2][x2+1]!=0 && map[y2][x2+1]!=3 && map[y2][x2+1]!=6)
            {
                x2=x2+1;
                break;
            }
        }
    }
    r++;
    if(r>3)
        break;
    }
        if(dark==0)
        update_space(x2,y2);
        if (x2==x&&y2==y)
        {
            death++;
            for(k=6;k>=0;k--)
            {
                sound(octave[k]);
                delay(50);
            }
            nosound();
            delay(750);
            if(death==3)
                kill_space();
            else
            {
                initpos_space();
                show_space();
            }
        }
        if (x2==tx2&&y2==ty2)
        {
            if(tx2==14&&ty2==14)
                tx2=4;
            else if(tx2==4&&ty2==14)
                ty2=2;
            else if(tx2==4&&ty2==2)
                tx2=14;
            else if(tx2==14&&ty2==2)
                ty2=14;
        }  
}
 
void ghost3_space()
{
    int k, r=0, f=0;
    if((abs(x3-x)<=8&&abs(y3-y)<=8)&&r3<=8&&f==0)
    {
        tx3=x;
        ty3=y;
        r3++;
        if(r3==8)
        f=1;
    }
    else
    {
        tx3=19-x;
        ty3=20-y;
        if(f==1)
            r3++;
    }
    if(r3==16)
    {
        r3=0;
        f=0;
    }
    while(1)
    {
    if(r==2||(abs(y3-ty3)>=abs(x3-tx3)&&r==0))
    {
        if (r==2||y3>ty3)
        {
            if (map[y3-1][x3]!=0 && map[y3-1][x3]!=3 && map[y3-1][x3]!=6)
            {
                y3=y3-1;
                break;
            }
        }
        else if (r==2||y3<=ty3)
        {
            if (map[y3+1][x3]!=0 && map[y3+1][x3]!=3 && map[y3+1][x3]!=6)
            {
                y3=y3+1;
                break;
            }
        }
    }
    else
    {
        if (r==2||x3>tx3)
        {
            if (map[y3][x3-1]!=0 && map[y3][x3-1]!=3 && map[y3][x3-1]!=6)
            {
                x3=x3-1;
                break;
            }
        }
        else if (r==2||x3<=tx3)
        {
            if (map[y3][x3+1]!=0 && map[y3][x3+1]!=3 && map[y3][x3+1]!=6)
            {
                x3=x3+1;
                break;
            }
        }
    }
    r++;
    if(r>3)
        break;
    }
        if(dark==0)
        update_space(x3,y3);
        if (x3==x&&y3==y)
        {
            death++;
            for(k=6;k>=0;k--)
            {
                sound(octave[k]);
                delay(50);
            }
            nosound();
            delay(750);
            if(death==3)
                kill_space();
            else
            {
                initpos_space();
                show_space();
            }
        }  
}

void ghost1_forest()
{
	int k, r=0;
	while(1)
	{
		if(r==2||(abs(y1-y)>=abs(x1-x)&&r==0)) // x1=7 y1=8	position of ghost 1 x=9 and y=14 is for pacman
		{
			if (r==2||y1>y)
			{
				if (map[y1-1][x1]!=0)
				{
					y1=y1-1;
					break;
				}
			}
			else if (r==2||y1<=y)
			{
				if (map[y1+1][x1]!=0)
				{
					y1=y1+1;
					break;
				}
			}
		}
		else 
		{
			if (r==2||x1>x)
			{
				if (map[y1][x1-1]!=0)
				{
					x1=x1-1;
					break;
				}	
			}
			else if (r==2||x1<=x)
			{
				if (map[y1][x1+1]!=0) // not block
				{
					x1=x1+1;
					break;
				}
			}
		}
	r++;
	if(r>3)
		break;
	}
		if(dark==0)
		update_forest(x1,y1);
		if (x1==x&&y1==y)
		{
			death++;
			for(k=6;k>=0;k--)
			{
				sound(octave[k]);
				delay(50);
			}
			nosound();
			delay(750);
			if(death==3)
				kill_forest();
			else
			{
				initpos_forest();
				show_forest();
			}
		}
}

void ghost2_forest()
{
	int k, r=0;
	while(1)
	{
	if(r==2||(abs(y2-ty2)>=abs(x2-tx2)&&r==0))
	{
		if (r==2||y2>ty2)
		{
			if (map[y2-1][x2]!=0)
			{
				y2=y2-1;
				break;
			}
		}
		else if (r==2||y2<=ty2)
		{
			if (map[y2+1][x2]!=0)
			{
				y2=y2+1;
				break;
			}
		}
	}
	else 
	{
		if (r==2||x2>tx2)
		{
			if (map[y2][x2-1]!=0)
			{
				x2=x2-1;
				break;
			}
		}
		else if (r==2||x2<=tx2)
		{
			if (map[y2][x2+1]!=0)
			{
				x2=x2+1;
				break;
			}
		}
	}
	r++;
	if(r>3)
		break;
	}
		if(dark==0)
		update_forest(x2,y2);
		if (x2==x&&y2==y)
		{
			death++;
			for(k=6;k>=0;k--)
			{
				sound(octave[k]);
				delay(50);
			}
			nosound();
			delay(750);
			if(death==3)
				kill_forest();
			else
			{
				initpos_forest();
				show_forest();
			}
		}
		if (x2==tx2&&y2==ty2)
		{
			if(tx2==14&&ty2==14)
				tx2=4;
			else if(tx2==4&&ty2==14)
				ty2=2;
			else if(tx2==4&&ty2==2)
				tx2=14;
			else if(tx2==14&&ty2==2)
				ty2=14;
		}	
}

void ghost3_forest()
{
	int k, r=0, f=0;
	if((abs(x3-x)<=8&&abs(y3-y)<=8)&&r3<=8&&f==0)
	{
		tx3=x;
		ty3=y;
		r3++;
		if(r3==8)
		f=1;
	}
	else
	{
		tx3=19-x;
		ty3=20-y;
		if(f==1)
			r3++;
	}
	if(r3==16)
	{
		r3=0;
		f=0;
	}
	while(1)
	{
	if(r==2||(abs(y3-ty3)>=abs(x3-tx3)&&r==0))
	{
		if (r==2||y3>ty3)
		{
			if (map[y3-1][x3]!=0)
			{
				y3=y3-1;
				break;
			}
		}
		else if (r==2||y3<=ty3)
		{
			if (map[y3+1][x3]!=0)
			{
				y3=y3+1;
				break;
			}
		}
	}
	else 
	{
		if (r==2||x3>tx3)
		{
			if (map[y3][x3-1]!=0)
			{
				x3=x3-1;
				break;
			}
		}
		else if (r==2||x3<=tx3)
		{
			if (map[y3][x3+1]!=0)
			{
				x3=x3+1;
				break;
			}
		}
	}
	r++;
	if(r>3)
		break;
	}
		if(dark==0)
		update_forest(x3,y3);
		if (x3==x&&y3==y)
		{
			death++;
			for(k=6;k>=0;k--)
			{
				sound(octave[k]);
				delay(50);
			}
			nosound();
			delay(750);
			if(death==3)
				kill_forest();
			else
			{
				initpos_forest();
				show_forest();
			}
		}	
}

void main()
{
   
    //The direction function is defined inside main
    char c;
    int k;
	first_page();
	if(g==1)//ocean
		{ 
			initialize_ocean();
			initpos_ocean();
			if (rep==0)
				
			start_ocean();
			dif();
			show_ocean();
			delay(500);
			while(1)
			{
				delay(t);
				while(kbhit())//KEYBOARD HIT
				//THIS WHILE LOOP IS FOR DIRECTION GUIDED BY (W,A,S,D)
				{  
					c= getch();
					if (c=='w'||c=='W')
					{
						dir=0;//UPP        
					}
					else if (c=='s'||c=='S')
					{
						dir=1;//DOWN
					}
					else if (c=='a'||c=='A')
					{
						dir=2;//LEFT
					}
					else if (c=='d'||c=='D')
					{
						dir=3;//RIGHT
					}
					else if (c==27)//27 is the ASCII value of Esc key
					{
						sound(octave[6]*2);
						delay(15);
						nosound();
						kill_ocean();//else block in kill()
					}
					else if (c=='~')//cheat code for score to be 149 and +1 point will yield win!!
							score=149;
				}
				if (dir==0)
				{
					if (map[y-1][x]==1)
					{
						y--;
						map[y][x]=2;// replace point with empty space
						sound(octave[6]*2);
						delay(50);
						nosound();
						score++;
					}
					else if (map[y-1][x]==3)
					{
						y--;
						map[y][x]=2;// replace point with empty space
						sound(octave[6]*2);
						delay(50);
						nosound();
						score+=2;
					}
					else if (map[y-1][x]==2)
					{
						y--;
					}
					else if (map[y-1][x]==4)
					{
						y--;
						map[y][x]=2;// replace point with empty space
						sound(octave[6]*2);
						delay(50);
						nosound();
						score+=50;
					}
					st=120, end=60;
       
				}
				else if (dir==1)
				{
					if (map[y+1][x]==1)
					{
						y++;
						map[y][x]=2;
						sound(octave[6]*2);
						delay(50);
						nosound();
						score++;
					}
					else if (map[y+1][x]==3)
					{
						y++;
						map[y][x]=2;
						sound(octave[6]*2);
						delay(50);
						nosound();
						score+=2;
					}
					else if (map[y+1][x]==4)
					{
						y++;
						map[y][x]=2;
						sound(octave[6]*2);
						delay(50);
						nosound();
						score+=50;
					}
					else if (map[y+1][x]==2)
					{
						y++;
					}
					st=300, end=240;
				}
				else if (dir==2)
				{
					if (map[y][x-1]==1)
					{
						x--;
						map[y][x]=2;
						sound(octave[6]*2);
						delay(50);
						nosound();
						score++;
					}
					else if (map[y][x-1]==3)
					{
						x--;
						map[y][x]=2;
						sound(octave[6]*2);
						delay(50);
						nosound();
						score+=2;
					}
					else if (map[y][x-1]==4)
					{
						x--;
						map[y][x]=2;
						sound(octave[6]*2);
						delay(50);
						nosound();
						score+=50;
					}
					else if (map[y][x-1]==2)
					{
						x--;
					}
					st=210, end=150;
				}
				else if (dir==3)
				{
					if (map[y][x+1]==1)
					{
						x++;
						map[y][x]=2;
						sound(octave[6]*2);
						delay(50);
						nosound();
						score++;
					}
					else if (map[y][x+1]==3)
					{
						x++;
						map[y][x]=2;
						sound(octave[6]*2);
						delay(50);
						nosound();
						score+=2;
					}
					else if (map[y][x+1]==4)
					{
						x++;
						map[y][x]=2;
						sound(octave[6]*2);
						delay(50);
						nosound();
						score+=50;
					}
					else if (map[y][x+1]==2)
					{
						x++;
					}
					st=30, end=330;
				}
				if((x==x1&&y==y1)||(x==x2&&y==y2)||(x==x3&&y==y3))
				{
					death++;
					for(k=6;k>=0;k--)
					{
						sound(octave[k]);
						delay(50);
					}
					nosound();
					delay(750);
					if(death==3)
					{
						kill_ocean();
					}
					else
					{
						initpos_ocean();
						show_ocean();
					}
				}  
				ghost1_ocean();
				ghost2_ocean();
				ghost3_ocean();
				update_ocean(x,y);
				if (score==150)
				{
					delay(500);
					kill_ocean();
				}
			}
		}
	
	
	
	
	else if(g==2)//space
	{
		initialize_space();
			initpos_space();
			if (rep==0)
			start_space();
			dif();
			show_space();
			delay(500);
			while(1)
			{
				delay(t);
				while(kbhit())//KEYBOARD HIT
				//THIS WHILE LOOP IS FOR DIRECTION GUIDED BY (W,A,S,D)
				{  
					c= getch();
					if (c=='w'||c=='W')
					{
						dir=0;//UPP        
					}
					else if (c=='s'||c=='S')
					{
						dir=1;//DOWN
					}
					else if (c=='a'||c=='A')
					{
						dir=2;//LEFT
					}
					else if (c=='d'||c=='D')
					{
						dir=3;//RIGHT
					}
					else if (c==27)//27 is the ASCII value of Esc key
					{
						sound(octave[6]*2);
						delay(15);
						nosound();
						kill_space();//else block in kill()
					}
					else if (c=='~')//cheat code for score to be 149 and +1 point will yield win!!
							score=149;
				}
				if (dir==0)
        {
            if (map[y-1][x]==1)
            {
                y--;
                map[y][x]=2;
                sound(octave[6]*2);
                delay(50);
                nosound();
                score++;
            }
            else if (map[y-1][x]==2)
            {
                y--;
            }
            else if (map[y-1][x]==5 && x==16 && (y-1)==3)
            {
                //map[y][x]=2;
                y--;
                map[y-1][x]=2;
                x=9;
                y=7;
                //y--;
                //map[y][x]=2;
            }
            else if (map[y-1][x]==5 && x==9 && (y-1)==7)
            {
                //map[y][x]=2;
                y--;
                map[y-1][x]=2;
                x=16;
                y=3;
               // y--;
                //map[y][x]=2;
            }
            else if(map[y-1][x]==7)
            {
                y--;
                map[y][x]=2;
                sound(octave[6]*2);
                delay(50);
                nosound();
                score+=50;
            }
            st=120, end=60;
        }
        else if (dir==1)
        {
            if (map[y+1][x]==1)
            {
                y++;
                map[y][x]=2;
                sound(octave[6]*2);
                delay(50);
                nosound();
                score++;
            }
            else if (map[y+1][x]==2)
            {
                y++;
            }
            else if (map[y+1][x]==5 && x==16 && (y+1)==3)
            {
                //map[y][x]=2;
                y++;
                map[y+1][x]=2;
                x=9;
                y=7;
               // y++;
                //map[y][x]=2;
            }
            else if (map[y+1][x]==5 && x==9 && (y+1)==7)
            {
                //map[y][x]=2;
                y++;
                map[y+1][x]=2;
                x=16;
                y=3;
                //y++;
                //map[y][x]=2;
            }
            else if(map[y+1][x]==7)
            {
                y++;
                map[y][x]=2;
                sound(octave[6]*2);
                delay(50);
                nosound();
                score+=50;
            }
            st=300, end=240;
        }
        else if (dir==2)
        {
            if (map[y][x-1]==1)
            {
                x--;
                map[y][x]=2;
                sound(octave[6]*2);
                delay(50);
                nosound();
                score++;
            }
            else if (map[y][x-1]==2)
            {
                x--;
            }
            else if (map[y][x-1]==5 && (x-1)==16 && y==3)
            {
                //map[y][x]=2;
                x--;
                map[y][x-1]=2;
                x=9;
                y=7;
               // x--;
                //map[y][x]=2;
            }
            else if (map[y][x-1]==5 && (x-1)==9 && y==7)
            {
                //map[y][x]=2;
                x--;
                map[y][x-1]=2;
                x=16;
                y=3;
               // x--;
                //map[y][x]=2;
            }
            else if(map[y][x-1]==7)
            {
                x--;
                map[y][x]=2;
                sound(octave[6]*2);
                delay(50);
                nosound();
                score+=50;
            }
            st=210, end=150;
        }
        else if (dir==3)
        {
            if (map[y][x+1]==1)
            {
                x++;
                map[y][x]=2;
                sound(octave[6]*2);
                delay(50);
                nosound();
                score++;
            }
            else if (map[y][x+1]==2)
            {
                x++;
            }
            else if (map[y][x+1]==5 && (x+1)==16 && y==3)
            {
                //map[y][x]=2;
                x++;
                map[y][x+1]=2;
                x=9;
                y=7;
                //x++;
                //map[y][x]=2;
            }
            else if (map[y][x+1]==5 && (x+1)==9 && y==7)
            {
                //map[y][x]=2;
                x++;
                map[y][x+1]=2;
                x=16;
                y=3;
                //x++;
                //map[y][x]=2;
            }
            else if(map[y][x+1]==7)
            {
                x++;
                map[y][x]=2;
                sound(octave[6]*2);
                delay(50);
                nosound();
                score+=50;
            }
            st=30, end=330;
        }
        if((x==x1&&y==y1)||(x==x2&&y==y2)||(x==x3&&y==y3))
        {
            death++;
            for(k=6;k>=0;k--)
            {
                sound(octave[k]);
                delay(50);
            }
            nosound();
            delay(750);
            if(death==3)
                kill_space();
            else
            {
                initpos_space();
                show_space();
            }
        }  
        ghost1_space();
        ghost2_space();
        ghost3_space();
        update_space(x,y);
        if (score==150)
        {
            delay(500);
            kill_space();
        }
    
	}
	}
	
		
		
		
		
		
		
		
		
	else//forest
	{
		initialize_forest();
	initpos_forest();
	if (rep==0)
		start_forest();
	dif();
	show_forest();
	delay(500);
	while(1)
	{
	delay(t);
	while(kbhit())//KEYBOARD HIT
	//THIS WHILE LOOP IS FOR DIRECTION GUIDED BY (W,A,S,D)
	{	
		c= getch();
		if (c=='w'||c=='W')
		{
			dir=0;//UPP			
		}
		else if (c=='s'||c=='S')
		{
			dir=1;//DOWN
		}
		else if (c=='a'||c=='A')
		{
			dir=2;//LEFT
		}
		else if (c=='d'||c=='D')
		{
			dir=3;//RIGHT
		}
		else if (c==27)//27 is the ASCII value of Esc key
		{
			sound(octave[6]*2);
			delay(15);
			nosound();
			kill_forest();//else block in kill()
		}
		else if (c=='~')//cheat code for score to be 149 and 1 point will yeild win!!
			score=149;
	}
	if (dir==0)
		{
			if (map[y-1][x]==1)
			{
				y--;
				map[y][x]=2;// replace point with empty space
				sound(octave[6]*2);
				delay(50);
				nosound();
				score++;
			}
			else if (map[y-1][x]==3)
			{
				y--;
				map[y][x]=2;// replace point with empty space
				sound(octave[6]*2);
				delay(50);
				nosound();
				score+=2;
			}
			else if (map[y-1][x]==2)
			{
				y--;
			}
			else if (map[y-1][x]==4)
			{
				y--;
				map[y][x]=2;// replace point with empty space
				sound(octave[6]*2);
				delay(50);
				nosound();
				score+=50;
			}
			st=120, end=60;
		
		}
		else if (dir==1)
		{
			if (map[y+1][x]==1)
			{
				y++;
				map[y][x]=2;
				sound(octave[6]*2);
				delay(50);
				nosound();
				score++;
			}
			else if (map[y+1][x]==3)
			{
				y++;
				map[y][x]=2;
				sound(octave[6]*2);
				delay(50);
				nosound();
				score+=2;
			}
			else if (map[y+1][x]==4)
			{
				y++;
				map[y][x]=2;
				sound(octave[6]*2);
				delay(50);
				nosound();
				score+=50;
			}
			else if (map[y+1][x]==2)
			{
				y++;
			}
			st=300, end=240;
		}
		else if (dir==2)
		{
			if (map[y][x-1]==1)
			{
				x--;
				map[y][x]=2;
				sound(octave[6]*2);
				delay(50);
				nosound();
				score++;
			}
			else if (map[y][x-1]==3)
			{
				x--;
				map[y][x]=2;
				sound(octave[6]*2);
				delay(50);
				nosound();
				score+=2;
			}
			else if (map[y][x-1]==4)
			{
				x--;
				map[y][x]=2;
				sound(octave[6]*2);
				delay(50);
				nosound();
				score+=50;
			}
			else if (map[y][x-1]==2)
			{
				x--;
			}
			st=210, end=150;
		}
		else if (dir==3)
		{
			if (map[y][x+1]==1)
			{
				x++;
				map[y][x]=2;
				sound(octave[6]*2);
				delay(50);
				nosound();
				score++;
			}
			else if (map[y][x+1]==3)
			{
				x++;
				map[y][x]=2;
				sound(octave[6]*2);
				delay(50);
				nosound();
				score+=2;
			}
			else if (map[y][x+1]==4)
			{
				x++;
				map[y][x]=2;
				sound(octave[6]*2);
				delay(50);
				nosound();
				score+=50;
			}
			else if (map[y][x+1]==2)
			{
				x++;
			}
			st=30, end=330;
		}
		if((x==x1&&y==y1)||(x==x2&&y==y2)||(x==x3&&y==y3))
		{
			death++;
			for(k=6;k>=0;k--)
			{
				sound(octave[k]);
				delay(50);
			}
			nosound();
			delay(750);
			if(death==3)
				kill_forest();
			else
			{
				initpos_forest();
				show_forest();
			}
		}	
		ghost1_forest();
		ghost2_forest();
		ghost3_forest();
		update_forest(x,y);
		if (score==150)
		{
			delay(500);
			kill_forest();
		}
	}
	
	}
    
}
 
void kill_ocean()
{
    clrscr();
    cleardevice();
    if (score==150)
    {
        outtextxy(maxx/2-40, maxy/2-50, "YOU WIN!");
        outtextxy(maxx/2-180, maxy-50, "(Press Spacebar to play again, Esc to exit)");
    }
    else if (death==3)
    {
        outtextxy(maxx/2-46, maxy/2-50, "GAME OVER!");
        outtextxy(maxx/2-190, maxy-50, "(Press Spacebar to start new game, Esc to exit)");
        sprintf(sc, "%d", score);
        outtextxy(maxx/2-40, maxy/2-20,"Score: ");
        outtextxy(maxx/2+15, maxy/2-20,sc);
    }
    else
    {
        outtextxy(maxx/2-46, maxy/2-50, "GAME PAUSED");
        outtextxy(maxx/2-240, maxy-50, "(Press P to resume, Spacebar to start new game, Esc to exit)");
        sprintf(sc, "%d", score);
        outtextxy(maxx/2-40, maxy/2-20,"Score: ");
        outtextxy(maxx/2+15, maxy/2-20,sc);
    }
    delay(750);
    while(1)
    {   ch=getch();
        if (ch==' ')
        {
            rep=1;          //repetition of the game(to start new game)
            main();
        }
        else if (ch==27)        //27 is the ASCII value of esc; ends the game
        {
            clrscr();
            exit(0);
        }
        else if (ch=='p'||ch=='P')          //resume the game
        {
            show_ocean();
            break;
        }
    }
}


void kill_space()
{
    clrscr();
    cleardevice();
    if (score==150)
    {
        outtextxy(maxx/2-40, maxy/2-50, "YOU WIN!");
        outtextxy(maxx/2-180, maxy-50, "(Press Spacebar to play again, Esc to exit)");
    }
    else if (death==3)
    {
        outtextxy(maxx/2-46, maxy/2-50, "GAME OVER!");
        outtextxy(maxx/2-190, maxy-50, "(Press Spacebar to start new game, Esc to exit)");
        sprintf(sc, "%d", score);
        outtextxy(maxx/2-40, maxy/2-20,"Score: ");
        outtextxy(maxx/2+15, maxy/2-20,sc);
    }
    else
    {
        outtextxy(maxx/2-46, maxy/2-50, "GAME PAUSED");
        outtextxy(maxx/2-240, maxy-50, "(Press P to resume, Spacebar to start new game, Esc to exit)");
        sprintf(sc, "%d", score);
        outtextxy(maxx/2-40, maxy/2-20,"Score: ");
        outtextxy(maxx/2+15, maxy/2-20,sc);
    }
    delay(750);
    while(1)
    {   ch=getch();
        if (ch==' ')
        {
            rep=1;          //repetition of the game(to start new game)
            main();
        }
        else if (ch==27)        //27 is the ASCII value of esc; ends the game
        {
            clrscr();
            exit(0);
        }
        else if (ch=='p'||ch=='P')          //resume the game
        {
            show_space();
            break;
        }
    }
}


void kill_forest()
{
    clrscr();
    cleardevice();
    if (score==150)
    {
        outtextxy(maxx/2-40, maxy/2-50, "YOU WIN!");
        outtextxy(maxx/2-180, maxy-50, "(Press Spacebar to play again, Esc to exit)");
    }
    else if (death==3)
    {
        outtextxy(maxx/2-46, maxy/2-50, "GAME OVER!");
        outtextxy(maxx/2-190, maxy-50, "(Press Spacebar to start new game, Esc to exit)");
        sprintf(sc, "%d", score);
        outtextxy(maxx/2-40, maxy/2-20,"Score: ");
        outtextxy(maxx/2+15, maxy/2-20,sc);
    }
    else
    {
        outtextxy(maxx/2-46, maxy/2-50, "GAME PAUSED");
        outtextxy(maxx/2-240, maxy-50, "(Press P to resume, Spacebar to start new game, Esc to exit)");
        sprintf(sc, "%d", score);
        outtextxy(maxx/2-40, maxy/2-20,"Score: ");
        outtextxy(maxx/2+15, maxy/2-20,sc);
    }
    delay(750);
    while(1)
    {   ch=getch();
        if (ch==' ')
        {
            rep=1;          //repetition of the game(to start new game)
            main();
        }
        else if (ch==27)        //27 is the ASCII value of esc; ends the game
        {
            clrscr();
            exit(0);
        }
        else if (ch=='p'||ch=='P')          //resume the game
        {
            show_forest();
            break;
        }
    }
}



