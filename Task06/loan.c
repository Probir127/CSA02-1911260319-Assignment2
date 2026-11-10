#include "loan.h"
#include <stdio.h>
/* Domain bounds make balance*rate_bp+5000 and totals safe in long long.
   rate_bp=200 means 2% per month. Monthly interest rounded half-up to paise. */
Loan simulate(long long principal,unsigned rate_bp,long long payment,unsigned limit,bool print_rows) {
    Loan r={INVALID,0,0,0,principal};
    if(principal<0||principal>1000000000000LL||rate_bp>10000||payment<=0||
       payment>1000000000000LL||limit==0||limit>100000)return r;
    r.status=PAID;
    if(print_rows)puts("month,opening_paise,interest_paise,payment_paise,closing_paise");
    while(r.balance>0) {
        if(r.months==limit){r.status=LIMIT_REACHED;break;}
        long long interest=(r.balance*rate_bp+5000)/10000;
        if(payment<=interest){r.status=NON_AMORTIZING;break;}
        long long due=r.balance+interest,actual=due<payment?due:payment;
        long long opening=r.balance;
        r.balance=due-actual;r.interest+=interest;r.paid+=actual;++r.months;
        if(print_rows)printf("%u,%lld,%lld,%lld,%lld\n",r.months,opening,interest,actual,r.balance);
    }
    return r;
}
