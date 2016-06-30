#include "unity.h"
#include "SUB.h"
#include "MCU_Operation.h"
#include <stdint.h>
#include "CPUConfig.h"
#include "Memory.h"
#include <malloc.h>

#define A     cpu->a            //Accumulator
#define XH    cpu->xh           //most significant byte of the X index register  (1 byte)
#define XL    cpu->xl           //least significant byte of the X index register (1 byte)
#define YH    cpu->yh           //most significant byte of the y index register  (1 byte)
#define YL    cpu->yl           //least significant byte of the y index register (1 byte)
#define SPH   cpu->sph          //most significant byte of the sph index register  (1 byte)
#define SPL   cpu->spl          //least significant byte of the spl index register (1 byte)


void setUp(void)
{
  instantiateCPU();
}

void tearDown(void)
{
   free(cpu);
}

void test_module_generator_needs_to_be_implemented(void)
{
	TEST_IGNORE_MESSAGE("Implement me!");
}
