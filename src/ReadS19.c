#include "ReadS19.h"
#include <CException.h>
#include "MCU_Operation.h"
#include "CPUConfig.h"
#include "Memory.h"
#include "ErrorObject.h"
#include <malloc.h>
#include "Description.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>


/**
   brief  :  Open a S19 file by pass in the path (char *fileName)

   then write in the data of S19 file to stm8 virtual memory 
*/

void readS19(char *fileName){
  char line[512], S_type[4] = {0,0,0,0};
  FILE *fp = fopen(fileName, "r");
  
  while(fgets(line, sizeof(line), fp)){     // Get the nextLine while it is exist
    sscanf(&line[0], "%2s", S_type);        // Get S type (S type is 2 char locate at line(0) )
    
    if (strcmp(S_type,"S1") == 0){          // if S type is S1
      S19Interpret(line);                   // record the data cointained in a line 
      //printf("%s\n",line);
    }
  }
  fclose(fp);
}

/** 
 *   brief  :  Get the address and data from line, write the datas to stm8 virtual memory  (according the address)
 *              
 *   Example :  char *line = S11480E04A34352C4A359A8D0080948D0080AD20F622       
 *             
 *      S type   ByteCount    Address     Data                                   checkSum
 *      S1        14          80E0        4A34352C4A359A8D0080948D0080AD20F6     22 
 *     (1 byte)   (1 byte)    (2 byte)    (? byte)                               (1 byte)  
 *        
 *  ByteCount : number of byte ( address + data + checkSum)
 *          
 *  address is always 2 byte , checkSum is 1 byte
 *  number of data = byteCount - 2 - 1
 *                 = byteCount - 3  (for loop))
 *
 *  The data range is always start from line[8] to line[?], so j = 8, then line[j] 
 *  Inside the for loop, every loop write in 2 char of data to the address, which is byte of data
 *  so j+=2 evey loop
 */
void S19Interpret(char *line){
  int i,j = 8; 
  char buffer[3] = {0,0,0};
  uint16_t address;
  uint8_t byteCount, data, sum, checkSum = 0;
  
  getRecords(&byteCount, &address, &checkSum, line);
  sum = byteCount + (address & 0xFF) + ( (address & 0xFF00) >> 8); // sum = byteCount + address(lsb) + address(msb)
  
  for(i=0; i<byteCount-3; i++){
    sscanf(&line[j], "%2s", buffer);
    data = strtol(buffer, NULL, 16); // NULL means the tail of buffer, 16(Hex) is base number , so it convert the entire buffer to hex number
    sum += data;

    MEM_WRITE_BYTE(address, data);
    address+=1;
    j+=2;
  }
  
  if(((~sum) & 0xFF) != checkSum) // if sum does not meet the checkSum
    Throw(ERR_CHECKSUM_WRONG);
}

/** 
 *   brief  :  Get the value of byteCount , address , checkSum from line
 *              
 */
void getRecords(uint8_t *byteCount, uint16_t *address, uint8_t *checkSum, char *line){
  char buffer[5] = {0,0,0,0,0};
  
  sscanf(&line[2], "%2s", buffer);        //byteCount locate at line[2]
  *byteCount = strtol(buffer, NULL, 16);

  sscanf(&line[4], "%4s", buffer);        //address locate at line[4]
  *address = strtol(buffer, NULL, 16);
  
  sscanf(&line[(*byteCount+1)*2], "%2s", buffer);  //checkSum is last two char of line[] , where the position is (byteCount+1) X 2
  *checkSum = strtol(buffer, NULL, 16);
}

