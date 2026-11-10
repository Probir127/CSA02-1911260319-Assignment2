#include <stdio.h>
#include <assert.h>
/* Monetary domain: non-negative paise, these bounded classroom fixtures. */
static long long percent(long long amount, unsigned rate) {
    return (amount * rate + 50) / 100; /* half-up at one paisa */
}
int main(void) {
    const int price[] = {100,999,199}, qty[] = {10,1,3}, senior[] = {1,0,1};
    const int predicted_total[] = {900,1048,537}, predicted_net[] = {900,998,537};
    const long long predicted_correct[] = {89250,99895,53282};
    puts("price,qty,senior,predicted_total,observed_total,predicted_net,observed_net,correct_paise");
    for (int i=0;i<3;i++) {
        int total=price[i]*qty[i]-price[i]*qty[i]*15/100*senior[i]+price[i]*qty[i]*5/100;
        int net=total>1000?total-50:total;
        long long gross=(long long)price[i]*100*qty[i];
        long long discount=senior[i]?percent(gross,15):0;
        long long taxable=gross-discount, tax=percent(taxable,5);
        long long after_tax=taxable+tax;
        long long payable=after_tax>100000?after_tax-5000:after_tax;
        assert(total==predicted_total[i] && net==predicted_net[i]);
        assert(payable==predicted_correct[i]);
        printf("%d,%d,%d,%d,%d,%d,%d,%lld\n",price[i],qty[i],senior[i],
               predicted_total[i],total,predicted_net[i],net,payable);
        printf("gross=%lld discount=%lld taxable=%lld GST=%lld payable=%lld paise\n",
               gross,discount,taxable,tax,payable);
    }
    int count=0; ++count; assert(count==1);
    puts("Correct counter update: ++count; count=1");
    assert((100000>100000?100000-5000:100000)==100000);
    assert((100001>100000?100001-5000:100001)==95001);
    puts("Rebate threshold: 100000 paise unchanged; 100001 paise -> 95001");
    return 0;
}
