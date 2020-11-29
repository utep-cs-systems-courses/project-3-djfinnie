#ifndef switches_included
#define switches_included

#define SW1 BIT3		/* switch1 is p1.3 */
//#define SWITCHES SW1		/* only 1 switch on this board */

#define S1 BIT0

#define S2 BIT1

#define S3 BIT2

#define S4 BIT3

#define SWITCHES (S1 | S2 | S3 | S4)

void switch_init();
void switch_interrupt_handler();

extern char switch_state_down, switch_state_changed; /* effectively boolean */

#endif // included
