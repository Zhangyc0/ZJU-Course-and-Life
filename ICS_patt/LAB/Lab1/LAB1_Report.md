# LAB 1 Report

3190104611 Xuzheng Chen



### Lab Target 

This Lab need to write a program in  LC-3 machine language to detect whether or not a 16-bit value has at least three consecutive '1's.



### Algorithm

The algorithm is :

- Get number from x3100 in binary and storage it in register, init the register which needed.

- Do a loop to find 1

  - if now number is negative, it means the sign bit is 1, so we add 1 to counter
  - else if number is zero or positive, it means the  sign bit is 0, so we clean the counter

  if the counter is 3, then we break out.

  then we left shifted the now number and subtraction 1 to number counter.

- finally we check the number counter

  - 0 means it don't break out , we put 0 to register 010
  - else means it break out, we put 1 to register 010.

![image-20200708173827070](https://cdn.raynor.top/typora/202007/08/173827-75679.png)

### Code

~~~
0011 0000 0000 0000 ; (start address at 0x3000)


; This program use 5 register
;  001: the number of x3100    010: the left shifted of num
;  011:  the last number to shift   100: the number of '1'
;  101: the 100reg -3
0010 001 011111111; load 0x3100 number to reg001
0001 010 001 1 00000; 010 reg store the now number we check
0101 011 011 1 00000;  clean 011 register
0101 100 100 1 00000;  clean 100 register
0001 011 011 1 01111; add 011reg  15
0001 011 011 1 00001; add 011reg  1

0000 010 000001010;
    0001 010 010 1 00000;  reput condition code
    0000 011 000000010; 
        0001 100 100 1 00001; add 100reg   1
        0000 111 000000001;

        0101 100 100 1 00000; clear reg100
        0001 101 100 1 11101;
        0000 011 000000011; 
        0001 010 010 0 00010; left shifted 010reg
        0001 011 011 1 11111; add 011reg  -1; 
        
0000 111 111110101;

0101 010 010 1 00000; clean reg010
0001 011 011 1 00000;
0000 001 000000010;    postive or zero
    0001 010 010 1 00000; 
    0000 111 000000001;
0001 010 010 1 00001;

1111 0000 0010 0101 ; halt

~~~



### Test Results

![image-20200708172341832](https://cdn.raynor.top/typora/202007/08/172343-446651.png)