#include <stdio.h>
#include <stdlib.h>
/*function prototypes*/
void menu();
int factors(int x,int y);
void sort(int array[10]);
void divide (int array[],int start,int end);
void merge(int array[],int start,int mid,int end);
void numberevaluate(int n);
int digit_count(int n,int counter);
int check_equal(int n,int num,int sum);
void capital(char *str);
int main()	
{
    int choice,num1,num2, array[10],sum=0;
    char str[100];
    printf("*****welcome*****");
    while(choice!=6)	/*exit condition to exit from the menu*/
    {
        menu();	/*function call to menu function which will display us what are the options we have*/	
        printf("enter your choice->");	
        scanf("%d",&choice);	/*user enters his choice */
        switch(choice)	/*switching to users choice */
        {
            case 1:	
                printf("enter two number: ");
                scanf("%d %d",&num1,&num2);	/*we take two numbers from user to calculate it's common factor*/
                printf("common factor value-> %d\n",factors(num1,num2));/*printing common factors by calling factors func*/
                break;											
            case 2:	
                sort(array);/*function call to sort function to sort an array*/
                break;
            case 3:
                printf("enter a number->");
                scanf("%d",&num1);/*we take a number from user to evaluate*/
                printf("output:");
                numberevaluate(num1);/*we call the numberevaluate function to evaluate the number*/
                printf("\n");
                break;
            case 4:
                printf("enter a number to check it's equality->");
                scanf("%d",&num1);/*we take a number from the user*/
                num2=num1;	/*we assign the same num to num2 so that it doesn't loose it's value in recursion steps*/
                /*the check_equal func will return a value after calculating using the give formula. if the return value and*/
                /*the given num are equal then we will print equal as result else we print not equal*/
                if(check_equal(num1,num2,sum)==num1)/*if num and return value are same then it's equal*/
                    printf("Output-> equal\n");
                else	/*else it's not equal*/
                    printf("Output-> not equal\n");
                break;
            case 5:	
                printf("enter a string-> ");
                scanf(" %[^\n]s",str);/*we take a string from user*/
                capital(str);/*we call the function called capital which will display the first capital letter*/
                break;
            case 6:
                return 0;/*exit condition is option 6*/
                break;
            default:
                printf("invalid choice!!!\n");/*warning the user for invalid input*/
                break;
        }
    }
    return 0;
}
void menu()	/*this functions just prints the available options*/
{
	printf("\n");
    printf("Choose one from below->\n");
    printf("1.perform factors operation\n");
    printf("2.perform sorting operation\n");
    printf("3.number evaluation operation\n");
    printf("4.check equal or not equal\n");
    printf("5.first capital letter of string\n");
    printf("6.exit\n");
}

int factors(int x,int y)	/*this fucntion finds the common factors of two number*/
{
	if (y==0)	/*base condition for recursive func*/
		return x;/*if the second number is 0 then we return the first num*/
	else
		return factors(y,x%y);/*this is the recursive state*/
}
void sort(int array[10]) /*this fucntion is for sorting an array */
{
    int i;
	printf("please enter 10 integer value:\n");
	for (i=0; i<10;i++)
	{
		scanf("%d",&array[i]);	/*we take 10 number from user*/
	}
	printf("input array : ");
	for (i=0; i<10;i++)
	{
		printf("%d ",array[i]);/*we display those number*/
	}
	printf("\n");
    divide(array,0,9);/*fucntion call to divide function*/
    printf("sorted array: ");
	for (i=0; i<10;i++)
	{
		printf("%d ",array[i]);/*we print the sorted array */
	}
	printf("\n");
}
void divide(int array[],int start,int end) /*this function will divide the array in two parts recursively*/
{

	if (end<=start)	/*if the array can't be divided anymore then we return.this is the base condition*/
	{
		return;
	}
	else
	{
		int mid=(start+end)/2;	/*else we calculate the middle of the array */
		divide(array,start,mid);/*we call the fucntion recursively to divide the first half of the array */
		divide(array,mid+1,end);/*then we call the same function but starting from middle+1 value to the end of the array*/
		merge(array,start,mid,end);/*function call to merge function that will assemble those array in sorted order*/
	}
}
void merge(int array[],int start,int mid,int end)/*this function will merge those divided array in sorted order*/
{
	int temp[10],i,j,k;/*we take temporary array to hold values after each sorting till the final step is completed*/
	i=start;
	j=mid+1;
	k=0;
	while (i<=mid && j<=end)/*this loop starts from the first element of both right and left divided array*/
	{
		if (array[i]<array[j])	/*if the  element of the left array is smaller than the  element of right hand array  */
		{
			temp[k++]=array[i++];	/*then we we place the small element in temp array and increament respective values*/
		}
		else
		{
			temp[k++]=array[j++];/*but if the right array element is less than left array element then we put that value in temp*/
		}
	}
	/*after comparing if there are any left over elements then we simply just fill them in temp array */
	while (i<=mid)	
	{
		temp[k++]=array[i++];
	}
	while (j<=end)
	{
		temp[k++]=array[j++];
	}
	/*again we fill our main array back but this time in sorted order*/
	for (i=start,k=0; i<=end; i++)
	{
		array[i]=temp[k++];
	}
}
void numberevaluate(int n)	/*this function takes a number and shows result according to a formula*/
{
	if (n==1)	/*if num becomes  1 then we simply print 1 and return. this is the base condition of recursive function*/
	{
		printf("1");
		return ;
	}
	/*till the num becomes 1 we continue the recursive step*/
	else
	{
		if (n%2==0 && n!=0)
		{
			printf("%d ", n);
			numberevaluate(n/2);
		}
		else if (n%2==1 &&n!=0)
		{
			printf("%d ", n);
			numberevaluate((3*n)+1);
		}
	}
}
int check_equal(int n,int num,int sum)	/*this functions returns a value after going through a certain formula*/
{
	int x,y=1,z=0,i,exp;
	if (n==0)	/*base condition. when the number becomes 0 we simply return the sum*/
	{
		return sum;
	}
	else
	{
		x=n%10;	/*we do the mod operation to get the last digit of the num*/
		exp=digit_count(num,z);	/*we call the digit_count function which actullay is the exponential for the formula*/
		for (i=1; i<=exp; i++)	/*this loop calculates the power*/
		{
			y*=x;
		}
		return  check_equal(n/10,num,sum+y);/*this is the recursive stage. we decreament the number and add sum to the previous sum.*/
	}
}
int digit_count(int n,int exp)	/*this functions takes a num and calculates it's digit num recursively*/
{
	if (n==0)	/*when the number becomes 0 then we return how many digit we have got. this is the base case*/
		return exp;
	else
	{
		return exp+=digit_count(n/10,exp++);/*this is the recursive state*/
	}
}
void capital(char *str)/*this function calculates the first capital letter in a string recursively*/
{
	if(*str)	/*if string position is valid.this is the base condition */
	{
		if (*str>='A' && *str<='Z')/*and if  we find a capital letter in that position then we simply print the letter and return*/
		{
			printf("first capital letter in the string is->  %c\n",*str );
			return;
		}
		capital(str+1);/*else we call the function again and again by increamenting it's position */
	}
}


