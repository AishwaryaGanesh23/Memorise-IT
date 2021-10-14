#include <stdio.h>
#include <stdlib.h>
#include <time.h> 
#include <fcntl.h>
#include <unistd.h>
#include<errno.h>
#include<signal.h>
#include <sys/wait.h>
#include "project_header.h"


void main()
{
	//home
	int pid,status;
	pid = fork();
	if(pid>0)
	{
		wait(&status);
		srand(time(0));
		int opt;
		do
		{	display_file("banner.txt");
			printf("|---------------|\n");
			printf("|1:Play\t\t|\n|2:Scores\t|\n|3:Information\t|\n|4.Exit\t\t|\n");
			printf("|---------------|\n");
			printf("Choose an option\n");
			scanf("%d",&opt);
			
			switch(opt)
			{
				case 1: game_menu();
						break;
				
				case 2: system("clear");
						display_file("banner.txt");
						display_file("score.txt");
						enter_to_continue(stdin);
						break;
				
				
				case 3: system("clear");
						display_file("banner.txt");
						display_file("info.txt");
						enter_to_continue(stdin);
						break;
				
				case 4: system("clear");
						display_file("banner.txt");
						printf("You have chosen to exit\n");
						sleep(1);
						system("clear");
						break;
						
				default: printf("Invalid choice please try again\n");
			}
		}while(opt!=4);
	}
	else if(pid==0)
	{
		
		system("clear");
		display_file("welcome.txt");
		sleep(2);
		system("clear");
		
	}
}



























