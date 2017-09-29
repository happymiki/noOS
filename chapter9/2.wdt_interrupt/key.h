#ifndef __KEY_H__
#define __KEY_H__

void key_init_interrupt(void);
void isr_eint2(void);
void isr_eint3(void);
void isr_eint16_19(void);



void key_init(void);
void key_polling(void);






#endif




