# HQM

==只记录一些特殊点，并不代表其他不用复习==

**结构**

* AVL熟悉例程
* Leftist Heap熟悉例程
* Binomial Queue熟悉例程

**基础算法**

* 贪心：只找本地最优，全局不一定是最优，并且不能反悔
* 分治：Divide+Recur+Conquer
* 动规：熟悉OMM和Floyd的例程
* 回溯：穷举搜索+剪枝，turnpike，决策树(+αβ)

**优化算法**

* 近似：
    * Bin Packing：online(不知道后面的情况，马上决定)/offline(所有的都知道了，可以先按高排序)，NF/BF/FF
* LS：
    * 顶点覆盖：Metropolis(为了跳出局部最优\\)+SimAnnealing
    * Hop
    * MaxCut：KL启发式搜索：允许有多个点不同
* 随机：通过随机来避免worst case提高效率
    * Hiring：k=N/e
    * QS：随机挑，分完不满足¼\~¾就重新挑
* 并行
    * 都要看
* 外排

**分析技术**

* NPC
    * 问题分类
        * undecidable
        * deciable
            * NP
            * NPC
    * 图灵机
        * D
        * NonD
    * Formal Language
* Amo
    * Ex
        * BQ: $\Phi_i$ = number of trees
        * Sp: $\Phi_i$ = $\sum_{i\in T}\log (S(i))$
        * Multi_Pop: $\Phi_i$ = number of elems in stack
        * Ske: $\Phi_i$ = number of *heavy* node



# 易混淆

**NPL**：当前节点到没有两个子节点(**至少一个为NULL**)的节点的最短路径长，<u>自平衡的依据</u> (左式堆)

Merge

**bh(x)**：从x节点开始往下的**黑**节点个数(所有同路一样的) (红黑树)



# 诡异题目

* To implement a binomial queue, <u>the subtrees of a binomial tree</u> are linked in <u>increasing</u> sizes. **False**
* <u>For potential method, a good potential function should always assume its **minimum** at the start of the sequence</u> **True**
* In an AVL tree, it is impossible to have this situation that the balance factors of **a** node and both of its children are all +1. **False**
* The difference between <u>aggregate</u> analysis and <u>accounting</u> method is that the later one assumes that the amortized costs of the operations may differ from each other. **True**
* 问B+数度为n的节点最多/最少有❓个的基本上都是完满n叉🌲
* If a problem can be solved by dynamic programming, it must be solved in polynomial time. **False**
    * https://blog.csdn.net/jim7424994/article/details/39926459
* In Work-Depth presentation, each time unit consists of a sequence of instructions to be performed concurrently; the sequence of instructions may include any number. **True**
* If only one tape drive is available to perform the external sorting, then the tape access time for any algorithm will be $\Omega(N^2)$ **True** (记住就好)
* 可以用逻辑等价转换
    <img src="assets/image-20200622204023680.png" style="zoom:33%;" />
* A language $L_1$ is polynomial time transformable to $L_2$ f there exists a polynomial time function f such that $w \in L_1$ if $f(w) \in L_2$. **False, iff**
* 



# 复杂度整理

树

|              | 访问x                                                        | 插入(amo)                   | m次插入 | 删除(amo) | m次删除 |
| ------------ | ------------------------------------------------------------ | --------------------------- | ------- | --------- | ------- |
| AVL          | O(logN)                                                      |                             |         |           |         |
| Splay        | O(logN) (amo)                                                |                             |         |           |         |
| RB           | O(logN)                                                      | O(1)                        | O(m+N)  | O(1)      | O(m+N)  |
| B+(M为order) | O(logN)<br />(深度为$O(\lceil \log_{\lceil M/2\rceil} N\rceil)$) | $O(\frac{M}{\log M}\log N)$ |         |           |         |

堆

|               | 访问最小        | 插入(amo) | m次插入  | 删除最小(amo) | Merge   |
| ------------- | --------------- | --------- | -------- | ------------- | ------- |
| BinHeap       |                 | O(logN)   |          | O(1)          |         |
| Leftiest      | O(1)            | O(1)      |          | O(logN)       | O(logN) |
| Skew          | O(1)            | O(logV)   | O(mlogN) | O(logN)       | O(logV) |
| BinomialQueue | O(logN) or O(1) | O(1)      |          | O(logN)       | O(logN) |

DP: 课件样例都是O(N^3^)，产品组装为O(N)

---

$$
{
    第k层个数：2^k
    \\
    第k层代价：\log N-k
    \\
    总瘫痪代价：(\sum_{k=1}^{\log N}{2^k(\log N - k)})/2^{\log N}
    = \sum_{k=1}^{H}{2^{k-H}(H - k)}
    = \sum_{i=0}^{H-1}{\frac{i}{2^i}}
    = O(1)
}
$$

