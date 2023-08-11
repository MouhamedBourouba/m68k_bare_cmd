#include "command_struct.h"

#define VERSION    "1.0"

extern void put_string(const char *c);
extern void put_char(const char c);
extern int strcomp(const char *s1, const char *s2);

command COMMAND_LIST[COMMAND_COUNT];

command create_command(const char *name, void (*fun)(int args, char *argv[]))
{
   static int command_count = 0;
   if (command_count >= COMMAND_COUNT)
   {
      put_string("ERROR: CANT ADD MORE COMMANDS, PLZ INCREASE THE COMMAND_COUNT");
   }
   command cmd;
   cmd.name = name;
   cmd.fun = fun;
   COMMAND_LIST[command_count] = cmd;
   command_count++;
   return(cmd);
}

int get_command(const char *name, command *cmd)
{
   for (int i = 0; i < COMMAND_COUNT; i++)
   {
      if (strcomp(name, COMMAND_LIST[i].name) == 0)
      {
         *cmd = COMMAND_LIST[i];
         return(1); // Return success flag
      }
   }
   return(0); // Return failure flag
}

// command funs

void version_command(int args, char *argv[])
{
   put_string(VERSION);
   put_char('\n');
}

void info_command(int args, char *argv[])
{
   put_string("give info");
   put_char('\n');
}

void init_commands()
{
   create_command("version", version_command);
   create_command("info", info_command);
}
