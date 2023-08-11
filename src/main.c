#include <stdint.h>

/* 68Katy memory map
 *
 * ROMBASE	      EQU $00000
 * RAM            EQU $80000
 * RAMTOP         EQU $FFFFF  //100000-1
 *
 */

#define NULL ((void *)0L)

#define ROM_ADDR 0x000000
#define ROM_SIZE 0x080000 -

#define RAM_ADDR 0x080000
#define RAM_SIZE 0x080000
#define SUPERVISOR_ADDR 0x100000

#define DISABLE_INTERRUPTS() __asm__ volatile("move.w  #0x2700, %sr");
#define ENABLE_INTERRUPTS() __asm__ volatile("move.w  #0x2000, %sr");

#define VERSION "v0.1"
#define BUFF_SIZE 100

#define COMMAND_COUNT 4
#define COMMAND_LIST command[4]

typedef struct {
  const char *name;
  void (*function)();
} command;


extern char put_string(char *c);
extern char put_char(char c);
extern char read_char();



void run_command(char *buf) {}

void parse_line(char *buff) {}

void read_line(char *buff, uint8_t max) {
  for (uint8_t i = 0; i < max; i++) {
    buff[i] = read_char();
    switch (buff[i]) {
    case '\n':
      put_char('\n');
      buff[i++] = '\0';
      parse_line(buff);
      break;

    default:
      put_char(buff[i]);
    }
  }
}

void serial_loop() {
  char *buff;

  while (1) {
    put_string("> ");
    read_line(buff, BUFF_SIZE);
  }
}

int main() {
  put_string("\n\nWELCOME TO BASIC\n\n");
  serial_loop();

  return (0);
}
