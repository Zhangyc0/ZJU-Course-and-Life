# External Sorting

[TOC]

## Intro

Why using merge sort? 快排之类的都是随机访问的，但是Merge是连续访问的，HDD可不支持随机访问(得寻道，找扇区，麻烦死了)



**概念区分**：

* Run：排好序的一段数据
* Pass：一趟，由于是对多个tape进行合并，且tape上的都是排好序的，因此一次pass中每个tape上的seek time也只有一次



To simplify – 

* Store data on tapes (can only be accessed sequentially)
* Can use at least 3 tape drives
* 一个run是存一次合并后的结果



关注点

* **Seek time = O(number of passes)** Bottleneck
* TIme of I/O of one block
* TIme to internally sort M records
* Time to merge N records from input buffer to output buffer

Computer can carry out I\O and CPU processing in parallel



**目标**

* Reduction of the number of passes
* Run merging
* Buffer handling for parallel operation
* Run generation

## Pass Reduction

### Use a k-way merge

<u>目的：reduce the number of passes?</u>

k-way：用堆，小的出去之后他的下一个进来，并且要确保新进来的比刚出去的大(否则说明这个run已经越界了)

* Number of passes = $\rm 1 + \lceil \log_k(N/M) \rceil$
    * N是总数，M是当前run内个数，所以N/M是当前run数？是的
* Tapes required: 2k

**Copy的问题**(以2-way为例)

传统的方法，merge完一次之后所有数据在一个tapes上，这样的话必然会造成在一个tape上前后跳着访问的情况，因此必须把其中一部分拷贝到另一个tape上

不均匀分配可以不用拷贝，使用斐波那契数列，

> Claim：如果有Fib(n)个runs，现在可以拆成Fib(n-1)和Fib(n-2)个runs的两组，分别在两个tapes。这种方法虽然要更多pass(因为分配不均衡)，但是省下了copy的时间。
>
> 称为Polyphase Merge
>
> 需要 k+1 tapes only(pass数也是k+1)

 如果run数不是Fib数，可以加上一些dummy number，排好序之后再去掉他们

`1 1 2 3 5 8 13 21 34 55`

## Parallel Operation

In general, for a k-way merge we need 2k input buffers and 2 output buffers for parallel operations.

## Run Generation and Merge

Generate a longer run. 能否弄一个run使得它能超过mem所能装的number的数量

*Replacement Selection方法*：用内存来放堆

幻灯片放映 [PPT](../../ADS/ADS_课件/ADS15ExternalSorting_TS.ppt) Slide10，一直pop直到新进来的比刚出去的小，就结束这个run(因为不能继续把smaller的放在这个run了)，把剩下的pop出去，直到没有上一个run的元素了

内存大小为M，则run平均长度能达到2M



## Minimize Merge Time

Use Huffman Tree

