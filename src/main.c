#include <stdint.h>

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

extern char put_string(char *c);
extern char put_char(char c);
extern char read_char();

typedef struct
{
   const char *name;
   void (*fun)(int args, char *argv)
} command;

#define COMMND_COUNT    3

int strcomp(const char *str1, const char *str2)
{
   while (*str2 == *str1 && *str1 && *str2)
   {
      str1++;
      str2++;
   }

   return(*str1 - *str2);
}

void run_command(char *buf)
{
}

void parse_line(char *buff)
{
}

int get_command(const char *name, command *cmd)
{
   for (int i = 0; i < COMMND_COUNT; i++)
   {
      if (strcomp(name, COMMAND_LIST[i].name))
      {
         *cmd = COMMAND_LIST[i];
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
            for (int i = 0; i < COMMND_COUNT; ++i)
            {
               put_string(COMMAND_LIST[i].name);
            }
         }
         parse_line(buff);
         break;

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

command create_command(const char *name, void (*fun)(int args, char *argv))
{
   command cmd;
   cmd.name = name;
   cmd.fun = fun;
   return(cmd);
}

void version_command(int args, char *argv)
{
   put_string(VERSION);
}

int main()
{
   put_string("\n\nWELCOME TO CMD\n\n");

   serial_loop();

   return(0);
}
