# BackTracking

### 8Queen



### TurnPike

设给定N个点p1,p2,...,pNp1,p2,...,pN位于x轴上，xixi为pipi的坐标，假设x1=0x1=0且这些点从左至右分布。则每一对点之间都对应一个距离|xi,xj|, (i≠j)|xi,xj|, (i≠j)，共计有N(N-1)/2对点产生的距离。
收费公路重建问题就是根据距离的集合重新构造或确定一个点集合的分布，即已知M=N(N-1)/2个距离值，反解出N个点（的坐标）。
————————————————
版权声明：本文为CSDN博主「SanFanCSgo」的原创文章，遵循CC 4.0 BY-SA版权协议，转载请附上原文出处链接及本声明。
原文链接：https://blog.csdn.net/weixin_40170902/article/details/80856799



## MiniMax Strategy

### TicTacToe

例如井字棋，设**评估函数**W为当前状态下某方的可能赢的三条(Win Line)有W个，则f(P) = W_Computer - W_Me，我要使fP尽可能小

评估函数很重要

另外的评估函数：$\begin{cases}赢了：1\\平局：0\\输了：-1\end{cases}$

## α-β pruning

when both techniques are combined.  In practice, it limits the searching to only nodes, where N is the size of the full game tree.

http://inst.eecs.berkeley.edu/~cs61b/fa14/ta-materials/apps/ab_tree_practice/

https://www.bilibili.com/video/BV1XJ411n7Ee?from=search&seid=10293850935654516783

* α：max节点最大推算评估值
* β：min界定最小推算评估值

```
Max:                3
                /       \
               /         \ 
Min:          3          <=-4
            /   \        /   \
Max:       3    >=5    -4    ?
          / \   / \    / \
Min:	 -1  3  5  ?  -6 -4
```

<img src="assets/Screen Shot 2020-03-29 at 22.59.37.png" style="zoom: 25%;" />

想问一下为什么这个要被剪枝(白max黑min)？如果问号右边是5和4，那上边那个黑2就要变成4，在上边那个白2也要变成>=4，这样的话如果在旁边那个白色也大于3，那再上层的黑色就会是(min(>=4, >3))，这时候根节点就会选择右边，并且有可能走到问号这条路(~~如果问号比4还大~~(无所谓，因为这样的话上面那个黑色就会选择1而不是问号了，**这个黑色的<=1确保了路不会走到<=1这边**))





蒙特卡洛树搜索



Game Trees

