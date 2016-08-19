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


void openFile(){
  FILE *file;
  
  // file = fopen("test.txt", "r");
  
  // if(!file){
    // printf("error open\n");
  // }
  
  file = fopen("C:\\Users\\D203C-01\\Desktop\\STM8-Simulator\\test\\support\\acia.s19", "r");
  
  if(!file){
    printf("error open\n");
  }
 
}

/** 
 *   brief  : Initialise InStream and allocate memory for it
 *  
 *   Return : return pointer to allocted memory for initalised InStream
 *   
 */
InStream *initInStream()
{
  InStream *inStream = malloc(sizeof(InStream));
  inStream->file = NULL;
  inStream->byteToRead = 0;
  inStream->bitIndex = 8;

  return inStream;
}

/** 
 *   brief  : Initialise OutStream and allocate memory for it
 * 
 *   Return : return pointer to allocted memory for initalised OutStream
 *   
 */
OutStream *initOutStream()
{
  OutStream *outStream = malloc(sizeof(OutStream));
  
  outStream->file = NULL;
  outStream->byteToWrite = 0;
  outStream->bitIndex = 0;

  return outStream;
}




/** 
 *   brief  :  Free the allocted memory for InStream and set it to NULL
 *  
 *   Input  : inStream is a pointer to pointer of InStream to be freed
 *  
 */
void freeInStream(InStream **inStream)
{
    free(*inStream);
    *inStream = NULL;
}

/** 
 *   brief  : Free the allocted memory for OutStream and set it to NULL
 *  
 *   Input  : outStream is a pointer to pointer of OutStream to be freed
 *    
 */
void freeOutStream(OutStream **outStream)
{
  free(*outStream);
  *outStream = NULL;
}


/** 
 *   brief  : Open the selected files in selected  mode for InStream
 *  
 *   Input  : fileName        is the name of the file to be opened
 *   Input  : mode            is the file operation mode 
 *            Possible value
 *            "r"             open file for reading. File must exist !
 *  
 *   Input  : outStream       is the pointer to the OutStream
 *  
 *   Return : return          the InStream with opened file
 *  
 */ 
InStream *openInStream(char *fileName, char *mode, InStream *inStream)
{
  inStream->file = fopen(fileName, mode);
  
  if(inStream->file == NULL)
    Throw(ERR_FAILED_TO_OPEN);
  else
    inStream->fileName = fileName;

  return inStream;
}

/** 
 *   brief  : Open the selected files in selected mode for OutStream
 *  
 *   Input  : fileName        is the name of the file to be opened
 *   Input  : mode            is the file operation mode 
 *            Possible value
 *            "w"             write mode. Create an empty file if the file initially does not exist or discard the contents if the file initially exist 
 *            "a"             open for appending
 *  
 *   Input  : outStream       is the pointer to the OutStream
 *  
 *   Return : return          the OutStream with opened file
 *  
 *  
 */ 
OutStream *openOutStream(char *fileName, char *mode, OutStream *outStream)
{
  outStream->file = fopen( fileName, mode);
 
  outStream->fileName = fileName;

  return outStream;
}

/** 
 *   brief  : Close the file inside the InStream
 *  
 *   Input  : inStream  is the pointer to the InStream
 *  
 */
void closeInStream(InStream *inStream)
{
  fclose(inStream->file);
}

/** 
 *   brief  : Close the file inside the OutStream and flush any remaing unwritten data
 *  
 *   Input  : outStream  is the pointer to the OutStream
 *  
 */ 
void *closeOutStream(OutStream *outStream)
{
  if (outStream->bitIndex != 0)
    streamFlush(outStream);

  fclose(outStream->file);
}

/** 
 *   brief  : Read 1 bit of data from byteToRead in InStream
 *  
 *   Input  : inStream is a pointer to inStream
 *  
 *   Return : return 1 if the bit value is 1
 *            return 0 if the bit value is 0
 */
uint8_t streamReadBit(InStream *inStream)
{
  uint8_t bitTest ;

  bitTest = inStream->byteToRead & (1 << inStream->bitIndex) ; //read lSB first
  inStream -> bitIndex ++ ;

  if (bitTest != 0 )
    return 1 ;
  else
    return 0 ;
}

/** 
 *   brief  : Read multiple bits of data from the file stream
 *  
 *   Input  : inStream  is the pointer to InStream
 *   Input  : bitSize   is the number of bits to be read
 *  
 *   Return : return the data read
 */
uint64_t streamReadBits(InStream *inStream, uint8_t bitSize)
{
  uint64_t dataRead = 0;
  uint8_t bitRead = 0 , index ;

  for ( index = 0 ; index < bitSize ; index ++)
  {
    if (inStream->bitIndex == 8 ) //fully extracted 1 byte
    {
      if (inStream->file != NULL)
        fread(&(inStream->byteToRead),1,1,inStream->file); //read new byte

			inStream->bitIndex = 0 ;
    }

    bitRead = streamReadBit(inStream);
    dataRead = dataRead | bitRead << index;
  }

  return dataRead ;
}


/** 
 *   brief  : Write 1 bit of data into OutStream 
 *  
 *   Input  : outStream   is the pointer to the OutStream
 *   Input  : bitToWrite  is the value of the bit to be written either 1 or 0
 *  
 */
void streamWriteBit(OutStream *outStream,uint8_t bitToWrite)
{
  outStream->byteToWrite |= (bitToWrite << outStream->bitIndex) ; //write lSB first
  outStream->bitIndex ++ ;
}

/** 
 *   brief  : Write multiple bits of the specified data into OutStream and flushed into file stream if necessary
 *  
 *   Input  : outStream   is the pointer to the OutStream
 *   Input  : value       is the value to be written
 *   Input  : bitSize     is the number of bits for the value to be written
 *    
 */ 
void streamWriteBits(OutStream *outStream, uint64_t value, uint8_t bitSize)
{
  uint8_t bitToWrite, index ;

  for ( index = 0 ; index < bitSize ; index ++) //write value to buffer
  {
    if (outStream->bitIndex == 8)
      streamFlush(outStream);

    bitToWrite = value & (1 << index ) ;

    if (bitToWrite != 0 )
      bitToWrite = 1 ;
    else
      bitToWrite = 0 ;

    streamWriteBit(outStream,bitToWrite);
  }
}

/** 
 *   brief  : Write whole data block into file stream if necessary
 *  
 *   Input  : outStream   is the pointer to the OutStream
 *   Input  : buffer      is the data block to be written into file stream
 *    
 */
void streamWriteDataBlock(OutStream *outStream,char *buffer)
{
  fwrite(buffer,1,strlen(buffer),outStream->file);
}

/** 
 *   brief  : Flush byteToWrite in OutStream to file stream
 *  
 *   Input  : outStream   is the pointer to the OutStream 
 *  
 */ 
void streamFlush(OutStream *outStream)
{
  fwrite(&(outStream->byteToWrite),1,1,outStream->file);

  outStream->byteToWrite = 0;
  outStream->bitIndex = 0 ;
}


/** 
 *   brief  : Check end of file (EOF) for the file currently opened in InStream
 *  
 *   Input  : inStream is a pointer to InStream
 *  
 *   Return : return 1 if end of file is encountered
 *            return 0 if end of file is not encountered yet
 */
uint8_t checkEndOfFile(InStream *inStream)
{
  uint8_t result ;
  result = feof (inStream->file) ;

  if (result != 0)
    return 1;
  else
    return 0;
}