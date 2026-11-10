#include <stdio.h>
/* Each bit of one byte stores the ON/OFF state of one device. */
enum { LIGHT = 0, FAN = 1, AC = 2, HEATER = 3, PUMP = 4 };
unsigned char switch_on(unsigned char reg, int dev)
{
    // TODO 1: Set the bit of device dev to 1 and return the new register value
    return (unsigned char)(reg | (1u << dev));
}
unsigned char switch_off(unsigned char reg, int dev)
{
    // TODO 2: Clear the bit of device dev to 0 and return the new register value
    return (unsigned char)(reg & ~(1u << dev));
}
unsigned char toggle(unsigned char reg, int dev)
{
    // TODO 3: Flip the bit of device dev and return the new register value
    return (unsigned char)(reg ^ (1u << dev));
}
int is_on(unsigned char reg, int dev)
{
    // TODO 4: Return 1 if the bit of device dev is 1, otherwise 0
    return (reg >> dev) & 1u;
}
void show(unsigned char reg)
{
    for (int bit = 7; bit >= 0; bit--) putchar(((reg >> bit) & 1u) ? '1' : '0');
    putchar('\n');
}
int main(void)
{
    unsigned char reg = 0;
    reg = switch_on(reg, LIGHT);
    reg = switch_on(reg, AC);
    show(reg);
    reg = toggle(reg, FAN);
    reg = switch_off(reg, LIGHT);
    show(reg);
    printf("AC is %s, PUMP is %s\n", is_on(reg, AC) ? "ON" : "OFF",
           is_on(reg, PUMP) ? "ON" : "OFF");
    return 0;
}
