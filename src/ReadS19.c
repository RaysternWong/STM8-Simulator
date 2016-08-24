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
  
  fgets(line, sizeof(line), fp);
  fgets(line, sizeof(line), fp);
  S19Interpret(line);
  
  // while(fgets(line, sizeof(line), fp))
    // S19Interpret(line);
  
 
  fclose(fp);
}

void S19Interpret(char *line){
  char buffer[3] = {0,0,0};
  sscanf(line, "%2s", buffer);
  
  //sscanf(&line[2], "%2s", buffer);
  //mark[0] = line[0];
  //mark[1] = line[1];
  
 // printf("%s\n",line[0]);
 // printf("%s\n",line[1]);
  //printf("%s\n",buffer);
   //strncpy(mark, line, 2);

  // printf("%s\n",line);
  // line += 2;
  printf("%s\n",line);
  

  if( strcmp(buffer, "S0") == 0){
    //printf("enter S0\n");
  }
  else if( strcmp(buffer, "S1") == 0){
     recordS1(line);
  }
  else if( strcmp(buffer, "S9") == 0){
    // printf("enter S9\n");
  }
}

void recordS1(char *line){
  int i,j = 8; 
  char buffer[3] = {0,0,0};
  uint16_t address;
  uint8_t byteCount, data, checkSum = 0;
  
  
  sscanf(&line[2], "%2s", buffer);
  byteCount = strtol(buffer, NULL, 16);
 // printf("%x\n",byteCount);
  
  sscanf(&line[4], "%4s", buffer);
  address = strtol(buffer, NULL, 16);
  
  int loop = (byteCount-0x6)/2;
  // printf("%x\n",loop);
  for(i = 0; i <loop; i++){
    sscanf(&line[j], "%2s", buffer);
    data = strtol(buffer, NULL, 16);
   // printf("%x\n",data);

   // printf("%x\n",i);
   // printf("%x\n",address);
    MEM_WRITE_BYTE(address, data);
    address+=1;
    j+=2;
  }
}

void getRecords(uint8_t *byteCount, uint16_t *address, uint8_t *checkSum, char *line){
  char buffer[5] = {0,0,0,0,0};
  
  sscanf(&line[2], "%2s", buffer);
  *byteCount = strtol(buffer, NULL, 16);

  sscanf(&line[4], "%4s", buffer);
  *address = strtol(buffer, NULL, 16);
  
  sscanf(&line[(*byteCount+1)*2], "%2s", buffer);
  *checkSum = strtol(buffer, NULL, 16);
}

