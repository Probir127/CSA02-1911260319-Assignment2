#include <stdio.h>
#include <assert.h>
static char ladder(int m) {
    if(m<0||m>100)return '?';
    if(m>=90)return 'S';else if(m>=80)return 'A';else if(m>=70)return 'B';
    else if(m>=60)return 'C';else if(m>=50)return 'D';else return 'F';
}
static char by_switch(int m) {
    if(m<0||m>100)return '?';
    switch(m/10){case 10:case 9:return 'S';case 8:return 'A';case 7:return 'B';
    case 6:return 'C';case 5:return 'D';default:return 'F';}
}
static char lookup(int m) {
    static const char grades[11]={'F','F','F','F','F','D','C','B','A','S','S'};
    return (m<0||m>100)?'?':grades[m/10];
}
/* Illustrative rules, because the assignment supplies no scholarship thresholds.
   Income <=250000: S/A full, B partial. Income <=500000: S/A partial.
   Others none. Returns -1 invalid, 0 none, 1 partial, 2 full. */
static int scholarship(int marks,long income) {
    char g=ladder(marks);
    if(g=='?'||income<0)return -1;
    if(income<=250000) {
        if(g=='S'||g=='A')return 2;
        if(g=='B')return 1;
    } else if(income<=500000 && (g=='S'||g=='A'))return 1;
    return 0;
}
int main(void) {
    int inputs[]={-1,0,1,49,50,51,59,60,61,69,70,71,79,80,81,89,90,91,99,100,101};
    puts("marks,ladder,switch,lookup");
    for(unsigned i=0;i<sizeof inputs/sizeof inputs[0];i++) {
        int m=inputs[i];char g=ladder(m);
        assert(g==by_switch(m)&&g==lookup(m));
        printf("%d,%c,%c,%c\n",m,g,by_switch(m),lookup(m));
    }
    for(int m=-2;m<=102;m++)assert(ladder(m)==by_switch(m)&&ladder(m)==lookup(m));
    int marks[]={95,85,75,65};long incomes[]={250000,250001,500000,500001};
    puts("marks,income,scholarship(0=none;1=partial;2=full)");
    for(unsigned i=0;i<4;i++)for(unsigned j=0;j<4;j++)
        printf("%d,%ld,%d\n",marks[i],incomes[j],scholarship(marks[i],incomes[j]));
    assert(scholarship(90,250000)==2 && scholarship(90,250001)==1);
    assert(scholarship(90,500000)==1 && scholarship(90,500001)==0);
    assert(scholarship(70,250000)==1 && scholarship(70,250001)==0);
    assert(scholarship(101,100)==-1 && scholarship(90,-1)==-1);
    puts("105 marks inputs and scholarship boundaries verified.");return 0;
}
