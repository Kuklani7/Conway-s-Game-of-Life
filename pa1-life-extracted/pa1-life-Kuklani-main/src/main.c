#include <stdio.h>
#include <stdbool.h>
#include "life.h"

/* Be sure to read life.h and the other given source files to understand
 * what they provide and how they fit together.  You don't have to
 * understand all of the code, but you should understand how to call
 * parse_life() and clearterm().
 */

/* This is where your program will start.  You should make sure that it
 * is capable of accepting either one or two arguments; the first
 * argument (which is required) is a starting state in one of the Life
 * formats supported by parse_life(), and the second (which is optional)
 * is a number of generations to run before printing output and stopping.
 *
 * The autograder will always call your program with two arguments.  The
 * one-argument format (as described in the handout) is for your own
 * benefit!
 */
void printer_bancho(int rows, int cols, char printable[rows][cols]){
  for(int j=0;j<rows;j++){
      for(int i=0;i<cols;i++){
        putchar(printable[j][i]);
          }
      putchar('\n');
      }
}
int count_neighbours_single(int j, int i,char expanded[GRIDY+2][GRIDX+2], char singled){
  if(i==0 || i==GRIDX+1 || j==0 || j==GRIDY+1){
    return 0;
  }
  int count=0;
  for(int w=-1;w<2;w++){
    for(int v=-1; v<2; v++){
      if(w==0 && v==0){
        continue;
      }
      if(expanded[j+w][i+v]==LIVE){
        count++;
      }
    }
  }
  return count;
  }
void calculator(char worker[GRIDY+2][GRIDX+2], char next_gen[GRIDY+2][GRIDX+2]){
  for(int j=0;j<GRIDY+2;j++){
    for(int i=0; i<GRIDX+2; i++){
      next_gen[j][i]=worker[j][i];
    }
  }
  for(int j=1; j<GRIDY+1; j++){
    for(int i=1; i<GRIDX+1; i++){
      int hold = count_neighbours_single(j,i,worker,worker[j][i]);
	if(worker[j][i]==LIVE && (hold<2 || hold>3)){
	  next_gen[j][i]=DEAD;
	  }
      if((worker[j][i]==LIVE) &&(hold==2 || hold==3)){
        next_gen[j][i]=LIVE;
      }
      if((worker[j][i]==DEAD) && (hold==3)){
        next_gen[j][i]=LIVE;
      }
    }
  }
  //printer_bancho(GRIDY+2,GRIDX+2,next_gen);
}
void convert_back(char larger[GRIDY+2][GRIDX+2]){
  char removed_bounds[GRIDY][GRIDX];
  for(int j=0; j<GRIDY; j++){
    for(int i=0; i<GRIDX; i++){
        removed_bounds[j][i]= larger[j+1][i+1];
    }
  }
  for(int j=0;j<GRIDY;j++){
      for(int i=0; i<GRIDX; i++){
        putchar(removed_bounds[j][i]);
    }
      putchar('\n');
  }
}
void somethinger(char worker[GRIDY+2][GRIDX+2], int generate_number){
  char grids [2][GRIDY+2][GRIDX+2];
  int current=0;
  for(int j=0;j<GRIDY+2;j++){
      for(int i=0; i<GRIDX+2; i++){
        grids[current][j][i]= worker[j][i];
    }
  }
  for (current = 0; generate_number > 0 ; current = (current + 1) % 2) {
    int alterer =(current+1)%2;
    calculator(grids[current],grids[alterer]);
    generate_number--;
 }
  /*for(int j=0;j<GRIDY+2; j++){
      for(int i=0; i<GRIDX+2; i++){
        putchar(grids[current][j][i]);
    }
      putchar('\n');
  }*/
  char passer[GRIDY+2][GRIDX+2];
  for(int j=0;j<GRIDY+2;j++){
      for(int i=0; i<GRIDX+2; i++){
        passer[j][i] = grids[current][j][i];
    }
  }
  convert_back(passer);
}
void create_border(char **orig, int gen_num){
  char converter[GRIDY+2][GRIDX+2];
  /*for(int v=0; v<GRIDY+2;v++){
     for(int w=0; w<GRIDX+2; w++){
       char ch='A';
       converter[v][w]=ch;
      }
   }*/
   for(int i=0; i<GRIDY+2; i++){
     converter[i][0]=DEAD;
     }
   for(int i=0; i<GRIDY+2; i++){
     converter[i][GRIDX+1]=DEAD;
     }
   for(int i=0; i<GRIDX+2; i++){
     converter[0][i]=DEAD;
     }
   for(int i=0; i<GRIDX+2; i++){
     converter[GRIDY+1][i]=DEAD;
     }
   for(int j=1;j<GRIDY+1;j++){
     for(int i=1; i<GRIDX+1; i++){
       converter[j][i]=orig[j-1][i-1];
     }
   }
   somethinger(converter,gen_num);
   //printer_bancho(GRIDY+2,GRIDX+2, converter);
   /*int DD = count_neighbours_single(2,2,converter,converter[2][2]);
   printf("%d",DD);
   putchar('\n');*/
   //char alternator[2][GRIDY][GRIDX];
   /*for(int j=0;j<GRIDY+2;j++){
      for(int i=0;i<GRIDX+2;i++){
        putchar(converter[j][i]);
          }
      putchar('\n');
      }*/
   }
bool isnumber(char c){
  if(48<=c && c<=57){
    return 1;
  }
  else{
    return 0;
  }
}
int main(int argc, char *argv[])
{
  if(argc!=3){
    printf("Error invalid number of arguments.");
      return 1;
  }
    char **input_grid = parse_life(argv[1]);
    char *gen_number = argv[2];
    int num_builder=0;
     for(int i=0; gen_number[i]!='\0';i++){
    if(isnumber(gen_number[i])){
      num_builder=(num_builder*10)+(gen_number[i]-'0');
      }
     }
    create_border(input_grid,num_builder);
    /*for(int w=0; w<GRIDY; w++){
      char ch='r';
      if(w!=0){
	input_grid[w][0]= ch;
        }
      else{
	continue;
      }
      }
    for(int j=0;j<GRIDY;j++){
      for(int i=0;i<GRIDX;i++){
        putchar(input_grid[j][i]);
	  }
      putchar('\n');
      }*/
  return 0;
}


