#include <stdio.h>
unsigned long checks = 0;     /* number of divisions performed by the last call */
/* Returns 1 if n is prime, otherwise 0. */
int is_prime(unsigned long n)
{
    checks = 0;
    if (n < 2) return 0;
    // TODO 1: Try divisors i = 2, 3, 4 ... only while i * i <= n, adding 1 to checks
    //   for every division; return 0 as soon as a divisor is found, otherwise return 1
    for (unsigned long i=2; i<=n/i; ++i) {
        ++checks;
        if(n%i==0)return 0;
    }
    return 1;
}
int main(void)
{
    unsigned long tickets[] = {97, 100, 7919, 1000003};
    for (int k = 0; k < 4; k++) {
        int p = is_prime(tickets[k]);
        printf("%8lu  %-9s  divisions = %lu\n", tickets[k],
               p ? "prime" : "not prime", checks);
    }
    return 0;
}
