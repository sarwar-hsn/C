#include <stdio.h>
#include <stdlib.h>
#include <time.h>
typedef enum /*defining enum*/
{
	noone,cap,car
}player_type;
typedef enum 
{
	start, property, tax, punish,fortune
}block_type;
struct player/*structure for player */
{
	player_type type;
	int current_block_id;
	int owned_block_ids[12];
	int account;
	int turn_to_wait;
	char * name;
};
struct block /*structure for block*/
{
	int block_id;
    char *block_name;
    int price;
    int rent;/*block rent with no house*/
    int rent_1;/*block rent with 1 house*/
    int rent_2;/*block rent with 2 house*/
    int rent_3;/*block rent with 3 house*/
    int house_price;/*Holds price of building a house on the block*/
    int house_count;
    struct player owner;
    block_type type; 
	struct block *next;
}*head;
/*fucntion prototypes*/
void init_the_board(struct block *board);/*this function initialize the board with respective values*/
void show_board(struct block *board,struct player player_one, struct player player_two);/*this function just prints the current state of the game */
void property_menu();/*this function prints the gameplay menu */
void show_properties(struct block *board );/*this function displays all the properties*/
void my_properties(struct player *current_player,struct block *board);/*this function shows the all the properties that a user has*/
int check_owned_block(struct player *current_player);/*this function check if a property belongs to him or not*/
int check_opponents_owned_block(struct player *player_one,struct player *player_two);/*this function checks if a property belongs to his opponent or not*/
void buy_property(struct block* current_block, struct player* current_player);/*this function helps the user player to buy a property*/
void buy_property_for_computer(struct block* current_block, struct player* current_player);/*this function is to buy property for computer*/
void sell_property(struct block *board, struct player* current_player);/*this function is to sell property for user player*/
void sell_property_for_computer(struct block *board, struct player* current_player);/*sell property for computer*/
void buy_house(struct block *current_block,struct player *current_player);/*buy house for user player*/
void buy_house_for_computer(struct block *current_block,struct player *current_player);/*buy house for computer*/
void gameplay (struct block *board, struct player player_one, struct player player_two);/*this function is to play the game*/
int property_count(struct player *current_player);/*this function is to check if a user has property or not*/
int balance_control(struct block *board, struct player *current_player,int tax);/*this func control's balance issue for user player*/
int balance_control_for_computer(struct block *board, struct player *current_player,int tax);/*this function controls balance for computer*/
int fortune_card(struct block *board,struct player *current_player,struct player *opponent);/*fortune card related option for user player*/
int fortune_card_for_computer(struct block *board,struct player *current_player,struct player *opponent);/*fortune card handling for computer*/
int rent_control(struct block *board,struct player *current_player);/*this function calculates the amount of rent to pay*/
double price_of_all_property(struct block *board);/*this function returns the average of all the properties*/
void menu();
struct block *position(struct block *x,int n);/*returns the current position of player*/
int main()
{
	int i;
	struct block *board;
	struct player player_one;
	struct player player_two;
	player_one.type=cap;
	player_two.type=car;
	for (i=0; i<12;i++)
	{
		player_one.owned_block_ids[i]=-1;	/*initializing the owned block array with -1 value*/
		player_two.owned_block_ids[i]=-1;
	}
	srand(time(NULL));
	player_one.current_block_id=0;
	player_two.current_block_id=0;
	player_one.account=10000;
	player_two.account=10000;
	player_one.turn_to_wait=0;
	player_two.turn_to_wait=0;
	player_one.name="cap";
	player_two.name="car";
	init_the_board(board);
	show_board(board,player_one,player_two);/*calling show board func*/
	gameplay(board,player_one,player_two);/*calling gameplay func*/
}
void gameplay (struct block *board, struct player player_one, struct player player_two)/*gameplay function*/
{
	int i,turn,select,dice,rent,choice,flag;double average;char x;
	average=price_of_all_property(board);/*stores the average of all the properties*/
		turn = car;  /*first we start with the player type car */
		while (1)/*gameplay continues till one of them loose */
		{
			if (turn==cap)/*if the turn is for cap*/
			{
				dice=rand()%(6-1+1)+1;/*randomly generate number between 1-6*/
				player_one.current_block_id+=dice;
				if (player_one.current_block_id>23)/*if the player cross start block*/
				{
					player_one.current_block_id-=24;
					player_one.account+=10000;/*we add 10000$ in his account*/
					printf("10000$ added to your computer's account\n");
				}
				board=position(board,player_one.current_block_id);/*storing the pos of player one*/
				printf("\nComputer rolled the dice (%d).Computar arrived at %s\n",dice,board->block_name );
				if(check_owned_block(&player_one)==1)/*if computer arrived in a block that it owns */
				{
					buy_house_for_computer(board,&player_one);/*we call the buy house for computer*/
				}
				if (check_owned_block(&player_one)==0 && check_opponents_owned_block(&player_two,&player_one)==0 && board->type==property)/*if computer arrives in a unwoned property*/
				{
					if(board->price<average)/*if the price of the property is less than average*/
					{
						buy_property_for_computer(board,&player_one);/*we call the buy property func to buy this property for computer*/
					} 
					else
					{
						dice=rand()%(6-1+1)+1;/*if the average is not greater then we roll the dice */
						if (dice>=1 && dice<=3)/*if the dice roll is between 1-3 than we buy it else we skip*/
						{
							buy_property_for_computer(board,&player_one);
						}
					}
				}
				if(board->type==fortune)/*if computer arrives in a property of fortune type*/
				{
					flag=fortune_card_for_computer(board,&player_one,&player_two);/*we call the fortune for computer func and saves it value*/
					if (flag==1)/*if the return type is one that means it failed to pay his debt and we declare opponent as winner*/
					{
						printf("computer coudn't pay the debt. car wins!!!\n");
						return;
					}
				}
				if (board->type==tax)/*if the player falls into a tax block we cut from his balance */
				{
					if (player_one.account<board->rent)/*if the player doesn't have enough money*/
					{
						flag=balance_control_for_computer(board, &player_one,board->rent);/*we call the balance control tand store it's return value*/
						if (flag==0)/*if the return value is 0 that means it failed to pay it's debt and we declare the opponent as winner*/
						{
							printf("computer failed pay it's debt.you win!!!\n");
							return;
						}
					}
					else/*if he manages to get the required amount then we just pay the rent and game continues*/
					{
						player_one.account-=board->rent;/*but if he already has enough money then we just cut the money and game continues*/
						printf("computer paid %d as tax\n",board->rent);
					}	
				}
				if(check_opponents_owned_block(&player_two,&player_one)==1)/*if computer falls into a property owned by it's opponent then we do the same procedure like tax*/
				{
					rent=rent_control(board,&player_one);
					if(player_one.account>rent)
					{
						player_one.account-=rent;
						player_two.account+=rent;
						printf("computer paid %d as rent\n",board->rent);
					}
					else
					{
						flag=balance_control_for_computer(board,&player_one,rent);
						if (flag==0)
						{
							printf("computer failed pay it's debt.you win!!!\n");
							return;
						}
						else
						{
							player_one.account-=rent;
							player_two.account+=rent;
							printf("computer paid %d as rent\n",board->rent);
						}
					}
				}
				
				/*this portion is for punishment block. if the player falls into a punishment block then he will wait that number of turns*/
				if (player_one.current_block_id==6)/*if the player falls into wait to turn */
				{
					player_one.turn_to_wait=2;/*we change it's turn to wait amount*/
				}
				else if (player_one.current_block_id==18)/*same procedure like above depending on the block*/
				{
					player_one.turn_to_wait=1;
				}
				else
				{
					player_one.turn_to_wait=0;
				}
				if (player_two.turn_to_wait==2)/*if the opponent has 2 turn punishment*/
				{
					if (player_one.turn_to_wait==0)/*but computer doesn't have punishment then computer keep his turn*/
					{
						turn=cap;
						player_two.turn_to_wait-=1;/*we decrease the turn to wait for opponent*/
					}
					else if (player_one.turn_to_wait!=0)/*but if opponent is in 2 turn punishment and computer also falls into punishment block then turn goes for opponent*/
					{
						turn=car;
						player_one.turn_to_wait=0;/*we set the turn to wait for opponent to 0*/
					}
						
				}
				else if (player_two.turn_to_wait==1)/*same logic like above but this one is for wait one turn block*/
				{
					if (player_one.turn_to_wait==0)
					{
						turn=cap;
						player_two.turn_to_wait-=1;
					}
					else if (player_one.turn_to_wait!=0)
					{
						turn=car;
						player_one.turn_to_wait=0;
					}
				}
				else if (player_two.turn_to_wait==0)
				{
					turn=car;
				}
			}
		 	else if (turn==car)/*if the turn is for user player that means car*/
			{
				printf("------------------\n");
				printf("| Turn for car   |\n");
				printf("------------------\n");
				menu();/*we call the menu function to display option*/
				printf("please select an option to continue:");/*we ask the user to select an option and depending on the selection switch to case */
				scanf("%d",&select);
				switch(select)
				{
					case 1:
							dice=rand()%(6-1+1)+1;/*roll the dice between 1-6*/
							player_two.current_block_id+=dice;
							if (player_two.current_block_id>23)/*if the dice value exceeds start block then add 10000 and adjust it's position*/
							{
								player_two.current_block_id-=24;
								player_two.account+=10000;
								printf("10000$ added to your account\n");
							}
							board=position(board,player_two.current_block_id);/*we get the position of the player depending on the rolled dice*/
							/*if the player falls into a tax block we cut from his balance following the same procedure like computer*/
							/*this time we just call the function that is relative to user player*/
							if (board->type==tax)
							{					 
								if (player_two.account<board->rent)
								{
									flag=balance_control(board,&player_two,board->rent);
									if(flag==0)
									{
										printf("you don't have enough balance to pay the debt.computer wins!!!");
										return;
									}
									else
									{
										player_two.account-=board->rent;
										printf("you paid %d as tax\n",board->rent);
									}
								}
								else
								{
									player_two.account-=board->rent;
									printf("you paid %d as tax\n",board->rent);
								}	
							}
							/*if the user falls into a fortune block we does the same thing like computer*/
							if(board->type==fortune)
							{
								flag=fortune_card(board,&player_two,&player_one);
								if (flag==1)
								{
									printf("you coudn't pay the debt . computer wins!!!\n");
									return;
								}
								
								
							}
							show_board(board,player_one,player_two);/*calling to show board function to display the position of players*/
							printf("you rolled the dice (%d).you arrived at %s\n",dice,board->block_name );
							/*if the user falls into an unwoned property */
							if (check_opponents_owned_block(&player_one,&player_two)==0 && check_owned_block(&player_two)==0 && board->type==property)
							{
								printf("this is an unowned property.do you want to buy(y/n):");/*we ask the user if he want's to buy*/
								scanf(" %c",&x);
								if (x=='y' ||x=='Y')/*if yes then we continue*/
								{
									choice=-1;
									while(choice!=0)/*while user don't want to go back we keep him showing the options*/
									{
										printf("\n1.buy property\n");
										printf("2.sell_property\n");
										printf("0.back\n");
										printf("enter your choice:");
										scanf("%d",&choice);
										if(choice==1)/*if user selects 1 then  we go for buy property*/
										{
											if(player_two.account<board->price)/*if the user doesn't have enough money to buy then we print a msg*/
											{
												printf("insufficient balance\n");
											}
											else
											{
												buy_property(board,&player_two);/*if the player has enough money then we call the buy property func */
											}
											
										}
										if(choice==2)/*if the user want's to sell some of his property when he face low balance issue then he can do that using option 2*/
										{
											if(property_count(&player_two)==0)
											{
												printf("you don't have any property to sell\n");/*if he doesn't have any property to sell then we skip*/
											}
											else
											{
												sell_property(board,&player_two);/*else we go for sell property func*/
											}
										}
									}
									
								}
							}
							/*if the  user falls into a property that opponent own then he pays the rent. procedure is same like computer */
							if(check_opponents_owned_block(&player_one,&player_two)==1)
							{
								rent=rent_control(board,&player_two);
								if(player_two.account>rent)
								{
									player_two.account-=rent;
									player_one.account+=rent;
								}
								else
								{
									flag=balance_control(board,&player_two,rent);
									if(flag==0)
										printf("car wins!!!\n");
									else
									{
										player_two.account-=rent;
										player_one.account+=rent;
									}
								}
							}
							/*if user falls into punishment block. procedure is same like computer*/
							if (player_two.current_block_id==6 )
							{
								player_two.turn_to_wait=2;
							}
							else if (player_two.current_block_id==18 )
							{
								player_two.turn_to_wait=1;
							}
							else
							{
								player_two.turn_to_wait=0;
							}
							if (player_one.turn_to_wait==2 )
							{
								if (player_two.turn_to_wait==0)
								{
									turn=car;
									printf("turn continues for you!!!\n");
									player_one.turn_to_wait-=1;
									break;
								}
								else if (player_two.turn_to_wait!=0)
								{
									turn=cap;
									player_two.turn_to_wait=0;
									break;
								}
									
							}
							if (player_one.turn_to_wait==1)
							{
								if (player_two.turn_to_wait==0)
								{
									turn=car;
									printf("turn continues for you!!!\n");
									player_one.turn_to_wait-=1;
									break;
								}
								else if (player_two.turn_to_wait!=0)
								{
									turn=cap;
									player_two.turn_to_wait=0;
									break;
								}
									
							}
							if (player_one.turn_to_wait==0)
							{
								turn=cap;
							}
							break;
					case 2:
							show_board(board,player_one,player_two);
							printf("your current account balance is:%d\n\n",player_two.account);/*prints the current balace of the user */
							break;
					case 3: 
							show_board(board,player_one,player_two);
							my_properties(&player_two,board);/*calling to my properties func to sell the properties that user has*/
							break;
					case 4:
							show_properties(board);/*calling to show property func to see property deed*/
							show_board(board,player_one,player_two);
							break;
					case 5:
							show_board(board,player_one,player_two);
							if (check_opponents_owned_block(&player_one,&player_two)==1 || check_owned_block(&player_two)==1)/*checks if the property that user wants to buy already owned or not*/
							{
								printf("\nthis property is already owned\n");
								printf("--------------------------------\n");
								break;
							}
							else
							{
								/*if not owned then we for transaction*/
								board=position(board,player_two.current_block_id);
								buy_property(board,&player_two);
								break;
							}
							break;
					case 6:
							show_board(board,player_one,player_two);
							buy_house(board,&player_two);/*calling to buy property function*/
							break;
					case 7:
							show_board(board,player_one,player_two);
							sell_property(board,&player_two);/*calling to sell property func*/
							break;
					default:
							show_board(board,player_one,player_two);
							printf("invalid choice!!!\n");
							break;
				}
			}
		}
}

void menu()/*this func simply prints menu to guide the player to play the game*/
{
	printf("1 - Roll the dice \n");
	printf("2 - Show my account\n");
	printf("3 - Show my properties\n");
	printf("4 - Show pro deeds\n");
	printf("5 - Buy property\n");
	printf("6 - Buy house\n");
	printf("7 - Sell property\n");
}
void show_board(struct block *board,struct player player_one, struct player player_two)/*this function just prints the current state of the game */
{
	int i,j;
	struct block *temp;
	board=head;
	temp=head;
	printf("-------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
	for (i=1; i<=7; i++)
	{
		if (i==1 )
		{
			printf("|");
			for (j=1; j<=7;j++)
			{
				printf("\t%-10s\t|",board->block_name);
				board=board->next;
				temp=temp->next;
			}
			printf("\n|");
			board=head;
			for (j=1; j<=7;j++)
			{
				if (board->price==0 && board->rent==0)
					printf("\t\t\t|");
				else if(board->price==0 && board->rent!=0)
				{
					if (board->type==punish ||board->type==fortune)
						printf("\t\t\t|");
					else
						printf("\t%d$\t\t|",board->rent);
				}
				else
					printf("\t%d$\t\t|",board->price);
				board=board->next;
			}
			printf("\n|");
			if (player_one.current_block_id==0 && player_two.current_block_id==0)
			{
				printf("\t%-6s %s\t|",player_one.name,player_two.name);
			}
			else if(player_one.current_block_id==0)
				printf("\t%-10s\t|",player_one.name);
			else if (player_two.current_block_id==0)
				printf("\t%-10s\t|",player_two.name);
			else
				printf("\t\t\t|");
			if (player_one.current_block_id==1 && player_two.current_block_id==1)
			{
				printf("\t%-6s %s\t|",player_one.name,player_two.name);
			}
			else if(player_one.current_block_id==1)
				printf("\t%-10s\t|",player_one.name);
			else if (player_two.current_block_id==1)
				printf("\t%-10s\t|",player_two.name);
			else
				printf("\t\t\t|");
			if (player_one.current_block_id==2 && player_two.current_block_id==2)
			{
				printf("\t%-6s %s\t|",player_one.name,player_two.name);
			}
			else if(player_one.current_block_id==2)
				printf("\t%-10s\t|",player_one.name);
			else if (player_two.current_block_id==2)
				printf("\t%-10s\t|",player_two.name);
			else
				printf("\t\t\t|");
			if (player_one.current_block_id==3 && player_two.current_block_id==3)
			{
				printf("\t%-6s %s\t|",player_one.name,player_two.name);
			}
			else if(player_one.current_block_id==3)
				printf("\t%-10s\t|",player_one.name);
			else if (player_two.current_block_id==3)
				printf("\t%-10s\t|",player_two.name);
			else
				printf("\t\t\t|");
			if (player_one.current_block_id==4 && player_two.current_block_id==4)
			{
				printf("\t%-6s %s\t|",player_one.name,player_two.name);
			}
			else if(player_one.current_block_id==4)
				printf("\t%-10s\t|",player_one.name);
			else if (player_two.current_block_id==4)
				printf("\t%-10s\t|",player_two.name);
			else
				printf("\t\t\t|");
			if (player_one.current_block_id==5 && player_two.current_block_id==5)
			{
				printf("\t%-6s %s\t|",player_one.name,player_two.name);
			}
			else if(player_one.current_block_id==5)
				printf("\t%-10s\t|",player_one.name);
			else if (player_two.current_block_id==5)
				printf("\t%-10s\t|",player_two.name);
			else
				printf("\t\t\t|");
			if (player_one.current_block_id==6 && player_two.current_block_id==6)
			{
				printf("\t%-6s %s\t|",player_one.name,player_two.name);
			}
			else if(player_one.current_block_id==6)
				printf("\t%-10s\t|",player_one.name);
			else if (player_two.current_block_id==6)
				printf("\t%-10s\t|",player_two.name);
			else
				printf("\t\t\t|");
			printf("\n");
			printf("-------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
		}
		if (i==2)
		{
			while(head!=NULL)
			{
				if (temp->block_id==23)
					break;
				temp=temp->next;
			}
			printf("|");
			printf("\t%-10s\t|",temp->block_name);
			printf("\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t|");
			printf("\t%-10s\t|",board->block_name);
			printf("\n|");
			printf("\t%d$\t\t|",temp->price);
			printf("\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t|");
			printf("\t%d$\t\t|",board->price);
			printf("\n|");
			board=board->next;
			if (player_one.current_block_id==23 && player_two.current_block_id==23)
			{
				printf("\t%-6s %s\t|",player_one.name,player_two.name);
			}
			else if(player_one.current_block_id==23)
				printf("\t%-10s\t|",player_one.name);
			else if (player_two.current_block_id==23)
				printf("\t%-10s\t|",player_two.name);
			else
				printf("\t\t\t|");
			printf("\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t|");
			if (player_one.current_block_id==7 && player_two.current_block_id==7)
			{
				printf("\t%-6s %s\t|",player_one.name,player_two.name);
			}
			else if(player_one.current_block_id==7)
				printf("\t%-10s\t|",player_one.name);
			else if (player_two.current_block_id==7)
				printf("\t%-10s\t|",player_two.name);
			else
				printf("\t\t\t|");
			printf("\n");
			printf("-------------------------\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t-------------------------\n");
		}
		if (i==3)
		{
			temp=head;
			while(head!=NULL)
			{
				if (temp->block_id==22)
					break;
				temp=temp->next;
			}
			printf("|");
			printf("\t%-10s\t|",temp->block_name);
			printf("\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t|");
			printf("\t%-10s\t|",board->block_name);
			printf("\n|");
			printf("\t%d$\t\t|",temp->rent);
			printf("\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t|");
			printf("\t%d$\t\t|",board->price);
			printf("\n|");
			board=board->next;
			if (player_one.current_block_id==22 && player_two.current_block_id==22)
			{
				printf("\t%-6s %s\t|",player_one.name,player_two.name);
			}
			else if(player_one.current_block_id==22)
				printf("\t%-10s\t|",player_one.name);
			else if (player_two.current_block_id==22)
				printf("\t%-10s\t|",player_two.name);
			else
				printf("\t\t\t|");
			printf("\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t|");
			if (player_one.current_block_id==8 && player_two.current_block_id==8)
			{
				printf("\t%-6s %s\t|",player_one.name,player_two.name);
			}
			else if(player_one.current_block_id==8)
				printf("\t%-10s\t|",player_one.name);
			else if (player_two.current_block_id==8)
				printf("\t%-10s\t|",player_two.name);
			else
				printf("\t\t\t|");
			printf("\n");
			printf("-------------------------\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t-------------------------\n");
		}
		if (i==4)
		{
			temp=head;
			while(head!=NULL)
			{
				if (temp->block_id==21)
					break;
				temp=temp->next;
			}
			printf("|");
			printf("\t%-10s\t|",temp->block_name);
			printf("\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t|");
			printf("\t%-10s\t|",board->block_name);
			printf("\n|");
			printf("\t\t\t|");
			printf("\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t|");
			printf("\t\t\t|");
			printf("\n|");
			board=board->next;
			if (player_one.current_block_id==21 && player_two.current_block_id==21)
			{
				printf("\t%-6s %s\t|",player_one.name,player_two.name);
			}
			else if(player_one.current_block_id==21)
				printf("\t%-10s\t|",player_one.name);
			else if (player_two.current_block_id==21)
				printf("\t%-10s\t|",player_two.name);
			else
				printf("\t\t\t|");
			printf("\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t|");
			if (player_one.current_block_id==9 && player_two.current_block_id==9)
			{
				printf("\t%-6s %s\t|",player_one.name,player_two.name);
			}
			else if(player_one.current_block_id==9)
				printf("\t%-10s\t|",player_one.name);
			else if (player_two.current_block_id==9)
				printf("\t%-10s\t|",player_two.name);
			else
				printf("\t\t\t|");
			printf("\n");
			printf("-------------------------\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t-------------------------\n");
		}
		if (i==5)
		{
			temp=head;
			while(head!=NULL)
			{
				if (temp->block_id==20)
					break;
				temp=temp->next;
			}
			printf("|");
			printf("\t%-10s\t|",temp->block_name);
			printf("\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t|");
			printf("\t%-10s\t|",board->block_name);
			printf("\n|");
			printf("\t%d$\t\t|",temp->price);
			printf("\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t|");
			printf("\t%d$\t\t|",board->rent);
			printf("\n|");
			board=board->next;
			if (player_one.current_block_id==20 && player_two.current_block_id==20)
			{
				printf("\t%-6s %s\t|",player_one.name,player_two.name);
			}
			else if(player_one.current_block_id==20)
				printf("\t%-10s\t|",player_one.name);
			else if (player_two.current_block_id==20)
				printf("\t%-10s\t|",player_two.name);
			else
				printf("\t\t\t|");
			printf("\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t|");
			if (player_one.current_block_id==10 && player_two.current_block_id==10)
			{
				printf("\t%-6s %s\t|",player_one.name,player_two.name);
			}
			else if(player_one.current_block_id==10)
				printf("\t%-10s\t|",player_one.name);
			else if (player_two.current_block_id==10)
				printf("\t%-10s\t|",player_two.name);
			else
				printf("\t\t\t|");
			printf("\n");
			printf("-------------------------\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t-------------------------\n");
			
		}
		if (i==6)
		{
			temp=head;
			while(head!=NULL)
			{
				if (temp->block_id==19)
					break;
				temp=temp->next;
			}
			printf("|");
			printf("\t%-10s\t|",temp->block_name);
			printf("\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t|");
			printf("\t%-10s\t|",board->block_name);
			printf("\n|");
			printf("\t%d$\t\t|",temp->price);
			printf("\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t|");
			printf("\t%d$\t\t|",board->price);
			printf("\n|");
			if (player_one.current_block_id==19 && player_two.current_block_id==19)
			{
				printf("\t%-6s %s\t|",player_one.name,player_two.name);
			}
			else if(player_one.current_block_id==19)
				printf("\t%-10s\t|",player_one.name);
			else if (player_two.current_block_id==19)
				printf("\t%-10s\t|",player_two.name);
			else
				printf("\t\t\t|");
			printf("\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t|");
			if (player_one.current_block_id==11 && player_two.current_block_id==11)
			{
				printf("\t%-6s %s\t|",player_one.name,player_two.name);
			}
			else if(player_one.current_block_id==11)
				printf("\t%-10s\t|",player_one.name);
			else if (player_two.current_block_id==11)
				printf("\t%-10s\t|",player_two.name);
			else
				printf("\t\t\t|");
			printf("\n");
			printf("-------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
			
		}
		if (i==7 )
		{
			temp=head;
			while(head!=NULL)
			{
				if (temp->block_id==18)
					break;
				temp=temp->next;
			}
			printf("|");
			printf("\t%-10s\t|",temp->block_name);
			temp=head;
			while(head!=NULL)
			{
				if (temp->block_id==17)
					break;
				temp=temp->next;
			}
			printf("\t%-10s\t|",temp->block_name);
			temp=head;
			while(head!=NULL)
			{
				if (temp->block_id==16)
					break;
				temp=temp->next;
			}
			printf("\t%-10s\t|",temp->block_name);
			temp=head;
			while(head!=NULL)
			{
				if (temp->block_id==15)
					break;
				temp=temp->next;
			}
			printf("\t%-10s\t|",temp->block_name);
			temp=head;
			while(head!=NULL)
			{
				if (temp->block_id==14)
					break;
				temp=temp->next;
			}
			printf("\t%-10s\t|",temp->block_name);
			temp=head;
			while(head!=NULL)
			{
				if (temp->block_id==13)
					break;
				temp=temp->next;
			}
			printf("\t%-10s\t|",temp->block_name);
			temp=head;
			while(head!=NULL)
			{
				if (temp->block_id==12)
					break;
				temp=temp->next;
			}
			printf("\t%-10s\t|",temp->block_name);
			printf("\n|");
			printf("\t\t\t|");
			temp=head;
			while(head!=NULL)
			{
				if (temp->block_id==17)
					break;
				temp=temp->next;
			}
			printf("\t%d$\t\t|",temp->price);
			temp=head;
			while(head!=NULL)
			{
				if (temp->block_id==16)
					break;
				temp=temp->next;
			}
			printf("\t%d$\t\t|",temp->price);
			printf("\t\t\t|");
			temp=head;
			while(head!=NULL)
			{
				if (temp->block_id==14)
					break;
				temp=temp->next;
			}
			printf("\t%d$\t\t|",temp->rent);
			temp=head;
			while(head!=NULL)
			{
				if (temp->block_id==13)
					break;
				temp=temp->next;
			}
			printf("\t%d$\t\t|",temp->price);
			temp=head;
			while(head!=NULL)
			{
				if (temp->block_id==12)
					break;
				temp=temp->next;
			}
			printf("\t%d$\t\t|",temp->rent);
			
			printf("\n|");
			if (player_one.current_block_id==18 && player_two.current_block_id==18)
			{
				printf("\t%-6s %s\t|",player_one.name,player_two.name);
			}
			else if(player_one.current_block_id==18)
				printf("\t%-10s\t|",player_one.name);
			else if (player_two.current_block_id==18)
				printf("\t%-10s\t|",player_two.name);
			else
				printf("\t\t\t|");
			if (player_one.current_block_id==17 && player_two.current_block_id==17)
			{
				printf("\t%-6s %s\t|",player_one.name,player_two.name);
			}
			else if(player_one.current_block_id==17)
				printf("\t%-10s\t|",player_one.name);
			else if (player_two.current_block_id==17)
				printf("\t%-10s\t|",player_two.name);
			else
				printf("\t\t\t|");
			if (player_one.current_block_id==16 && player_two.current_block_id==16)
			{
				printf("\t%-6s %s\t|",player_one.name,player_two.name);
			}
			else if(player_one.current_block_id==16)
				printf("\t%-10s\t|",player_one.name);
			else if (player_two.current_block_id==16)
				printf("\t%-10s\t|",player_two.name);
			else
				printf("\t\t\t|");
			if (player_one.current_block_id==15 && player_two.current_block_id==15)
			{
				printf("\t%-6s %s\t|",player_one.name,player_two.name);
			}
			else if(player_one.current_block_id==15)
				printf("\t%-10s\t|",player_one.name);
			else if (player_two.current_block_id==15)
				printf("\t%-10s\t|",player_two.name);
			else
				printf("\t\t\t|");
			if (player_one.current_block_id==14 && player_two.current_block_id==14)
			{
				printf("\t%-6s %s\t|",player_one.name,player_two.name);
			}
			else if(player_one.current_block_id==14)
				printf("\t%-10s\t|",player_one.name);
			else if (player_two.current_block_id==14)
				printf("\t%-10s\t|",player_two.name);
			else
				printf("\t\t\t|");
			if (player_one.current_block_id==13 && player_two.current_block_id==13)
			{
				printf("\t%-6s %s\t|",player_one.name,player_two.name);
			}
			else if(player_one.current_block_id==13)
				printf("\t%-10s\t|",player_one.name);
			else if (player_two.current_block_id==13)
				printf("\t%-10s\t|",player_two.name);
			else
				printf("\t\t\t|");
			if (player_one.current_block_id==12 && player_two.current_block_id==12)
			{
				printf("\t%-6s %s\t|",player_one.name,player_two.name);
			}
			else if(player_one.current_block_id==12)
				printf("\t%-10s\t|",player_one.name);
			else if (player_two.current_block_id==12)
				printf("\t%-10s\t|",player_two.name);
			else
				printf("\t\t\t|");
			printf("\n");
			printf("-------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
			printf("computer:%d car:%d\n\n",player_one.account,player_two.account );
		}
	}

}
void init_the_board(struct block *board)/*this func is just to initializing the board with the respective price */
{
	struct block *p;
	board=(struct block*)malloc(sizeof(struct block));
	board->block_id=0;
	board->block_name="start";
	board->price=0;
	board->rent=0;
	board->rent_1=0;
	board->rent_2=0;
	board->rent_3=0;
	board->house_price=0;
	board->house_count=0;
	board->owner.type=noone;
	board->type=start;
	board->next=NULL;
	head=board;
	board=(struct block*)malloc(sizeof(struct block));
	board->block_name="esenyurt";
	board->block_id=1;
	board->price=16000;
	board->rent=800;
	board->rent_1=4000;
	board->rent_2=9000;
	board->rent_3=25000;
	board->house_price=10000;
	board->house_count=0;
	board->owner.type=noone;
	board->type=property;
	board->next=NULL;
	head->next=board;
	board=(struct block*)malloc(sizeof(struct block));
	board->block_id=2;
	board->block_name="car park";
	board->price=0;
	board->rent=1500;
	board->rent_1=0;
	board->rent_2=0;
	board->rent_3=0;
	board->house_price=0;
	board->house_count=0;
	board->owner.type=noone;
	board->type=tax;
	board->next=NULL;
	head->next->next=board;
	//head->next->next=board;
	board=(struct block*)malloc(sizeof(struct block));
	board->block_id=3;
	board->block_name="fortune card";
	board->price=0;
	board->rent=0;
	board->rent_1=0;
	board->rent_2=0;
	board->rent_3=0;
	board->house_price=0;
	board->house_count=0;
	board->owner.type=noone;
	board->type=fortune;
	p=head;
	while(p->next!=NULL)
	{
		p=p->next;
	}
	p->next=board;
	board=(struct block*)malloc(sizeof(struct block));
	board->block_id=4;
	board->block_name="tuzla";
	board->price=16500;
	board->rent=850;
	board->rent_1=4250;
	board->rent_2=9500;
	board->rent_3=26000;
	board->house_price=12000;
	board->house_count=0;
	board->owner.type=noone;
	board->type=property;
	while(p->next!=NULL)
	{
		p=p->next;
	}
	p->next=board;
	board=(struct block*)malloc(sizeof(struct block));
	board->block_id=5;
	board->block_name="arnavutkoy";
	board->price=17000;
	board->rent=875;
	board->rent_1=4500;
	board->rent_2=10000;
	board->rent_3=28000;
	board->house_price=12000;
	board->house_count=0;
	board->owner.type=noone;
	board->type=property;
	while(p->next!=NULL)
	{
		p=p->next;
	}
	p->next=board;
	board=(struct block*)malloc(sizeof(struct block));
	board->block_id=6;
	board->block_name="wait 2 turn";
	board->price=0;
	board->rent=2;
	board->rent_1=0;
	board->rent_2=0;
	board->rent_3=0;
	board->house_price=0;
	board->house_count=0;
	board->owner.type=noone;
	board->type=punish;
	while(p->next!=NULL)
	{
		p=p->next;
	}
	p->next=board;
	board=(struct block*)malloc(sizeof(struct block));
	board->block_id=7;
	board->block_name="catalca";
	board->price=20000;
	board->rent=1000;
	board->rent_1=5000;
	board->rent_2=12000;
	board->rent_3=30000;
	board->house_price=13000;
	board->house_count=0;
	board->owner.type=noone;
	board->type=property;
	while(p->next!=NULL)
	{
		p=p->next;
	}
	p->next=board;
	board=(struct block*)malloc(sizeof(struct block));
	board->block_id=8;
	board->block_name="beykoz";
	board->price=23000;
	board->rent=1100;
	board->rent_1=5500;
	board->rent_2=12500;
	board->rent_3=33000;
	board->house_price=13000;
	board->house_count=0;
	board->owner.type=noone;
	board->type=property;
	while(p->next!=NULL)
	{
		p=p->next;
	}
	p->next=board;
	board=(struct block*)malloc(sizeof(struct block));
	board->block_id=9;
	board->block_name="fortune card";
	board->price=0;
	board->rent=0;
	board->rent_1=0;
	board->rent_2=0;
	board->rent_3=0;
	board->house_price=0;
	board->house_count=0;
	board->owner.type=noone;
	board->type=fortune;
	while(p->next!=NULL)
	{
		p=p->next;
	}
	p->next=board;
	board=(struct block*)malloc(sizeof(struct block));
	board->block_id=10;
	board->block_name="car fix";
	board->price=0;
	board->rent=1750;
	board->rent_1=0;
	board->rent_2=0;
	board->rent_3=0;
	board->house_price=0;
	board->house_count=0;
	board->owner.type=noone;
	board->type=tax;
	while(p->next!=NULL)
	{
		p=p->next;
	}
	p->next=board;
	board=(struct block*)malloc(sizeof(struct block));
	board->block_id=11;
	board->block_name="maltepe";
	board->price=30000;
	board->rent=1350;
	board->rent_1=7000;
	board->rent_2=15000;
	board->rent_3=40000;
	board->house_price=15000;
	board->house_count=0;
	board->owner.type=noone;
	board->type=property;
	while(p->next!=NULL)
	{
		p=p->next;
	}
	p->next=board;
	board=(struct block*)malloc(sizeof(struct block));
	board->block_id=12;
	board->block_name="bills";
	board->price=0;
	board->rent=2000;
	board->rent_1=0;
	board->rent_2=0;
	board->rent_3=0;
	board->house_price=0;
	board->house_count=0;
	board->owner.type=noone;
	board->type=tax;
	while(p->next!=NULL)
	{
		p=p->next;
	}
	p->next=board;
	board=(struct block*)malloc(sizeof(struct block));
	board->block_id=13;
	board->block_name="sisli";
	board->price=33000;
	board->rent=1500;
	board->rent_1=8000;
	board->rent_2=16000;
	board->rent_3=42000;
	board->house_price=16000;
	board->house_count=0;
	board->owner.type=noone;
	board->type=property;
	while(p->next!=NULL)
	{
		p=p->next;
	}
	p->next=board;
	board=(struct block*)malloc(sizeof(struct block));
	board->block_id=14;
	board->block_name="oil";
	board->price=0;
	board->rent=2250;
	board->rent_1=0;
	board->rent_2=0;
	board->rent_3=0;
	board->house_price=0;
	board->house_count=0;
	board->owner.type=noone;
	board->type=tax;
	while(p->next!=NULL)
	{
		p=p->next;
	}
	p->next=board;
	board=(struct block*)malloc(sizeof(struct block));
	board->block_id=15;
	board->block_name="fortune card";
	board->price=0;
	board->rent=0;
	board->rent_1=0;
	board->rent_2=0;
	board->rent_3=0;
	board->house_price=0;
	board->house_count=0;
	board->owner.type=noone;
	board->type=fortune;
	while(p->next!=NULL)
	{
		p=p->next;
	}
	p->next=board;
	board=(struct block*)malloc(sizeof(struct block));
	board->block_id=16;
	board->block_name="atasehir";
	board->price=35000;
	board->rent=1600;
	board->rent_1=8500;
	board->rent_2=17000;
	board->rent_3=45000;
	board->house_price=17000;
	board->house_count=0;
	board->owner.type=noone;
	board->type=property;
	while(p->next!=NULL)
	{
		p=p->next;
	}
	p->next=board;
	board=(struct block*)malloc(sizeof(struct block));
	board->block_id=17;
	board->block_name="sariyer";
	board->price=40000;
	board->rent=1750;
	board->rent_1=9500;
	board->rent_2=19000;
	board->rent_3=48000;
	board->house_price=19000;
	board->house_count=0;
	board->owner.type=noone;
	board->type=property;
	while(p->next!=NULL)
	{
		p=p->next;
	}
	p->next=board;
	board=(struct block*)malloc(sizeof(struct block));
	board->block_id=18;
	board->block_name="wait 1 turn";
	board->price=0;
	board->rent=1;
	board->rent_1=0;
	board->rent_2=0;
	board->rent_3=0;
	board->house_price=0;
	board->house_count=0;
	board->owner.type=noone;
	board->type=punish;
	while(p->next!=NULL)
	{
		p=p->next;
	}
	p->next=board;
	board=(struct block*)malloc(sizeof(struct block));
	board->block_id=19;
	board->block_name="kadikoy";
	board->price=43000;
	board->rent=1900;
	board->rent_1=11000;
	board->rent_2=21500;
	board->rent_3=55000;
	board->house_price=23000;
	board->house_count=0;
	board->owner.type=noone;
	board->type=property;
	while(p->next!=NULL)
	{
		p=p->next;
	}
	p->next=board;
	board=(struct block*)malloc(sizeof(struct block));
	board->block_id=20;
	board->block_name="besiktas";
	board->price=60000;
	board->rent=25000;
	board->rent_1=15000;
	board->rent_2=28000;
	board->rent_3=60000;
	board->house_price=30000;
	board->house_count=0;
	board->owner.type=noone;
	board->type=property;
	while(p->next!=NULL)
	{
		p=p->next;
	}
	p->next=board;
	board=(struct block*)malloc(sizeof(struct block));
	board->block_id=21;
	board->block_name="fortune card";
	board->price=0;
	board->rent=0;
	board->rent_1=0;
	board->rent_2=0;
	board->rent_3=0;
	board->house_price=0;
	board->house_count=0;
	board->owner.type=noone;
	board->type=fortune;
	while(p->next!=NULL)
	{
		p=p->next;
	}
	p->next=board;
	board=(struct block*)malloc(sizeof(struct block));
	board->block_id=22;
	board->block_name="vocation";
	board->price=0;	
	board->rent=5000;
	board->rent_1=0;
	board->rent_2=0;
	board->rent_3=0;
	board->house_price=0;
	board->house_count=0;
	board->owner.type=noone;
	board->type=tax;
	while(p->next!=NULL)
	{
		p=p->next;
	}
	p->next=board;
	board=(struct block*)malloc(sizeof(struct block));
	board->block_id=23;
	board->block_name="bebek";
	board->price=70000;	
	board->rent=3500;
	board->rent_1=20000;
	board->rent_2=35500;
	board->rent_3=65000;
	board->house_price=35000;
	board->house_count=0;
	board->owner.type=noone;
	board->type=property;
	while(p->next!=NULL)
	{
		p=p->next;
	}
	p->next=board;

}
void show_properties(struct block *board )/*this function prints the data that a property has depending on selection value*/
{
	int choice;
	board=head;
	while(choice!=0)
	{
		property_menu();
		printf("enter your choice->");
		scanf(" %d",&choice);
		if (choice==1||choice==5||choice==7||choice==8||choice==11||choice==13||choice==16||choice==17||choice==19||choice==20||choice==23)
		{
			board=position(board,choice);
			printf("----------------------------------\n");
			printf("|\t     %-10s\t\t |",board->block_name);
			printf("\n----------------------------------\n");
			printf("|\trent 1 H\t%-6d$  |\n",board->rent);
			printf("|\trent 2 H\t%-6d$  |\n",board->rent_1);
			printf("|\trent 3 H\t%-6d$  |\n",board->rent_2);
			printf("|\trent 3 H\t%-6d$  |",board->rent_3);
			printf("\n----------------------------------\n");
			printf("|\tHouse price\t%-6d$  |",board->house_price);
			printf("\n----------------------------------\n");
			
		}
		else if (choice==0)
		{
			return;
		}
		else
		{
			printf("wrong choice!!!\n");
		}
		
	}
}
void property_menu()
{
	printf("\nplease select a property to see details:\n");
	printf("1-  esenyurt\n");
	printf("5-  arnavutkoy\n");
	printf("7-  catalca\n");
	printf("8-  beykoz\n");
	printf("11-  maltepe\n");
	printf("13- sisli\n");
	printf("16- atasehir\n");
	printf("17- sariyer\n");
	printf("19- kadikoy\n");
	printf("20- besiktas\n");
	printf("23- bebek\n");
	printf("0-  exit\n");
	printf("\n");

}
void my_properties(struct player *current_player,struct block *board)/*function declaration */
{
	int i,count=0; 
	if(property_count(current_player)==0)/*if the user has no property */
	{
		printf("you don't have any property\n");
	}
	else 
	{
		for (i=0; i<12;i++)/*loop goes till 12*/
		{
			if (current_player->owned_block_ids[i]!=-1)/*if not -1 one that means it has a property */
			{
				board=position(board,current_player->owned_block_ids[i]);/*we get the position of the property*/
				printf("%d-   %s\n",current_player->owned_block_ids[i],board->block_name);/*we print it's name and block code*/
				printf("     house number in %s:%d\n\n",board->block_name,board->house_count);

			}
		}
	}
}
int check_owned_block(struct player *current_player)/*this func check if the player is already owner of a specific block and returns 1 or 0 depending on that */
{
	int i,found;
	found=0;
	for (i=0; i<12; i++)
	{
		if (current_player->current_block_id==current_player->owned_block_ids[i])
		{
			found=1;
			break;
		}
	}
	if (found==1)
		return 1;
	else if (found==0)
		return 0;
}
int check_opponents_owned_block(struct player *player_one,struct player *player_two)/*this func checks if a price of property belongs to his opponent or not*/
{
	int i,found;
	found=0;
	for (i=0; i<12;i++)
	{
		if(player_one->owned_block_ids[i]==player_two->current_block_id)
		{
			found=1;
			break;
		}
	}
	if (found==1)
		return 1;
	else if (found==0)
		return 0;
}
struct block *position(struct block *x,int n)/*function declaration*/
{
	x=head;/*we set x to head of the linked list */
	while(x!=NULL)
	{
		if (x->block_id==n)/*when we go to desired location we break the loop*/
			break;
		x=x->next;
	}
	return x;/*we return the position as pointer*/
}
void buy_property(struct block* current_block, struct player* current_player)/*this func is to buy a property for user player*/
{
	char x;int y;
	if (current_block->type==property && check_owned_block(current_player)==0  && current_player->account>=current_block->price)/*we check is the property is already owned by him , if he has enough money and is the block a property type */
	{
		int i;
		printf("congratulation you bought this property!!!\n");/*if all of them are satisfied then we add this property in his pocket*/
		current_player->account-=current_block->price;
		for (i=0; i<12; i++)/*we add the property in the owned property id array*/
		{
			if (current_player->owned_block_ids[i]==-1)
			{
				current_player->owned_block_ids[i]=current_player->current_block_id;
				break;
			}
		}
		buy_house(current_block,current_player);/*we call buy house function func if the user is insterested in building some houses in his new property*/
	}
	else
	{
		if(current_player->account<current_block->price)
		{
			printf("insufficient balace!!!\n");
		}
		if(current_block->type!=property ||check_owned_block(current_player)==1)
		{
			printf("%s is not eligible to buy this property\n",current_player->name);
		}
	}
}
void buy_property_for_computer(struct block* current_block, struct player* current_player)/*this func is to buy a property for computer */
{
	char x;int y;
	if (current_block->type==property && check_owned_block(current_player)==0  && current_player->account>=current_block->price)/*we check is the property is already owned by him , if he has enough money and is the block a property type */
	{
		int i;
		printf("computer bought %s !!! \n",current_block->block_name);/*if all of them are satisfied then we add this property in his pocket*/
		current_player->account-=current_block->price;
		for (i=0; i<12; i++)/*we add the property in his owned blocked id*/
		{
			if (current_player->owned_block_ids[i]==-1)
			{
				current_player->owned_block_ids[i]=current_player->current_block_id;
				break;
			}
		}
	}
}
void sell_property_for_computer(struct block *board, struct player* current_player)/*this func is to sell players property for computer*/
{
	int highest_value=0,block,i;
	struct block *temp;
	if (property_count(current_player)==0)/*if the computer has no property then we simply return */
	{
		return;
	}
	else/*but if has property */
	{
		for (i=0; i<12;i++)/*we run the loop to check all the properties */
		{
			if(current_player->owned_block_ids[i]!=-1)
			{
				if (current_player->owned_block_ids[i]>highest_value)
				{
					highest_value=current_player->owned_block_ids[i];
					block=current_player->owned_block_ids[i];/*we store the highest valued property in the variable named block*/
				}
			}
		}
		temp=position(board,block);/*we change out positon to that block*/
		for (i=0; i<12;i++)
		{
			if (current_player->owned_block_ids[i]==block)
			{
				current_player->owned_block_ids[i]=-1;/*we set the value of that block to -1*/
				break;
			}
		}
		current_player->account+=(temp->price/2);
		current_player->account+=((temp->house_count*temp->house_price)/2);
		printf("computer sold %s\n",temp->block_name);

	}	
}
int balance_control_for_computer(struct block *board, struct player *current_player,int tax)/*this function handles the related transaction problem for computer*/
{
	int choice,flag;
	while (current_player->account<tax && property_count(current_player)!=0)/*if computer has no money to pay rent or tax or garnishment or any kind of shortage*/
	{
		sell_property_for_computer(board,current_player);/*computer sells his property till */
		if (current_player->account>=tax)/*he is able to pay tax*/
		{
			return 1;/*if he is able to pay tax we return 1*/
			break;
		}
		if(current_player->account<tax && property_count(current_player)==0)/*or he has no property left to sell*/
		{
			return 0;/*if he is not able to pay tax and no property left then we return 0*/
			break;
		}
	}
}
void buy_house(struct block *current_block,struct player *current_player)/*this function is to buy a house from already owned property for user player*/
{
	int i,y;char x;
	if (current_block->type==property && check_owned_block(current_player)==1 )/*at first we check if the property is owned by the player*/
	{
		printf("\nyou have %d house in this property\n",current_block->house_count);/*we print how many houses he has*/
		printf("------------------------------------\n");
		printf("do you want to buy a house(y/n)->\n");/*we ask permission*/
		scanf(" %c",&x);/*we ask the use if he want's to buy a house to make sure*/
		if(x=='y')
		{
			if(current_block->house_count==3)/*if the block has already 3 house then he can't build more house*/
			{
				printf("\nyou have maximum number of house in this property\n");
				printf("---------------------------------------------------\n");
			}
			else
			{
				printf("enter the number of house you want to build(maximum %d):",3-current_block->house_count);/*else we say what is the max num of house he can built*/
				scanf("%d",&y);
				if (y<=(3-current_block->house_count) && y>=1 )/*if the num is valid then we add the house in that block for him */
				{
					if (current_player->account>= (y*current_block->house_price) )
					{
						current_block->house_count+=y;
						current_player->account-=(current_block->house_price*y);
						printf("%d house builted\n",y );
					}
					else
					{
						printf("\nyou don't have sufficient balance to build house\n");
					}
				}
				else
				{
					printf("\ninvalid number of house\n");
					printf("-------------------------\n");
				}
			}
		}
	}
	else /*if not owned by the player then we skip*/
	{
		printf("%s is not eligible to buy house here\n",current_player->name);
		printf("-----------------------------------------\n");
	}

}
void buy_house_for_computer(struct block *current_block,struct player *current_player)/*this function is to buy a house from already owned property for computer */
{
	int i,y,dice,count;char x;
	if (current_block->type==property && check_owned_block(current_player)==1 )/*we check if computer is the owner or not*/
	{
		if(current_block->house_count==3)/*if the block has already 3 house then he can't build more house*/
		{
			return;
		}
		else
		{
			if (current_player->account < current_block->house_price)/*if computer has not enough money to build a house*/
			{
				return;
			}
			else if (current_player->account >= current_block->house_price)
			{
				for(i=0; i<12;i++)
				{
					if (current_player->owned_block_ids[i]!=-1)
					{
						count++;
					}
				}
				if (count>=4)/*1 third of 12 property is 4. so if computer has 1/3 of the property only then he can proceed to build a house*/
				{
					dice=rand()%(6-1+1)+1;/*now after having 1/3 we roll the dice */
					if (dice>=1 && dice<=3)/*if the dice value is between 1-3 then  we build a house*/
					{
						current_block->house_count+=1;
						current_player->account-=current_block->house_price;
						printf("computer built a house in his property!!!\n");
					}
				}
			}
		}
	}

}
int rent_control(struct block *board,struct player *current_player)/*this function will return the amount of rent a player would need to pay*/
{
	int sum;
	board=position(board,current_player->current_block_id);
	if (board->house_count==1)/*if opponent has 1 house in his property then he will pay rent worth of one house and property */
	{
		sum=board->rent+board->rent_1;
	}
	else if (board->house_count==2)
	{
		
		sum=board->rent+board->rent_1+board->rent_2;
	}
	else if (board->house_count==3)
	{
		sum=board->rent+board->rent_1+board->rent_2+board->rent_3;
	}
	else
	{
		sum=board->rent;
	}
	return sum;
}
int property_count(struct player *current_player)/*this function will return 0 if a player has no house otherwise it will return 1*/
{
	int count=0,i;
	for (i=0; i<12;i++)
	{
		if (current_player->owned_block_ids[i]!=-1)
		{
			count++;
		}
	}
	if (count!=0)
		return 1;
	else 
		return 0;
}
void sell_property(struct block *board, struct player* current_player)/*this func is to sell players property */
{
	int i,x,y,z,money,count=0,found=0;
	struct block *temp;
	while (x!=0)/*we keep asking till player doen's exit*/
	{	
		printf("   sell property \n");
		printf("--------------------\n");
		printf("1.sell property\n");
		printf("0.exit\n");
		printf("enter your choice: ");
		scanf("%d",&x);
		switch(x)
		{
			case 1:
					if(property_count(current_player)==0)
					{
						printf("you don't have any property to sell!!!\n");
						break;
					}
					else
					{
						printf("\n");
						my_properties(current_player, board);
						printf("----------------------------\n");
						printf("enter property code to sell->");/*we take the property code which will be displayed*/
						scanf("%d",&y);
						for (i=0; i<12;i++)
						{
							if (current_player->owned_block_ids[i]==y)/*if it's a valid code then we proceed*/
							{
								temp=position(board,y);
								current_player->account+=(temp->price/2);
								current_player->account+=((temp->house_count*temp->house_price)/2);
								temp->house_count=0;
								current_player->owned_block_ids[i]=-1;/*we set the value to -1 to make sure that property is selled */
								printf("property selled\n");
								found=1;
								break;
							}
						}
						if (found==0)
						{
							printf("invalid choice!!!\n");
						}
						break;
					}
					
			case 0:
					break;
			default: 
					printf("\ninvalid choice\n");
					printf("---------------\n");
					break;
		}
	}		

}
int balance_control(struct block *board, struct player *current_player,int tax)/*this function handles all transaction related problem for user player*/
{																				/*the procedure is alike to balance control for computer*/
	int choice,flag;

	while (current_player->account<tax && property_count(current_player)!=0)
	{
		printf("\n%s need more %d$ to pay\n",current_player->name, tax-current_player->account);
		printf("---------------------------\n");
		printf("1.show my properties\n");
		printf("2.show my account\n");
		printf("3.sell_property\n");
		printf("0.exit\n");
		printf("enter your choice:");
		scanf(" %d",&choice);
		switch(choice)
		{
			case 1:
				my_properties(current_player,board);
				break;
			case 2:
				printf("your current account balance is:%d\n\n",current_player->account);
				break;
			case 3:
				sell_property(board,current_player);
				break;
			case 0:
				if (current_player->account<tax && property_count(current_player)==1)
				{
					break;
				}
				else if (current_player->account>tax)
				{
					flag=1;
					return flag;
					break;
				}
				else if (current_player->account<tax && property_count(current_player)==0)
				{
					flag=0;
					return flag;
					break;
				}
				break;
			default:
				printf("invalid choice!!!\n");
				break;

		}
	}
}
double price_of_all_property(struct block *board)/*this function will return the average of the all the properties available in this game*/
{
	int count=0,sum=0;
	board=head;
	while(board->next!=NULL)
	{
		if(board->type==property)
		{
			sum+=board->price;
			count++;
		}
		board=board->next;
	}
	return(sum/count);
	
}
int fortune_card(struct block *board,struct player *current_player,struct player *opponent)/*this function is for handling the fortune card for user player*/
{
	int random,select,dice,flag;
	random=rand()%(5-1+1)+1;/*we randomly picks a card for the user player*/
	printf("\n\n\tfortune deck\n");
	printf("\t-------------\n");
	if(random==1)/*if the card is 1 then we giva free house to the user*/
	{
		printf("you unlocked free house\n");
		if(property_count(current_player)==0)/*if user has no property then he can't use the card*/
		{
			printf("you don't have any property.unfortunately you can't use this fortune card\n");
		}
		else/*if the user has a property */
		{
			my_properties(current_player,board);
			printf("select a property from above to build a house for free:");/*we ask the user to select a property*/
			scanf("%d",&select);
			{
				board=position(board,select);/*we set the position to that block*/
				board->house_count+=1;/*and add a house to the user*/
			}
		}
		return 0;
	}
	else if(random==2)/*if random number is 2 then */
	{
		printf("you unlocked time travel\n");
		dice=rand()%(6-1+1)+1;/*we roll the dice */
		if (dice>=1 && dice<=3)/*if the dice is between 1-3 then user goes two block forward*/
		{
			current_player->current_block_id+=2;
			printf("travelling two block forward\n");

		}
		else/*else the user goes two block backward*/
		{
			current_player->current_block_id-=2;
			printf("travelling two block backward\n");

		}
		return 0;
	}
	else if(random==3)/*if the random number is 3 then the card is garishment and pays 5000 to the bank*/
	{
		printf("you unlocked garnishment\n");
		if(current_player->account<5000)/*if the user has not enough money to pay to the bank*/
		{
			printf("you don't have enough balance to pay to the bank. !!!\n");
			flag=balance_control(board,current_player,5000);/*we call the balance control func and save it's return value*/
			if (flag==1)/*if the return value if 1 that means he has enough money to pay the debt now */
			{
				current_player->account-=5000;/*so pays off the debt*/
				return 0;/*and we return 0*/
			}
			else/*but if he failed to pay the debt then we return 1*/
				return 1;
		}
		else/*if he already has enough money then he simply pays off the debt*/
		{
			current_player->account-=5000;
			printf("you paid 5000$ to the bank\n");
			return 0;
		}
		
	}
	else if(random==4)/*if random number is 4 then user should pay 10000 to his opponent*/
	{
		printf("you unlocked generosity\n");
		if(current_player->account<10000)/*if he has shortage of money then we call balance control*/
		{
			printf("you don't have enough balance to pay to your opponent.!!!\n");
			flag=balance_control(board,current_player,10000);
			if (flag==1)/*after controling balance if he manage to have enough money to pay the debt */
			{
				current_player->account-=10000;/*we cut the deu monet*/
				printf("10000$ added to computer's account\n");
				return 0;
			}
			else/*but if he fails then we return 1*/
				return 1;
		}
		else/*if he already has enough money then he simply pays off the debt*/
		{
			current_player->account-=10000;
			opponent->account+=10000;
			printf("10000$ added to computer's account\n");
			return 0;
		}
	}
	else if(random==5)/*if the random number is 5 then he gets 20000 from the bank*/
	{
		printf("you unlocked tressure hunter\n");
		current_player->account+=20000;
		printf("you got 20000$ from bank\n");
		return 0;
	}
}
/*fortune card for computer does the same job like fortune card but this time it's for computer and logic is the same*/
int fortune_card_for_computer(struct block *board,struct player *current_player,struct player *opponent)
{
	int random,select,dice,i,flag;
	random=rand()%(5-1+1)+1;
	printf("\n\n\tfortune deck\n");
	printf("\t-------------\n");
	if(random==1)
	{
		printf("computer unlocked free house\n");
		if(property_count(current_player)!=0)
		{
			for(i=0; i<12;i++)
			{
				if(current_player->owned_block_ids[i]!=-1)
				{
					board=position(board,current_player->owned_block_ids[i]);
					if(board->house_count<3)
					{
						board->house_count+=1;
						printf("computer built a house on %s for free using fortune card\n",board->block_name);
						return 0;
					}
				}
			}
			
		}
		return 0;
	}
	else if(random==2)
	{
		printf("computer unlocked time travel\n");
		dice=rand()%(6-1+1)+1;
		if (dice>=1 && dice<=3)
		{
			current_player->current_block_id+=2;
			printf("computer travelled two block forward\n");
		}
		else
		{
			current_player->current_block_id-=2;
			printf("computer travelled  two block backward\n");

		}
		return 0;
	}
	else if(random==3)
	{
		printf("computer unlocked garnishment\n");
		if(current_player->account<5000)
		{
			flag=balance_control_for_computer(board,current_player,5000);
			if (flag==1)
			{
				current_player->account-=5000;
				return 0;
			}
			else
				return 1;
		}
		else
		{
			current_player->account-=5000;
			printf("computer paid 5000$ to the bank\n");
			return 0;
		}
		
	}
	else if(random==4)
	{
		printf("computer unlocked generosity\n");
		if(current_player->account<10000)
		{
			flag=balance_control_for_computer(board,current_player,10000);
			if (flag==1)
			{
				current_player->account-=5000;
				return 0;
			}
			else
				return 1;
		}
		else
		{
			current_player->account-=10000;
			opponent->account+=10000;
			printf("10000$ added to car's account\n");
			return 0;
		}
		
	}
	else if(random==5)
	{
		printf("computer unlocked tressure hunter\n");
		current_player->account+=20000;
		printf("computer got 20000$ from bank\n");
		return 0;
	}	
}