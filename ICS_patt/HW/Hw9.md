# HW9



#### Chapter 14: 2, 4, 15

#### Chapter 17: 2, 5, 7



14.2:

- the dynamic link tell the begin address of action records, and it's also the now action's base address.
- it is the value of R7 which tell RET instruction where to JMP
- return value is the result of Sub Function, so if we don't return it , the Sub Function is maybe useless



14.4:

- caller
- callee
-  callee
- callee



14.15:

![img](https://cdn.raynor.top/typora/202007/24/002654-930663.jpeg)

to be honest, I don't read this questino clearly!

In my opinion, the return address is JSR address +1 and the function h 's record  cover the functino g 's





17.2:

No! like what we learn from Chapter 14, each callee has its own action records address, and the callee's is on the top of caller's always , so the return address is different and it is now caller's address.



17.5:

- 0
- 2
- 0

the function Power computer the max power of b that the result not bigger than a and it's biggest.

- **from the bottom to top, the value of '?' is 1 7 1 0 and the last '?' indicate to the right above of the first '?'**



17.7:

- for the main Function, it will contain 4\*2=8 bytes because it has a variable a, and for each Function SevenUp, it will contain 4\*2=8 bytes. SO totally we can 16*1024/8 -1 SevenUps Functinos LOOP. if we can recurise 2047 times, obviously the largest input is 2047.*
- the same as Question a , it will contain 4*1024/8-1=511 LOOP so the answer is the largest Number is 511.

