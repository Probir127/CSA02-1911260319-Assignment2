# Predictions recorded before executing the programs

Q1: All original operands are int rupees, with senior restricted to 0/1. For (price,qty,senior) = (100,10,1), original total/net = 900/900; (999,1,0) = 1048/998; (199,3,1) = 537/537. Corrected billing taxes the discounted amount, rounds discount and GST separately half-up to paise, and applies the Rs 50 rebate after tax only above Rs 1000: expected payable amounts 89250, 99895, 53282 paise. The unsequenced count statement will be compiled for its warning, never executed.

Q2: For i=0..999: senior=(i%4==0), eligible=(i%3!=0), card=(i%10==0). Senior-and-eligible is true for 166 records, so checking that first saves 166 card calls: 834 versus 1000 card-first or bitwise calls. Expected grants: 166+100-33=233. Nested if should match. An all-passenger card audit requires 1000 verifications.

Q3: Complete-code states after initialization/on LIGHT/on AC/toggle FAN/off LIGHT: 0,1,5,7,6. Printed binary: 00000101 and 00000110. AC on, pump off. Extra bit7 test: 6|128=134; clearing AC gives 130; toggling bit7 gives 2. Bit7 example reg=128,dev=7 gives reg&(1<<dev)=128 but (reg&1)<<dev=0.

Q4: Grades at 100,90,89,0,-1,101: S,S,A,F,?,?. Provided exercise: 100:S 95:S 83:A 50:D 49:F -5:?. Removing the S return makes 100 and 95 fall into A. Each valid boundary b=50,60,70,80,90 needs b-1,b,b+1, with -1,0,1,99,100,101 for domain edges.

Q5: Remainder tests for 97,100,7919,1000003: full trial 95,1,7917,1000001; square-root bound 8,1,87,999. for/while/do-while must match. These counts follow the supplied convention: checks counts n%i only. A safe n/i guard also performs a division and is counted separately. For n=2 and 3 the guarded versions should do zero remainder tests.

Q6: P=Rs10000,r=2% monthly,E=Rs2000. Closing balances in paise: 820000,636400,449128,258111,63273,0. Monthly interest: 20000,16400,12728,8983,5162,1265 paise. Last payment 64538 paise; total interest 64538 paise. Lower payments above interest should require more months; E<=Rs200 is non-amortizing. The 360-month limit must stop an unfinished loan without reporting it paid.

Q7: Choose repeated prime checks for 1000 tickets cycling 97,100,7919,1000003. The Q5 square-root trial performs (8+1+87+999)*250=273750 remainder tests. A sieve through 1000003 should perform zero remainder tests per lookup after preprocessing, with 1000004 char flags and 1000 lookups. Expected prime count 750. Objective: eliminate at least 99% of repeated query remainder tests while preserving all answers; count sieve markings separately rather than calling preprocessing free. Cross-check every integer through 1000003 against trial division before accepting the redesign.
