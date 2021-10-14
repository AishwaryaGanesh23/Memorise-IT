#include <stdio.h>
#include <stdlib.h>
#include <time.h> 
#include <fcntl.h>
#include <unistd.h>
#include<errno.h>
#include<signal.h>
#define SIZE 3

int timer=0;

void game_menu();
void init_num_mat(char num[SIZE][SIZE]);
void init_star_mat(char star[SIZE][SIZE]);
void display_star_mat(char star[SIZE][SIZE]);
void display_num_mat(char num[SIZE][SIZE]);
int game_play(char uname[10],char star[SIZE][SIZE],char num[SIZE][SIZE]);
int check_random(int random,char num[SIZE][SIZE]);
void score_store(char uname[10],int score);
void score_display();
void delay_time(int seconds);
int check_numbers(char num[SIZE][SIZE]);
void gametime();

void main()
{
	system("clear");
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
			case 1: game_menu();
					break;
			case 2: score_display();
					break;
			case 3: system("clear");
					printf("You have chosen to exit\n");
					break;
			default: printf("Invalid choice please try again\n");
		}
	}while(opt!=3);
}

void game_menu()//start game
{
	system("clear");
	
	char uname[10];
	printf("Enter Username: ");
	scanf("%s",uname);
	
	char num[SIZE][SIZE];
	init_num_mat(num);//initialise matrix num
	//display_num_mat(num);
	
	char star[SIZE][SIZE];
	init_star_mat(star);//init star matrix
	//display_star_mat(star);
	
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

void display_star_mat(char star[SIZE][SIZE])
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
			printf("%c\t",star[i][j]);
		}
		printf("\n");
	}
}

void display_num_mat(char num[SIZE][SIZE])
{
	int i,j;
	//print random number matrix
	for(i=0;i<SIZE;i++)//print colum number
	{
		printf("\tc%d",i);
	}printf("\t\n");
	
	for(i=0;i<SIZE;i++)
	{
		printf("r%d\t",i);//print row number
		for(j=0;j<SIZE;j++)
		{
			printf("%c\t",num[i][j]);
		}
		printf("\n");
	}
	
}

int game_play(char uname[10],char star[SIZE][SIZE],char num[SIZE][SIZE])//where main part of game is played
{
	int row, col, random, score=10,status=0;//start score = 10
	signal(SIGALRM,&gametime);
	alarm(30);
	
	do
	{
		printf("Memorise Where each number is\n\n");
		display_num_mat(num);//show user num matrix
		sleep(3);//wait 2 seconds and then clear
		system("clear");
		printf("Current Score: %d\n",score);
		display_star_mat(star);//show star matrix 
		
		do//check if random is there in the num matrix otherwise ask again
		{
			random = rand()%9;
			
		}while(check_random(random,num)==0);
		
		printf("%s, where is number %d\n",uname,random);//ask where # is
		printf("Row: ");
		scanf("%d",&row);
		printf("Col: ");
		scanf("%d",&col);
		
		if(timer==0)
		{
			//check if r and c are correct
			if((num[row][col]-48)==random)//correct
			{
				
				score++;//add 1 point to score
				star[row][col]=48+random;//then change corresponding char in star to same as #
				num[row][col]='#';//
				printf("Correct!+1 added to score\nCurrent score: %d\n",score);	
			}
			else//wrong
			{		
				score--;//sub 1 point from score
				printf("Wrong! -1 added to score\nCurrent score: %d\n",score);
			}
		}
		else
		{
			printf("Time up! Last Input not counted\n");
		}
		sleep(2);//wait 2 second
		system("clear");
		
		status=check_numbers(num);
	}while(timer==0&&status<=9);//change to time over&&status

	printf("Your score is:%d\n\n",score);
	//timer back to 0
	return score;
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
			if(num[i][j]==35)
				count++;	
		}
	}
	return count;
}

void score_store(char uname[10],int score)
{
	FILE *fd;
	fd=fopen("score.txt", "a+");
    fseek(fd, 0, SEEK_END);
    fprintf(fd, "%s\t\t%d\n", uname,score);//enter score into file
    fclose(fd);
}



void score_display()//display score
{
    system("clear");
    FILE *fd;
    char c;
	printf("Username\tScore\n");
    fd=fopen("score.txt", "r");
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
    printf("\n\n");
}


void gametime()//signal handler for time limit using sigalrm
{
	timer=1;
	printf("\nTime up\n");
}





