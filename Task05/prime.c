#include "prime.h"
bool prime_full(unsigned long n,Counts *c) {
    *c=(Counts){0,0};if(n<2)return false;
    for(unsigned long i=2;i<n;i++){++c->remainders;if(n%i==0)return false;}
    return true;
}
static bool within(unsigned long i,unsigned long n,Counts *c) {
    ++c->guards;return i<=n/i; /* no i*i overflow; also performs a division */
}
bool prime_for(unsigned long n,Counts *c) {
    *c=(Counts){0,0};if(n<2)return false;
    for(unsigned long i=2;within(i,n,c);i++){++c->remainders;if(n%i==0)return false;}
    return true;
}
bool prime_while(unsigned long n,Counts *c) {
    *c=(Counts){0,0};if(n<2)return false;unsigned long i=2;
    while(within(i,n,c)){++c->remainders;if(n%i==0)return false;++i;}
    return true;
}
bool prime_do(unsigned long n,Counts *c) {
    *c=(Counts){0,0};if(n<2)return false;if(n<4)return true;
    unsigned long i=2;
    do {++c->remainders;if(n%i==0)return false;++i;}while(within(i,n,c));
    return true;
}
