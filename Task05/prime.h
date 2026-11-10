#ifndef CSA02_PRIME_H
#define CSA02_PRIME_H
#include <stdbool.h>
typedef struct { unsigned long remainders, guards; } Counts;
bool prime_full(unsigned long n,Counts *c);
bool prime_for(unsigned long n,Counts *c);
bool prime_while(unsigned long n,Counts *c);
bool prime_do(unsigned long n,Counts *c);
#endif
