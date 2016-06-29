#ifndef Memory_H
#define Memory_H
#include "CPUConfig.h"
#include <stdint.h>

typedef uint8_t Memory;

extern Memory ram_addr         [0x3FF];
extern Memory reserved1_addr   [0X37FF];
extern Memory eeprom_addr      [0X27F];
extern Memory reserved2_addr   [0X57F];
extern Memory optionByte_addr  [0XA];
extern Memory reserved3_addr   [0X59];
extern Memory uniqueID_addr    [0XB];
extern Memory reserved4_addr   [0X8E];
extern Memory gpio_addr        [0X7FF];
extern Memory reserved5_addr   [0X26FF];
extern Memory cpu_addr         [0xFF];
extern Memory interrupt_addr   [0X7F];
extern Memory flash_addr       [0X1F7F];
extern Memory reserved6_addr   [0X1DFF];

void    writeCPU(void);
void    readCPU(void);

uint8_t getValueFromAddress   (uint16_t addr);
void    writeValueToTheAddress(uint16_t addr, uint8_t value);


#endif // Memory_H

