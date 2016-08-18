#ifndef main_H
#define main_H

int main(void);

void executeOneInstructon(uint8_t *opcode);
int executeOneInstructonNoUpdatePC(uint8_t *opcode);

#endif // main_H
