#include <stdio.h>
#include <assert.h>
#include <math.h>
#include "loan.h"
static const char *name(Status s) {
    switch(s){case PAID:return "PAID";case NON_AMORTIZING:return "NON_AMORTIZING";
    case LIMIT_REACHED:return "LIMIT_REACHED";default:return "INVALID";}
}
static double formula(double principal,double rate,double payment) {
    if(principal==0)return 0;
    if(rate==0)return ceil(principal/payment);
    if(payment<=rate*principal)return INFINITY;
    return ceil(-log1p(-rate*principal/payment)/log1p(rate));
}
int main(void) {
    Loan base=simulate(1000000,200,200000,360,true);
    assert(base.status==PAID&&base.months==6&&base.interest==64538&&base.paid==1064538&&base.balance==0);
    printf("Baseline: months=%u total_interest=%lld total_paid=%lld paise\n",base.months,base.interest,base.paid);
    long long amounts[]={200000,100000,50000,25000,21000,20100,20001,20000,19999};
    puts("payment_paise,months,status,remaining_paise,total_interest_paise,unrounded_formula_months");
    for(unsigned i=0;i<sizeof amounts/sizeof amounts[0];i++){
        Loan r=simulate(1000000,200,amounts[i],360,false);
        printf("%lld,%u,%s,%lld,%lld,%.0f\n",amounts[i],r.months,name(r.status),r.balance,r.interest,
               formula(1000000,0.02,(double)amounts[i]));
        assert(r.months<=360);
        if(r.status==PAID)assert(r.paid==1000000+r.interest);
    }
    assert(simulate(10000,0,3000,360,false).months==4);
    assert(simulate(0,200,2000,360,false).months==0);
    assert(simulate(1000000,200,20000,360,false).status==NON_AMORTIZING);
    assert(simulate(1000000,200,20001,360,false).status==LIMIT_REACHED);
    assert(simulate(1000000,200,200000,2,false).status==LIMIT_REACHED);
    assert(simulate(-1,200,100,360,false).status==INVALID);
    assert(simulate(10000,200,0,360,false).status==INVALID);
    assert(simulate(10000,10001,100,360,false).status==INVALID);
    assert(simulate(10000,200,100,0,false).status==INVALID);
    /* Independently stated hand calculation, including each rounded interest. */
    const long long openings[]={1000000,820000,636400,449128,258111,63273};
    const long long expected_interest[]={20000,16400,12728,8983,5162,1265};
    for(unsigned i=0;i<6;i++)assert((openings[i]*200+5000)/10000==expected_interest[i]);
    puts("Hand schedule, zero-rate/principal, final payment, invalid data and safety-limit checks passed.");
    return 0;
}
