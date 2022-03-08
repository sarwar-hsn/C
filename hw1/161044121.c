#include <stdio.h>			/*header files*/
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define PI 3				/*pre defining values */
#define SQUARE 1
#define RECTANGULAR 2
#define CIRCULAR 3

#define red 0
#define yellow 1
#define blue 2
#define black 3
#define white 4

double CreateBody(int shape);     	/*function prototypes*/
int SetColor(int color);
double LoadMoves(int shape,double body_size);
int SetAttackPower(int lower_bound,int upper_bound);
void ShowPokemon(int shape,double size_of_body,int color,double move_length,int attack_power);

int main( void )
{
	int shape,color,attack_power;
	double size_of_body,move_length;
		shape=CIRCULAR;
		size_of_body=CreateBody(shape);
		color=798;
		color=SetColor(color);
		move_length=LoadMoves(shape,size_of_body);
		attack_power=SetAttackPower(0,150);
		ShowPokemon(shape, size_of_body, color, move_length, attack_power);
		return 0;
}
double CreateBody(int shape)		/*function declaration*/
{
	double height,weidth,r,area;			
	if (shape==SQUARE)				/*condition for square*/
	{
		printf("enter the height of square pokemon\n");		/*takes height if shape is square*/
		scanf("%lf",&height);
		area=height*height;			/*area of rectangle is height^2*/
	}		
	else if (shape==RECTANGULAR)	/*condition of rectangular Pokemon*/
	{
		printf("enter the height & weidth of rectangular pokemon\n");   	/*takes height and weidth of rectangle shape */
		scanf("%lf %lf",&height,&weidth);
		area=height*weidth;		/*area of a rectangle is height*weidth */
	}
	else if (shape==CIRCULAR)	/*condition for circular pyramid*/
	{
		printf("enter the radius of the circular pokemon\n");		/*takes the radius value of circle shape*/
		scanf("%lf",&r);
		area=PI*pow(r,2);		/*area of a circle is pi*r^2*/
	}
	return area;				/*function returns the area of the choosen shape*/
}

int SetColor(int color)			/*function prototype*/
{
	if (color>=0 && color<=1000)	/*if color value is between 0 and 1000 we use mod 5 to the color*/
		return(color%5);		/*return the color code*/
	else 
		return(1);  			/*if color value is outside of 0-1000 then we return 1 as default*/
}

double LoadMoves(int shape,double body_size)/*function declaration*/
{
	int r,move_length;
	if (shape==SQUARE)			/*if the shape is square */
	{
		r=sqrt(body_size);		/*we get the length of one side of a square*/
		move_length = 4*r; 		/*summation of the four side which is the move of the pokemon*/
	}
	if (shape==RECTANGULAR)		/*condition to check if the shape is rectangular*/
	{
		r=body_size/5;			/*we get length of one side of the rectangle. we consider the another side to be 5 */
		move_length = 10+2*r;	/*calculates the move length of rectangular pokemon*/
	}
	if (shape==CIRCULAR)		/*condition for circular pokemon*/
	{
		r=sqrt((body_size/PI)); /*gives the radius of a circle */
		move_length = 2*PI*r;	/*we the the circumference of the circle which is the move for circular pokemon*/
	}
	return move_length; 		/*this function return the move length*/
}

int SetAttackPower(int lower_bound,int upper_bound)		/*this function takes two argument*/
{
	srand(time(NULL));		/*function to generate random numbers*/
	return(rand()%(upper_bound-lower_bound+1)+lower_bound) ; 	/*this function return random number between two given range*/
}

void ShowPokemon(int shape,double size_of_body,int color,double move_length,int attack_power)	/*function declaration to print the specification of pokemon*/
{
	int i,j,row,col,n,space1,space2,height,weidth;
	if (shape==SQUARE)	
	{
		height=move_length/4;	/*calculates the height of rectangular pokemon to print it's shape */
		for (i=1; i<=height; i++) /*this loop prints the shape of the square pokemon*/
		{
			for (j=1; j<=height; j++)
			{
				printf("x");
			}
			printf("\n");
		}
		printf("\n\nName: Square pokemon\n");
		printf("Size: %.2f\n",size_of_body);	/*prints the size of the square pokemon*/
		if (color==red)						/*checks the condition for color code and which color to print*/
			printf("Color: red\n");			
		else if (color==yellow)
			printf("Color: yellow\n");			
		else if (color==blue)					
			printf("Color: blue\n");					
		else if (color==black)
			printf("Color: black\n");
		else if (color==white)
			printf("Color: white\n");
		else
			printf("Color: yellow\n");
		printf("Attack Power: %d\n",attack_power );	/*prints the attack power of the square pokemon*/
	}
	else if (shape==RECTANGULAR)
	{
		weidth=size_of_body/5; 	/*one height of the pokemon is static and it's 5. we get the weidth of the pokemon from here*/
		for (i=1; i<=5; i++)	/*this loop prints the rectangular pokemon*/
		{
			for (j=1; j<=weidth; j++)
			{
				printf("x");
			}
			printf("\n");
		}
		printf("\n\nName: Rectangular Pokemon\n");
		printf("Size: %.2f\n",size_of_body);	/*prints the size of the square pokemon*/
		if (color==red)			/*checks the condition for color code and which color to print*/
			printf("Color: red\n");
		else if (color==yellow)
			printf("Color: yellow\n");
		else if (color==blue)
			printf("Color: blue\n");
		else if (color==black)
			printf("Color: black\n");
		else if (color==white)
			printf("Color: white\n");
		else
			printf("Color: yellow\n");
		printf("Attack Power: %d\n",attack_power );	/*prints the attack power of the rectangular pokemon*/	

	}
	/*********************************************************************************/
	/*to print the circular pokemon i divided the part into two catagory.one if for  */
	/*even num and one for odd num. for both even and odd num. I divided the circle  */
	/*into lower part and upper part.for lower part at first I print the spaces which*/
	/*is calculated as space1 and the spaces for lower part is initiated by space2.	 */
	/*after printing the space I printed x by calculation how much x I need. I have  */	
	/*used tab between two x.														 */
	/*********************************************************************************/
	else if (shape==CIRCULAR)
	{
		n=sqrt((size_of_body/PI));	/*we get the radius of the circular pokemon*/
		space1=n/2;																
    	space2=1;																
	  	if (n%2!=0)		/*check if the num is  odd*/							
	    {																		
	      for (row=1; row<=n/2+1; row++)/*this loop is to print the upper part for odd num*/
	      {																		
	        for (col=1; col<=space1;col++)		/*this loop prints spaces*/									
	          {																	
	            printf("\t"); 													
	          }
	          space1--;										
	        for (col=1; col<=row*2-1; col++)	/*this loop prints x*/
	        {
	          if (col==1 || col==2*row-1)
	            printf("x\t");
	          else 
	            printf("\t");
	        }
	      	printf("\n");       
	      }
	      for ( row = n/2; row >= 1; row--) /*this loop prints the lower part of the circle for even num*/
	        { 
	            for (col = 1; col <=space2; col++)	/*this loop prints spaces*/
	            {
	              printf("\t"); 
	            } 
	            for ( col = 1;col <=row*2-1;col++)	/*this loop prints x*/
	            {
	            if (col==1 || col==row*2-1)
	                    printf("x\t");
	                  else 
	                    printf("\t");
	            }         
	          	printf("\n");
	            space2++; 
	        }
	    }
    	if (n%2==0)	/*condition to check even number*/
	    {
	      for (row=1; row<=n/2+1; row++)	/*this loop prints the upper part of the circle for even num*/
	      {
			for (col=1; col<=space1;col++)	/*this loop prints spaces*/
			  {
			    if (row==1 && col==space1 )	
			      printf("    x");
			    else
			      printf("\t"); 
			  }
			space1=space1-1;
			for  (col=2; col<=row*2-1; col++)	/*this loop prints x*/
			{
			  if (col==2 || col==row*2-1)
			    printf("x\t");
			  else
			    printf("\t");
			}
			printf("\n");
	      }
	      for (row = n/2; row >=1; row--) /*this loop prints the lower part of the circle for even num*/
	        { 
	            for ( col =1 ; col <=space2; col++)	/*this loop prints spaces*/
	            {
	              if (row==1 && col==n/2)
	                printf("    x");
	              else
	                printf("\t"); 
	            } 
	            for (col = 2;col <=row*2-1;col++)	/*this loop prints x*/
	            {
	              if (col==2 || col==row*2-1)
	               printf("x\t");
	              else 
	               printf("\t");
	            }         
	            printf("\n");
	            space2++; 
	       }      
	    }
		printf("\n\nName: Circular Pokemon\n");
		printf("Size: %.2f\n",size_of_body);	/*this loop prints size of circular pokemon*/
		if (color==red)			/*checks condition for color code of circular pokemon*/
			printf("Color: red\n");
		else if (color==yellow)
			printf("Color: yellow\n");
		else if (color==blue)
			printf("Color: blue\n");
		else if (color==black)
			printf("Color: black\n");
		else if (color==white)
			printf("Color: white\n");
		else
			printf("Color: yellow\n");
		printf("Attack Power: %d\n",attack_power ); /*prints the attack power of circular pokemon*/	
	}
}

