## HW5

#### Chapter 5: 15, 25, 33, 34, 35, 40, 41

#### Chapter 6: 3, 9, 10



##### chapter 5:

15: 

R1= 0X3121

R2= 0100 0101 0110 0110 =0x4566

R3= 1010 1011 1100 1101 = 0xabcd

R4= 1010 1011 1100 1101 = 0xabcd



**25**:

~~~assembly
NOT R4,R3;   R4 STORE the negative R3;
ADD R4,R4,#1;
ADD R1,R2,R4;
BRZ #5 ;
BRn #1 ;
BRp #2 ;
ADD R1,R3,#0;
BRnzp #1;
ADD R1,R2,#0;
TRAP x25;
~~~



**33**:

THis program contain a loop to AND every bits to check whether it is '1'

The value of R0 is 5 means the last eight number of R0 contains five '1' bits.

Like assume the last bits of R0 is xxxx xxxx, then there are exactly fve '1' in these bits.



**34**:

![image-20200710164404588](https://cdn.raynor.top/typora/202007/10/164406-903126.png)

the most import elements are ALU and REG File, but the LOGIC and finite state machine are also important.



**35**:

![image-20200710164707158](https://cdn.raynor.top/typora/202007/10/164708-591113.png)

the most important elements are ALU,REGFILE,IR,SEXT and SR2MUX, also LOGIC and finite state machine are also important.



**40**:

if the signal A is 1,  it means the opcode is 0000(BR) and exist a flag in N or Z or P,.So the signal A means whether the instruction is a **taken branch instruction.**



**41**:

a: if the global bus data is positive ,then the input of the storage element is 1, so y is 1. But if the global bus data is zero or negative ,the input of the input ofthe storage element is 0.

SO the Y is the condition P code.

b: the input of X means the oldest input will be storage in storage element, so if a opcode can change the state, it will be connect will the gate.

**But obvisouly opcode 0000(BR) shouldn't change the state.**,so the logic should not have the logic gate A



##### chapter6:

3:

~~~assembly
.ORIG x3000
AND R1,R1,#0;
ADD R1,R1,#1;
LDI R0,PTR1;

BRz #3;
ADD R1,R1,R1;
ADD R0,R0,#-1;
BRnzp #-4;

LDI R2,PTR2;
NOT R1,R1;
NOT R2,R2;
ADD R1,R1,R2;
STI R1, PTR2;

PTR1 .fill x4000;
PTR2 .fill x4001;
.END



~~~



![image-20200710161813185](https://cdn.raynor.top/typora/202007/10/161813-378318.png)



9:

~~~assembly
.ORIG x3000;
LD R0,DDD;
LD R1,Hun;
BRz #3;
TRAP x21;
ADD R1,R1,#-1;
BRnzp #-4;
Hun .fill #100
DDD .fill x7A;
;
HALT;
.END;
~~~

![image-20200710162939482](https://cdn.raynor.top/typora/202007/10/162940-156689.png)



10:

~~~assembly
.ORIG x3000;
AND R0,R0,#0;
AND R2,R2,#1;
BRz #1;
ADD R0,R0,#1;
TRAP x21;
HALT;
.END
~~~

![image-20200710163347581](https://cdn.raynor.top/typora/202007/10/163348-276956.png)

if it is odd, output is 1, else if it is even,output is 0.