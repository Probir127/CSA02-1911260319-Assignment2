#include <stdio.h>
#include <assert.h>
#include "prime.h"
int main(void) {
    unsigned long numbers[]={0,1,2,3,4,9,97,100,7919,1000003};
    puts("n,prime,full_remainders,for_remainders,while_remainders,do_remainders,for_guard_divisions,do_guard_divisions");
    for(unsigned k=0;k<sizeof numbers/sizeof numbers[0];k++) {
        unsigned long n=numbers[k];Counts a,b,c,d;
        bool p=prime_full(n,&a),q=prime_for(n,&b),r=prime_while(n,&c),s=prime_do(n,&d);
        assert(p==q&&q==r&&r==s&&b.remainders==c.remainders&&c.remainders==d.remainders);
        printf("%lu,%d,%lu,%lu,%lu,%lu,%lu,%lu\n",n,p,a.remainders,b.remainders,c.remainders,d.remainders,b.guards,d.guards);
    }
    for(unsigned long n=0;n<=10000;n++) {
        Counts a,b,c,d;bool p=prime_full(n,&a);
        assert(p==prime_for(n,&b)&&p==prime_while(n,&c)&&p==prime_do(n,&d));
    }
    puts("All four versions agree for 0..10000.");return 0;
}
