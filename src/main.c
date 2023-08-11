#include "command_struct.h"
#include "stdint.h"

/* 68Katy memory map
 *
 * ROMBASE        EQU $00000
 * RAM            EQU $80000
 * RAMTOP         EQU $FFFFF  //100000-1
 *
 */

#define NULL               ((void *)0L)

#define ROM_ADDR           0x000000
#define ROM_SIZE           0x080000 -
#define RAM_ADDR           0x080000
#define RAM_SIZE           0x080000
#define SUPERVISOR_ADDR    0x100000

#define DISABLE_INTERRUPTS()    __asm__ volatile ("move.w  #0x2700, %sr");
#define ENABLE_INTERRUPTS()     __asm__ volatile ("move.w  #0x2000, %sr");

#define VERSION      "v0.1"
#define BUFF_SIZE    100

extern char put_string(const char *c);
extern char put_char(const char c);
extern char read_char();
extern void init_commands();

extern command COMMAND_LIST[COMMAND_COUNT];

int strcomp(const char *str1, const char *str2)
{
   while (*str2 == *str1 && *str1 && *str2)
   {
      str1++;
      str2++;
   }

   return(*str1 - *str2);
}

void parse_line(char *buff)
{
   uint8_t args;
   char ** argv;
   for (int i = 0; i < COMMAND_COUNT; ++i)
   {
      if (strcomp(COMMAND_LIST[i].name, buff) == 0)
      {
         COMMAND_LIST[i].fun(args, argv);
      }
   }
}

void read_line(char *buff, uint8_t max)
{
   for (uint8_t i = 0; i < max; i++)
   {
      buff[i] = read_char();
      switch (buff[i])
      {
      case '\n':
         put_char('\n');
         buff[i++] = '\0';
         if (strcomp(buff, "help") == 0)
         {
            for (int c = 0; c < COMMAND_COUNT; ++c)
            {
               put_string(COMMAND_LIST[c].name);
               put_char('\n');
            }
         }
         else
         {
            parse_line(buff);
         }
         return;

      default:
         put_char(buff[i]);
      }
   }
}

void serial_loop()
{
   char *buff;

   while (1)
   {
      put_string("> ");
      read_line(buff, BUFF_SIZE);
   }
}

int main()
{
   init_commands();
   put_string("\n\nWELCOME TO CMD\n\n");

   serial_loop();

   return(0);
}
