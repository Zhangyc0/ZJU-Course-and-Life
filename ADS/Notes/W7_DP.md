# Dynamic Programing

何时使用？

* 是否是最优子结构 (一个问题的最优解包含其子问题的最优解)
* 子问题空间足够小但是重叠大‘
* 可以将问题存储在表中，而不需重构

**How to design a DP method?**

1. Characterize an optimal solution
2. Recursively define the optimal values
3. Compute the values in some order
4. Reconstruct the solving strategy

## 案例

### Fib

### 矩阵连乘

$\large T(N) = O(N^3)$

Z=XY，$Z(i, j) = \sum_{k=1}^n X(i, k)Y(k,j)$，耗时为mnk

`dp[i][j]`表示第i个到第j个的最小次数

```cpp
for (auto matNum = 2; matNum <= Total_MatNum; matNum++)
    for (auto iMat = 1; iMat <= Total_MatNum - matNum + 1; iMat++) {
        int Min = __INT_MAX__;
        for (auto i = iMat; i < iMat + matNum - 1; i++) {
            // [iMat, i][i+1, iMat + matNum - 1]
            auto tmp = dp[iMat][i] + dp[i + 1][iMat + matNum - 1] +
                       length[iMat - 1] * length[i] * length[iMat + matNum - 1];
            Min = tmp < Min ? tmp : Min;
        }
        dp[iMat][iMat + matNum - 1] = Min;
    }
```

### 最优(概率)二叉搜索树

$\large T(N) = O(N^3)$

这个推导式还挺复杂的，到时候直接画个简单的图试试看

`cost[i][j]`表示从第j个开始连续i个的最小cost

```cpp
for (auto i = 1; i < nodeNum; i++) {
    for (auto j = 0; j < nodeNum - i; j++) {
        weight[i][j] = weight[i - 1][j] + weight[0][j + i];
        cost[i][j]   = __DBL_MAX__;
    }
    for (auto j = 0; j < nodeNum - i; j++)
        // Type max = __DBL_MAX__;
        for (auto k = 0; k <= i; k++) {   // i+1 times
            auto tmp = weight[0][j + k];  // j+k as root
            // One subtree from j to j+k-1
            tmp += k > 0 ? cost[k - 1][j] + weight[k - 1][j] : 0;
            // Another subtree from j+k+1 to j+i
            tmp += k < i ? cost[i - k - 1][k + j + 1] + weight[i - k - 1][k + j + 1] : 0;
            if (tmp < cost[i][j]) {
                cost[i][j] = tmp;
                root[i][j] = j + k;
            }
        }
}
```

### 所有点对最短路

$\large T(N) = O(V^3)$

三层遍历点，然后以第一层的作为必经之点

`cost[i][j]`表示第i个到第j个的最小花费和

```cpp
for (auto k = START_POINT; k < nodeNum + START_POINT; k++)
    for (auto i = START_POINT; i < nodeNum + START_POINT; i++)
        for (auto j = START_POINT; j < nodeNum + START_POINT; j++)
            if (cost[i][k] + cost[k][j] < cost[i][j])
                cost[i][j] = cost[i][k] + cost[k][j];
```

### 产品组装

$\large T(N) = O(2N) = O(N)$

```cpp
for(stage = 1; stage <= n; stange++)	// stage必须在外层循环，这样才能两条线同时推进
    for(line = 0; line < 2; line++)
        f[line][stage] = MIN(f[line][stage-1] + t_process[line][stage-1], // 同一条线直接来
            f[1-line][stage-1] + t_transit[1-line][stage-1]));	// 另一条线跳过来
```

