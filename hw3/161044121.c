#include <stdio.h>
/*function prototype*/
void main_menu();
void simple_calculator();
void student_grade();
void pattern();
void calc_menu();
int add();
int sub();
int mul();
int divi();
int power();
int mod();
int doit();
int take_grades();
int take_exam_grades();
double calculate_homework();
double calculate_lab();
double calculate_all();

int main()		/*main function*/
{
	int choice; 
	printf("\n*****welcome*****");
	main_menu();	/*fucntion call to main menu function to display the options*/
	while (choice!=4)	/*exit condition.exits from the program if user press 4*/
	{
		printf("enter your choice:");
		scanf("%d",&choice);	/*taking choice from user to select what he wants to do*/
		switch(choice)	/*switching to choice */
		{
			case 1:								/*if user choice is 1 then we call the calculator program */
					simple_calculator();
					main_menu();	/*after exiting from the program we display the menu again*/
					break;
			case 2:
					student_grade();	/*if user choice is 2 then we call the program that calculates student grade*/
					main_menu();	/*we display the menu again after the execution of the program*/
					break;
			case 3: 
					pattern();	/*if the user choice is 3 then we call the function that prints the pattern*/
					main_menu();	/*after execution we call the menu again*/
					break;
			case 4:			/*if user enter 4 then the whole program closes*/
					break;
			default: 	/*it reminds user if his choice is not in our list*/
					printf("invalid choice\n");
		}		
	}
return 0;
}
void main_menu()	/*this function displays the option that our program is capable of doing*/
{
	printf("\n");
	printf("1.simple calculator\n");
	printf("2.student grade calculation\n");
	printf("3.pattern print\n");
	printf("4.exit\n\n");
}

void simple_calculator()	/*fucntion declaration for simple calculator*/
{
	int num1,num2,result=0;		
	char x,y,z;	/*this charecter variables are to check user input format*/
	calc_menu();	/*function call to display calculator menu*/
	while(1)	/*program runs till the exit condition is satisfied*/
	{	
		printf("input:");
		scanf(" %c",&x);	/*x checks what operator user has entered*/
			if (x=='e' || x=='E')	/*if the x equals to e that means user wants to from the program*/
			{
				break;
			}
		scanf("%c",&z);	/*if the first operator is not e then we scan z to detect whats there in the second position*/
		scanf("%d",&num1);/*then we scan the first number*/
		scanf("%c",&y);	/*this one check what is the input after the first number*/
		if (y!='\n' && z==' ')	/*if there is a space after the first operator and no "enter" after the first number then we scan the second number*/
		{
			scanf("%d",&num2);	
		}
		else if(y=='\n' && z==' ')/*if operator is not "**" and there is a "enter" after the first number */
								/*that means the user will not enter the second number so we set the value of second number to value of previous result*/
		{		
			num2=result;
		}											
		else if(y=='\n' && z=='*')/*if the operator is "**" and user press enter after the first number that means he will give any second number */
		{
			num2=result;	/*so we set the value of second number to previous result*/
		}
		else if(y!='\n' && z=='*')	/*if the operator is "**" and the user doesn't press "enter" after the first number then we scan the second number*/
		{
			scanf("%d",&num2);
		}

		if (x=='+')	/*if the user enters "+" as operator*/
		{
			result=doit(add,num1,num2);/*then we call the doit and set add function as parameter to calculate the sum*/
		}
		if (x=='-')/*if the user input is "-"*/
		{
			if (y=='\n')	/*and if the user don't enter any second number then we call the function doit to substract the number from previous result*/
			{
				result=doit(sub,num2,num1);	/*after calculation we save the result to result variable*/
			}
			else
			{							
				result=doit(sub,num1,num2);/*if the user has a second input then we substract the second number from first number */
			}
		} 
		if (x=='/')/*if the user input is "/"*/
		{
			if (y=='\n')	/*if the user doesn't enter any second number*/
			{
				if (num1==0)/*and tries to divide by zero then shows invalid input and sets the result to zero*/
				{
					printf("invalid operation\n");	
					result=0;
				}
				else 
				{
					result=doit(divi,num2,num1); /*if the number is not zero then does the normal calculation*/
				}
			}
			else if (y!='\n')	/*if the user enter two number */
			{
				if (num2==0)	/*if the second number is zero then it's a invalid input */
				{
					printf("invalid operation\n");
					result=0;	/*we set the result value to zero */
				}
				else /*if the second number is not zero for dividation then does the normal operation*/
				{
					result=doit(divi,num1,num2);
				}
				
			}
		}
		if (x=='*')/*if the user selects * as operator then we call the functio doit and muliplication function as parameter in it*/
		{
			result=doit(mul,num1,num2);
		}
		if (x=='*' && z=='*')/*it user enter two star then we does the power operation*/
		{

			
			if (y=='\n')	/*if user enters one number then we does the power operation with the previous result*/
			{
				result=doit(power,num2,num1);
			}
			else /*if the user enters two number then does the normal operation*/
			{
				result=doit(power,num1,num2);
			}
		}
		if (x=='%')/*if the user choose "%" operator the we does the mod opration*/
		{
			if (y=='\n')	/*if user enters only one number */
			{
				if (num1==0)/*if that only number is zero then we consider it as invalid operation and set the result value to zero*/
				{
					printf("invalid operation\n");
					result=0;
				}
				else/*if the only number is not zero then we does the operation taking the previous result as another number*/
				{
					result=doit(mod,num2,num1);
				}
			}
			else
			{
				if (num2==0)/*if user enters two number and the second number is zero then it's a invalid operation too*/
				{
					printf("invalid operation\n");
					result=0;
				}
				else	/*if the second number is not zero then we does the normal operation */
				{
					result=doit(mod,num1,num2);
				}
			}		
		}
		printf("%d\n",result );	/*prints the result after each operation*/
		
	}
	
}


int add (int number1,int number2)/*this function takes two integer as input and returns the sum of them*/
{
	int sum;
	sum=number1+number2;
	return sum;
}
int sub (int number1,int number2)/*this function takes two integer as input and returns the substration value of them */
{
	int sub;
	sub=number1 - number2;
	return sub;
}
int mul(int number1,int number2)/*this function takes two interger and return the multiplication value of them*/
{
	int mul;
	mul=number1*number2;
	return mul;
}
int divi(int number1,int number2)/*this function takes two interger as input and returns the value after dividing the first number by second number*/
{
	int div;
	div=number1/number2;
	return div;
}
int power (int number1,int number2)/*this function takes two integer and returns the power of second number to the first number*/
{
	int i,power=1;
	for (i=1; i<=number2; i++)
	{
		power=power*number1;
	}
	return (power);
}
int mod(int number1,int number2)/*this function takes two interger as input and does the mod operation*/
{
	int mod;
	mod=number1%number2;
	return mod;
}
int doit(int(*f)(),int first_number(int,int),int second_number)/*this funtion takes a function as parameter who has return type interger and who has two integer as input*/
{
	return (f(first_number,second_number)); /*returns the result*/
}
void calc_menu()/*this function prints how the calculator operates*/
{
	printf("\n");
	printf("\t*****WELCOME TO SIMPLE CALCULATOR****\n");
	printf("   (caution: case sensitive.exact format expected)\n\n");
	printf("+ :\taddition\n");
	printf("- :\tsubstraction\n");
	printf("* :\tmultiplication\n");
	printf("/ :\tdivision\n");
	printf("**:\tpower operation\n");
	printf("%% :\tmod operation\n");
	printf("e :\texit calculator\n");
	printf("\n");
}

void student_grade()/*this function is for the student grade calculation program*/
{
	int homework_grade[10],lab_grade[10],xm_grade[2];/*initializing three arrays. one for homework,one for lab and one for midterm and final exam*/
	double homework_average,lab_average,final;
	homework_average=calculate_homework(homework_grade);/*function call to calculate average mark of homework grades*/
	lab_average=calculate_lab(lab_grade);/*function call to calculate the average mark of lab grades*/
	final=calculate_all(homework_average,xm_grade,lab_average);/*function call to print the mid and final exam average and return the final mark*/
	printf("FINAL MARK:%.2f\n",final);/*prints the final mark*/
}
int take_grades(int *array)/*this function takes an array as input*/
{
	int i;
	for (i=0 ; i<10; i++)	/*this array takes ten value from the user */
	{
		printf("%d : ",i+1);
		scanf("%d",&array[i]);
	}
}

int take_exam_grades(int xm_grade[2])	/*this functions takes an array as input */
{
	printf("enter mid-term grade->");
	scanf("%d",&xm_grade[0]);	/*takes the midterm exam grade */
	printf("enter final xm grade->");
	scanf("%d",&xm_grade[1]);/*takes the final exam grade*/
	printf("\n");
}

double calculate_homework(int homework_grade[10])/*this function takes an array as argument*/
{
	double average,sum=0;int i;
	printf("enter homework grade->\n");
	take_grades(homework_grade);	/*we call the take_grade function to take the homework grade */
	for (i=0; i<10; i++)	/*this loop calculates the sum of all the grades */
	{
		sum=sum+homework_grade[i];
	}
	/*we calculate the homework mark taking it as 10 percent out of hundred*/
	average=sum/10;
	average=(average/100);
	average=average*10;
	return average; 
}
double calculate_lab(int lab_grade[10])
{
	double average,sum=0;int i;
	printf("enter lab grade->\n");
	take_grades(lab_grade);/*fucntion call to take_grade function to take the lab grades*/
	for (i=0; i<10; i++)	/*this loop goes till we calculate all the sum */
	{
		sum=sum+lab_grade[i];	
	}
	/*we calcultae the lab grades taking it as 20 percent out of hundred*/
	average=sum/10;
	average=(average/100);
	average=average*20;
	return average;
}

double calculate_all(double homework_average,int xm_grade[2],double lab_average)/*this function takes three argunment*/
{
	double average_homework,average_lab,average_midterm,average_final,final;
	take_exam_grades(xm_grade);/*this functions takes the midterm and final */
	/*we calculate the midterm average taking it as 30 percent out of hundred*/
	average_midterm=xm_grade[0];
	average_midterm=average_midterm/100;
	average_midterm=average_midterm*30;
	/*we calculate the final exam average taking it as 40 percent out of hundred*/
	average_final=xm_grade[1];
	average_final=average_final/100;
	average_final=average_final*40;
	/*printint the averages*/
	printf("homework average:%.2f\n",homework_average );
	printf("lab average:%.2f\n",lab_average);
	printf("mid-term average:%.2f\n",average_midterm );
	printf("final exam average:%.2f\n\n",average_final );
	final=homework_average+lab_average+average_midterm+average_final;
	return(final);/*returns the final exam*/
}

void pattern()/*this function prints the pattern */
{
		int i,j,height,space=0;	
		printf("enter height:");
		scanf("%d",&height);/*takes the height*/
		for (i=1; i<=height; i++)	/*this loop prints the upper part of the pattern*/
		{
			for (j=height; j>i; j--)/*this loop prints the spaces for the upper part*/
			{
				printf(" ");
			}
			for (j=1; j<=i*2; j++)/*this loop prints the * of the upper part*/
			{
				if (j==1)
					printf("/");/*prints / for the first column*/
				else if (j==i*2)/*prints \ for the last column*/
					printf("\\");
				else 
					printf("*");
			}
			printf("\n");
		}
		for (i=height; i>=1; i--)/*this loop prints the lower part*/
		{
			for (j=1; j<=space; j++) /*this loop prints the spaces for the lower part*/
			{
				printf(" ");
			}
			for (j=i*2; j>=1; j--)	/*this loop prints the * / \ for the lower part*/
			{
				if (j==i*2)
					printf("\\");
				else if (j==1)
					printf("/");
				else 
					printf("*");
			}
			space++;
			printf("\n");
		}

}