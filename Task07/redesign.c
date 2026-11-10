#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <time.h>
#include "../Task05/prime.h"
int main(void) {
    const unsigned long N=1000003, tickets[]={97,100,7919,1000003};
    unsigned char *flags=malloc((size_t)N+1);
    if(!flags){fputs("Cannot allocate sieve; no results issued\n",stderr);return 2;}
    clock_t start=clock();
    memset(flags,1,(size_t)N+1);flags[0]=flags[1]=0;
    unsigned long long marks=0,outer_tests=0;
    for(unsigned long p=2;p<=N/p;p++){
        ++outer_tests;
        if(!flags[p])continue; /* composites already have a smaller prime factor */
        for(unsigned long multiple=p*p;multiple<=N;multiple+=p){flags[multiple]=0;++marks;}
    }
    double build_ms=1000.0*(clock()-start)/CLOCKS_PER_SEC;
    unsigned long long rem=0,guards=0;unsigned original_primes=0,new_primes=0;
    start=clock();
    for(unsigned i=0;i<1000;i++){
        Counts c;original_primes+=prime_for(tickets[i%4],&c);rem+=c.remainders;guards+=c.guards;
    }
    double trial_ms=1000.0*(clock()-start)/CLOCKS_PER_SEC;
    start=clock();
    for(unsigned i=0;i<1000;i++)new_primes+=flags[tickets[i%4]];
    double lookup_ms=1000.0*(clock()-start)/CLOCKS_PER_SEC;
    assert(rem==273750 && original_primes==750 && new_primes==original_primes);
    puts("method,queries,prime_answers,query_remainders,query_guard_divisions,flag_bytes");
    printf("sqrt_trial,1000,%u,%llu,%llu,0\n",original_primes,rem,guards);
    printf("sieve,1000,%u,0,0,%zu\n",new_primes,(size_t)N+1);
    printf("Preprocessing: initialized_flags=%zu outer_tests=%llu marking_writes=%llu\n",(size_t)N+1,outer_tests,marks);
    printf("CPU_ms: trial=%.3f sieve_build=%.3f lookups=%.3f\n",trial_ms,build_ms,lookup_ms);
    for(unsigned long n=0;n<=N;n++){Counts c;assert((flags[n]!=0)==prime_for(n,&c));}
    printf("Exhaustive validation: all %lu inputs from 0 through %lu agree.\n",N+1,N);
    puts("Measured objective: 100% fewer query remainder tests; preprocessing and memory are additional costs.");
    free(flags);return 0;
}
