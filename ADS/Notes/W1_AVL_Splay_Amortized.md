# AVL, Splay

## Feb24

# AVL

树的高度用边/节点个数来衡量 (考试会用单节点时的高度来标明)

BF(Balance Factor)：左子树高减右

* ~~判断题：能全部为+1？~~

在保持平衡的同时要注意二叉树条件`L<M<R`的保持

<u>多个冲突调离trouble maker(只有一个，即新插入的)**最近**的那个trouble finder(被破坏节点，可能有多个)</u>；通过递归的方式从下往上找trouble finder即可

然后从TF开始往下向着新插入的找两层看是LL/LR/RL/RR哪一个(==而不是从新插入节点向上两层==)

高为h的**最少**节点：f(h)=f(h-1)+f(h-2)+1 (f(0)=1还是f(1)=1要搞搞清楚)

# Splay

摊还代价为logN

将每次访问的节点翻转到根节点

跟AVL的区别：ZigZig/ZagZag和LL/RR：AVL是减少不平衡，因此是让中间的上去，Splay是让下面的上去。ZigZag和LR就一样了



为什么全部用单旋转(Zig)不行：不会显著改变path上其他节点的深度甚至有可能会往下推

==Zig：SingleRotation，仅在parent为根节点时进行==

ZigZag/ZagZig：DoubleRotation，同LR/RL(先转爸爸再转爷爷(此时已经是爸爸了))

ZigZig/ZagZag：SingleRotation，reverse(LL$\Rightarrow$RR, RR$\Rightarrow$LL，先转爷爷再转爸爸)

```c++
void splay(node *x) {	// Find
	while (x->parent) {
		if (!x->parent->parent) {      // Must use Single Rotation
			if (x->parent->left == x)  // Left Child
				right_rotate(x->parent);
			else
				left_rotate(x->parent);
		} else if (x->parent->left == x &&  // Zig-Zig
		           x->parent->parent->left == x->parent) {
			right_rotate(x->parent->parent);
			right_rotate(x->parent);
		} else if (x->parent->right == x &&  // Zag-Zag
		           x->parent->parent->right == x->parent) {
			left_rotate(x->parent->parent);
			left_rotate(x->parent);
		} else if (x->parent->left == x &&  // Zag-Zig
		           x->parent->parent->right == x->parent) {
			right_rotate(x->parent);
			left_rotate(x->parent);
		} else {  // Zig-Zag
			left_rotate(x->parent);
			right_rotate(x->parent);
		}
	}
}
```

删除：访问待删除元素，得到左右子树，访问左子树最大元素(一路向右)使其到 达根，将右子树作为左子树右儿子。

**势能函数**：$\displaystyle \Phi(T) = \sum_{i=1}^n\log S(i)$(S(i)表示子树i中总节点数，日中R(i)=logS(i)又被称为rank)

amortized cost 在PPT25

# Amortized(均摊) Analysis

均摊时间：log

例子：12 345，连续3次操作均值的上界为amortized bound，worst5，amortzied4，average3

|                  |                                                              |
| ---------------- | ------------------------------------------------------------ |
|                  | 这种方法用来确定一个n个操作序列的总代价的上界T(n)，因此每个操作的平均代价为T(n)/n |
| 对操作的度量     | 核算法：用来分析每个操作的摊还代价。核算法将序列中某些较早的操作的“余额”作为“预付信用”存储起来，与数据结构中的特定对象相关联。在操作序列中随后的部分，存储的信用即可用来为拿些缴费少于实际代价的操作支付差额 |
| 对数据结构的度量 | 势能法：也是分析每个操作的摊还代价，也是通过较早的操作的余额来补偿稍后操作的差额。势能法将信用作为数据结构的势能存储起来，且**将势能作为一个整体存储**，而**不是将信用与数据结构中单个对象关联分开存储**。 |



## Aggregate analysis聚合分析

n个操作（任意操作）序列worst是T(n)，则摊还代价为T(n)/n

pop()和multiPop()都需要push()来支持，三种栈操作的代价都是O(n)/n=O(1)

## Accounting method核算法

The difference between aggregate analysis and accounting method is that the later one assumes that the amortized costs of the operations may differ from each other.

核算法是对<u>不同的操作</u>赋予<u>**不同**的摊还代价</u>，这个代价可能与其实际操作代价不同，但是通过整体的调整，会使得对一系列操作的整体摊还代价的分析变得简单。

Ex. 20个人的生产队，初始估计的为amortized cost，实际需要食品量为actual cost，差值就是credit

$\rm \Large T_{amortized}= \frac{\sum \hat c_i(\geqslant \sum c_i)}{n}{}$

只要有办法保证估计的肯定不小于实际的就可以了，例如push=2

## Potential method势能法

<u>For potential method, a good potential function should always assume its **minimum** at the start of the sequence</u>

==势能与整个数据结构相关联，而不是特定对象==

势能法选择一个合适的势能函数，势能函数的值即是当前的总信用(+Φ_0)（类比核算法）。

D表示状态

==credit = Φ(D\_i)-Φ(D\_0) >= 0(经常用这个进行判定)，但是D_i-D_{i-1}没要求一定非负==

其中Φ()为势能函数

$\large\displaystyle \sum \hat c_i = \sum c_i+\Phi(D_n)-\Phi(D_0)$

动态数组的势能函数$\Phi(D_i) = 2T_{num}-T_{size}$(元素个数的两倍减去动态数组占用大小)

