# Binomial Queue

http://courses.zju.edu.cn:8001/download/processed/e803a9a557c385812c8506c6188744de31ecee82_HD.mp4?timestamp=1584277200&token=5152fdea03918a3459d3990519920bf5

为什么儿子要用Left？因为另一边(最Right)的没有儿子，越往Left儿子子树越大，因此查找越快



`!!`能巧妙地把0还是0，非0变成1



## Time

**FindMin**

O(logN)，如果有个ptrToMin来存则为O(1)

**Merge**

O(logN)

聚合函数：i次的link每2^i+1^发生一次

势能法：分析类似于二进制计数器翻转

**Insert**

单个：If the smallest nonexistent binomial tree is Bi , then Tp = Const · (i + 1).

均摊：Performing N Inserts on an initially empty binomial queue will take O(N) worst-case time.  Hence the average time is constant.

**DeleteMin**

FindMin(logN)+RemoveTree(1)+RemoveRoot(logN)+Merge(logN)=O(logN)

