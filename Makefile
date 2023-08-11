
ROOT = .

include $(ROOT)/config.mk

#_________________________________________________________________________


ASLISTING    = -alh

HELLO_OBJS   = src/crt0.o  src/main.o src/vectors.o src/tty.o

all: basic.bin 

basic.bin:	$(HELLO_OBJS)
	$(CC) $(CFLAGS) $(LDFLAGS) --entry=_start -Tbasic.ld -o $@.elf $^
	$(CC) $(CFLAGS) $(LDFLAGS) --entry=_start -Tbasic.ld -Wl,--oformat=binary -o $@ $^

#_________________________________________________________________________ generale rules

%.a: $^
	$(AR) rc $@ $^
	$(RANLIB) $@

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

%.o: %.s
	$(AS) $(ASFLAGS) -c -o $@ $<

clean:
	find . \( -name "*.o" -or -name "*.a" -or -name "*.bin" -or -name "*.elf" -or -name "*.load" \) -delete -print




