#ifndef COMMAND_STRUCT_H
#define COMMAND_STRUCT_H

#define COMMAND_COUNT    2

typedef struct
{
   const char *name;
   void (*fun)(int args, char *argv[]);
} command;

#endif
