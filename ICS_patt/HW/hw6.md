# HW6

#### Chapter 6: 3

#### Chapter 7: 4, 7, 18



**3**：

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

**4**：

| Symbol | Address |
| ------ | ------- |
| TEST   | x301F   |
| FINISH | x3027   |
| SAVE3  | x3029   |
| SAVE2  | x302A   |

![image-20210715174807056](C:\Users\MSI-NB\Desktop\7y.4)

**7**:

~~~assembly
.ORIG x3000;
AND R1,R1,#0;
ADD R2,R1,#1;  R2 is 1 and continue left shift
BRz NEXT; NEXT INSTRUCTION
AND R3,R0,R2;
BRz #1;
ADD R1,R1,#1;
ADD R2,R2,R2;
BR #-6;
NEXT HALT;
.END
~~~

![image-20200713132727632](C:\Users\cxz666\AppData\Roaming\Typora\typora-user-images\image-20200713132727632.png)



**18**:

~~~assembly
a: LDR R3,R1,#0;
b: NOT R3,R3;
c: ADD R3,R3,#1;

~~~





| register file |  value  |
| :-----------: | :-----: |
|      R0       | 0X A400 |
|      R1       | 0X 23FF |
|      R2       | 0X E1FF |
|      R3       | 0X A401 |
|      R4       | 0X 0000 |
|      R5       | 0X 0000 |
|      R6       | 0X 0000 |
|      R7       | 0X 0000 |

![image-20210715175820481](C:\Users\MSI-NB\Desktop\7.8.JPG)
