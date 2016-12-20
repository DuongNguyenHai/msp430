# Nguyen Hai Duong
# Nov 30 2016

# makfile configuration
NAME            = main
CPU             = msp430g2553
CFLAGS          = -mmcu=${CPU} -O2 -Wall -g
CC 				= msp430-gcc
GDB     		= msp430-elf-gdb
#switch the compiler (for the internal make rules)

SOURCES = UART.c main.c
OBJECTS = $(addsuffix .o, $(basename $(SOURCES)) )

all: ${NAME}.elf ${NAME}.a43 ${NAME}.lst

#confgigure the next line if you want to use the serial download
download: download-jtag

$(NAME).elf: $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) $(LDFLAGS) $(INCLUDES) $(LIBS) -o $@

${NAME}.a43: ${NAME}.elf
	msp430-objcopy -O ihex $^ $@

${NAME}.lst: ${NAME}.elf
	msp430-objdump -dSt $^ > $@

# pull in dependency info for *existing* .o files
-include $(OBJECTS:.o=.d)

%.o: %.c
	$(CC) -c $(CFLAGS) $(INCLUDES) $*.c -o $*.o

	$(CC) -MM $(CFLAGS) $(INCLUDES) $*.c > $*.d
	@mv -f $*.d $*.d.tmp
	@sed -e 's|.*:|$*.o:|' < $*.d.tmp > $*.d
	@sed -e 's/.*://' -e 's/\\$$//' < $*.d.tmp | fmt -1 | \
	  sed -e 's/^ *//' -e 's/$$/:/' >> $*.d
	@rm -f $*.d.tmp

download-jtag: all
	msp430-jtag -e ${NAME}.elf

debug: all
	$(GDB) $(NAME).elf

clean:
	$(RM) $(NAME).elf ${NAME}.a43 ${NAME}.lst

deep-clean:
	$(RM) *.o *.d $(NAME).elf ${NAME}.a43 ${NAME}.lst
