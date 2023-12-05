#ifndef FM_RECEIVER_H_
#define FM_RECEIVER_H_

#define FM_RECEIVER_PIN 7

void fm_receiver_init();
void isr_fm_receiver_on_high();

#endif /* #define FM_RECEIVER_H_ */
