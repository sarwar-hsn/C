#include <stdio.h>
#include <stdlib.h>
#include <time.h>
/*defining moves*/
#define up 8
#define down 2
#define right 6
#define left 4
/*declaring eunmurtation type*/
typedef enum 
{
  Charmander,Pikachu,Squirtle,Bulbasaur,Pidgeotto,Ratata,Mug,Caterpie,Zubat,Krabby
}pokemon;
typedef enum 
{
  linear,quadratic
}attack_type;
/*function protype*/
void main_menu();
void lab_menu();
int compare_strings();
void pokedex();
void oaks_laboratory();
void show_area ();
void battle();
void show_Pokemons();
void catch_a_pokemon();
void release_a_pokemon();

int main()
{
  char Pokemon_name[10][11]={"Charmander","Pikachu","Squirtle","Bulbasaur","Pidgeotto","Ratata","Mug","Caterpie","Zubat","Krabby"};/*charecter array hold the pokemon name*/
  int range[10],attack_power[10], stamina[10],choice;
  attack_type type[10];/*array for attack type*/
  pokemon pokemons[10];
  /*filling initial array values*/
  pokemons[0]=Charmander;pokemons[1]=Pikachu;pokemons[2]=Squirtle;pokemons[3]=Bulbasaur;pokemons[4]=Pidgeotto;pokemons[5]=Ratata;pokemons[6]=Mug;pokemons[7]=Caterpie;pokemons[8]=Zubat;pokemons[9]=Krabby;
  type[Charmander]=quadratic;type[Pikachu]=linear;type[Squirtle]=linear;type[Bulbasaur]=linear; type[Pidgeotto]=quadratic;type[Ratata]=linear;type[Mug]=quadratic; type[Caterpie]=quadratic;type[Zubat]=linear;type[Krabby]=linear;/*attack types for related pokemon*/
  type[Charmander]=quadratic;type[Pikachu]=linear; type[Squirtle]=linear;type[Bulbasaur]=linear;
  range[Charmander]=1;range[Pikachu]=3; range[Squirtle]=4; range[Bulbasaur]=3;range[Pidgeotto]=2;range[Ratata]=2; range[Mug]=1; range[Caterpie]=2; range[Zubat]=3; range[Krabby]=2;/*attack range for related pokemons*/
  attack_power[Charmander]=500;attack_power[Pikachu]=350; attack_power[Squirtle]=300; attack_power[Bulbasaur]=400;attack_power[Pidgeotto]=250;attack_power[Ratata]=250; attack_power[Mug]=350; attack_power[Caterpie]=200; attack_power[Zubat]=350; attack_power[Krabby]=300;/*attack power for related pokemons*/
  stamina[Charmander]=2200;stamina[Pikachu]=1500; stamina[Squirtle]=1700; stamina[Bulbasaur]=2500;stamina[Pidgeotto]=1900;stamina[Ratata]=2500; stamina[Mug]=3000; stamina[Caterpie]=1200; stamina[Zubat]=1250; stamina[Krabby]=2600;/*stamina for related pokemons*/
  main_menu();
  pokemon user_Pokemons[4];
  /*assigning user pokemon with -1*/
  user_Pokemons[0]=-1;
  user_Pokemons[1]=-1;
  user_Pokemons[2]=-1;
  user_Pokemons[3]=-1;
  int i,j;
  while (choice!=4)/*condition to exit from main menu*/
  {

    printf("enter your choice: ");
    scanf("%d",&choice);
    switch (choice)
    {
      case 1:
          pokedex(Pokemon_name,range,type,attack_power,stamina);/*function call to pokedox function*/
          break;
      case 2:
          oaks_laboratory(Pokemon_name,pokemons,user_Pokemons);/*function call to oaks laboratory*/
          break;
      case 3:
          for(i=0; i<4;i++)
          {
            if(user_Pokemons[i]==-1)/*condition to check if user has 4 pokemon in his pocket*/
            {
              printf("not enough pokemon to battle!!!\n");
              break;
            }
            else
            {
              battle(Pokemon_name,range,type,attack_power,stamina,user_Pokemons);
              break;
            }
            
          }   
      case 4:
          break;
      default:
          printf("!!!invalid input\n");
    }
    main_menu();
  }
}
void battle(char Pokemon_name[10][11], int range[10], attack_type type[10], int attack_power[10], int stamina[10], pokemon user_Pokemons[4])/*battle function*/
{
  int area[8][8],pokemon_staminas_view[8][8], a,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p,q,r,pokemon_code,move,x,y,array[4],ai_array[4],hasDuplicate;
  srand(time(NULL));
 
    for(i=0;i<4;i++)/*filling array with random number for columns of ai pokemon*/
    {
        array[i] = rand() % 7;
        hasDuplicate = 0;
 
        for(j=0; j<=(i-1); j++)
            {
                if (array[i] == array[j])
                {
                    hasDuplicate = 1;
                    i--;
                }
 
            }
    }
    for(i=0;i<4;i++)/*filling array for ai pokemons*/
    {
        ai_array[i] = rand() % (4-0+1)+0;
        hasDuplicate = 0;
 
        for(j=0; j<=(i-1); j++)
            {
                if (ai_array[i] == ai_array[j])
                {
                    hasDuplicate = 1;
                    i--;
                }
 
            }
    }
  pokemon ai_pokemon[4];
  /*assigning values to ai pokemon*/
  ai_pokemon[0]=ai_array[0];
  ai_pokemon[1]=ai_array[1];
  ai_pokemon[2]=ai_array[2];
  ai_pokemon[3]=ai_array[3];
  /*taking cordinates for user pokemon*/
    printf("enter x and y co-ordinate for %s\n",Pokemon_name[user_Pokemons[0]]);
    scanf("%d %d",&a,&b);
    if (a<0 || a>1 || b<0 || b>7)
    {
      printf("invalid input\n");
      return;
    }
    printf("enter x and y co-ordinate for %s\n",Pokemon_name[user_Pokemons[1]]);
    scanf("%d %d",&c,&d);
    if (c<0 || c>2 || d<0 || d>7)
    {
      printf("invalid input\n");
      return;
    }
    printf("enter x and y co-ordinate for %s\n",Pokemon_name[user_Pokemons[2]]);
    scanf("%d %d",&e,&f);
    if (e<0 || e>2 || f<0 || f>7)
    {
      printf("invalid input\n");
      return;
    }
    printf("enter x and y co-ordinate for %s\n",Pokemon_name[user_Pokemons[3]]);
    scanf("%d %d",&g,&h);
    if (g<0 || g>2 || h<0 || h>7)
    {
      printf("invalid input\n");
      return;
    }
    /*assigning random values for ai pokemon*/
  	  k=rand()%(7-6+1)+6;
	  l=array[0];
	  m=rand()%(7-6+1)+6;
	  n=array[1];
	  o=rand()%(7-6+1)+6;
	  p=array[2];
	  q=rand()%(7-6+1)+6;
	  r=array[3];
    for (i=0; i<8; i++)
    {
      for (j=0; j<8; j++)
      {
        area[i][j]=-1;
        pokemon_staminas_view[i][j]=-1;
      }
    }
    /*assigning stamina to user pokemons*/
    pokemon_staminas_view[a][b]=stamina[user_Pokemons[0]];
    pokemon_staminas_view[c][d]=stamina[user_Pokemons[1]];
    pokemon_staminas_view[e][f]=stamina[user_Pokemons[2]];
    pokemon_staminas_view[g][h]=stamina[user_Pokemons[3]];
    /*assigning area values for user pokemon*/
    area[a][b]=user_Pokemons[0];
    area[c][d]=user_Pokemons[1];
    area[e][f]=user_Pokemons[2];
    area[g][h]=user_Pokemons[3];
    /*assinging stamina for ai pokemon*/
    pokemon_staminas_view[k][l]=stamina[ai_pokemon[0]];
    pokemon_staminas_view[m][n]=stamina[ai_pokemon[1]];
    pokemon_staminas_view[o][p]=stamina[ai_pokemon[2]];
    pokemon_staminas_view[q][r]=stamina[ai_pokemon[3]];
    /*assigning area for ai pokemon*/
    area[k][l]=ai_pokemon[0];
    area[m][n]=ai_pokemon[1];
    area[o][p]=ai_pokemon[2];
    area[q][r]=ai_pokemon[3];
    while(1)
    {

    show_area(Pokemon_name,area,pokemon_staminas_view);/*function call to show area function*/
    printf("enter pokemon code(0)%.2s(1)%.2s(2)%.2s(3)%.2s->",Pokemon_name[user_Pokemons[0]],Pokemon_name[user_Pokemons[1]],Pokemon_name[user_Pokemons[2]],Pokemon_name[user_Pokemons[3]]);
    scanf("%d",&pokemon_code);
  
	      if(pokemon_code==0)/*if user selects his first pokemon*/
	      {
	          area[a][b]=-1;
	          pokemon_staminas_view[a][b]=-1;
	          printf("you selected %s.(2.down 4.left 6.right 8.up)move->",Pokemon_name[user_Pokemons[pokemon_code]] );
	          scanf("%d",&move);
				if(move==right)/*condition for moving right */
				{
					b=b+1;
					if(area[a][b]!=-1 || a<0 || a>7 || b<0 || b>7)
					{
					printf("INVALID MOVE!!! AI'S TURN\n");
					b=b-1;
					area[a][b]=user_Pokemons[0];
					pokemon_staminas_view[a][b]=stamina[user_Pokemons[0]];
					}

					else
					{
						area[a][b]=user_Pokemons[pokemon_code];
						pokemon_staminas_view[a][b]=stamina[user_Pokemons[pokemon_code]];
					}  
				}
	          if(move==down)/*condition for moving down*/
	          {
	          		a=a+1;
	              if(area[a][b]!=-1 || a<0 || a>7 || b<0 || b>7)
	                {
						printf("INVALID MOVE!!! AI'S TURN\n");
						a=a-1;
						area[a][b]=user_Pokemons[0];
						 pokemon_staminas_view[a][b]=stamina[user_Pokemons[0]];
	                }

	              else
	              {
	                area[a][b]=user_Pokemons[pokemon_code];
	                pokemon_staminas_view[a][b]=stamina[user_Pokemons[pokemon_code]];
	               
	              }  
	          }
	          if(move==left)/*condition for moving left*/
	          {
	          		b=b-1;
	              if(area[a][b]!=-1 || a<0 || a>7 || b<0 || b>7)
	                {
		                printf("INVALID MOVE!!! AI'S TURN\n");
		                b=b+1;
		                area[a][b]=user_Pokemons[0];
						 pokemon_staminas_view[a][b]=stamina[user_Pokemons[0]];
	                }

	              else
	              {
	                area[a][b]=user_Pokemons[pokemon_code];
	                pokemon_staminas_view[a][b]=stamina[user_Pokemons[pokemon_code]];
	               
	              }  
	          }
	          if(move==up)/*condition for moving up*/
	          {
	          		a=a-1;
	              if(area[a][b]!=-1 || a<0 || a>7 || b<0 || b>7)
	                {
						printf("INVALID MOVE!!! AI'S TURN\n");
						a=a+1;
						area[a][b]=user_Pokemons[0];
						 pokemon_staminas_view[a][b]=stamina[user_Pokemons[0]];
	                }

	              else
	              {
	                area[a][b]=user_Pokemons[pokemon_code];
	                pokemon_staminas_view[a][b]=stamina[user_Pokemons[pokemon_code]];
	               
	              }  
	          }

	      }
		/*conditions for user pokemon two*/
	      else if(pokemon_code==1)
	      {
	          area[c][d]=-1;
	          pokemon_staminas_view[c][d]=-1;
	          printf("you selected %s.(2.down 4.left 6.right 8.up)move->",Pokemon_name[user_Pokemons[pokemon_code]] );
	          scanf("%d",&move);
	          if(move==right)
	          {
	          		d=d+1;
	              if(area[c][d]!=-1 || c<0 || c>7 || d<0 || d>7)
	                {
						printf("INVALID MOVE!!! AI'S TURN\n");
						d=d-1;
						area[c][d]=user_Pokemons[1];
						pokemon_staminas_view[c][d]=stamina[user_Pokemons[1]];
	                }

	              else
	              {
	                area[c][d]=user_Pokemons[pokemon_code];
	                pokemon_staminas_view[c][d]=stamina[user_Pokemons[pokemon_code]];
	                
	              }  
	          }
	          if(move==down)
	          {
	          		c=c+1;
	              if(area[c][d]!=-1 || c<0 || c>7 || d<0 || d>7)
	                {
						printf("INVALID MOVE!!! AI'S TURN\n");
						c=c-1;
						area[c][d]=user_Pokemons[1];
						pokemon_staminas_view[c][d]=stamina[user_Pokemons[1]];
	                }

	              else
	              {
	                area[c][d]=user_Pokemons[pokemon_code];
	                pokemon_staminas_view[c][d]=stamina[user_Pokemons[pokemon_code]];
	                
	              }  
	          }
	          if(move==left)
	          {
	          		d=d-1;
	              if(area[c][d]!=-1 || c<0 || c>7 || d<0 || d>7)
	                {
						printf("INVALID MOVE!!! AI'S TURN\n");
						d=d+1;
						area[c][d]=user_Pokemons[1];
						pokemon_staminas_view[c][d]=stamina[user_Pokemons[1]];
	                }

	              else
	              {
	                area[c][d]=user_Pokemons[pokemon_code];
	                pokemon_staminas_view[c][d]=stamina[user_Pokemons[pokemon_code]];
	                
	              }  
	          }
	          if(move==up)
	          {
	          		c=c-1;
	              if(area[c][d]!=-1 || c<0 || c>7 || d<0 || d>7 )
	                {
						printf("INVALID MOVE!!! AI'S TURN\n");
						c=c+1;
						area[c][d]=user_Pokemons[1];
						pokemon_staminas_view[c][d]=stamina[user_Pokemons[1]];
	                }
	              else
	              {
	                area[c][d]=user_Pokemons[pokemon_code];
	                pokemon_staminas_view[c][d]=stamina[user_Pokemons[pokemon_code]];
	                
	              }  
	          }

	      }
	      /*condition for third pokemon*/
	      else if(pokemon_code==2)
	      {
	          area[e][f]=-1;
	          pokemon_staminas_view[e][f]=-1;
	          printf("you selected %s.(2.down 4.left 6.right 8.up)move->",Pokemon_name[user_Pokemons[pokemon_code]] );
	          scanf("%d",&move);
	          if(move==right)
	          {
	          		f=f+1;
	              if(area[e][f]!=-1 || e<0 || e>7 || f<0 || f>7)
	                {
						printf("INVALID MOVE!!! AI'S TURN\n");
						f=f-1;
						area[e][f]=user_Pokemons[2];
						pokemon_staminas_view[e][f]=stamina[user_Pokemons[2]];
	                }

	              else
	              {
	                area[e][f]=user_Pokemons[pokemon_code];
	                pokemon_staminas_view[e][f]=stamina[user_Pokemons[pokemon_code]];
	               
	              }  
	          }
	          if(move==down)
	          {
	          		e=e+1;
	              if(area[e][f]!=-1 || e<0 || e>7 || f<0 || f>7)
	                {
						printf("INVALID MOVE!!! AI'S TURN\n");
						e=e-1;
						area[e][f]=user_Pokemons[2];
						pokemon_staminas_view[e][f]=stamina[user_Pokemons[2]];
	                }

	              else
	              {
	                area[e][f]=user_Pokemons[pokemon_code];
	                pokemon_staminas_view[e][f]=stamina[user_Pokemons[pokemon_code]];
	               
	              }  
	          }
	          if(move==left)
	          {
	          		f=f-1;
	              if(area[e][f]!=-1 || e<0 || e>7 || f<0 || f>7)
	                {
						printf("INVALID MOVE!!! AI'S TURN\n");
						f=f+1;
						area[e][f]=user_Pokemons[2];
						pokemon_staminas_view[e][f]=stamina[user_Pokemons[1]];
	                }

	              else
	              {
	                area[e][f]=user_Pokemons[pokemon_code];
	                pokemon_staminas_view[e][f]=stamina[user_Pokemons[pokemon_code]];
	               
	              }  
	          }
	          if(move==up)
	          {
	          		e=e-1;
	              if(area[e][f]!=-1 || e<0 || e>7 || e<0 || e>7 )
	                {
						printf("INVALID MOVE!!! AI'S TURN\n");
						e=e+1;
						area[e][f]=user_Pokemons[2];
						pokemon_staminas_view[c][d]=stamina[user_Pokemons[2]];
	                }
	              else
	              {
	                area[e][f]=user_Pokemons[pokemon_code];
	                pokemon_staminas_view[e][f]=stamina[user_Pokemons[pokemon_code]];
	                
	              }  
	          }

	      }

	    /*condition for fourth pokemon*/

	    else if(pokemon_code==3)
	      {
	          area[g][h]=-1;
	          pokemon_staminas_view[g][h]=-1;
	          printf("you selected %s.(2.down 4.left 6.right 8.up)move->",Pokemon_name[user_Pokemons[pokemon_code]] );
	          scanf("%d",&move);
	          if(move==right)
	          {
	          		h=h+1;
	              if(area[g][h]!=-1 || g<0 || g>7 || h<0 || h>7)
	                {
						printf("INVALID MOVE!!! AI'S TURN\n");
						h=h-1;
						area[g][h]=user_Pokemons[3];
						pokemon_staminas_view[g][h]=stamina[user_Pokemons[3]];
	                }

	              else
	              {
	                area[g][h]=user_Pokemons[pokemon_code];
	                pokemon_staminas_view[g][h]=stamina[user_Pokemons[pokemon_code]];
	               
	              }  
	          }
	          if(move==left)
	          {
	          		h=h-1;
	              if(area[g][h]!=-1 || g<0 || g>7 || h<0 || h>7)
	                {
						printf("INVALID MOVE!!! AI'S TURN\n");
						h=h+1;
						area[g][h]=user_Pokemons[3];
						pokemon_staminas_view[g][h]=stamina[user_Pokemons[3]];
	                }

	              else
	              {
	                area[g][h]=user_Pokemons[pokemon_code];
	                pokemon_staminas_view[g][h]=stamina[user_Pokemons[pokemon_code]];
	                
	              }  
	          }
	          if(move==down)
	          {
	          		g=g+1;
	              if(area[g][h]!=-1 || g<0 || g>7 || h<0 || h>7)
	                {
						printf("INVALID MOVE!!! AI'S TURN\n");
						g=g-1;
						area[g][h]=user_Pokemons[3];
						pokemon_staminas_view[g][h]=stamina[user_Pokemons[3]];
	                }

	              else
	              {
	                area[g][h]=user_Pokemons[pokemon_code];
	                pokemon_staminas_view[g][h]=stamina[user_Pokemons[pokemon_code]];
	               
	              }  
	          }

	          if(move==up)
	          {
	          		g=g-1;
	              if(area[g][h]!=-1 || g<0 || g>7 || h<0 || h>7)
	                {
						printf("INVALID MOVE!!! AI'S TURN\n");
						g=g+1;
						area[g][h]=user_Pokemons[3];
						pokemon_staminas_view[g][h]=stamina[user_Pokemons[3]];
	                }
	              else
	              {
	                area[g][h]=user_Pokemons[pokemon_code];
	                pokemon_staminas_view[g][h]=stamina[user_Pokemons[pokemon_code]];
	                
	              }  
	          }
	      }

	    pokemon_code=rand()%(3-0+1)+0;/*ai randomly selects a pokemon*/
 		printf("AI PLAYED %s\n",Pokemon_name[ai_pokemon[pokemon_code]] );
 		move=rand()%(8-2+1)+2;/*ai randomly selects a move*/
 		if (move==3)
 			move=move-1;
 		if (move==5)
 			move=move-1;
 		if(move==7)
 			move=move+1;
 		/*if ai selects pokemon in zero index then it's move condition*/
	   	 if(pokemon_code==0)
	      {
	          area[k][l]=-1;
	          pokemon_staminas_view[k][l]=-1;
	         
	          if(move==right)
	          {
	          		l=l+1;
	              if(area[k][l]!=-1 || k<0 || k>7 || l<0 || l>7)
	                {
						printf("INVALID MOVE BY AI!!! YOUR TURN\n\n");
						l=l-1;
						area[k][l]=ai_pokemon[pokemon_code];
						pokemon_staminas_view[k][l]=stamina[ai_pokemon[pokemon_code]];
	                }

	              else
	              {
	                area[k][l]=ai_pokemon[pokemon_code];
	                pokemon_staminas_view[k][l]=stamina[ai_pokemon[pokemon_code]];
	                
	              }  
	          }
	          if(move==down)
	          {
	          		k=k+1;
	              if(area[k][l]!=-1 || k<0 || k>7 || l<0 || l>7)
	                {
						printf("INVALID MOVE BY AI!!! YOUR TURN\n\n");
						k=k-1;
						area[k][l]=ai_pokemon[pokemon_code];
						 pokemon_staminas_view[k][l]=stamina[ai_pokemon[pokemon_code]];
	                }

	              else
	              {
	                area[k][l]=ai_pokemon[pokemon_code];
	                pokemon_staminas_view[k][l]=stamina[ai_pokemon[pokemon_code]];
	               
	              }  
	          }
	          if(move==left)
	          {
	          		l=l-1;
	              if(area[k][l]!=-1 || k<0 || k>7 || l<0 || l>7)
	                {
		               printf("INVALID MOVE BY AI!!! YOUR TURN\n\n");
		                l=l+1;
		                area[k][l]=ai_pokemon[pokemon_code];
						pokemon_staminas_view[k][l]=stamina[ai_pokemon[pokemon_code]];
	                }

	              else
	              {
	                area[k][l]=ai_pokemon[pokemon_code];
	                pokemon_staminas_view[k][l]=stamina[ai_pokemon[pokemon_code]];
	               
	              }  
	          }
	          if(move==up)
	          {
	          		k=k-1;
	              if(area[k][l]!=-1 || k<0 || k>7 || l<0 || l>7)
	                {
						printf("INVALID MOVE BY AI!!! YOUR TURN\n\n");
						k=k+1;
						area[k][l]=ai_pokemon[pokemon_code];
						 pokemon_staminas_view[k][l]=stamina[ai_pokemon[pokemon_code]];
	                }

	              else
	              {
	                area[k][l]=ai_pokemon[pokemon_code];
	                pokemon_staminas_view[k][l]=stamina[ai_pokemon[pokemon_code]];
	               
	              }  
	          }
	      }
		/*if ai selects pokemon in first index then it's move condition*/
	   	 else if(pokemon_code==1)
	      {
	          area[m][n]=-1;
	          pokemon_staminas_view[m][n]=-1;
	          if(move==right)
	          {
	          		n=n+1;
	              if(area[m][n]!=-1 || m<0 || m>7 || n<0 || n>7)
	                {
						printf("INVALID MOVE BY AI!!! YOUR TURN\n\n");
						n=n-1;
						area[m][n]=ai_pokemon[pokemon_code];
						pokemon_staminas_view[m][n]=stamina[ai_pokemon[pokemon_code]];
	                }

	              else
	              {
	                area[m][n]=ai_pokemon[pokemon_code];
	                pokemon_staminas_view[m][n]=stamina[ai_pokemon[pokemon_code]];
	               
	              }  
	          }
	          if(move==down)
	          {
	          		m=m+1;
	              if(area[m][n]!=-1 || m<0 || m>7 || n<0 || n>7)
	                {
						printf("INVALID MOVE BY AI!!! YOUR TURN\n\n");
						m=m-1;
						area[m][n]=ai_pokemon[pokemon_code];
						 pokemon_staminas_view[k][l]=stamina[ai_pokemon[pokemon_code]];
	                }

	              else
	              {
	                area[m][n]=ai_pokemon[pokemon_code];
	                pokemon_staminas_view[m][n]=stamina[ai_pokemon[pokemon_code]];
	               
	              }  
	          }
	          if(move==left)
	          {
	          		n=n-1;
	              if(area[m][n]!=-1 || m<0 || m>7 || n<0 || n>7)
	                {
		                printf("INVALID MOVE BY AI!!! YOUR TURN\n\n");
		                n=n+1;
		                area[m][n]=ai_pokemon[pokemon_code];
						 pokemon_staminas_view[m][n]=stamina[ai_pokemon[pokemon_code]];
	                }

	              else
	              {
	                area[m][n]=ai_pokemon[pokemon_code];
	                pokemon_staminas_view[m][n]=stamina[ai_pokemon[pokemon_code]];
	               
	              }  
	          }
	          if(move==up)
	          {
	          		m=m-1;
	              if(area[m][n]!=-1 || m<0 || m>7 || n<0 || n>7)
	                {
						printf("INVALID MOVE BY AI!!! YOUR TURN\n\n");
						m=m+1;
						area[m][n]=ai_pokemon[pokemon_code];
						 pokemon_staminas_view[m][n]=stamina[ai_pokemon[pokemon_code]];
	                }

	              else
	              {
	                area[m][n]=ai_pokemon[pokemon_code];
	                pokemon_staminas_view[m][n]=stamina[ai_pokemon[pokemon_code]];
	               
	              }  
	          }
	      }
	      /*if user selects pokemon in second index then it's move condition*/
	      else if(pokemon_code==2)
	      {
	          area[o][p]=-1;
	          pokemon_staminas_view[o][p]=-1;
	          if(move==right)
	          {
	          		p=p+1;
	              if(area[o][p]!=-1 || o<0 || o>7 || p<0 || p>7)
	                {
						printf("INVALID MOVE BY AI!!! YOUR TURN\n\n");
						p=p-1;
						area[o][p]=ai_pokemon[pokemon_code];
						pokemon_staminas_view[o][p]=stamina[ai_pokemon[pokemon_code]];
	                }

	              else
	              {
	                area[o][p]=ai_pokemon[pokemon_code];
	                pokemon_staminas_view[o][p]=stamina[ai_pokemon[pokemon_code]];
	               
	              }  
	          }
	          if(move==down)
	          {
	          		o=o+1;
	              if(area[o][p]!=-1 || o<0 || o>7 || p<0 || p>7)
	                {
						printf("INVALID MOVE BY AI!!! YOUR TURN\n\n");
						o=o-1;
						area[o][p]=ai_pokemon[pokemon_code];
						pokemon_staminas_view[o][p]=stamina[ai_pokemon[pokemon_code]];
	                }

	              else
	              {
	                area[o][p]=ai_pokemon[pokemon_code];
	                pokemon_staminas_view[o][p]=stamina[ai_pokemon[pokemon_code]];
	               
	              }  
	          }
	          if(move==left)
	          {
	          		p=p-1;
	              if(area[o][p]!=-1 || o<0 || o>7 || p<0 || p>7)
	                {
						printf("INVALID MOVE BY AI!!! YOUR TURN\n\n");
						p=p+1;
						area[o][p]=ai_pokemon[pokemon_code];
						pokemon_staminas_view[o][p]=stamina[ai_pokemon[pokemon_code]];
	                }

	              else
	              {
	                area[o][p]=ai_pokemon[pokemon_code];
	                pokemon_staminas_view[o][p]=stamina[ai_pokemon[pokemon_code]];
	                
	              }  
	          }
	          if(move==up)
	          {
	          		o=o-1;
	              if(area[o][p]!=-1 || o<0 || o>7 || p<0 || p>7)
	                {
						printf("INVALID MOVE BY AI!!! YOUR TURN\n\n");
						o=o+1;
						area[o][p]=ai_pokemon[pokemon_code];
						pokemon_staminas_view[o][p]=stamina[ai_pokemon[pokemon_code]];
	                }
	              else
	              {
	                area[o][p]=ai_pokemon[pokemon_code];
	                pokemon_staminas_view[o][p]=stamina[ai_pokemon[pokemon_code]];
	                
	              }  
	          }
	      }
	    /*if user selects pokemon in first index then it's move condition*/
	    else if(pokemon_code==3)
	      {
	          area[q][r]=-1;
	          pokemon_staminas_view[q][r]=-1;
	          if(move==right)
	          {
	          		r=r+1;
	              if(area[q][r]!=-1 || q<0 || q>7 || r<0 || r>7)
	                {
						printf("INVALID MOVE BY AI!!! YOUR TURN\n\n");
						r=r-1;
						area[q][r]=ai_pokemon[pokemon_code];
						pokemon_staminas_view[g][h]=stamina[ai_pokemon[pokemon_code]];
	                }

	              else
	              {
	                area[q][r]=ai_pokemon[pokemon_code];
	                pokemon_staminas_view[q][r]=stamina[ai_pokemon[pokemon_code]];
	               
	              }  
	          }
	          if(move==down)
	          {
	          		q=q+1;
	              if(area[q][r]!=-1 || q<0 || q>7 || r<0 || r>7)
	                {
						printf("INVALID MOVE BY AI!!! YOUR TURN\n\n");
						q=q-1;
						area[q][r]=ai_pokemon[pokemon_code];
						pokemon_staminas_view[q][r]=stamina[ai_pokemon[pokemon_code]];
	                }

	              else
	              {
	                area[q][r]=ai_pokemon[pokemon_code];
	                pokemon_staminas_view[q][r]=stamina[ai_pokemon[pokemon_code]];
	              
	              }  
	          }
	          if(move==left)
	          {
	          		r=r-1;
	              if(area[q][r]!=-1 || q<0 || q>7 || r<0 || r>7)
	                {
						printf("INVALID MOVE BY AI!!! YOUR TURN\n\n");
						r=r+1;
						area[q][r]=ai_pokemon[pokemon_code];
						pokemon_staminas_view[q][r]=stamina[ai_pokemon[pokemon_code]];
	                }

	              else
	              {
	                area[q][r]=ai_pokemon[pokemon_code];
	                pokemon_staminas_view[q][r]=stamina[ai_pokemon[pokemon_code]];
	               
	              }  
	          }
	          if(move==up)
	          {
	          		q=q-1;
	              if(area[q][r]!=-1 || q<0 || q>7 || r<0 || r>7)
	                {
						printf("INVALID MOVE BY AI!!! YOUR TURN\n\n");
						q=q+1;
						area[q][r]=ai_pokemon[pokemon_code];
						pokemon_staminas_view[q][r]=stamina[ai_pokemon[pokemon_code]];
	                }
	              else
	              {
	                area[q][r]=ai_pokemon[pokemon_code];
	                pokemon_staminas_view[q][r]=stamina[ai_pokemon[pokemon_code]];
	             
	              }  
	          }
	      }
    }
  }

void show_area (char Pokemon_name[10][11],int area[8][8],int pokemon_staminas_view[8][8])/*function to print the  current condtion of battle function*/
{
  int i,j,k,l;
  printf("*********************************************************************************************************************************\n");
  for (i=0; i<8; i++)
  {

    for (j=0; j<=8; j++)
    {
      if(j==8)
      {
        printf("|\n|\t\t|\t\t|\t\t|\t\t|\t\t|\t\t|\t\t|\t\t");
        printf("|\n*********************************************************************************************************************************");
      }
      else
      {
          if (pokemon_staminas_view[i][j]!=-1)/*if we don't find -1 that means there is a pokemon so we print it*/
          {
            printf("|\t%d %.2s\t",pokemon_staminas_view[i][j],Pokemon_name[area[i][j]]);
          }
          else
          {
                  printf("|\t\t");
          }
      }
    }
    printf("\n");
  }
}

void oaks_laboratory(char *Pokemon_name[11],pokemon pokemons[10],pokemon my_Pokemons[4])/*oak's lab function*/
{
  int choice,pokemon_count,i,count=0;
  /*we initialize my pokemon array with -1*/
  my_Pokemons[0]=-1;
  my_Pokemons[1]=-1;
  my_Pokemons[2]=-1;
  my_Pokemons[3]=-1;
  pokemon pocket;
  lab_menu();
  while(choice!=5)/*condtion to exit from oak's lab*/
  {

    printf("enter your choice:");
    scanf("%d",&choice);
    switch (choice)
    {
      case 1:
          pokemon_count=10;
          show_Pokemons(Pokemon_name,pokemons,pokemon_count);/*function call to show pokemon function*/
          break;
      case 2:
          if(count<=4)
          {
            if(count==4)/*if pocket is full then we can't select more pokemon*/
            {
              printf("!!!pocket is full !!!\n");
              break;
            }
            catch_a_pokemon(Pokemon_name,pokemons,&pocket);/*function call to catch a pokemon */
            if(pocket==-1)
            {
              printf("invalid choice!!!\n");
              break;
            }
            /*we assign the return value returned from catch a pokemon function to my pokemon function*/
            if(my_Pokemons[0]==-1)
            {
              my_Pokemons[0]=pocket;
              count++;
            }
            else if (my_Pokemons[1]==-1 )
            {
              if(pocket!=my_Pokemons[0])
              {
                my_Pokemons[1]=pocket;
                count++;
              }
              else
              {
                printf("!!!already in pocket !!!\n");
              }
            }
            else if(my_Pokemons[2]==-1)
            {
              if(pocket!=my_Pokemons[0] && pocket!=my_Pokemons[1] )
              {
                my_Pokemons[2]=pocket;
                count++;
              }
              else
              {
                printf("!!!already in pocket !!!\n");
              }
            }
            else if(my_Pokemons[3]==-1)
            {
              if(pocket!=my_Pokemons[0] && pocket!=my_Pokemons[1] && pocket!=my_Pokemons[2])
              {
                my_Pokemons[3]=pocket;
                count++;
              }
              else
              {
                printf("!!!already in pocket !!!\n");
              }
            }

          }
          break;
      case 3:
          if(count==0)/*if there is no pokemon to release*/
          {
            printf("!!!pocket is empty !!!\n");
            break;
          }
          else
          {
            printf("***pokemons you can remove***\n");
            show_Pokemons(Pokemon_name,my_Pokemons,count);/*function call to show pokemon function to list the pokemons we can remove*/
            release_a_pokemon(Pokemon_name,my_Pokemons,&pocket);/*function to release a pokemon*/
            /*we use the return value from release a pokemon function to rearrange the my pokemon function*/
            if(pocket==0 && my_Pokemons[0]!=-1)
            {
              my_Pokemons[0]=my_Pokemons[1];
              my_Pokemons[1]=my_Pokemons[2];
              my_Pokemons[2]=my_Pokemons[3];
              my_Pokemons[3]=-1;
              printf("pokemon remvoed!!!\n");
              count--;
            }
            else if(pocket==1 && my_Pokemons[1]!=-1)
            {
              my_Pokemons[1]=my_Pokemons[2];
              my_Pokemons[2]=my_Pokemons[3];
              my_Pokemons[3]=-1;
              printf("pokemon remvoed!!!\n");
              count--;
            }
            else if(pocket==2 && my_Pokemons[2]!=-1)
            {
              my_Pokemons[2]=my_Pokemons[3];
              my_Pokemons[3]=-1;
              printf("pokemon remvoed!!!\n");
              count--;
            }
            else if (pocket==3 && my_Pokemons[3]!=-1)
            {
              my_Pokemons[3]=-1;
              printf("pokemon remvoed!!!\n");
              count--;
            }
            else 
            {
              printf("!!!Invalid choice !!!\n");
              break;
            }
            
          }

          break;
      case 4:
          if(count==0)
            printf("!!!your pocket is empty !!!\n");
          else
          {
            printf("***pokemons you have***\n");
            show_Pokemons(Pokemon_name,my_Pokemons,count);/*function to show pokemon function to show what pokemons we have in our pocket*/
          }
          break;
      case 5:
          break;
      default: 
          printf("\ninvalid choice!!!\n");
    }
    lab_menu();

  }
}
void release_a_pokemon(char *Pokemon_name[11], pokemon Pokemons[10],pokemon *my_pocket)/*this function returns the pokemon that user wants to remove as pointer*/
{
  int count=4,choice;
  printf("enter pokemon code to release: ");
  scanf("%d",&choice);
  if(choice>=0 && choice<=3)
  {
    *my_pocket=choice;  

  }
  else 
    *my_pocket=-1;
}
void show_Pokemons(char Pokemon_name[10][11],pokemon *pokemons,int pokemon_count)/*this function prints pokemons in a array */
{
  int i;
  for (i=0;i<pokemon_count;i++)
  {
    printf("(%d) %s\n",i,Pokemon_name[pokemons[i]] );
    
  }

}

void catch_a_pokemon(char Pokemon_name[10][11], pokemon pokemons[10],pokemon *my_pocket)/*this function takes the pokemon that user wants to catch and returns as pointer */
{
  int choice,pokemon_count=10;
  show_Pokemons(Pokemon_name,pokemons,pokemon_count);
  int i;
  printf("enter pockemon code to catch: ");
  scanf("%d",&choice);
  if(choice>=0 && choice<=9)
  {
    *my_pocket=choice;  
    printf("you added %s in your pocket\n",Pokemon_name[choice] );  
  }
  else
  {
    *my_pocket=-1;
  }
    
}

void pokedex(char Pokemon_name[10][11],int range[10],attack_type type[10],int attack_power[10],int stamina[10])/*declaring pokedox function*/
{
  char name[11];
  int i;
  printf("Please type name of the Pokémon (type exit to close Pokedex):\n");
  scanf("%s",name);/*taking pokemon name for showing it's database*/
  for (i=Charmander; i<=Krabby; i++)/*this loop goes from first pokemon to last pokemon*/
  {
    if (compare_strings(Pokemon_name[i],name)==0)/*condition to check if the pokemon we are looking is present in our database */
    {
      printf("\nname: %s\n",Pokemon_name[i]);/*we print the name of the poke*/
      /*prints the attack type of the pokemon*/
      if(type[i]==quadratic)
      {
        printf("attack type: quadratic\n");
      }
      else 
      {
        printf("attack type: linear\n");
      }
      printf("range: %d block\n",range[i] );/*prints the attack range of the searched pokemon*/
      printf("attack power: %d\n",attack_power[i]);/*prints the attack power*/
      printf("stamina: %d\n\n",stamina[i] );  /*prints the stamina*/    
    }
    else if(compare_strings(name,"exit")==0)
    {
      return;
    }

  }
  
}
/*compare string function takes two string and if they are same then returns us 0 else returns us 1*/
int compare_strings(char *str1, char *str2)/*fucntion declartion for compare string function*/
{
   int i = 0;/**/
 
   while (str1[i] == str2[i]) 
   {
      if (str1[i] == '\0' || str2[i] == '\0')
      {
         break;
      }
      i++;
   }
   
   if (str1[i] == '\0' && str2[i] == '\0')
   {
      return 0;
   }
   else
      return -1;
}

void main_menu()/*function to print the first menu*/
{
  printf("\n");
  printf("1.open pokedox\n");
  printf("2.go to oak's oak's laboratory\n");
  printf("3.enter the tournament\n");
  printf("4.exit\n\n");

}
void lab_menu()/*function to print the oak's labratory menu*/
{
  printf("\n");
  printf("(1) Show Pokémons        \n");
  printf("(2) Catch a Pokémon      \n");
  printf("(3) Release a Pokémon    \n");
  printf("(4) Show my pocket       \n");
  printf("(5) Back               \n");
}