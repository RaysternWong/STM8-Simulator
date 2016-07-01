#include "Memory.h"
#include <stdint.h>
#include <stdio.h>
#include <malloc.h>
#include "CPUConfig.h"

#define RAM_SIZE          0x3FF
#define RES1_SIZE         0X37FF
#define EEPROM_SIZE       0X27F
#define RES2_SIZE         0X57F
#define OPTION_BYTE_SIZE  0XA
#define RES3_SIZE         0X59
#define UNIQUE_ID_SIZE    0XB
#define RES4_SIZE         0X8E
#define GPIO_SIZE         0X7FF
#define RES5_SIZE         0X26FF
#define CPU_SIZE          0xFF
#define IRQ_SIZE          0X7F
#define FLASH_SIZE        0X1F7F
#define RES6_SIZE         0X1DFF

#define RAM_START_ADDR          0x0
#define RAM_END_ADDR            0x3FF

#define RES1_START_ADDR         0X800
#define EEPROM_START_ADDR       0X4000
#define RES2_START_ADDR         0X4280
#define OPTION_BYTE_START_ADDR  0X4800
#define RES3_START_ADDR         0X480B
#define UNIQUE_ID_START_ADDR    0X4865
#define RES4_START_ADDR         0X4871
#define GPIO_START_ADDR         0X5000
#define RES5_START_ADDR         0X5800
#define CPU_START_ADDR          0x7F00
#define IRQ_START_ADDR          0X8000
#define FLASH_START_ADDR        0X8080
#define RES6_START_ADDR         0XA000



stm8Memory memoryTable[256] = {

  [0X03] = ramMemory,
  [0X04] = ramMemory,
  [0X05] = ramMemory,

};

uint8_t ramMemory( Mode mode, uint8_t size)
{
  return 0x01;
}
















Memory ram_addr         [RAM_SIZE];
Memory reserved1_addr   [RES1_SIZE];
Memory eeprom_addr      [EEPROM_SIZE];
Memory reserved2_addr   [RES2_SIZE];
Memory optionByte_addr  [OPTION_BYTE_SIZE];
Memory reserved3_addr   [RES3_SIZE];
Memory uniqueID_addr    [UNIQUE_ID_SIZE];
Memory reserved4_addr   [RES4_SIZE];
Memory gpio_addr        [GPIO_SIZE];
Memory reserved5_addr   [RES5_SIZE];
Memory cpu_addr         [CPU_SIZE];
Memory interrupt_addr   [IRQ_SIZE];
Memory flash_addr       [FLASH_SIZE];
Memory reserved6_addr   [RES6_SIZE];


void readCPU(void)
{
  cpu->a = cpu_addr[0x00];
}


void writeCPU(void)
{
  cpu_addr[0x00] = cpu->a;
  cpu_addr[0x01] = cpu->pce;
  cpu_addr[0x02] = cpu->pch;
  cpu_addr[0x03] = cpu->pcl;
  cpu_addr[0x04] = cpu->xh;
  cpu_addr[0x05] = cpu->xl;
  cpu_addr[0x06] = cpu->yh;
  cpu_addr[0x07] = cpu->yl;
  cpu_addr[0x08] = cpu->sph;
  cpu_addr[0x09] = cpu->spl;
  cpu_addr[0x0A] = (cpu->ccr).full;
}


/** Notice :
*   To save the code size, the if else statements below are arrange based on the "define valuue" from small to big
*   so the checking statement is simplied
*
*/
uint8_t getValueFromAddress(uint32_t addr)
{
  if( addr  <= RAM_END_ADDR){
    return ram_addr[addr];
  }
  
  else if( addr < EEPROM_START_ADDR ){
    return reserved1_addr[addr - RES1_START_ADDR ];
  }
  
  else if( addr < RES2_START_ADDR ){
    return eeprom_addr[addr - EEPROM_START_ADDR ];
  }
  
  else if( addr < OPTION_BYTE_START_ADDR ){
    return reserved2_addr[addr - RES2_START_ADDR ];
  }
  
  else if( addr < RES3_START_ADDR ){
    return optionByte_addr[addr - OPTION_BYTE_START_ADDR];
  }
  
  else if( addr < UNIQUE_ID_START_ADDR ){
    return reserved3_addr[addr - RES3_START_ADDR ];
  }
  
  else if( addr < RES4_START_ADDR ){
    return uniqueID_addr[addr - UNIQUE_ID_START_ADDR ];
  }
  
  else if( addr < GPIO_START_ADDR ){
    return reserved4_addr[addr - RES4_START_ADDR ];
  }
  
  else if( addr < RES5_START_ADDR ){
    return gpio_addr[addr - GPIO_START_ADDR ];
  }
  
  else if( addr < CPU_START_ADDR ){
    return reserved5_addr[addr - RES5_START_ADDR ];
  }
  
  else if( addr < IRQ_START_ADDR ){
    return cpu_addr[addr - CPU_START_ADDR ];
  }
  else if( addr < FLASH_START_ADDR ){
    return interrupt_addr[addr - IRQ_START_ADDR ];
  }
  
  else if( addr < RES6_START_ADDR ){
    return flash_addr[addr - FLASH_START_ADDR ];
  }
  
  else{
    return reserved6_addr[addr - RES6_START_ADDR ];
  }
}

void  writeValueToTheAddress(uint32_t addr, uint8_t value)
{
  if( addr  <= RAM_END_ADDR){
     ram_addr[addr] = value;
  }
  
  else if( addr < EEPROM_START_ADDR ){
     reserved1_addr[addr - RES1_START_ADDR ] = value;
  }
  
  else if( addr < RES2_START_ADDR ){
     eeprom_addr[addr - EEPROM_START_ADDR ] = value;
  }
  
  else if( addr < OPTION_BYTE_START_ADDR ){
     reserved2_addr[addr - RES2_START_ADDR ] = value;
  }
  
  else if( addr < RES3_START_ADDR ){
     optionByte_addr[addr - OPTION_BYTE_START_ADDR] = value;
  }
  
  else if( addr < UNIQUE_ID_START_ADDR ){
     reserved3_addr[addr - RES3_START_ADDR ] = value;
  }
  
  else if( addr < RES4_START_ADDR ){
     uniqueID_addr[addr - UNIQUE_ID_START_ADDR ] = value;
  }
  
  else if( addr < GPIO_START_ADDR ){
     reserved4_addr[addr - RES4_START_ADDR ] = value;
  }
  
  else if( addr < RES5_START_ADDR ){
     gpio_addr[addr - GPIO_START_ADDR ] = value;
  }
  
  else if( addr < CPU_START_ADDR ){
     reserved5_addr[addr - RES5_START_ADDR ] = value;
  }
  
  else if( addr < IRQ_START_ADDR ){
     cpu_addr[addr - CPU_START_ADDR ] = value;
  }
  else if( addr < FLASH_START_ADDR ){
     interrupt_addr[addr - IRQ_START_ADDR ] = value;
  }
  
  else if( addr < RES6_START_ADDR ){
     flash_addr[addr - FLASH_START_ADDR ] = value;
  }
  
  else{
     reserved6_addr[addr - RES6_START_ADDR ] = value;
  }
}