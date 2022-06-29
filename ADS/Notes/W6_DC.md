# Divide and conqure

Backtrcking是DFS，越往深剪枝越准

DC是BFS，那么BFS适用于什么样的问题呢？启发式搜索，例如A*算法



**用BFS解4皇后问题**

通过启发式函数对节点进行评价，例如还剩多少个位置能摆(像井字棋中“还有多少种获胜方式”)

A*算法



Steps

Divide $\Longrightarrow$ Conquer $\Longrightarrow$ Combine

==T(N) = aT(N/b) + f(N)==，把N规模的分成a个子问题，每个的规模是N/b，f(N)是本层在Divide&Combine上花的时间



重要公式：$\Huge a^{\log_b^N} = N^{\log_b^a}$



### 最短点对问题

将点集分为两部分，求左边的最短路，右边的最短路，跨越分界线的最短路

其中跨越分界线的最短路的时间即为f(N)，需要降低尽量fN，

```
TN	= 2T(N/2) + cN (若fN为线性)
	= ....
	= 2^kT(N/2^k) + kcN
	= ....
	= N + cNlogN
	= O(NlogN)
	
TN	= 2T(N/2) + cN^2 (若fN为O(N^2))
	= ....
	= 2^kT(N/2^k) + cN^2(1+1/2 + ... + 1/2^{k-1})
	= ....
	= O(N^2)
```

找σ-strip，只在挡板内找，其中σ=min(左最短，右最短)/2

(假设挡板内节点个数为O(√N)(均匀分布的结论)

算法一，求挡板内任意两个点的距离，O(√N×√N)，但是如果不均匀，则会变成WorstCase：O(N^2^)

```cpp
/* points are all in the strip */
for ( i=0; i<NumPointsInStrip; i++ )
    for ( j=i+1; j<NumPointsInStrip; j++ )
        if(Dist(Pi ,Pj) < σ)
            σ = Dist( Pi , Pj );
```

算法二，在纵轴上也进行考虑

```cpp
/* points are all in the strip */
/* and sorted by y coordinates */
for ( i = 0; i < NumPointsInStrip; i++)			// O(√N)~O(N)
    for ( j = i + 1; j < NumPointsInStrip; j++)	// O(1)
        if ( Dist_y( Pi , Pj ) > σ ) // sorted 就是要确保这里能break
            break;
        else if ( Dist( Pi , Pj ) < σ )
            σ = Dist(Pi ,Pj );
```

Worst Case: 边界上有点，日字型，得找七个点(边界上既左又右)，f(N)变O(N)



## 三种方法

### Substitution Method

基本思路：猜一个解然后用归纳法证明(整就是一个数学归纳法？)

证：$T(N) = 2T(\lfloor N/2 \rfloor) + N \Longrightarrow T(N) = O(NlogN)$

T(|N/2|) <= c[N/2] log [N/2]

为什么T(N) = O(N)不行？

### Recursion-tree method

根据递归式用树的方式展开，TN是最低层节点和(Conquer)+每层节点和的和(Divide+Combine)

==最底层节点别漏了==

**例题**：TN = 3T(N/4) + $\Theta$(N^2^)

画树，节点的key表示自己的fN(Divide&Combine所花时间)，每个节点三个儿子，每个的key是自己的1/4；树高是log(4,N)，求每层的key之和

每层key(fN)之和为$\large (\frac{3}{16})^{k-1}cN^2$，==最底层有$\large 3^{\log_4N} = N^{\log_43}$个==(这个的证明自己推一下)

$\displaystyle T(N) = \sum_{i=0}^{log_4N-1}(\frac 3 {16})^i cN^2 + O(N^{<1}) = \frac{cN^2}{1-3/16} + O(N) = O(N^2)$

 fN在分支数>16时才起到改变T(N)的作用	



**例题**：TN = T(N/3) + T(2N/3) + cN

先用RT法猜(每层key和都是cN，深度为O(logN))出NlogN再用替代法证明

### Master Method

`T(N) = aT(N/b) + f(N)`

#### First Way

分三种情况，主要就是比较累加的两部分谁更强

1. ==fN=$\large O(N^{log_ba-\epsilon})$，TN = $\large \Theta(N^{log_ba})$==
2. fN=$\large \Theta(N^{log_ba})$，TN = $\large \Theta(N^{log_ba}logN) = \Theta( f (N)log_b N)$
3. ==fN=$\large \Omega(N^{log_ba+\epsilon})$，TN =$\large \Theta(f(N))$==

通过递归树法证明(PPT13)，得到$\displaystyle T(N) = \Theta(N^{log_ba}) + \sum_{i=0}^{log_bN-1}a_if(n/b^i)$

1. a=b
2. a>b，子问题空间有重叠，越分解工作量越大
3. a<b，

实际上就是

#### Second Form

1. If af(N/b) =$\kappa$f(N) for some constant $\kappa$< 1, thenT(N) = $\Theta$(f (N))
2. If af(N/b) = $\Kappa$f(N) for some constant $\Kappa$ > 1,  [W4_BQ.md](W4_BQ.md) thenT(N) = $\Theta (N^{\log_b a} )$
3. If af(N/b) = f(N), thenT(N) = $\Theta( f (N)log_b N)$

#### Third

如果$T(N) = aT(N/b) + \Theta(N^k \log ^pN)$

![](assets/image-20200616104545174.png)

