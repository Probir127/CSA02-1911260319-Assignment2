## Q2 - Short-circuit evaluation (4 marks)

### Experiment and predictions
Concession means (senior AND eligible class) OR verified disability card. A deterministic stub models the expensive card check by incrementing calls; it returns true when passenger index is divisible by 10. For indices 0..999, senior is index%4==0 and eligible is index%3!=0. No actual server or passenger records are used.

There are 250 seniors, of whom 84 have indices divisible by 12 and are ineligible, leaving 166 eligible seniors. Checking this cheap branch first makes 1000-166=834 card calls. There are 100 card holders and 33 overlap with eligible seniors, so 166+100-33=233 concessions. These are the predictions, independently checked by assertions.

```text
0 && verify: calls=0
1 || verify: calls=0
0 & verify: calls=1
version,passengers,card_calls,grants
eligible_first,1000,834,233
card_first,1000,1000,233
nested_if,1000,834,233
bitwise,1000,1000,233
audit_all,1000,1000,233
Verifier is a deterministic test stub; calls model expensive work, not network timings.
```

### Evaluation semantics and order choice
A false left operand of && skips its right operand; a true left operand of || skips its right operand. When the right operand is evaluated, the left side is sequenced before it. Logical operators produce 0 or 1. Bitwise & and | evaluate both operands and combine integer bits; they are not interchangeable with logical operators on arbitrary nonzero values (2&1 is zero although both values are logically true). In the experiment every condition returns 0 or 1, so the bitwise version grants the same 233 concessions but makes 1000 slow calls. It does not promise a left-to-right order for its operands. The fixture has only one counter-mutating verifier call in each expression.

For A&&B, a cheap, often-false A can avoid B; for A||B, a cheap, often-true A can avoid B. With pure independent checks, approximate expected work is cost(A)+P(A true)*cost(B) for AND and cost(A)+P(A false)*cost(B) for OR. Compare the reverse order rather than assuming 'cheapest first' is always optimal. Real dependencies and conditional probabilities also matter. The boolean result is unchanged by reordering pure commutative conditions; the number/cost of calls can change. Order is immaterial to savings when every needed operand is always evaluated anyway or both candidate orders have equal expected cost. Side effects and validity guards can make reordering incorrect even if the boolean formula seems equivalent.

### Changed audit requirement
Once verification writes an audit record, reordering also changes which 166 passengers are omitted from that log. If the policy is simply 'log each actual verification', the cheap branch may still run first, but the log must be described as a verification log, not a complete passenger audit. If the new requirement is to verify and record every passenger, perform verify(i) once unconditionally, then evaluate concession using its cached result. The audit_all experiment makes exactly 1000 calls while preserving the same 233 decisions. The recommendation therefore depends on the audit completeness requirement; performance must not silently decide that policy.

### Alternatives and complexity
The nested-if version implements the same lazy decision:
```text
if senior:
    if eligible: grant
    else: grant only if verify_card()
else:
    grant only if verify_card()
```
For n passengers and slow-call cost C, cheap-first/nested-if work is O(n + m*C), where m is the number not already granted by the cheap branch; here m=834. Card-first, unconditional audit and bitwise versions each make n card calls, O(n+n*C). All are O(n) if C is treated as constant, but measured operation counts expose the important constant difference. Calculation state is O(1) when streaming. Persisting one audit record per verification requires O(m) storage, or O(n) for a complete audit, outside the counter-only stub.
