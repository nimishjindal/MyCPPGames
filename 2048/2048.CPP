#include<iostream.h>
#include<fstream.h>
#include<conio.h>
#include<graphics.h>
#include<dos.h>
#include<iomanip.h>
#include<process.h>
#include<stdlib.h>
void display(int a);
int board[4][4]={{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0}},score=0,colour;
int checkmove();
void calcscore(int a);
int checkspace();
void move(char choice);
int gencolor(int a);
void display(int c=0);
void gencell();
int menu();
int inst();

void main()
{
	window(1,1,getmaxx(),getmaxy());
	textbackground(0);
	int gd=DETECT,gm,x,y,temp=0,i=0;
	x=50;
	y=8;
	ifstream scorein;
	ofstream scoreout;
	initgraph(&gd,&gm,"c:\\TURBOC3\\bgi");
	setcolor(6);
	settextstyle(1,0,7);
	outtextxy(210,5,"2048++");
	textbackground(15);
	textcolor(0);
	i=menu();
	if(i==1)
	{
		gencell();
		char choice;
		textbackground(15);
		textcolor(0);
		gotoxy(x,y++);
		y++;
		cout<<"ENTER MOVE";
		gotoxy(x,y++);
		cout<<"'a' for LEFT";
		gotoxy(x,y++);
		cout<<"'w' for UP";
		gotoxy(x,y++);
		cout<<"'s' for DOWN";
		gotoxy(x,y++);
		cout<<"'d' for RIGHT";
		gotoxy(x,y++);
		cout<<"anything for EXIT";
		scorein.open("scores.dat",ios::in);
		scorein.seekg(0);
		scorein>>temp;
		scorein.close();
		do
		{
			if(checkspace()==1)
				gencell();
			if((checkmove()==0)&&(checkspace==0))
				goto exit;
			display();
			if(score>temp)
			{
				temp=score;
				scoreout.open("scores.dat",ios::out);
				scoreout.seekp(0);
				scoreout<<temp;
				scoreout.close();
			}
			scorein.open("scores.dat",ios::in);
			scorein.seekg(0);
			scorein>>temp;
			scorein.close();
			gotoxy(x,y+3);
			cout<<"Score "<<score;
			gotoxy(x,y+2);
			cout<<"High  Score "<<temp;

			repeat:
			choice=getch();
			if((choice!='w')&&(choice!='a')&&(choice!='s')&&(choice!='d'))
			{
				gotoxy(x,y+5);
				cout<<"sure you wanna EXIT?";
				gotoxy(x,y+6);
				cout<<"(Press 'y' for YES) ";
				choice=getch();
				if(choice=='y')
					goto exit;
				else
					gotoxy(x,y+5);
					clreol();
					gotoxy(x,y+6);
					clreol();
					goto repeat;
			}
			move(choice);
			display();
			delay(200);
		}while((checkspace()!=0)||(checkmove()!=0));
		exit:
		gotoxy(x,y+7);
		cout<<"GAME OVER !!";
	}
	else if(i==3)
		exit(0);
	getch();
	closegraph();
}
int checkmove()
{
	for(int i=0;i<4;i++)
		for(int j=0;j<3;j++)
			if(board[i][j]!=0)
				if(board[i][j]==board[i][j+1])
					return 1;
	for(i=0;i<3;i++)
		for(j=0;j<4;j++)
			if(board[i+1][j]==board[i][j])
					return 1;
	return 0;
}
void calcscore(int a)
{
	score+=a;
}
int checkspace()
{
	for(int i=0;i<4;i++)
		for(int j=0;j<4;j++)
			if(board[i][j]==0)
				return 1;
	return 0;
}
void move(char choice)
{
	int pos=0,check=0;
	if((choice=='s')||(choice=='S'))
	{
		for(int j=0;j<4;j++)
			for(int i=3;i>=0;i--)
				if(board[i][j]!=0)
				{
					pos=i;
					while((board[pos+1][j]==0)&&(pos<3))
					{
						board[pos+1][j]=board[pos][j];
						board[pos++][j]=0;
						display(1);
					}

					if((board[pos][j]==board[pos+1][j])&&(pos<3)&&(check!=1))
					{
						board[pos][j]=0;
						board[pos+1][j]*=2;
						calcscore(board[pos+1][j]);
						check=1;
						display(1);
					}
					else
						check=0;
				}
	}
	else if((choice=='w')||(choice=='W'))
	{
		for(int j=0;j<4;j++)
			for(int i=0;i<4;i++)
				if(board[i][j]!=0)
				{
					pos=i;
					while((board[pos-1][j]==0)&&(pos>0))
					{
						board[pos-1][j]=board[pos][j];
						board[pos--][j]=0;
						display(1);
					}
					if((board[pos][j]==board[pos-1][j])&&(pos>0)&&(check!=1))
					{
						board[pos][j]=0;
						board[pos-1][j]*=2;
						calcscore(board[pos-1][j]);
						check=1;
						display(1);
					}
					else
						check=0;
				}
	}
	else if((choice=='a')||(choice=='A'))
	{
		for(int i=0;i<4;i++)
			for(int j=0;j<4;j++)
				if(board[i][j]!=0)
				{
					pos=j;
					while((pos>0)&&(board[i][pos-1]==0))
					{
						board[i][pos-1]=board[i][pos];
						board[i][pos--]=0;
						display(1);
					}
					if((board[i][pos]==board[i][pos-1])&&(pos>0)&&(check!=1))
					{
						board[i][pos]=0;
						board[i][pos-1]*=2;
						calcscore(board[i][pos-1]);
						check=1;
						display(1);
					}
					else
						check=0;
				}
	}
	else if((choice=='d')||(choice=='D'))
	{
		for(int i=0;i<4;i++)
			for(int j=3;j>=0;j--)
				if(board[i][j]!=0)
				{
					pos=j;
					while((board[i][pos+1]==0)&&(pos<3))
					{
						board[i][pos+1]=board[i][pos];
						board[i][pos++]=0;
						display(1);
					}
					if((board[i][pos+1]==board[i][pos])&&(pos<3)&&(check!=1))
					{
						board[i][pos]=0;
						board[i][pos+1]*=2;
						calcscore(board[i][pos+1]);
						check=1;
						display(1);
					}
					else
						check=0;
				}
	}
}
int gencolor(int a)
{
	int i=1,num=a;
	if(a==0)
		return 0;
	else if(a==128)
		return 4;
	else if(a==512)
		return 3;
	for(i=8;num>2;num/=2,i++);
	return i;
}
void display(int c)
{
	char num[4];
	int a,b;
	a=getmaxx()/8-20;
	b=(getmaxy()/8);
	for(int i=0;i<4;i++)
	{
		for(int j=0;j<4;j++)
		{
			setcolor(7);
			rectangle((2+j)*a,(2+i)*b,(3+j)*a,(3+i)*b);
			colour=gencolor(board[i][j]);
			setfillstyle(1,colour);
			floodfill(((2+j)*a)+1,(((2+i)*b)+1),7);
			if(board[i][j]!=0)
			{
				setcolor(0);
				itoa(board[i][j],num,10);
				settextstyle(0,0,2);
				if(board[i][j]>10 && board[i][j]<99)
					outtextxy((2+j)*a+19,(2+i)*b+25,num);
				else if(board[i][j]>99)
					outtextxy((2+j)*a+5,(2+i)*b+25,num);
				else
					outtextxy((2+j)*a+25,(2+i)*b+25,num);
			}

		}
	}
		if(c==1)
			delay(20);
}
void gencell()
{
	srand(time(NULL));
	int i,j,number,creatable[]={2,4};
	char choice;
	do
	{
		i=rand()%4;
		j=rand()%4;
	}while(board[i][j]!=0);
	board[i][j]=creatable[rand()%2];
}
int menu()
{
	int a,x=35,y=11;
	gotoxy(x,y++);
	cout<<"1.New Game";
	gotoxy(x,y++);
	cout<<"2.Instructions";
	gotoxy(x,y++);
	cout<<"3.Exit ";
	a=getch();
	a-='0';
	clreol();
	gotoxy(x,y--);
	gotoxy(x,y--);
	clreol();
	gotoxy(x,y--);
	clreol();
	gotoxy(x,y--);
	clreol();
	gotoxy(x,y--);
	clreol();
	if(a==2)
		a=inst();
	return a;
}

int inst()
{
	int i=0;
	int y=10;
	gotoxy(28,8);
	cout<<" 2048++ - How to play? \n";
	gotoxy(1,10);
	cout<<"The objective of the game is to get the number 2048 by adding tiles of same \nnumber";
	cout<<"\nYou will have a grid of 16 tiles. Two numbers will be generated at the begining:2 or 4. ";
	cout<<"\nMove up or down, left or right trying to join two equal numbers. ";
	cout<<"\nWhen two equal numbers are in touch, they will add up.";
	cout<<"\nIf there are no free tiles on our grid or no combination is possible, the game \nwill end.";
	cout<<"\nBy adding numbers, we get higher numbers and we approach to 2048, which is\nthe goal of the game.";
	cout<<"\nWant to START ? (Press 1 to START and press any key to EXIT) \n";
	i=getch();
	i-='0';
	if(i!=1)
		exit(0);
	gotoxy(28,8);
	clreol();
	gotoxy(1,y++);
	clreol();
	gotoxy(1,y++);
	clreol();
	gotoxy(1,y++);
	clreol();
	gotoxy(1,y++);
	clreol();
	gotoxy(1,y++);
	clreol();
	gotoxy(1,y++);
	clreol();
	gotoxy(1,y++);
	clreol();
	gotoxy(1,y++);
	clreol();
	gotoxy(1,y++);
	clreol();
	gotoxy(1,y++);
	clreol();
	gotoxy(1,y++);
	clreol();
	gotoxy(1,y++);
	clreol();
	gotoxy(1,y++);
	clreol();
	return i;

}
