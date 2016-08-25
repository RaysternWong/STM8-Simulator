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

/**
*
*
*
*/
void S19Interpret(char *line){
  int i,j = 8; 
  char buffer[3] = {0,0,0};
  uint16_t address;
  uint8_t byteCount, data, sum, checkSum = 0;
  
  getRecords(&byteCount, &address, &checkSum, line);
  sum = byteCount + (address & 0xFF) + ( (address & 0xFF00) >> 8);
  
  for(i=0; i<byteCount-3; i++){
    sscanf(&line[j], "%2s", buffer);
    data = strtol(buffer, NULL, 16);
    sum += data;

    MEM_WRITE_BYTE(address, data);
    address+=1;
    j+=2;
  }
  
  printf("%x  ",sum);
  printf("%x\n ",(~sum)&0xFF);
  printf("%x\n",checkSum);
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

