#include <stdio.h>
#include <assert.h>
static unsigned calls;
static int verify(unsigned i) { ++calls; return i%10==0; }
static int senior(unsigned i) { return i%4==0; }
static int eligible(unsigned i) { return i%3!=0; }
int main(void) {
    calls=0; int answer=0 && verify(0); assert(!answer && calls==0);
    printf("0 && verify: calls=%u\n",calls);
    calls=0; answer=1 || verify(0); assert(answer && calls==0);
    printf("1 || verify: calls=%u\n",calls);
    calls=0; answer=0 & verify(0); assert(!answer && calls==1);
    printf("0 & verify: calls=%u\n",calls);
    const char *names[]={"eligible_first","card_first","nested_if","bitwise","audit_all"};
    unsigned expected[]={834,1000,834,1000,1000};
    puts("version,passengers,card_calls,grants");
    for (unsigned version=0;version<5;version++) {
        calls=0;unsigned grants=0;
        for (unsigned i=0;i<1000;i++) {
            int grant=0;
            switch(version) {
            case 0:grant=(senior(i)&&eligible(i))||verify(i);break;
            case 1:grant=verify(i)||(senior(i)&&eligible(i));break;
            case 2:
                if (senior(i)) {
                    if (eligible(i)) grant=1;
                    else grant=verify(i);
                } else grant=verify(i);
                break;
            case 3:grant=(senior(i)&eligible(i))|verify(i);break;
            default: {
                int audited_card=verify(i); /* independent mandatory audit step */
                grant=(senior(i)&&eligible(i))||audited_card;break;
            }
            }
            grants+=(unsigned)grant;
        }
        assert(calls==expected[version] && grants==233);
        printf("%s,1000,%u,%u\n",names[version],calls,grants);
    }
    puts("Verifier is a deterministic test stub; calls model expensive work, not network timings.");
    return 0;
}
