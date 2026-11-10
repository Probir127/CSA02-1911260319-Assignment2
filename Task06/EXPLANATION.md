## Q6 - Loan repayment and termination (8 marks)

### Monetary model and loop choice
All money is long long paise. A rate of 200 basis points means 2% per month. Interest is added first, rounded half-up once per month using (balance*rate_bp+5000)/10000, followed by payment. The brief does not define a rounding policy; this policy is explicit and used consistently in the hand calculation and program. A while loop fits an unknown month count and skips the schedule entirely if the initial balance is zero.

```text
validate principal, monthly rate, repayment and month limit
while balance > 0:
    if months == safety_limit: status=LIMIT_REACHED; break
    interest = round_half_up(balance * monthly_rate)
    if repayment <= interest: status=NON_AMORTIZING; break
    actual_payment = minimum(repayment, balance + interest)
    balance = balance + interest - actual_payment
    accumulate interest and actual payment; increment months
    print the month's row
```
The final payment is capped at amount due, so the balance reaches exactly zero without an overpayment. Floating balance!=0 can be unsafe because representation and subtraction may leave a tiny residual or a negative balance; epsilon tests can also obscure contractual rounding. Integer paise makes this stopping condition exact within the chosen monetary policy.

If repayment is below interest, debt increases; if equal, it does not decrease. Neither is a successful repayment plan. The program rejects such a schedule before issuing a fictitious payment row. With a fixed non-negative rate and rounding, a strictly decreasing balance cannot make monthly interest increase, so an initially amortizing payment continues reducing the debt. A reduction of at least one paisa per month gives mathematical termination, but that alone is not a practical duration guarantee.

### Independent hand schedule, verified row by row
| Month | Opening (Rs) | Interest (Rs) | Payment (Rs) | Closing (Rs) |
| --- | --- | --- | --- | --- |
| 1 | 10000.00 | 200.00 | 2000.00 | 8200.00 |
| 2 | 8200.00 | 164.00 | 2000.00 | 6364.00 |
| 3 | 6364.00 | 127.28 | 2000.00 | 4491.28 |
| 4 | 4491.28 | 89.83 | 2000.00 | 2581.11 |
| 5 | 2581.11 | 51.62 | 2000.00 | 632.73 |
| 6 | 632.73 | 12.65 | 645.38 | 0.00 |

Monthly rounded interest totals Rs645.38; total payments are Rs10645.38. Month 4 interest 89.8256 rounds to 89.83, month 5 interest 51.6222 rounds to 51.62, and month 6 interest 12.6546 rounds to 12.65. The program asserts six months, the exact interest and paid totals, and checks the six independently specified interest amounts.

### Growth as repayment approaches interest
The prediction is that repayment closer to the first month's Rs200 interest requires more iterations, with no repayment at or below Rs200. The measured results confirm that trend:

| Monthly repayment (Rs) | Executed months | Status | Remaining balance (Rs) |
| --- | --- | --- | --- |
| 2000.00 | 6 | PAID | 0 |
| 1000.00 | 12 | PAID | 0 |
| 500.00 | 26 | PAID | 0 |
| 250.00 | 82 | PAID | 0 |
| 210.00 | 154 | PAID | 0 |
| 201.00 | 268 | PAID | 0 |
| 200.01 | 360 | LIMIT_REACHED | 9425.52 |
| 200.00 | 0 | NON_AMORTIZING | 10000.00 |
| 199.99 | 0 | NON_AMORTIZING | 10000.00 |

The 360 limit is a deployment policy, not evidence of repayment or proof the loan could never finish. On reaching it, report 'schedule incomplete after 360 months', the remaining balance, and request revised terms or an explicitly approved longer projection. Do not label the result PAID. The test with Rs200.01 leaves Rs9425.52 outstanding; the unrounded formula estimates 501 months, so the limit is meaningful. Zero principal, zero rate, invalid negative principal, zero payment, invalid rate and invalid limit are also tested.

### Bounds and formula alternative
Accepted principal and payment are each at most 10^12 paise, rate at most 10000 basis points (100% monthly), and safety limit at most 100000 months. A non-amortizing schedule stops before accumulation; an accepted one has balance no greater than principal. Thus balance*rate+5000 is at most 10^16+5000, due at most 2*10^12, and accumulated interest/payment at most about 10^17 paise, safely below the minimum long long maximum. These are validation limits for the classroom function, not suggested loan terms.

The formula n=-log(1-r*P/E)/log(1+r) comes from a constant-rate, constant-payment recurrence without monthly rounding. For P>0, r>0, it requires E>r*P; use ceil(n), log1p(-r*P/E), and log1p(r) to reduce cancellation. Handle r=0 separately as ceil(P/E), P=0 as zero, and E<=r*P as non-amortizing. The demonstration applies the formula only after supplying valid bounded fixtures. Near E=r*P the argument approaches zero and the estimate becomes sensitive to rounding.

Formula evaluation is O(1) time/O(1) state in the fixed-precision operation model; simulation is O(m) for m months, capped by the safety limit, and O(1) working state when rows stream out. Storing all rows takes O(m). The formula cannot produce a full month-by-month schedule or enforce the selected monthly-paisa rounding by itself. It is useful as an estimate and cross-check, while integer simulation is retained for the issued schedule. Formula and rounded simulation match the paid fixtures here; that is not a guarantee for every input.

```text
month,opening_paise,interest_paise,payment_paise,closing_paise
1,1000000,20000,200000,820000
2,820000,16400,200000,636400
3,636400,12728,200000,449128
4,449128,8983,200000,258111
5,258111,5162,200000,63273
6,63273,1265,64538,0
Baseline: months=6 total_interest=64538 total_paid=1064538 paise
payment_paise,months,status,remaining_paise,total_interest_paise,unrounded_formula_months
200000,6,PAID,0,64538,6
100000,12,PAID,0,127032,12
50000,26,PAID,0,289875,26
25000,82,PAID,0,1031912,82
21000,154,PAID,0,2228652,154
20100,268,PAID,0,4383119,268
20001,360,LIMIT_REACHED,942552,7142912,501
20000,0,NON_AMORTIZING,1000000,0,inf
19999,0,NON_AMORTIZING,1000000,0,inf
Hand schedule, zero-rate/principal, final payment, invalid data and safety-limit checks passed.
```
