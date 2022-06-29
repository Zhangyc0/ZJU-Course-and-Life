随机算法和不确定图灵机一点关系没有(它还是根据确定的步骤来做的，所以是确定图灵机)



**目的**

* 减少worst case出现概率
* 提高求解效率
    * 随机打点求积分



$Pr[A]$ := the probability of the even A

$\overline{A}$ := the complementary of the even A (A did not occur)

\\	$Pr[A] + Pr[\overline A] = 1$

$E[X]$ := the expectation (期望，the “average value”) of the random variable X

\\	$E[X] = \sum_{i=1}^\infin(j \times Pr[X=j])$



## The Hiring Problem

* Hire an office assistant from headhunter 
* Interview a different applicant per day for N days
* $Interviewing\ Cost = C_i  \ll  Hiring\ Cost = C_h$
* Analyze interview & hiring cost instead of running time

Assume M people are hired. Total Cost: $O(N\cdot C_i+M\cdot C_j)$

### Naive Solution

```cpp
int Hiring ( EventType C[ ], int N )
{   /* candidate 0 is a least-qualified dummy candidate */
    int Best = 0;
    int BestQ = the quality of candidate 0;
    for ( i=1; i<=N; i++ ) {
        Qi = interview( i ); /* Ci */
        if ( Qi > BestQ ) {
            BestQ = Qi;
            Best = i;
            hire( i );  /* Ch */
        }
    }
    return Best;
}
```

Worst case：面试顺序升序或降序排列，不仅要么找一堆人/找不到人

#### Analysis on rand case

X = number of hires

$X_i = \begin{cases} 1 & {\rm i\ is\ hired} \\ 0 & {\rm i\ is\ not\ hired} \end{cases}$

$X = \sum_{i=1}^{N}X_i$

$E[X_i]=Pr[{\rm i\ is\ hired}] = \frac1i$

$E[X] = E[\sum X_i] = \sum E[X_i] = lnN+O(1)$

所以复杂度是$O(\ln N \cdot C_h + N \cdot C_i)$

### Randomized Algorithm

```cpp
int RandomizedHiring ( EventType C[ ], int N )
{   /* candidate 0 is a least-qualified dummy candidate */
    int Best = 0;
    int BestQ = the quality of candidate 0;

    randomly permute the list of candidates;// 打乱
	
    // Naive
```

对输入数据进行随机处理，然后再用naive算法。

随机数列算法

```pseudocode
void PermuteBySorting ( ElemType A[ ], int N )
{
    for ( i=1; i<=N; i++ )
        A[i].P = 1 + rand()%(N^3); 
        /* makes it more likely that all priorities are unique */
    Sort A, using P as the sort keys;
}
```

### Online Hiring

只挑一个人，挑到了之后的也不面了

```pseudocode
int OnlineHiring ( EventType C[ ], int N, int k ) {
    int Best = N;
    int BestQ = -infty ;
    for ( i=1; i<=k; i++ ) {	/* k个只面试不录取 */
        Qi = interview( i );
        if ( Qi > BestQ )   BestQ = Qi;
    }
    for ( i=k+1; i<=N; i++ ) {	/* 剩下的人遇到比之前k个最好的还好就要了，剩下的也不面试了 */
        Qi = interview( i );
        if ( Qi > BestQ ) {
            Best = i;
            break;
        }
    }
    return Best;
}
```

问题在于k怎么取

#### Analysis

Si := the ith applicant is the best

Pr[Si] = Pr[the best one is at i && no one at k+1~i-1 are hired] (这两个是独立事件)

\\          = (1/N) \* (前i-1个中最好的在前k个) = (1/N) \* (k/(i-1)) = $\large \rm \frac{k}{N(i-1)}$

$\displaystyle Pr[S] = \sum_{i=k+1}^{N} Pr[S_i] = \sum_{i=k+1}^{N}\frac{k}{N(i-1)} = \frac k N \sum_{i=k}^{N-1} \frac1i$

$\displaystyle \because \int_k^N \frac1x dx \leqslant \sum_{i=k}^{N-1} \frac1i \leqslant \int_{k-1}^{N-1} \frac1x dx$ 

$\displaystyle \therefore \frac{k}{N}\ln(\frac{N}{k}) \leqslant Pr[S] \leqslant \frac{k}{N}\ln(\frac{N-1}{k-1})$

求$\frac{k}{N}\ln(\frac{N}{k})$对应的k即可，求出来是$\large k = \frac{N}{e}$

## Quicksort

1/4和3/4之内都认为是均匀的

**Central splitter** := the pivot that divides the set so that each side contains at least n/4

**Modified Quicksort** := always select a central splitter before recursions



因此Pr[find a central splitter] = 0.5

**Claim: The expected number of iterations needed until we find a central splitter is at most 2.**



Type j : the subproblem S is of type j if $N(\frac34)^{j+1} \leqslant |S| \leqslant N(\frac34)^{j}$

Claim: There are at most $(\frac43)^{j+1}$ subproblems of type j.

$O(N\log N) \begin{cases} E[T_{type\ j}] = O(N(\frac34)^{j} \times (\frac43)^{j+1}) = O(N) \\ {\rm Number\ of\ different\ types} = \log_{4/3}N = O(\log N) \end{cases}$



从概率的角度来说挑两次差不多

时间复杂性可以用递归树方法分析

