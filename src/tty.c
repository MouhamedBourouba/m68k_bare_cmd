#include <stdint.h>

#define M68KATY_SERIAL_IN            (*(volatile uint8_t *)0x078000)
#define M68KATY_SERIAL_STATUS_RDF    (*(volatile uint8_t *)0x07C000)
#define M68KATY_SERIAL_STATUS_TXE    (*(volatile uint8_t *)0x07D000)
#define M68KATY_SERIAL_OUT           (*(volatile uint8_t *)0x07A000)

int init_tty()
{
   return(0);
}

void delay(uint16_t count)
{
   for (int i = 0; i < count; i++)
   {
      asm volatile (" ");
   }
}

void wait_read()
{
   while ((M68KATY_SERIAL_STATUS_RDF & 1) != 0)
   {
   }
}

void wait_write()
{
   while ((M68KATY_SERIAL_STATUS_TXE & 1) != 0)
   {
   }
}

char put_char(const char c)
{
   wait_write();
   M68KATY_SERIAL_OUT = c;
   return(c);
}

void put_string(const char *c)
{
   for (; *c != '\0'; c++)
   {
      put_char(*c);
   }
}

char read_char()
{
   wait_read();
   return(M68KATY_SERIAL_IN);
}
