#include <stdio.h>
#include <assert.h>
#include <limits.h>
_Static_assert(CHAR_BIT==8,"Eight-bit byte required for this memory comparison");
/* Bitwise ripple-carry addition keeps the counting arithmetic bitwise too. */
static unsigned bit_add(unsigned a,unsigned b) {
    while (b) { unsigned carry=(a&b)<<1; a^=b; b=carry; }
    return a;
}
static unsigned count_on(unsigned char reg) {
    unsigned count=0;
    while(reg) { count=bit_add(count,reg&1u);reg=(unsigned char)(reg>>1); }
    return count;
}
int main(void) {
    unsigned char reg=6;
    reg=(unsigned char)(reg|(1u<<7)); assert(reg==134);
    printf("set bit7: %u\n",(unsigned)reg);
    reg=(unsigned char)(reg&~(1u<<2)); assert(reg==130);
    printf("clear AC: %u\n",(unsigned)reg);
    reg=(unsigned char)(reg^(1u<<7)); assert(reg==2);
    printf("toggle bit7: %u, on=%u\n",(unsigned)reg,count_on(reg));
    reg=128;int dev=7;
    printf("reg & 1u << dev = %u; (reg & 1u) << dev = %u\n",reg&1u<<dev,(reg&1u)<<dev);
    signed char signed_reg=(signed char)reg; /* implementation-defined if not representable */
    printf("This platform: signed char after converting 128 = %d\n",signed_reg);
    for(unsigned value=0;value<256;value++) {
        unsigned array_count=0;char state[8];
        for(unsigned bit=0;bit<8;bit++) { state[bit]=(char)((value>>bit)&1u);array_count+=(unsigned)state[bit]; }
        assert(count_on((unsigned char)value)==array_count);
    }
    printf("All 256 register values verified; million homes: packed=%zu bytes, array=%zu bytes\n",
           1000000*sizeof(unsigned char),1000000*sizeof(char[8]));
    puts("Function precondition: device index 0..7; validate external indices before shifting.");
    return 0;
}
