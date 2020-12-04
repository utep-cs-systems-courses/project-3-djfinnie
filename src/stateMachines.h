#ifndef stateMachine_included
#define stateMachine_included

extern char state;

void draw_square(short offc, short offr);

void diagonalLine(short offc, short offr);

void startingScreen();

void imDown_button1();

void changeColor();

void gameResume_button0();

void state_advance();

void up_state();

void down_state();

void button2_siren();

void button3_off();

void blink_dim();

void buzzer_advance();

void main_state_advance();

#endif // included
