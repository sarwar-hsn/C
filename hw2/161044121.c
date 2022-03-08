/*header files*/
#include <stdio.h>		
#include <stdlib.h>			
#include <time.h>
/*function prototypes*/
void game();		
void show_scores();
int make_a_guess ();
void menu();
void draw_hourglass ();
void draw_mountain_road ();
int main() 		/*main function*/
{
	menu();		/*calling menu function*/
	return 0;
}

void menu()
{
	int Choice,height,length,max_radius,score1=0,score2=0,s_human,s_program;	/*declaring variables*/
	while (Choice!=4)		/*loop exit condition*/
	{
		/*printing menu options*/
		printf("\n\n");			
		printf("***** MENU *****\n");
		printf("1. Play Lucky Number\n");
		printf("2. Draw Hourglass\n");
		printf("3. Draw Mountain Road\n");
		printf("4. Exit\n");
		printf("Choice: ");
		scanf("%d",&Choice);	/*taking choice from user*/
		switch (Choice)		/*entering switch based on choice*/
		{
			case 1:
					game(&s_human,&s_program);	/*calling game function*/
					printf("\n");
					/*calculating number of wins using the return value from game function*/
					score1+=s_human;		
					score2+=s_program;
					show_scores(score1,score2);/*calling show_scores function to print score*/
					break;
			case 2:
					printf("enter height: ");	
					scanf("%d",&height);	/*taking height for hourglass*/
					draw_hourglass(height);/*calling hourglass function to print hourglass*/
					break;
			case 3:
					printf("Enter length: ");
					scanf("%d",&length);	/*taking length of mountain road*/
					printf("Enter maximum radius: ");	
					scanf("%d",&max_radius);	/*taking maximum radius value for mountain road*/
					draw_mountain_road(length,max_radius);	/*calling mountain road function to draw mountain road*/
					break;
			case 4:
					Choice=4;	/*if user enter 4 then exits*/
					break;
			default: 
					printf("\nThis is an invalid Choice.Try again!\n");	/*warning for invalid input*/
		}
	}
}

void game(int *score_human,int *score_program)	/*function declaration for lucky number game*/
{
	int ln,gn,count_human=0,count_program=0,trial,trial_count=1,max,min,distance;	/*creating variables for related fields*/
	srand(time(NULL));	/*to generate different random number each time*/
	trial=10;		/*the number of time you can guess*/
	max=1024;		/*initializing max */
	min=1;			/*initializing min*/
	ln=rand()%(max-min+1)+min;		/*generates random lucky number between the range of 1 to 1024*/
	printf("Lucky Number:%d\n",ln );
	while (trial_count <= trial)			/*this loop goes until we have trials left in our hand*/
	{
		printf("(trial:%d)make a guess between %d and %d: ",trial_count,min,max);	/*prints to enter a number between two range*/
		gn=make_a_guess(trial,min,max);		/*calling guess number function*/
		if (gn<=ln)			/*condition to determine limit value if guess number is less than lucky number*/
		{
			min=gn;
			max=max;
			distance=ln-gn;
		}
		else if (gn>=ln)	/*condition to determine limit value if guess number is greater than  lucky number*/
		{
			min=min;
			max=gn;
			distance=gn-ln;
		}
		/*depending on the difference of distance between guess number and lucky number we print a mapping distance */
		if (distance>=512 && distance<=1023)
		{
			printf("distance is 10\n");
		}
		if(distance>=256 && distance<=511)
		{
			printf("distance is 9\n");
		}
		else if(distance>=128 && distance<=255)
		{
			printf("distance is 8\n");
		}
		else if(distance>=64 && distance<=127)
		{
			printf("distance is 7\n");
		}
		else if(distance>=32 && distance<=63)
		{
			printf("distance is 6\n");
		}
		else if(distance>=16 && distance<=31)
		{
			printf("distance is 5\n");
		}
		else if(distance>=8 && distance<=15)
		{
			printf("distance is 4\n");
		}
		else if(distance>=4 && distance<=7)
		{
			printf("distance is 3\n");
		}
		else if(distance>=2 && distance<=3)
		{
			printf("distance is 2\n");
		}
		else if(distance==1)
		{
			printf("distance is 1\n");
		}
		else if (distance==0)	/*if distance between lucky and guess number is 0 within our trial limit then user wins*/
		{
			printf("\nyou win!!!\n");
			count_human++;	/*increamenting user win value*/
			printf("%d\n",count_human );
			break;	
		}
		if (ln!=gn && trial==trial_count)/*if trial is over and lucky and guess num are not equal then program wins and you lose */
		{
			printf("\nyou lose!!!\n");
			count_program++;	/*increamenting program win value if condition is satisfied*/
		}
		trial_count++;	/*increamenting trial value each time*/
	}
	*score_human=count_human;  /*updates your score*/
	*score_program=count_program;/*updates programs score*/

}
void show_scores(int score_human, int score_program)	/*function declaration to print score */
{

	printf("your score:%d program score:%d\n",score_human,score_program );
}

int make_a_guess (int trial, int min, int max)		/*function declaration .this function returns the guess number*/
{
	int guess;
	scanf("%d",&guess);	/*takes guess number from user */
	return guess;
}


void draw_hourglass (int height)	/*function declration*/
{
	int i,j;	
		if (height%2!=0)	/*condition for hourglass with odd number height value */
		{
			printf("\n");
			for (i=height/2+1; i>=1; i--)	/*this loop prints the upper part of hourglass*/
			{
				for (j=i; j<=height/2;j++)
				{
					printf(" ");
				}
				for (j=i*2-1; j>=1;j--)
				{
					printf("*");
				}
				printf("\n");
			}
			for (i=2; i<=height/2+1; i++)	/*this loop prints the lower part of hourglass*/
			{
				for (j=height/2; j>=i; j--)
				{
					printf(" ");
				}
				for (j=1; j<=i*2-1; j++)
				{
					printf("*");
				}

				printf("\n");
			}
		}
		while(height%2==0) 	/*if hourglass height is even then it asks for height until user enters odd height*/
		{
			printf("invalid input.Please enter height again: ");
			scanf("%d",&height); 	/*if even then it ask*/
			if (height%2!=0)
			{
				printf("\n");
				/*prints the hourglass after user enters odd num*/
				for (i=height/2+1; i>=1; i--)	/*upper part of hourglass*/
				{
					for (j=i; j<=height/2;j++)
					{
						printf(" ");
					}
					for (j=i*2-1; j>=1;j--)
					{
						printf("*");
					}
					printf("\n");
				}
				for (i=2; i<=height/2+1; i++)	/*lower part of hourglass*/
				{
					for (j=height/2; j>=i; j--)
					{
						printf(" ");
					}
					for (j=1; j<=i*2-1; j++)
					{
						printf("*");
					}
					printf("\n");
				}
			}

		}
}

void draw_mountain_road (int length, int max_radius)/*fucntion declaration*/

{
	int n,radius,i,j,k,space,max,min=0,count,count1,count2,middle_row,flag;/*related variables*/
	printf("Enter length and maximum radius:\n");
	n=length;	/*this is the length of the mountain road*/
	max=max_radius;	/*this is the maximum limit of the radius for the half circles*/
	middle_row=max;	/*we initialize to middle row to max and later adjust the mountain path around this middle row*/
	srand(time(NULL));	/*to generate different random number each time*/
	for (k=1;k<=n; k++)	/*loop goes till the length */
	{

		radius=rand()%(max-min+1)+min;	/*we generate radius of the half-circles between 0 to maximum radius*/
		if (k%2!=0)			/*if length value is odd */
		{
			if (k==1)	/*if the length value is odd and it's value is 1*/
			{
				/*draws the firs half circle for length value 1 which is always odd*/
				space=radius+middle_row;	
				if (radius==0)		
				{
					for (i=1; i<=1;i++)
					{
						count2=0;
						for (j=1;j<=space;j++)
						{
							printf(" ");
						}
						printf("|\n");
					}					
				}
				else
				{
					for (i=1; i<=radius+1;i++)
					{
						for (j=space; j>=i; j--)
						{
							printf(" ");
						}
						if (i==radius+1)
						{
							printf("|\n");
						}
						else
						{
							printf("/\n");
						}
						
					}
					for (i=1; i<=radius; i++)
					{
						space=i+middle_row;
						for (j=1;j<=space; j++)
						{
							printf(" ");
						}
						printf("\\\n");
					}
				}
	
			}
		
			else if (k!=1)	/*if the length value is odd and it's not the first length*/
			{
				/*if radius is 0 and previous half circle also has a radius 0 then we print these spaces*/
				if (radius==0 && flag==1)
				{
						space=count-1;
						for (i=1; i<=1;i++)
						{
							for (j=1;j<=count2;j++)
							{
								printf(" ");
							}
							printf("|\n");
						}
				}
				/*if the radius is 0 and previous half circle is not of radius 0 then we print these amount of space*/
				else if (radius==0 && flag==0)	
				{
					space=count-1;
					for (i=1; i<=1;i++)
					{
						for (j=1;j<=space;j++)
						{
							printf(" ");
						}
						printf("|\n");
					}
				}
				else if (radius!=0)	/*if radius of this half circle is not 0*/
				{
					if (flag==1)	/*radius of this halp circle is not 0 but radius of the previous half circle is 0*/
					{
						space=count2;
						for (i=1; i<=radius+1;i++)
						{
							count1=0;
							for (j=space; j>=i; j--)
							{
								printf(" ");
								if (i==radius+1)
								{
									count1++;
								}
							}
							if (i==radius+1)
							{
								printf("|\n");
							}
							else 
							{
								printf("/\n");
							}
						}
						for (i=1; i<=radius; i++)
						{
							for (j=1;j<=i+count1; j++)
							{
								printf(" ");
							}
							printf("\\\n");
						}
					}
					else if (flag==0)	/*if the radius is zero and the previous half is also not of radius 0*/
					{
						space=count-1;
						for (i=1; i<=radius+1;i++)
						{
							count1=0;
							for (j=space; j>=i; j--)
							{
								printf(" ");
								if (i==radius+1)
								{
									count1++;
								}
							}
							if (i==radius+1)
							{
								printf("|\n");
							}
							else 
							{
								printf("/\n");
							}
						}
						for (i=1; i<=radius; i++)
						{
							for (j=1;j<=i+count1; j++)
							{
								printf(" ");
							}
							printf("\\\n");
						}
					}
								
				}

			}
		}
		/*if the length is even number */
		if (k%2==0)
		{
			space=j;
			if (radius==0)
			{
				flag=1;		/*if the radius of the even half circle is 0 then we set flag value to 1*/
				for (i=1; i<=1;i++)
				{
					count2=0;
					for (j=1;j<space;j++)
					{
						printf(" ");
						count2++;
					}
					printf("|\n");
					
				}
				
			}
			else if (radius!=0)	
			{
				flag=0;	/*if the radius of the even half circle is not 0 then we set the flag value to 0*/
				/*prints the half circle depending on radius for even number */
				for (i=1; i<=radius+1; i++)	
				{
					for (j=1; j<=space; j++)
					{
						printf(" ");
					}
					if (i==radius+1)
						printf("|\n");
					else
						printf("\\\n");
					space++;
				}
				
				for (i=1;i<=radius;i++)
				{
					count=0;
					for (j=space-1; j>i;j--)
					{
						printf(" ");
						if (i==radius)
						{
							count++;
						}
					}
					printf("/\n");
				}	
			}	
	
		}
		
	}
}