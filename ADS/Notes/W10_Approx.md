01的那个证明没看懂，最后那个(1+ε)P <= P也搞不懂

## Theorem

### Approximation Ration

C是算法解，C\*是最优解

则如果有$\max(\frac{C}{C^*}, \frac{C^*}{C}) \leqslant \rho(n)$

称：algorithm achieves an **approximation ratio** of ρ(n), we call it a **ρ(n)-approximation algorithm**.

### Approximation scheme

【Definition】 An approximation scheme for an optimization problem is an approximation algorithm that takes as input not only an instance of the problem, but also a value ε > 0 such that for any fixed ε, the scheme is a **(1+ε)-approximation algorithm**.

We say that an approximation scheme is a polynomial-time approximation scheme (PTAS) if for any fixed ε > 0, the scheme runs in time polynomial in the size n of its input instance.

==近似算法有两个输入：一个是问题的实例 (instance)，另一个是$\varepsilon$ ，使得给定$\varepsilon$ ，近似比是$1+\varepsilon$==  

其中$\varepsilon$越小，精度越高，耗费时间有可能越长(?)

- 多项式时间近似模式 (PTAS, polynomial-time approximation scheme)
    - 给定任意有理数ε>0, 该模式可以在**输入规模n的多项式时间内**完成
    - 如$O(n^{2/ε}) $
- 完全多项式时间近似模式 (FPTAS, fully polynomial-time approximation scheme)
    - 给定任意有理数ε>0, 返回x的一个(1+ε)近似解在**n和1/ε的多项式(即次数为const)时间内**
    - 如$O((1/ε)^2n^3)$
- FPTAS $\subset$ PTAS 

# 实例

## Bin Packing

每个物品大小为0~1，箱子大小为1

### On-line

#### Next Fit算法

```pseudocode
void NextFit ( )
{   read item1;
    while ( read item2 ) {
        if ( item2 can be packed in the same bin as item1 )
            place item2 in the bin;
        else
            create a new bin for item2;
        item1 = item2;
    } /* end-while */
}
```

O(N)

【Theorem】 Let M be the optimal number of bins required to pack a list I of items.  Then next fit uses no more than 2M – 1 bins.  There exist sequences such that next fit uses 2M  – 1 bins.

证法：若NextFit需要了2M个箱子，则第2i-1和第2i个箱子的和必须>1，因此第1到第2M个箱子的和必须>M。因此最优解也至少要M+1个箱子。$最优 \geqslant \lceil NF/2 \rceil \Longrightarrow NF \leqslant 2最优-1$

#### First Fit算法

```pseudocode
void FirstFit ( )
{   while ( read item ) {
        scan for the first bin that is large enough for item;
        if ( found )
            place item in that bin;
        else
            create a new bin for item;
    } /* end-while */
}
```

O(NlogN)

【Theorem】Let M be the optimal number of bins required to pack a list I of items.  Then first fit never uses more than 17M / 10 bins.  There exist sequences such that first fit uses 17(M – 1) / 10 bins.

==去掉某个items，用的箱子可能更多==

#### Best Fit算法

Place a new item in the tightest spot among all bins.

T = O( N log N ) and bin no. ≤ 1.7M  

#### Addition

【Theorem】There are inputs that force any **on-line** bin-packing algorithm to use at least 5/3 the optimal number of bins.

### Off-line

View the entire item list before producing an answer.

Trouble-maker:  The large items

Solution:  **Sort** the items into non-increasing sequence of sizes.  <u>Then apply first (or best) fit – first (or best) fit decreasing.</u>



【Theorem】Let M be the optimal number of bins required to pack a list I of items.  Then first fit decreasing never uses more than 11M/9+6/9 bins.  There exist sequences such that first fit decreasing uses 11M/9+6/9 bins.



## Knapsack

### Fraction

> A knapsack with a capacity  M  is to be packed.  Given N items.  Each item  i  has a weight  wi  and a profit  pi .  If  xi is the <u>percentage</u> of the item  i  being packed,  then the packed profit will be  pixi .

Greedy: Use profit density pi/wi

### 0-1

> Same, but xi must be 1 or 0

#### Greedy Ver

如果还用greedy(`max{用max_profit, 用profit_density}`)，The approximation ratio is 2.

证：

p_max表示输入中最大profit，P_opt表示0-1的最优解，P_frac表示Fraction版本的最优解

有p_max <= P_greedy <= P_opt <= P_frac (显然)

因为即使用Fraction，也只有最后一个物品会被拆分，为了加上这个拆分的东西，就加上p_max保险，即P_greedy <= P_opt  (<= P_frac) <= P_greedy+p_max

因此P_opt/P_greedy <= 1+p_max/P_Greedy <= 2



#### DP ver

**Method**

W(i, p)表示 the <u>minimum weight</u> of a collection from {1, …, i } with total profit being **exactly** p

* 1: W(i, p) = wi + W(i-1, p-p_i)
* 0: W(i, p) = W(i-1, p)

$W(i, p) = \begin{cases}\infin & i=0\ (init) \\ W(i-1, p) & p_i > p\ (利润超了没必要增重 \\ \min\{W(i-1, p), w_i+W(i-1, p-p_i)\} & otherwise\end{cases}$

where i = 1, …, n;  p = 1, …,  p_max

**Analysis**

**O(n^2^p~max~)** (p~max~ = O(2^d^), where d is 输入的profit的最大值的二进制位数？？因为与p_max数量级基本一样？)

因此可以通过将profit的输入值整除的方法来加速，但是会稍减小精确度，使得(1+ε)P~粗算~ <= P~精确~，ε称为precision parameter



## K-center

<img src="assets/image-20200510103327597.png" style="zoom: 33%;" />

Input:  Set of **n** sites s1, …, sn

Center selection problem: Select **K** centers C so that the maximum distance from a site to the nearest center is minimized.

### Greedy

#### 一种 try again

依据：一个C\*的半径r(C\*)内的点集S，S中任一点要覆盖S的最小保证半径是2r(C\*)

👆和👇有什么关系:horse:

算法描述：给定半径r看行不行？行的话返回点集，不行的话报错

```pseudocode
Centers  Greedy-2r ( Sites S[], int n, int K, double r )
{   Sites  S’[] = S[]; /* S’ is the set of the remaining sites */
    Centers  C[] = ∅;
    while ( S’[] != ∅ ) {
        Select any s from S’ and add it to C;
        Delete all s’ from S’ that are at dist(s’, s) <= 2r;
    } /* end-while */
    if ( |C| <= K ) return C;
    else ERROR(No set of K centers with covering radius at most r);
}
```

【Theorem】 Suppose the algorithm selects more than K centers.  Then for any set C* of size at most K, the covering radius is r(C*) > r.

然后利用这个算法+BinarySearch找到r(C\*)

这个BinarySearch就类似于牛顿法在0到r_max之间找

```pseudocode
0 < r <= r_max, r = r_max/2
...
r_0 < r <= r_1, r = (r_0+r_1)/2
...
Solution radius = 2r_1 —— **2-approximation**
```



#### 另一种 far away

```pseudocode
Centers  Greedy-Kcenter ( Sites S[], int n, int K )
{   Centers  C[] = ∅;
    Select any s from S and add it to C;
    while ( |C| < K ) {
        Select s from S with maximum dist(s, C);	/* 找最远 */
        Add s it to C;
    } /* end-while */
    return C;
}
```

还是2-approximation