#### HW4

Chapter 4: 3, 5, 8, 9

Chapter5: 2, 7



##### chapter4

**3**：

For many of students, they try to regard program counter as a number, such as 1,2,3... and so on. But instruction pointer means it is a storage place for next instruction, and more important: It's a pointer!



**5**: 

a:the location 3 contain 0000 0000 0000 0000  , and location 6 contain 1111 1110 1101 0011 

b: 

- the location 0:x1E3 = 7747    and the location 1 :xF025= -4059

-  location 4 as an ASCII value is e

- the binary number is 0000 0110 1101 1001 1111 1110 1101 0011 

  the exponent is 13, the fraction is 101 1001 1111 1110 1101 0011 

  and the float is       $1.10110011111111011010011*2^{-114}$

- the location 0 as unsigned value is 7747, the location 1 as unsigned value is 61477

c: the instruction is ADD R7,R1,R3;

d:the location it reffers is 6, and the value in address 6 is 1111 1110 1101 0011



**8**:

the minimum number of bits required to represent the OPCODE is  **8**, because $2^8=256$ and 256 is bigger than 225 and $2^7<225$

the minimum number of bits required to represent the Destination Register is **7**,because $2^7=128$ and 128 is bigger than 120 and $2^6<120$

the maximum number of UNUSED bits in the instruction encoding is $32-8-3*7=3$, so the ans is 3.



**9**:

another important thing is PC increment, change the value of PC (add 1), ant the next instruction will be input auto;



##### chapter 5

**2**:

The MDR is at least 64 bits. The statement does not tell anything about the size of the MAR



**7**:

within an LC-3 ADD instruction the largest positive number we can represent literally is $15$, such as 0001 001 001 1 01111;