#include <stdio.h>
#include <stdlib.h>
#include <time.h> 
#include <fcntl.h>
#include <unistd.h>
#include<errno.h>
#include<signal.h>
#include <sys/wait.h>
#include "project_header.h"

int timer=0;//flag for time 

void display_file(char filename[10])//display file
{
	//system("clear");
	FILE *fd;
    char c;
    fd=fopen(filename, "r");
    if(fd==NULL)
    {
            printf("FILE DOESN'T EXIST");
    }

    c=fgetc(fd);
    while(c!= EOF)
    {
        printf("%c", c);
        c=fgetc(fd);
    }
    fclose(fd);
}

void game_menu()//start game
{
	system("clear");
	display_file("banner.txt");
	
	char uname[10];
	printf("Enter Username: ");
	scanf("%s",uname);
	
	char num[SIZE][SIZE];
	init_num_mat(num);//initialise matrix num
	
	char star[SIZE][SIZE];
	init_star_mat(star);//init star matrix
	
	int score = game_play(uname,star,num);//gameplay function
	
	score_store(uname,score);//store score in file
}

void init_num_mat(char num[SIZE][SIZE])//set number matrix
{
	 
	int i,j;
	//initialise matrix to random number between 0 and 9
	for(i=0;i<SIZE;i++)
	{
		for(j=0;j<SIZE;j++)
		{
			num[i][j]=48 + (rand()%9);
		}
	}	
}

void init_star_mat(char star[SIZE][SIZE])//set star matrix
{
	int i,j;
	//initialise matrix to *
	for(i=0;i<SIZE;i++)
	{
		for(j=0;j<SIZE;j++)
		{
			star[i][j]='*';
		}
	}
}

int game_play(char uname[10],char star[SIZE][SIZE],char num[SIZE][SIZE])//where main part of game is played
{
	
	int row, col, random, score=0,status=0;
	signal(SIGALRM,&gametime);
	alarm(120);//in seconds
	
	do
	{
		system("clear");
		display_file("banner.txt");
		
		printf("Memorise Where each number is\n\n");
		display_matrix(num);//show user num matrix
		sleep(3);//wait few seconds 
		system("clear");
		
		display_file("banner.txt");
		printf("Current Score: %d\n",score);
		display_matrix(star);//show star matrix 
		
		do//check if random is there in the num matrix otherwise ask again
		{
			random = rand()%9;
			
		}while(check_random(random,num)==0);
		
		printf("%s, where is number %d\n",uname,random);//ask where # is
		printf("Row: ");
		scanf("%d",&row);
		printf("Col: ");
		scanf("%d",&col);
		
		if(timer==0)//if time not up
		{
			//check if r and c are correct
			if((num[row][col]-48)==random)//correct
			{
				
				score++;//add 1 point to score
				star[row][col]=48+random;//then change corresponding char in star to same as #
				num[row][col]='#';//so correctly guessed is not option anymore/repeated
				printf("Correct!+1 added to score\nCurrent score: %d\n",score);	
			}
			else//wrong
			{		
				score--;//sub 1 point from score
				printf("Wrong! -1 added to score\nCurrent score: %d\n",score);
			}
		}
		else//if time up
		{
			printf("\nTime up\nLast Input not counted\n");
		}
		
		sleep(2);//wait 2 second
		system("clear");
		status=check_numbers(num);
	
	}while(timer==0&&status<9);//change to time over&&status
	
	display_file("banner.txt");
	printf("GAME OVER\n\nYour score is:%d\n\n",score);
	enter_to_continue(stdin);
	
	timer=0;//set timer flag back for next game
	return score;
}

void gametime()//signal handler for time limit using sigalrm
{
	timer=1;
}

void display_matrix(char matrix[SIZE][SIZE])
{
	int i,j;
	//print matrix of *
	for(i=0;i<SIZE;i++)//print colum number
	{
		printf("\tc%d",i);
	}printf("\t\n");
	
	for(i=0;i<SIZE;i++)
	{
		printf("r%d\t",i);//print row number
		for(j=0;j<SIZE;j++)
		{
			printf("%c\t",matrix[i][j]);
		}
		printf("\n");
	}
}
int check_random(int random, char num[SIZE][SIZE])//check if random number generated is in the matrix
{
	int i,j,count=0;
	
	for(i=0;i<SIZE;i++)
	{
		for(j=0;j<SIZE;j++)
		{
			if(random == (num[i][j]-48))
				count++;	
		}
	}
	return count;
}

int check_numbers(char num[SIZE][SIZE])//check if all numbers have been guessed
{
	int i,j,count=0;
	
	for(i=0;i<SIZE;i++)
	{
		for(j=0;j<SIZE;j++)
		{
			if(num[i][j]=='#')
				count++;	
		}
	}
	return count;
}

void enter_to_continue(FILE *in)
{	
	//flush
	int ch;
	do
	ch = fgetc ( in ); 
	while ( ch != EOF && ch != '\n' ); 
	clearerr ( in );
	
	//pause
	printf ( "Press [Enter] to continue: " );
	fflush ( stdout );
	getchar();

	system("clear");
}

void score_store(char uname[10],int score)
{
	FILE *fd;
	fd=fopen("score.txt", "a+");
    fseek(fd, 0, SEEK_END);
    fprintf(fd, "%s\t\t\t%d\n", uname,score);//enter score into file
    fclose(fd);
}
