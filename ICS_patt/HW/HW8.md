# HW8

#### Chapter 9: 2, 3, 8, 9.a, 13, 15, 17, 18

#### Chapter 10: 3, 4, 11, 23



chapter 9:

**2:** 

- the trap vector is 8 bits, so totally there are 256  trap service routines be implemented

- the TRAP routine store the next instruction address in R7 and change PC to the TRAP instruction, but if we don't RET after trap routine, the PC willn't return to the correct address ( which STORE in R7).

  Unconditional Branch is also useless because it doesn't change PC

- only one time when the TRAP instruction will be zero-extend to the 16-bits and this 16-bits will be send to MAR and the value will be read in MDR.

**3:**

- I don't think the computer can restart only by instruction, maybe it need people to reset the highest bit of MCR(xFFFE)
- STI R0,MCR.
-  LD R1, SAVER1
- It will return to the next instruction after the HALT instruction. and RET will set PC to next instruction's address.

8:

 if the value of A is prime, the value in A will be stored 1, else the value in A will be stored 0.



**9.a:**

~~~assembly
;we will chcek the value of x4001 whether is x0000
ST R1,SAVER1;
AND R0,R0,#0;

LDI R1,ADDRESS;  LD the address intot R1;
BRnp RETURN;
ADD R0,R0,#1;
RETURN LD R1,SAVR1;
RET;

SaveR1 .FILL #0;
ADDRESS .FILL #4001;
	
~~~

13:

JSR B destoryed the value of R7;



**15**:
TRAP x72;

this service routine will run correctly, **but the value of R0 is changed**



17:

- LD R3, NEGENTER
- STR R0,R1,#0;
- ADD R1,R1,#1;
- STR R2,R1,#0;



18:

- ADD R1, R1, #1
- HALT
- ADD R0,R0,#5;
- BRzp k;



chapter 10:

3:

-  PUSH R1
- POP R0
- PUSH R3
- POP R7



4:

~~~assembly
;assume the begin of the stack is x3000;
PEEK R1,R1,#0; R1 is the return value ,if overflow R1 will be 1
LD R0,STACK;
NOT R0;
ADD R0,R0,#1;
ADD R0,R0,R6;
;check whether R0 is -x3000;
BRz FLOW; now R6 is address -x3000;
LDR R0,R6;
RET;

FLOW ADD R5,R5,#1;
RET


STACK .FILL x3000;

~~~

we don't need to check the overflow because it willn't happend in this action if POP,PUSH are correct.



11;

the content of x01F1 is 0x6200;

the content of x01F2 is 0x6300;

the name is trap vector table;



23:

this program reverse the input of user's input by using the stack.

