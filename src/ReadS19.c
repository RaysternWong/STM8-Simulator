#include "ReadS19.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include <CException.h>
#include "MCU_Operation.h"
#include "CPUConfig.h"
#include "Memory.h"
#include "ErrorObject.h"
#include <malloc.h>
#include "Description.h"

/**
   Library    char *fgets(char *str, int n, FILE *stream)
                return the string of line


*/


void readS19(char *fileName){
  char line[512];
  FILE *fp = fopen(fileName, "r");
  
  if(!fp) 
    Throw(ERR_FAILED_TO_OPEN);
  
  while(fgets(line, sizeof(line), fp))
    S19Interpret(line);
  
 
  fclose(fp);
}

void S19Interpret(char *line){
  char buffer[3] = {0,0,0};
  sscanf(line, "%2s", buffer);
  
  sscanf(&line[2], "%2s", buffer);
  //mark[0] = line[0];
  //mark[1] = line[1];
  
 // printf("%s\n",line[0]);
 // printf("%s\n",line[1]);
  printf("%s\n",buffer);
   //strncpy(mark, line, 2);

  // printf("%s\n",line);
  // line += 2;
 //  printf("%s\n",line);
  

  // if( mark == "S0"){
    // printf("enter S0\n");
  // }
  // else if( mark == "S1"){
     // printf("enter S1\n");
  // }
  // else if( mark == "S9"){
     // printf("enter S0\n");
  // }
}

