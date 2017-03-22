#include<iostream.h>
#include<conio.h>
#include<stdio.h>
#include<stdlib.h>
#include<dos.h>
#include<fstream.h>
#include<string.h>

void viewhead()
	{
	for(int i=0;i<4;i++)
		{
		cout<<"\n\t\t\t\t Tic Tac Toe";
		delay(500);
		}
	}

int check(char a[4][4])
	{
	if( ( a[0][2]==a[1][1] ) && ( a[0][2]==a[2][0] ) )
		return 1;
	else if( ( a[0][0]==a[1][1] ) && ( a[0][0]==a[2][2]) )
		return 1;
	else
		for( int i=0; i<3; i++)
			if( ( a[i][0]==a[i][1] ) && ( a[i][0]==a[i][2] ) )
				return 1;
		for( i=0; i<3; ++i)
			if( ( a[0][i]==a[1][i] ) && ( a[0][i]==a[2][i] ) )
				return 1;
	return 0;
	}

void viewboard(char a[4][4])
	{

	cout<<"\n\t\t\t\t Tic Tac Toe"<<endl;
	cout<<"\n\n\n\n\n\n\n";
	cout<<endl<<"\t\t\t\t";

	for(int i=0;i<3;i++)
		{
		for(int j=0;j<3;j++)
			cout<<a[i][j]<<"     ";
		cout<<"\n\n"<<"\t\t\t\t";
		}
	}

void computerprocess(char a[4][4])
	{
	char temp,proc;
	for(int i=0; i<3; i++)
		for(int j=0; j<3; j++)
			{
			if( (a[i][j]!='X' ) && ( a[i][j]!='O' ) )
				{
				temp=a[i][j];
				a[i][j]='X';

				proc=check(a);	//check if computer can win
				if(proc!=1)
					a[i][j]=temp;

				else if(proc==1)
					goto final;
				}
			}

	for(i=0; i<3; i++)
		for(j=0; j<3; j++)
			if( ( a[i][j]!='X' ) && ( a[i][j]!='0' ) )
				{
				temp=a[i][j];
				a[i][j]='O';

				proc=check(a);	//check if player is winning
				if(proc!=1)
					a[i][j]=temp;

				else if(proc==1)
					{
					a[i][j]='X';
					goto final;
					}
			}

	temp=a[0][0];                        //fill corner 1
	a[i][j]='X';
	proc=check(a);
	if(proc!=1)
		a[i][j]=temp;
	else
		goto final;

	temp=a[0][0];                        //fill corner 2
	a[i][j]='X';
	proc=check(a);
	if(proc!=1)
		a[i][j]=temp;
	else
		goto final;

	srand(time(NULL));
	do
		{
		i=rand()%3;
		j=rand()%3;

		if( ( a[i][j]!='X' ) && ( a[i][j]!='O' ) )
			{
			a[i][j]='X';
			proc=1;
			}

		else
			proc=0;

		}while(proc==0);			// place at random if none of above is possible

	final:
	}
struct player
{
	char name[50];
	int score;
};
void main()
{
	player a;
	ifstream b;
	char name[50];
	int found=0;
	b.open("scores.dat",ios::in);
	clrscr();
	//viewhead();
	clrscr();
	cout<<"enter player name ";
	gets(name);
	while(b.read((char*)&a,sizeof(a)))
	{
		if(strcmp(a.name,name)==0)
		{
			cout<<"Player "<<a.name<<" score = "<<a.score<<" WINS "<<endl;
			found=1;
			break;
		}

	}
	if(found!=1)
	{	cout<<"new player "<<name<<endl;
		strcpy(a.name,name);
		a.score=0;

	}
	b.close();
	ofstream c;
	c.open("scores.dat",ios::app);
	char board[4][4], k='1', choice;
	int compwin, playerwin;

	for(int i=0; i<3; i++)
		for (int j=0; j<3; j++)
			board[i][j]=k++;

	viewboard(board);
	i=0;
	do
		{
		if(i%2==0)
			{
			re:
			cout<<"\n\n\nInput cell number (or press \'e\' to Exit): ";
			cin>>choice;
			clrscr();

			for(int m=0; m<3; m++)
				for(j=0; j<3; j++)
					if( board[m][j] == choice )
						{
						board[m][j]='O';
						viewboard(board);
						playerwin=check(board);
						goto jump;
						}

			if( choice=='e' || choice=='E' )
				goto exit;

			viewboard(board);

			cout<<"\nCell does not exist or is preoccupied";
			goto re;
			jump:
			}

		else
			{
			computerprocess(board);
			cout<<"\nComputer's turn..";
			delay(700);
			clrscr();
			viewboard(board);
			compwin=check(board);
			}

		++i;
		}while( (i<9) && (playerwin!=1) && (compwin!=1) );

	if(playerwin==1)
	{
		cout<<"\nYou Win!!";
		a.score++;

		cout<<a.name<<"\'s score = "<<a.score;
	}

	else if(compwin==1)
		{
		cout<<"\nComputer wins";

		exit:
		cout<<"\nThanks for Trying";

		}

	else
		{
		cout<<"\nMatch draw!!";
		cout<<"\nThanks for Trying";
		}
	c.write((char*)&a,sizeof(a));
	c.close();

getch();
}






