## Q1 - Precedence, associativity and the discount bug (6 marks)

### Assumptions and predictions
The given expression has no declared types. For a reproducible integer-division demonstration, price, quantity, senior, total and net are int; price is in whole rupees and senior is exactly 0 or 1. The fixtures are deliberately small enough to avoid int overflow. Monetary policy for the corrected program: apply 15% discount to the gross amount for seniors, apply 5% GST to the discounted amount, round each discount/tax component half-up to paise, then subtract Rs 50 only if the after-tax total exceeds Rs 1000. The brief does not specify whether the rebate changes the GST base; this solution explicitly uses the stated after-tax rebate order.

Predictions were written in PREDICTIONS.md before execution and committed before the output files. The predicted original results, then observed results, are:

| Price / quantity / senior | Predicted total / net (Rs) | Observed total / net (Rs) | Correct payable (Rs) |
| --- | --- | --- | --- |
| 100 / 10 / 1 | 900 / 900 | 900 / 900 | 892.50 |
| 999 / 1 / 0 | 1048 / 998 | 1048 / 998 | 998.95 |
| 199 / 3 / 1 | 537 / 537 | 537 / 537 | 532.82 |

### How C groups the expression
Multiplication and division have higher precedence than addition/subtraction. Multiplicative operators associate left-to-right, so price*qty*15/100*senior groups as ((((price*qty)*15)/100)*senior). Addition/subtraction also associate left-to-right. Assignment stores the completed right-hand result. These rules define grouping, not a general left-to-right order for evaluating all operands. There are no operand side effects in this total expression, so unspecified operand evaluation order does not change its mathematical result.

For 100 x 10, gross=1000, discount=150 and the original tax=50, yielding 900. Intended GST on 850 is 42.50, so the corrected bill is 892.50. For 999 x 1, 4995/100 truncates to 49 whole rupees; original total=1048, so net=998. Correct GST is 49.95. For 199 x 3, 8955/100 truncates to 89 and 2985/100 truncates to 29, yielding 597-89+29=537. In the corrected calculation discount=89.55, taxable=507.45, GST=25.3725 rounded to 25.37, total=532.82.

The original GST term taxes gross rather than discounted value for seniors. Integer division discards fractional rupees even when senior is false. Merely adding brackets cannot repair a wrong tax base or integer truncation. With floating operands the truncation changes, but the gross-tax logic bug remains. total>1000 is evaluated before the conditional ?: chooses exactly one branch; the strict > rule matches 'above Rs 1000'. The net expression inherits errors in total rather than being independently wrong for the chosen policy. Tests also check exactly 100000 paise and one paisa above it.

### Undefined counter statement and compiler evidence
count=count++ + 1 modifies count through both the postfix increment and assignment without the required sequencing between those side effects in C. It has undefined behaviour; no particular observed count is a valid portable result. The file is compiled to an object solely to capture the warning and is never executed. The actual Apple Clang diagnostic from gcc -Wall -Wextra is:

```text
Task01/undefined_example.c:2:42: warning: multiple unsequenced modifications to 'count' [-Wunsequenced]
    2 | int main(void) { int count=0; count=count++ + 1; return count; }
      |                                    ~     ^
1 warning generated.
```

The correction is ++count or count += 1 in its own statement. GNU GCC documents the related -Wsequence-point warning under -Wall; the local compiler reports -Wunsequenced. A warning diagnoses the problem rather than defining a result.

### Corrected design and alternative complexity
Use both intermediate variables and parentheses to make policy order visible:
```c
gross = (long long)price * 100 * qty;
discount = senior ? (gross * 15 + 50) / 100 : 0;
taxable = gross - discount;
tax = (taxable * 5 + 50) / 100;
after_tax = taxable + tax;
payable = after_tax > 100000 ? after_tax - 5000 : after_tax;
```
These formulas apply to non-negative, bounded paise. A real input-facing application must check price/quantity and product limits before multiplication. This demonstration uses fixed, asserted fixtures and does not claim to accept arbitrary input.

The original source repeats price*qty three times. A compiler may eliminate that repeated multiplication. Intermediate variables compute gross once and preserve component amounts for auditing; both designs remain O(1) time and O(1) space per bill. A handful of long long temporaries may occupy registers or stack slots, and optimization can remove them. The corrected algorithm's rounding and tax base intentionally change its arithmetic; its clarity is the main reason for choosing it, not an unsupported speed claim.

```text
price,qty,senior,predicted_total,observed_total,predicted_net,observed_net,correct_paise
100,10,1,900,900,900,900,89250
gross=100000 discount=15000 taxable=85000 GST=4250 payable=89250 paise
999,1,0,1048,1048,998,998,99895
gross=99900 discount=0 taxable=99900 GST=4995 payable=99895 paise
199,3,1,537,537,537,537,53282
gross=59700 discount=8955 taxable=50745 GST=2537 payable=53282 paise
Correct counter update: ++count; count=1
Rebate threshold: 100000 paise unchanged; 100001 paise -> 95001
```
