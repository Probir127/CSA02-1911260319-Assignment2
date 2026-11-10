#ifndef CSA02_LOAN_H
#define CSA02_LOAN_H
#include <stdbool.h>
typedef enum { PAID, NON_AMORTIZING, LIMIT_REACHED, INVALID } Status;
typedef struct { Status status; unsigned months; long long interest,paid,balance; } Loan;
Loan simulate(long long principal,unsigned rate_bp,long long payment,unsigned limit,bool print_rows);
#endif
