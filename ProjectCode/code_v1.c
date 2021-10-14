#include <stdio.h>
#include <stdlib.h>
#include <time.h> 

void game_menu();
void init_num_mat(int num[4][4]);
void init_star_mat(char star[4][4]);
void display_star_mat(char star[4][4]);
void display_num_mat(int num[4][4]);
int game_play(char star[4][4],int num[4][4]);


void main()
{
	srand(time(0));
	//home
	int opt;
	printf("Welcome to Memory game!\n");
	do
	{
		printf("Choose an option\n");
		printf("1:Play\n2:Scores\n3:Exit\n");
		scanf("%d",&opt);
		
		switch(opt)
		{
			case 1: printf("Call Game function\n");
					game_menu();
					break;
			case 2: printf("Call score display Function\n");
					break;
			case 3: printf("You have chosen to exit\n");
					break;
			default: printf("Invalid choice please try again\n");
		}
	}while(opt!=3);
}

void game_menu()
{
	char uname[10];
	printf("Enter Username: ");
	scanf("%s",uname);
	
	int num[4][4];
	init_num_mat(num);//initialise matrix num
	//display_num_mat(num);
	
	char star[4][4];
	init_star_mat(star);//init star matrix
	//display_star_mat(star);
	
	int score = game_play(star,num);//gameplay function
}

void init_num_mat(int num[4][4])
{
	 
	int i,j;
	//initialise matrix to random number between 0 and 9
	for(i=0;i<4;i++)
	{
		for(j=0;j<4;j++)
		{
			num[i][j]=rand()%9;
		}
	}
	
}

void init_star_mat(char star[4][4])
{
	int i,j;
	//initialise matrix to *
	for(i=0;i<4;i++)
	{
		for(j=0;j<4;j++)
		{
			star[i][j]='*';
		}
	}
	
}

void display_star_mat(char star[4][4])
{
	int i,j;
	//print matrix of *
	for(i=0;i<4;i++)
	{
		for(j=0;j<4;j++)
		{
			printf("%c\t",star[i][j]);
		}
		printf("\n");
	}
}

void display_num_mat(int num[4][4])
{
	int i,j;
	//print random number matrix
	for(i=0;i<4;i++)
	{
		for(j=0;j<4;j++)
		{
			printf("%d\t",num[i][j]);
		}
		printf("\n");
	}
	
}

int game_play(char star[4][4],int num[4][4])
{
	
	int row,col,random,score =10;//start score = 10
	display_num_mat(num);//show user num matrix for 1 second then hide it
	
	do
	{
		
		random = rand()%9;
		
		display_star_mat(star);//show star matrix 
		printf("Where is number %d\n",random);//ask where # is
		//check if random is there in the num matrix otherwisse ask again
		
		printf("Row: ");
		scanf("%d",&row);
		printf("col: ");
		scanf("%d",&col);
		
		//check if r and c are correct
		if(num[row][col]==random)//correct
		{
			
			score++;//add 1 point to score
			star[row][col]=48+random;//then change corresponding char in star to same as # (48+#)
			printf("Correct!+1 added to score\nCurrent score: %d",score);	
		}
		else//wrong
		{		
			score--;//sub 1 point from score
			printf("Wrong! -1 added to score\nCurrent score: %d",score);
		}
	}while(score>0||score<=18);//change to time over
	
	return score;
}











