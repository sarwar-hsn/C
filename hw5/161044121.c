#include<stdio.h>
#include<stdlib.h>
#define DICT_SIZE 15
#define WORD_LEN 10
#define LINE_LEN 18
/*function prototypes*/
int valid_word(char *str,char *dict[DICT_SIZE]);
char random_letter();
int compare_exit(char str1[], char str2[]) ;
int compare_string(char str1[], char str2[]);
int size(char *str);
void print_board(char str[DICT_SIZE][15]);
int check_found(char *a,char found_word[15][15]);


int get_line_size(char *line) {
	char *ch_iter = line; /* so as not to lose beginning of line*/
	int counter = 0;
	// go until you see new line or null char
	while(*ch_iter != '\n' && *ch_iter != '\0') {
		ch_iter++; // next char
		counter++; // increment counter
	}
	
	return counter;
}

void copy_string(char *source, char *destination) {
	// get iterators over original pointers
	char *src_iter = source;
	char *dst_iter = destination;
	// until null char
	while (*src_iter != '\0') {
		// copy pointers
		*dst_iter = *src_iter;
		// advance to next char
		src_iter++;
		dst_iter++;
   }
   // terminate string
   *dst_iter = '\0';
}

void remove_newline(char *line) {
	char *ch_iter = line;
	// go until you see new line
	while(*ch_iter != '\n') {
		ch_iter++; // next char
	}
	*ch_iter = '\0'; // overwrite new line
}

void print_dictionary(char *dict[]) {
	int i;
	for(i = 0 ; i < DICT_SIZE ; i++) {
	}
}

void print_coord(int coord[DICT_SIZE][4]) {
	int i, j;
	for(i = 0 ; i < DICT_SIZE ; i++) {
		for(j = 0 ; j < 4 ; j++) {
			printf("%d ", coord[i][j]);
		}
		printf("\n");
	}
}

int main(){
	char *dict[DICT_SIZE];
    int coord[DICT_SIZE][4];    
    char line[LINE_LEN];
	FILE *fp = fopen("word_hunter.dat", "r");
	char str[DICT_SIZE][15];int i,j,k,l,m,n,z,x1,x2,y1,y2,x,y,row=15,col=15,pos,count=0,g=0;
	char found_word[15][15];/*to save the word that we already found */
	char a[15];
	for (i=0; i<15; i++)/*we initialize the found charecter string with empty word */
	{
		copy_string("empty",found_word[i]);
	}
	int line_counter = 0;
	int dict_counter = 0;
	while(fgets(line, LINE_LEN, fp) != NULL) {
		if(line_counter%5 == 0) {
			dict[dict_counter] = (char*) malloc(sizeof(char) * get_line_size(line));
			remove_newline(line);
			copy_string(line, dict[dict_counter]);
		} else if (line_counter%5 == 1){
			coord[dict_counter][0] = atoi(line);
		} else if (line_counter%5 == 2){			
			coord[dict_counter][1] = atoi(line);		
		} else if (line_counter%5 == 3){
			coord[dict_counter][2] = atoi(line);
		} else if (line_counter%5 == 4){
			coord[dict_counter][3] = atoi(line);
			dict_counter++;
		}
		line_counter++;
	}
	
	fclose(fp);
	for ( i=0; i<DICT_SIZE; i++)
	{
		for( j=0; j<15; j++)/*we fill the str charecter string array with random letters*/
		{
			str[i][j]=random_letter();/*calling the random letter function to generate random letter*/
		}
	}
	for ( i=0; i<DICT_SIZE; i++)
	{
		x1=coord[i][0];x2=coord[i][2];y1=coord[i][1];y2=coord[i][3];
		if(x1<x2 && y1==y2)     /*checking the word hunter file to find word which are vertically top to down */
		{
			k=0;
			for (j=x1; j<=x2; j++)
			{
				str[j][y1]=dict[i][k];
				k++;
			}
		}
		if(x1>x2 && y1==y2)     /*checking the word hunter file to find word which are vertically down to top */
		{	
			k=0;
			for (j=x2; j<=x1; j++)
			{
				str[j][y1]=dict[i][k];
				k++;
			}
		}
		if(y1<y2 && x1==x2)     /*checking the word hunter file to find word which are horizontall left to right*/
		{
			k=0;
			m=x1;
			for (j=y1; j<=y2; j++)
			{
				str[m][j]=dict[i][k];
				k++;
			}
		}
		if(y1>y2 && x1==x2)     /*the words which are from horizontal left to right are replaced with random letter*/
		{
			k=0;
			m=x1;
			for (j=y2; j<=y1; j++)
			{
				str[m][j]=dict[i][k];
				k++;
			}
		}
		if(x1<x2&& y1<y2)      /*the words which are from diagonal left to right and from top to bottom are replaced with random letter*/
		{
			for(j=x1 ; j<=x2; ++j)
			{
				for(l=y1 ; l<=y2; ++l)
				{
					m=j;
					n=l;
					k=0;
					for (k=0; k<=(y2-y1);)
					{
						str[m][n]=dict[i][k];
						k++;
						m++;
						n++;
					}
					break;
				}
				break;
			}
		}
		if(x1>x2&& y1>y2)    /*the words which are from diagonal right to left and from top to bottom are replaced with random letter*/
		{
			for(j=x2 ; j<=x1; j++)
			{
				for(l=y2 ; l<=y1; l++)
				{
					m=j;
					n=l;
					for (k=0; k<=y1-y2;k++)
					{
						str[m][n]=dict[i][k];
						m++;
						n++;
					}
					break;
				}
				break;
			}
		}
		if(x1<x2 && y1>y2)     /*the words which are from diagonal right to left and from top to bottom are replaced with random letter*/
		{
			for(j=x1 ; j<=x2; ++j)
			{
				for(l=y1 ; l>=y2; --l)
				{
					m=j;
					n=l;
					for (k=0; k<=(y1-y2);k++)
					{
						str[m][n]=dict[i][k];
						m++;
						n--;
					}
					break;
				}
				break;
			}
		}
		if(x1>x2 && y1<y2)    /*the words which are from diagonal right to left and from bottom to top are replaced with random letter*/
		{
			for(j=x2 ; j<=x1; j++)
			{
				for(l=y2 ; l<=y2; l--)
				{
					m=j;
					n=l;
					for (k=0; k<=y2-y1;k++)
					{
						str[m][n]=dict[i][k];
						m++;
						n--;
					}
					break;
				}
				break;
			}
		}
	}
	printf("**************welcome to puzzle board game *****************\n\n");
	print_board(str);	/*we call the print board function to print the puzzle board with all the words on it */
	while (count!=DICT_SIZE )
	{
		
		printf("\nenter word (type exit to leave the game)->");
		scanf("%s",a);			/*we take a word from the user*/
		if (compare_exit(a,"exit")==1)/*if user enter exit then we leave the game */
		{
			printf("exiting.....\n");
			return 0;
		}
		else if (valid_word(a,dict)==0)
		{
			printf("word is not mapped in the puzzle board!!!\n");
		}
		else if (valid_word(a,dict)==1)/*we check for valid word that means we check if the word is present in the puzzle board then we can continue the game */
		{
			printf("x and y cordinate of the word-> ");/*if the word is valid then we ask user to enter the begging or ending cordinate of the word*/
			scanf("%d %d",&x,&y);
			/*now we start serching from top to bottom*/
			for(i=x ; i<x+size(a); i++)  /*we search the puzzle board from top to bottom */
			{
				pos=x;
				for (k=0;a[k]!='\0';k++)
				{
					if(a[k]!=str[pos][y] && str[pos][y]!=a[k]-32)/*if any of the charecter of mismatch then search is a fail and we break out of the loop*/
						break;
					pos++;/*if charecter keeps matching then we keep incresing the positon till the word is found */
				}
				if (k==size(a))/*condition for the word to be found */
				{
					if(check_found(a,found_word)==0)/*we check if the word is already founded before. if we didn't find the word before then we enter to the condition*/
					{
						copy_string(a,found_word[g]);/*as the word was not found before but we found it now. so we put the word in the found word array */
						g++;	/*we increament the position of the found word charecter array */
						count++;/*we increase the count value to keep a track about how many words we found from the puzzle */
						printf("found!!!\n");
						for(m=x ; m<x+size(a); m++)/*this loop follows the same logic like serching this time we make the word uppercase if the word is found ans wasn't found before*/
						{
							pos=x;
							for (n=0;a[n]!='\0';n++)
							{
								str[pos][y]=a[n]-32;	/*makes the lower case to upper case*/
								pos++;
							}
						}
						break;
					}	
				}
			}
			/*all the search follows same logic like above */
			for(i=x ; i>x-size(a); i--)   /*search the puzzle board from given cordinate vertically down */
			{
				pos=x;
				for (k=size(a)-1;k>=0;k--)
				{
					if(str[pos][y]!=a[k] && str[pos][y]!=a[k]-32)
					{
						break;
					}
					pos--;
				}
				if (k==-1)
				{
					if(check_found(a,found_word)==0)
					{
						copy_string(a,found_word[g]);
						g++;
						count++;
						printf("%s found!!!\n",a);
						for(m=x ; m>x-size(a); m--)
						{
							pos=x;
							for (n=size(a)-1;n>=0;n--)
							{
								str[pos][y]=a[n]-32;
								pos--;
							}
						}
						break;
					}	
				}
			}
			for(i=y ; i<y+size(a); i++)  /*search the puzzle board from given cordinate horizontally left to right  */
			{
				pos=y;
				for (k=0;a[k]!='\0';k++)
				{
					if(str[x][pos]!=a[k] && str[x][pos]!=a[k]-32)
					{
						break;
					}
					pos++;
				}
				if (k==size(a))
				{
					if(check_found(a,found_word)==0)
					{
						copy_string(a,found_word[g]);
						g++;
						count++;
						printf("%s found!!!\n",a);
						for(m=y ; m<x+size(a); m++)
						{
							pos=y;
							for (n=0;a[n]!='\0';n++)
							{
								str[x][pos]=a[n]-32;
								pos++;
							}
						}
						break;
					}
				}
			}
			for(i=y+size(a) ; i>=0; i--)   /*search the puzzle board from given cordinate horizontally right to left  */
			{
				pos=y;
				for (k=size(a)-1;k>=0;k--)
				{
					if(str[x][pos]!=a[k] && str[x][pos]!=a[k]-32)
					{
						break;
					}
					pos--;
				}

				if (k==-1)
				{
					if(check_found(a,found_word)==0)
					{
						copy_string(a,found_word[g]);
						g++;
						count++;
						printf("%s found!!!\n",a);
						for(m=y+size(a); m>=0; m--)
						{
							pos=y;
							for (n=size(a)-1;n>=0;n--)
							{
								str[x][pos]=a[n]-32;
								pos--;
							}
						}
						break;
					}
				}
			}
			for(i=x ; i<=x+size(a); i++)    /*search the puzzle board from given cordinate diagonally  left to right top to bottom  */
			{
				m=x;
				n=y;
				for (j=y; j<=y+size(a); j++)
				{
					for (k=0;k<size(a);k++)
					{
						
						if(str[m][n]!=a[k] && str[m][n]!=a[k]-32)
						{
							break;
						}
						m++;
						n++;
					}
					break;
				}		
				if (k==size(a))
				{
					if(check_found(a,found_word)==0)
					{
						copy_string(a,found_word[g]);
						g++;
						count++;
						printf("%s found!!!\n",a);
						for(m=x ; m<=x+size(a); m++) 
						{
							pos=x;
							l=y;
							for (k=0;k<size(a);k++)
							{
								str[pos][l]=a[k]-32;
								pos++;
								l++;
							}
						}
						break;
					}
				}
			}
			for(i=x; i>=0; i--)   /*search the puzzle board from given cordinate diagonally  left to right bottom  to top  */
			{
				for (j=y; j>=0; j--)
				{
					m=x;
					n=y;
					for (k=size(a)-1;k>=0;k--)
					{
						if(str[m][n]!=a[k] && str[m][n]!=a[k]-32)
						{
							break;
						}
						m--;
						n--;
					}
					break;
				}		
				if (k==-1)
				{
					if(check_found(a,found_word)==0)
					{
						copy_string(a,found_word[g]);
						g++;
						count++;
						printf("%s found!!!\n",a);
						for(m=x; m>=0; m--) 
						{
							for (n=y; n>=0; n--)
							pos=x;
							l=y;
							for (k=size(a)-1;k>=0;k--)
							{
								str[pos][l]=a[k]-32;
								pos--;
								l--;
							}
						}
						break;
					}
				}
			}
			for(i=x ; i<=x+size(a); i++)   /*search the puzzle board from given cordinate diagonally  right  to left top to bottom  */
			{
				m=x;
				n=y;
				for (j=y; j<=y+size(a); j++)
				{
					for (k=0;k<size(a);k++)
					{
						if(str[m][n]!=a[k] && str[m][n]!=a[k]-32)
						{
							break;
						}
						m++;
						n--;
					}
					break;
				}		
				if (k==size(a))
				{
					if(check_found(a,found_word)==0)
					{
						copy_string(a,found_word[g]);
						g++;
						count++;
						printf("%s found!!!\n",a);
						for(m=x ; m<=x+size(a); m++)
						{
							pos=x;
							l=y;
							for (k=0;k<size(a);k++)
							{
								str[pos][l]=a[k]-32;
								pos++;
								l--;
							}
						}
						break;
					}
				}
			}
			for(i=x; i>=0; i--)   /*search the puzzle board from given cordinate diagonally  right to left bottom  to top  */
			{
				for (j=y; j>=0; j--)
				{
					m=x;
					n=y;
					for (k=size(a)-1;k>=0;k--)
					{
						if(str[m][n]!=a[k] && str[m][n]!=a[k]-32)
						{
							break;
						}
						m--;
						n++;
					}
					break;
				}		
				if (k==-1)
				{
					if(check_found(a,found_word)==0)
					{
						copy_string(a,found_word[g]);
						g++;
						count++;
						printf("%s found!!!\n",a);
						for(m=x; m>=0; m--) 
						{
							for (n=y; n>=0; n--)
							pos=x;
							l=y;
							for (k=size(a)-1;k>=0;k--)
							{
								str[pos][l]=a[k]-32;
								pos--;
								l++;
							}
						}
						break;
					}
				}
			}
			print_board(str);	
			if(count==DICT_SIZE)	/* when we find all the words then counter value becomes equal to dict size and we exit from the game */
			{
				printf("!!!!congratulation you found all the word in the map!!!\n");
				return 0;
			}
		}			
	}


return 0;
}

char random_letter()/*this functions generate random lower case letters  */
{
	char x=rand()%(122-97+1)+97;/*condition to generate lowercase letters */
	return x;
}
void print_board(char str[DICT_SIZE][15])/*this function prints the board */
{
	int i,j;
	printf("\n");
	for ( i=0; i<DICT_SIZE; i++)
	{
		for( j=0; j<15; j++)
		{
			printf("%c  ",str[i][j]);
		}
		printf("\n");
	}
}
int size(char *str)/*this function returns size of an string */
{
	int count=0;
	while(str[count]!='\0')
	{
		count++;
	}
	return count;
}
/*since the string lenght of the word_hunter.dat file includes one more extra charecter so we write two function for comparing string . one is */
/*to compare with the strings of the word hunter file and the other is normal string compare function*/
int compare_string(char str1[], char str2[]) /*this functions compares a string with the strings of the word hunter file. if matche then returns 1 else return 0*/
{
	int i=0,flag=1,len1,len2;
	len1=size(str1);
    len2=size(str2)-1;
    if(len1==len2)
    { 
    	for(i=0;i<len1;i++)
    	{
        	if(str1[i]!=str2[i])
        	{
             flag=0;
                 break;
 			}
        }
    }
    else
    	flag=0; 
    if(flag==1)
        return 1;
    else
        return 0;
}
int compare_exit(char str1[], char str2[]) 
{
	int i=0,flag=1,len1,len2;
	len1=size(str1);
    len2=size(str2);
    if(len1==len2)
    { 
    	for(i=0;i<len1;i++)
    	{
        	if(str1[i]!=str2[i])
        	{
             flag=0;
                 break;
 			}
        }
    }
    else
    	flag=0; 
    if(flag==1)
        return 1;
    else
        return 0;
}
int valid_word(char *str,char *dict[DICT_SIZE])	/*this functions checks if the users word is present in the puzzle board by*/
{												/*comparing it with the words present in the word hunter file*/
	int i;
	for (i=0; i<DICT_SIZE; i++)
	{
		if (compare_string(str,dict[i])==1)
		{
			return 1;	/* returns one if the word if found*/
			break;
		}
	}
	return 0;/* if the word is not found then returns 0*/
}
int check_found(char *a,char found_word[15][15])/* this function checks if the word we are seaching was already found or not */
{
	int i;
	for (i=0; i<15; i++)
	{
		if (compare_exit(a,found_word[i])==1)/* if we found the word already then returns 1*/
		{
			return 1;
			break;
		}
	}
	return 0;	/*if we didn't find the word the before then it returns 0 */
}




