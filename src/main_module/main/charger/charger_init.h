#ifndef MAIN_CHARGER_CHARGER_INIT_H_
#define MAIN_CHARGER_CHARGER_INIT_H_

typedef void (*t_isr_charger_onkeypress)();

void charger_init();
void charger_stop();
void charger_confirm_in_progress();
void charger_set_isr_onkeypress_handler(t_isr_charger_onkeypress handler);

#endif /* MAIN_CHARGER_CHARGER_INIT_H_ */
