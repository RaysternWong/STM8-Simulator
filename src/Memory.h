#ifndef Memory_H
#define Memory_H
#include "CPUConfig.h"
#include <stdint.h>


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

typedef uint8_t Memory;

extern Memory ram_addr         [RAM_SIZE];
extern Memory reserved1_addr   [RES1_SIZE];
extern Memory eeprom_addr      [EEPROM_SIZE];
extern Memory reserved2_addr   [RES2_SIZE];
extern Memory optionByte_addr  [OPTION_BYTE_SIZE];
extern Memory reserved3_addr   [RES3_SIZE];
extern Memory uniqueID_addr    [UNIQUE_ID_SIZE];
extern Memory reserved4_addr   [RES4_SIZE];
extern Memory gpio_addr        [GPIO_SIZE];
extern Memory reserved5_addr   [RES5_SIZE];
extern Memory cpu_addr         [CPU_SIZE];
extern Memory interrupt_addr   [IRQ_SIZE];
extern Memory flash_addr       [FLASH_SIZE];
extern Memory reserved6_addr   [RES6_SIZE];

void    writeCPU(void);
void    readCPU(void);

uint8_t getValueFromAddress   (uint32_t addr);
void    writeValueToTheAddress(uint32_t addr, uint8_t value);


#endif // Memory_H

