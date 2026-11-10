## Q3 - Device-status register (6 marks)

### Representation and the completed program
Bit d is one device, with 0=OFF and 1=ON. The exercise uses unsigned char and device indices 0..7. The separate tests require CHAR_BIT==8, making the one-byte/eight-device comparison explicit. External device indices must be validated before calling these low-level functions; negative or excessive shift counts are not supported.

| Operation | Bitwise expression |
| --- | --- |
| Set device d | reg OR (1u shifted left d) |
| Clear device d | reg AND complement of (1u shifted left d) |
| Toggle device d | reg XOR (1u shifted left d) |
| Test device d | (reg shifted right d) AND 1u |

The complete_code.c file preserves the supplied program and fills only its four TODO bodies. Converting the results to unsigned char keeps the intended register width. 1u makes the mask unsigned.

| Main statement | Predicted decimal | Predicted binary | Observed consequence |
| --- | --- | --- | --- |
| Initialize reg | 0 | 00000000 | Initial value |
| Switch LIGHT on | 1 | 00000001 | Bit 0 set |
| Switch AC on | 5 | 00000101 | First printed register |
| Toggle FAN | 7 | 00000111 | Bit 1 set |
| Switch LIGHT off | 6 | 00000110 | Second printed register |
| Test AC / PUMP | 1 / 0 | Bit 2 / bit 4 | ON / OFF |

show() and is_on() receive the register by value and do not alter it.

```text
00000101
00000110
AC is ON, PUMP is OFF
```

### Binary display, counting and signedness
show prints bits 7 down to 0 using right shift and &1u. The separate count_on function examines successive low bits. Its bit_add helper uses XOR for sum bits and (a&b)<<1 for carries, so even the counting arithmetic uses bitwise operators; loops and comparisons provide control. The count is at most eight. Exhaustive tests compare this count against an eight-element state array for every register value 0..255.

Shift has higher precedence than bitwise AND: reg & 1u << dev means reg & (1u<<dev). The alternative (reg&1u)<<dev first discards every bit except bit 0, then moves that single bit. With reg=128 and dev=7, the first result is 128 and the second is 0.

The signed-char conversion of 128 is implementation-defined when it cannot be represented. On this platform it produces -128. A signed register may therefore appear negative; promoting it to int can preserve that negative value, and right shift of a negative signed value is implementation-defined in the selected C17 rules. Left-shifting a negative signed operand is undefined. Setting bit 7 in an unsigned register itself is well-defined. Use unsigned storage and unsigned masks instead of depending on these signed effects.

```text
set bit7: 134
clear AC: 130
toggle bit7: 2, on=1
reg & 1u << dev = 128; (reg & 1u) << dev = 0
This platform: signed char after converting 128 = -128
All 256 register values verified; million homes: packed=1000000 bytes, array=8000000 bytes
Function precondition: device index 0..7; validate external indices before shifting.
```

### Array alternative and complexity
With char state[8], setting, clearing, toggling and testing can use state[d]=1, state[d]=0, state[d]^=1 and state[d]. For fixed valid d these operations are O(1) in both designs. One million homes use 1,000,000 versus 8,000,000 bytes for the state payload alone on this eight-bit-byte system, excluding unrelated structure padding and metadata.

For d variable devices, array scanning costs O(d), and bit scanning also costs O(d), with storage O(d) bytes versus O(ceil(d/8)) bytes. With d=8, both count routines are bounded O(1). The strict bitwise carry-adder costs up to O(log d) for an increment in a generalized implementation, so this particular bit-only counter has an O(d log d) upper bound; for eight devices this is still constant. A usual counter with ++count reduces the generalized scan bound to O(d). Arrays are easier to inspect and extend with richer state; packed bits are preferable when memory matters and a boolean state is sufficient.
