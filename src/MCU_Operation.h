#ifndef MCU_Operation_H
#define MCU_Operation_H
#include <stdint.h>
#include "CPUConfig.h"
#include "Memory.h"

//----------------------------------STM 8 Architecture---------------------------------------------------------------

#define A     cpu->a            //Accumulator
#define PCE   cpu->pce          //Program counter extended
#define PCH   cpu->pch          //Program counter high
#define PCL   cpu->pcl          //Program counter low
#define XH    cpu->xh           //most significant byte of the X index register  (1 byte)
#define XL    cpu->xl           //least significant byte of the X index register (1 byte)
#define YH    cpu->yh           //most significant byte of the y index register  (1 byte)
#define YL    cpu->yl           //least significant byte of the y index register (1 byte)
#define SPH   cpu->sph          //most significant byte of the sph index register  (1 byte)
#define SPL   cpu->spl          //least significant byte of the spl index register (1 byte)

#define CC   ((cpu->ccr).full)  //  Condition code register ( 1 byte)

#define V   ((cpu->ccr).bits.v)   //overFlow
#define I1  ((cpu->ccr).bits.l1)  //interrupt mask level 1
#define H   ((cpu->ccr).bits.h)   //half cary
#define I0  ((cpu->ccr).bits.l0)  //interrupt mask level 0
#define N   ((cpu->ccr).bits.n)   //negative
#define Z   ((cpu->ccr).bits.z)   //zero
#define C   ((cpu->ccr).bits.c)   //carry

#define IM  ( I0 & I1 )           //Interrupt mask 

//-----------------------------------Flag Setting-------------------------------------------------------------------
#define CLEAR_ALL_FLAGS                 CC = 0;
#define UPDATE_Z_N_FLAG(num)            do { Z = ((num) == 0 ? 1 : 0); N = ((num) & 0X80) >> 7; }while(0)
#define UPDATE_Z_N_FLAG_FOR_WORD(num)   do { Z = ((num)  == 0 ? 1 : 0); N = ((num) & 0X8000) >> 15; }while(0)
#define SBC_FLAGS_UPDATE(num)           do { UPDATE_Z_N_FLAG(num) ; C = ( value > a ? 1 : 0) ; V = C ^ (_A6 & M6 | _A6 & R6 | A6 & M6 & R6); }while(0)
#define SUBW_FLAGS_UPDATE(num)          do { UPDATE_Z_N_FLAG_FOR_WORD(num) ; C = ( value > a ? 1 : 0) ; V = C ^ ( _A14 & M14 | _A14 & R14 | A14 & M14 & R14); }while(0)

//-------------------------------Memory Reading and Writing----------------------------------------------------------
#define MEM_READ_BYTE(addr)             memoryTable[addr/0x100](MEM_READ , addr, 1, 0)
#define MEM_READ_WORD(addr)             memoryTable[addr/0x100](MEM_READ , addr, 2, 0)
#define MEM_READ_EXT(addr)              memoryTable[addr/0x100](MEM_READ , addr, 3, 0)
#define MEM_WRITE_BYTE(addr,data)       memoryTable[addr/0x100](MEM_WRITE, addr, 1, data)
#define MEM_WRITE_WORD(addr,data)       memoryTable[addr/0x100](MEM_WRITE, addr, 2, data)
#define MEM_WRITE_EXT(addr,data)        memoryTable[addr/0x100](MEM_WRITE, addr, 3, data)

//-------------------------------Value transferring----------------------------------------------------------
#define TO_BYTE(ext)                    ( ext &= 0x0000FF)
#define TO_WORD(ext)                    ( ext &= 0x00FFFF)
#define GET_WORD(msb,lsb)               ( (msb<<8) + lsb )
#define GET_EXT(extb,msb,lsb)           ( (extb<<16) + (msb<<8) + lsb ) 

//-------------------------------Register Setting----------------------------------------------------------
#define SET_X(word)                     setBigEndianWord(&XH, word)
#define SET_Y(word)                     setBigEndianWord(&YH, word)
#define SET_SP(word)                    setBigEndianWord(&SPH, word)
#define SET_PC_WORD(word)               setBigEndianWord(&PCH, word)
#define SET_PC(extend)                  setBigEndianExt(&PCE, extend)

//-----------------------------Get the complete register ----------------------------------------------------------
#define X                               getBigEndianWord(&XH)
#define Y                               getBigEndianWord(&YH)
#define SP                              getBigEndianWord(&SPH)
#define PC_WORD                         getBigEndianWord(&PCH)
#define PC                              getBigEndianExt(&PCE)

#define X_SRC                           MEM_READ_BYTE(X)
#define Y_SRC                           MEM_READ_BYTE(Y)

//------------------------------------------------------------------------------------------------------------------------------------------------------

/**
*           Binary       Hex
*       0000 0001         1     bit 0
*       0000 0010         2
*       0000 0100         4
*       0000 1000         8
*       0001 0000        10
*       0010 0000        20
*       0100 0000        40
*       1000 0000        80     bit 7
*
*                       100    bit 8
*                       200
*                       400
*                       800
*                      1000
*                      2000
*                      4000
*                      8000    bit 15

*/

#define GET_BIT_0(num)  ((num)& 0X01)  
#define GET_BIT_1(num)  ((num & 0X02) >> 1)  
#define GET_BIT_2(num)  ((num & 0X04) >> 2)
#define GET_BIT_3(num)  ((num & 0X08) >> 3)
#define GET_BIT_4(num)  ((num & 0X10) >> 4)
#define GET_BIT_5(num)  ((num & 0X20) >> 5) 
#define GET_BIT_6(num)  ((num & 0X40) >> 6)  
#define GET_BIT_7(num)  ((num & 0X80) >> 7)
#define GET_BIT_15(num) ((num & 0X8000) >> 15)


#define GET_LEAST_BYTE(num)  ((num)& 0XFF)  
#define GET_MID_BYTE(num)    ((num)& 0XFF00)  >> 8
#define GET_MOST_BYTE(num)   ((num)& 0XFF0000) >> 16

// Memory
#define M0  (value & 0X01)      
#define M1  ( (value & 0X02) >> 1 )
#define M2  ( (value & 0X04) >> 2 )
#define M3  ( (value & 0X08) >> 3 )
#define M4  ( (value & 0X10) >> 4 )
#define M5  ( (value & 0X20) >> 5 )
#define M6  ( (value & 0X40) >> 6 )
#define M7  ( (value & 0X80) >> 7 )

#define M8  ( (value & 0X100) >> 8 )
#define M9  ( (value & 0X200) >> 9 )
#define M10 ( (value & 0X400) >> 10)
#define M11 ( (value & 0X800) >> 11)
#define M12 ( (value & 0X1000) >> 12)
#define M13 ( (value & 0X2000) >> 13)
#define M14 ( (value & 0X4000) >> 14)
#define M15 ( (value & 0X8000) >> 15)

#define _M0  (M0 == 0 ? 1 : 0)
#define _M1  (M1 == 0 ? 1 : 0)
#define _M2  (M2 == 0 ? 1 : 0)
#define _M3  (M3 == 0 ? 1 : 0)
#define _M4  (M4 == 0 ? 1 : 0)
#define _M5  (M5 == 0 ? 1 : 0)
#define _M6  (M6 == 0 ? 1 : 0)
#define _M7  (M7 == 0 ? 1 : 0)

#define _M8  (M8 == 0 ? 1 : 0)
#define _M9  (M9 == 0 ? 1 : 0)
#define _M10 (M10 == 0 ? 1 : 0)
#define _M11 (M11 == 0 ? 1 : 0)
#define _M12 (M12 == 0 ? 1 : 0)
#define _M13 (M13 == 0 ? 1 : 0)
#define _M14 (M14 == 0 ? 1 : 0)
#define _M15 (M15 == 0 ? 1 : 0)


// Accumulator (or others register like index X,Y,SP)
#define A0  (a & 0X01) 
#define A1  ((a & 0X02) >> 1)
#define A2  ((a & 0X04) >> 2)
#define A3  ((a & 0X08) >> 3)
#define A4  ((a & 0X10) >> 4)
#define A5  ((a & 0X20) >> 5)
#define A6  ((a & 0X40) >> 6)
#define A7  ((a & 0X80) >> 7)

#define A8  ((a & 0X100) >> 8)
#define A9  ((a & 0X200) >> 9)
#define A10 ((a & 0X400) >> 10)
#define A11 ((a & 0X800) >> 11)
#define A12 ((a & 0X1000) >> 12)
#define A13 ((a & 0X2000) >> 13)
#define A14 ((a & 0X4000) >> 14)
#define A15 ((a & 0X8000) >> 15)

#define _A0  (A0 == 0 ? 1 : 0)
#define _A1  (A1 == 0 ? 1 : 0)
#define _A2  (A2 == 0 ? 1 : 0)
#define _A3  (A3 == 0 ? 1 : 0)
#define _A4  (A4 == 0 ? 1 : 0)
#define _A5  (A5 == 0 ? 1 : 0)
#define _A6  (A6 == 0 ? 1 : 0)
#define _A7  (A7 == 0 ? 1 : 0)

#define _A8  (A8 == 0 ? 1 : 0)
#define _A9  (A9 == 0 ? 1 : 0)
#define _A10 (A10 == 0 ? 1 : 0)
#define _A11 (A11 == 0 ? 1 : 0)
#define _A12 (A12 == 0 ? 1 : 0)
#define _A13 (A13 == 0 ? 1 : 0)
#define _A14 (A14 == 0 ? 1 : 0)
#define _A15 (A15 == 0 ? 1 : 0)

// Result
#define R0  (result & 0X01)
#define R1  ((result & 0X02) >> 1)
#define R2  ((result & 0X04) >> 2)
#define R3  ((result & 0X08) >> 3)
#define R4  ((result & 0X10) >> 4)
#define R5  ((result & 0X20) >> 5)
#define R6  ((result & 0X40) >> 6)
#define R7  ((result & 0X80) >> 7)

#define R8  ((result & 0X100) >> 8)
#define R9  ((result & 0X200) >> 9)
#define R10 ((result & 0X400) >> 10)
#define R11 ((result & 0X800) >> 11)
#define R12 ((result & 0X1000) >> 12)
#define R13 ((result & 0X2000) >> 13)
#define R14 ((result & 0X4000) >> 14)
#define R15 ((result & 0X8000) >> 15)

// Bitwise result
#define _R0  (R0 == 0 ? 1 : 0)
#define _R1  (R1 == 0 ? 1 : 0)
#define _R2  (R2 == 0 ? 1 : 0)
#define _R3  (R3 == 0 ? 1 : 0)
#define _R4  (R4 == 0 ? 1 : 0)
#define _R5  (R5 == 0 ? 1 : 0)
#define _R6  (R6 == 0 ? 1 : 0)
#define _R7  (R7 == 0 ? 1 : 0)

#define _R8  (R8 == 0 ? 1 : 0)
#define _R9  (R9 == 0 ? 1 : 0)
#define _R10 (R10 == 0 ? 1 : 0)
#define _R11 (R11 == 0 ? 1 : 0)
#define _R12 (R12 == 0 ? 1 : 0)
#define _R13 (R13 == 0 ? 1 : 0)
#define _R14 (R14 == 0 ? 1 : 0)
#define _R15 (R15 == 0 ? 1 : 0)

#define BIT0_TO_BIT3(byte)  ( byte & 0X0F     )
#define BIT4_TO_BIT7(byte)  ( (byte & 0XF0)>>4)

#define BIT0_TO_BIT7(word)  ( word & 0X00FF     )
#define BIT8_TO_BIT15(word) ( (word & 0XFF00)>>8)

//-------------------------------------Instruction-------------------------------------------------------------------
#define SWAP_BYTE(byte)  ( BIT4_TO_BIT7(byte)  | BIT0_TO_BIT3(byte)<<4 )
#define SWAP_WORD(byte)  ( BIT8_TO_BIT15(byte) | BIT0_TO_BIT7(byte)<<8 )

#define LOAD_BYTE_TO_REG( reg, byte)    do { (reg) = (byte) ; UPDATE_Z_N_FLAG(reg); }while(0)
#define LOAD_WORD_TO_REG( regH, word)   do { uint16_t w = word ; setBigEndianWord(&(regH), w); UPDATE_Z_N_FLAG_FOR_WORD(w); }while(0)

#define LOAD_BYTE_TO_MEM( mem, byte)   do { MEM_WRITE_BYTE(mem,byte) ; UPDATE_Z_N_FLAG(byte); }while(0)
#define LOAD_WORD_TO_MEM( mem, word)   do { uint16_t w = word ; MEM_WRITE_WORD(mem, w); UPDATE_Z_N_FLAG_FOR_WORD(w); }while(0)
 
#define CLEAR(dst)                     do { MEM_WRITE_BYTE(dst,0) ; N = 0 ; Z = 1; }while(0)
#define EXCHANGE(dst,src)              do { uint8_t temp = src ; (src) = dst ; (dst) = temp; }while(0) 
#define MOV(dst,src)                   MEM_WRITE_BYTE(dst,src) 
        
 
#define sl(byte)   ( (byte) <<1 )                   //Shift Left
#define sr(byte)   ( (byte) >>1 )                   //Shift right
#define sra(byte)  ( (byte) & 0x80 | (byte)>>1 )    //Shift Right Arithmetic
#define sraw(word) ( (word) & 0X8000 | (word)>>1 )  //Shift Right Arithmetic Word

//Left rotate always assign carry to bit0, 
//Right rotate assign carry to bit7 for byte, bit15 for word
#define rl(byte)   ( byte<<1 | C)                   //Rotate left
#define rr(byte)   ( byte>>1 | C*0x80 )             //Rotate right
#define rrw(word)  ( word>>1 | C*0x8000 )           //Rotate right  word


//shift or rotate the contain, direction right or left
#define REG_OPERATION(reg, carry, mode)        do{ C = carry; LOAD_BYTE_TO_REG(reg, mode); }while(0) 
#define REG_WORD_OPERATION(reg, carry, mode)   do{ C = carry; LOAD_WORD_TO_REG(reg, mode); }while(0)  
#define MEM_OPERATION(mem, carry, mode)        do{ C = carry; LOAD_BYTE_TO_MEM(mem, mode); }while(0)     
     
 
#define REG_SHIFT_LEFT(reg)                   REG_OPERATION(reg, GET_BIT_7(reg), sl(reg) ) 
#define REG_SHIFT_RIGHT(reg)                  REG_OPERATION(reg, GET_BIT_0(reg), sr(reg) ) 
#define REG_SHIFT_RIGHT_ARITHMETIC(reg)       REG_OPERATION(reg, GET_BIT_0(reg), sra(reg)) 
#define REG_ROTATE_LEFT(reg)                  REG_OPERATION(reg, GET_BIT_7(reg), rl(reg) )  
#define REG_ROTATE_RIGHT(reg)                 REG_OPERATION(reg, GET_BIT_0(reg), rr(reg) )  
#define REG_WORD_SHIFT_LEFT(reg)              do{ uint16_t word = getBigEndianWord(&reg); REG_WORD_OPERATION(reg, GET_BIT_15(word), sl(word));  }while(0)    
#define REG_WORD_SHIFT_RIGHT(reg)             do{ uint16_t word = getBigEndianWord(&reg); REG_WORD_OPERATION(reg, GET_BIT_0(word) , sr(word));  }while(0) 
#define REG_WORD_SHIFT_RIGHT_ARITHMETIC(reg)  do{ uint16_t word = getBigEndianWord(&reg); REG_WORD_OPERATION(reg, GET_BIT_0(word) , sraw(word));}while(0)
#define REG_WORD_ROTATE_LEFT(reg)             do{ uint16_t word = getBigEndianWord(&reg); REG_WORD_OPERATION(reg, GET_BIT_15(word), rl(word));  }while(0)    
#define REG_WORD_ROTATE_RIGHT(reg)            do{ uint16_t word = getBigEndianWord(&reg); REG_WORD_OPERATION(reg, GET_BIT_0(word) , rrw(word));  }while(0) 

  
// Memory
#define MEM_SHIFT_LEFT(mem)                   do{ uint8_t byte = MEM_READ_BYTE(mem); MEM_OPERATION(mem, GET_BIT_7(byte), sl(byte)); }while(0)  
#define MEM_SHIFT_RIGHT(mem)                  do{ uint8_t byte = MEM_READ_BYTE(mem); MEM_OPERATION(mem, GET_BIT_0(byte), sr(byte)); }while(0) 
#define MEM_SHIFT_RIGHT_ARITHMETIC(mem)       do{ uint8_t byte = MEM_READ_BYTE(mem); MEM_OPERATION(mem, GET_BIT_0(byte), sra(byte));}while(0)
#define MEM_ROTATE_LEFT(mem)                  do{ uint8_t byte = MEM_READ_BYTE(mem); MEM_OPERATION(mem, GET_BIT_7(byte), rl(byte)); }while(0)  
#define MEM_ROTATE_RIGHT(mem)                 do{ uint8_t byte = MEM_READ_BYTE(mem); MEM_OPERATION(mem, GET_BIT_0(byte), rr(byte)); }while(0) 

 
uint16_t getBigEndianWord(uint8_t *bytes);
uint32_t getBigEndianExt(uint8_t *bytes);

void setBigEndianWord(uint8_t *bytes, uint16_t word);
void setBigEndianExt(uint8_t *bytes, uint32_t extend);

void sp_decrement(void);
void sp_increment(void);
void mcu_push(uint8_t value);
void mcu_call(uint16_t address, uint8_t length);
void mcu_callf(uint32_t address, uint8_t length);
void mcu_add(uint8_t value);
void mcu_adc(uint8_t value);
void mcu_addw(uint8_t *reg, uint16_t value);
void mcu_sub(uint8_t value);
void mcu_sbc(uint8_t value);
void mcu_subw(uint8_t *reg, uint16_t value);
void mcu_neg(uint16_t addr);
void mcu_inc(uint16_t addr);
void mcu_dec(uint16_t addr);
void mcu_cpl(uint16_t addr);
void mcu_div(uint8_t *reg);

void mcu_cp(uint8_t dst, uint8_t src);
void mcu_cpw(uint16_t dst, uint16_t src);

uint8_t mcu_pop(void);



#endif // MCU_Operation_H
