# makfile configuration
COMMON_OBJECTS  = 
CPU             = msp430g2553
CFLAGS          = -mmcu=${CPU} -Os -I../h
LDFLAGS		= -L../lib -L/opt/ti/msp430_gcc/include

#switch the compiler (for the internal make rules)
CC              = msp430-elf-gcc
AS              = msp430-elf-gcc -mmcu=${CPU} -c

all: go.elf 

#additional rules for files
go.elf: ${COMMON_OBJECTS} wdt_handler.o buzzer.o stateMachines.o p2_interrupt_handler.o led.o switches.o main.o stateAdvance.o isNegative.o ../lib/libTimer.a
	${CC} ${CFLAGS} ${LDFLAGS} -o $@ $^ -lTimer -lLcd

load: go.elf
	msp430loader.sh $^

clean:
	rm -f *.o *.elf

