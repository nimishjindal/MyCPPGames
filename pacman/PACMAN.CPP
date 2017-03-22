#include<iostream.h>
#include<conio.h>
#include<graphics.h>
#include<dos.h>
#include<fstream.h>
int stepx,stepy,maxx,maxy;
int posx,posy,size,ch,startposyP,startposxP;
int grid[21][21],dots=0,score=0,lives=3;
void createdot(int,int);
class ghost{
	public:
	int posxg,posyg,Size;
	int startposxG,startposyG;
	void startghost(int r=11){
		posxg=startposxG;
		posyg=startposyG;
		Size=r;
	}
	void posghost();
	void createghost(int color=RED);
	void moveghost(){
		posghost();
		createghost();
	}
	void retrace(){
		if(posx>=stepx && posy>=stepy)
			if(grid[posxg/stepx][posyg/stepy]==1)
				createdot(posxg,posyg);
	}
}GhostA;
void ghost::createghost(int color) {
		int size=Size/2,x=posxg,y=posyg;
		setcolor(color);
		line(x-size,y-size/2,x-size,y+size);
		line(x+size,y-size/2,x+size,y+size);

		arc(x,y-size/2,0,180,size);

		arc(x-((2*size)/3),y+size,180,360,size/3);
		arc(x+((2*size)/3),y+size,180,360,size/3);
		arc(x,y+size,180,360,size/3);
		setfillstyle(SOLID_FILL,color);
		floodfill(x,y,color);

		setcolor(WHITE);
		setfillstyle(SOLID_FILL,WHITE);
		fillellipse(x-size/2,y-1,(size/3),(size/2));
		fillellipse(x+size/2,y-1,size/3,(size/2));

		//setcolor(BLUE);
		//setfillstyle(SOLID_FILL,BLUE);
		//circle(x-size/2,y,1);
		//circle(x+size/2,y,2);
		//floodfill(x-size/2,y,BLUE);
		//putpixel(x+size/2,y,BLUE);

}
void ghost::posghost(){
		int priorityx=0,priorityy=0;
		if(posx>posxg)
			priorityx=stepx;
		else
			priorityx=-stepx;

		if(grid[(posxg+priorityx)/stepx][posyg/stepy]!=0){
			posxg+=priorityx;
			return;
		}

		if(posy>posyg)
			priorityy=stepy;
		else
			priorityy=-stepy;

		if(grid[posxg/stepx][(posyg+priorityy)/stepy]!=0){
			posyg+=priorityy;
			return;
		}
		if(grid[(posxg-priorityx)/stepx][posyg/stepy]!=0){
			posxg-=priorityx;
			return;
		}
		if(grid[posxg/stepx][(posyg-priorityy)/stepy]!=0){
			posyg-=priorityy;
			return;
		}
}
void createdot(int x,int y){
	int color=7;
	setcolor(color);
	circle(x,y,2);
	setfillstyle(SOLID_FILL,color);
	floodfill(x,y,color);
}
void Score(){
	if(grid[posx/stepx][posy/stepy]==1){
		dots--;
		score+=5;
		gotoxy(60,11);
		cout<<score<<"  ";
		grid[posx/stepx][posy/stepy]=3;
	}
}
void createGrid(){
	ifstream gridfile;
	gridfile.open("C:\\TURBOC3\\BIN\\pacman\\grid.txt");
	int i,j;
	for(i=0;i<20;i++){
		grid[i][0]=1;
		grid[0][i]=1;
	}
	for( i=1;i<21;i++){
		for( j=1;j<21;j++){
			gridfile>>grid[j][i];
			if(grid[j][i]==3){	//pacmanpos
				startposxP=j*stepx;
				startposyP=i*stepy;
			}
			if(grid[j][i]==4){      //Ghostpos
				GhostA.startposyG=i*stepy;
				GhostA.startposxG=j*stepx;
				grid[j][i]=1;
			}
		}
	}
	for(int y=stepy;y<=maxy;y+=stepy)
		for(int x=stepx;x<=maxx;x+=stepx){
			if(grid[x/stepx][y/stepy]==1 || grid[x/stepx][y/stepy]==4){
				createdot(x,y);
				dots++;
			}
			else if(grid[x/stepx][y/stepy]==0){
				setcolor(BLUE);
				rectangle(x-(stepx/2),y-(stepy/2),x+(stepx/2),y+(stepy/2));
				//setfillstyle(SOLID_FILL,BLACK);
				//floodfill(x,y,CYAN);
			}
		}
		gotoxy(60,10);
		cout<<"Score ";
		gotoxy(60,12);
		cout<<"Lives";
		gotoxy(60,13);
		cout<<lives;

}
void pacman(int x,int y,int r,int dir=ch){
	setcolor(YELLOW);
	setfillstyle(SOLID_FILL,YELLOW);
	circle(x,y,r);
	floodfill(x,y,YELLOW);
	setcolor(BLACK);
	setfillstyle(SOLID_FILL,BLACK);
	switch(dir)
	{
		case 'd':       pieslice(x,y,0,360,r);
				setfillstyle(SOLID_FILL,YELLOW);
				pieslice(x,y,45,315,r);
				break;
		case 'w':	pieslice(x,y,46,135,r);
				break;
		case 's':	pieslice(x,y,225,315,r);
				break;
		case 'a':        pieslice(x,y,135,225,r);
				break;
		default:	break;
	}
}
void removeTrail(int x,int y,int r){
	setcolor(6);
	circle(x,y,r);
	setfillstyle(SOLID_FILL,BLACK);
	floodfill(x,y,6);
	setcolor(BLACK);
	circle(x,y,r);
}
void newlife(){
	posx=startposxP;
	posy=startposyP;
	ch='d';
	GhostA.startghost();
	pacman(posx,posy,8,'m');
	GhostA.createghost();
	gotoxy(58,15);
	cout<<"press any key to start";
	getch();
	gotoxy(58,15);
	cout<<"\t \t \t" ;
	removeTrail(GhostA.posxg,GhostA.posyg,size);
	removeTrail(posx,posy,size);
}
void setpacinc(int &incx,int &incy){
		switch(ch){
			case 'a': 	incx=-stepx;
					incy=0;
					break;
			case 'w':       incx=0;
					incy=-stepy;
					break;
			case 's':       incx=0;
					incy=stepy;
					break;
			case 'd':       incx=stepx;
					incy=0;
					break;
		}
}
void start(){
	maxx=maxy=400;

	stepx=stepy=maxx/20;

	size=(stepx/2)-2;
	createGrid();
	newlife();
	lives=3;
}
int checkcolide(){
	if(posx==GhostA.posxg && posy==GhostA.posyg){
		gotoxy(60,13);
		cout<<--lives;
		delay(1000);
		return 1;
	}
	else return 0;
}
void movepac(int incx,int incy){
	int newposx,newposy;
	newposx=posx+incx;
	newposy=posy+incy;
	if(grid[newposx/stepx][newposy/stepy]!=0){
			if(newposx>maxx)
				posx=stepx;
			else if(newposx<stepx)
				posx=maxx;
			else
				posx=newposx;

			if(newposy>maxy)
				posy=stepy;
			else if(newposy<stepy)
				posy=maxy;
			else
				posy=newposy;
	}
	pacman(posx,posy,size,ch);
}
void controler(){
	int incx,incy;
	while(dots>0 && ch!='e' && lives>0){
		nl:
		setpacinc(incx,incy);
		//ch=getch();
		while(!kbhit()){
			movepac(incx,incy);
			Score();
			if(checkcolide()){
				removeTrail(posx,posy,size);
				newlife();
				if(lives==0){
					cout<<" game over!";
					getch();
					break;
				}
				ch='d';
				goto nl;
			}
			GhostA.moveghost();
			delay(180);
			removeTrail(GhostA.posxg,GhostA.posyg,size);
			removeTrail(posx,posy,size);
			GhostA.retrace();
			if(dots==0){
				cout<<"You Win!";
				pacman(posx,posy,size);
				break;
			}
			else if(checkcolide()){
				newlife();
				if(lives==0){
					cout<<" game over!";
					getch();
					break;
				}
				ch='d';
				goto nl;
			}
		}
		ch=getch();
	}
}
void main(){
	int gm,gd=DETECT;
	initgraph(&gd,&gm,"C:\\TURBOC3\\BGI");
	start();
	//GhostA.createghost(100,100,11);
	controler();
	//pacman(stepx,posy,8,'a');
	//getch();
	closegraph();
}