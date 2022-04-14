# HW7

### Chapter 8: 6, 9, 12, 14, 15, 16



6：

the programa will read a lot of same data, because if ready bit of KBSR is 0, that means there don't exist new data or the data have been read.

9:

if the keyboard hardware does not check the KBSR before writing to KBDR, maybe the programa will not read the correct input and the lastest input maybe fill the older one.

12:

~~~assembly
START LDI R1,A
BRz START
LDI R0,B
AND R1,R1,#0;
STI R1,A
BR NEXT_WORK

A .FILL xFE00; the address of KBDSR maybe 
~~~



14:

we don't care the date load from KBSR or 0xFE02, because for user ,the KBSR is the same as 0xFE02, because the KBSR is mapping to oxFE02, so we don't need to know.

15:

a: they will output '2' continue, because the 14bit of KBSR was set 1, so it has the ability to interrupt.

b: the char of what you typed will be ouput to screen twice;

c: the programa will halt and stop to output '2',



16:

It will output ABCDEFGHI in steps.