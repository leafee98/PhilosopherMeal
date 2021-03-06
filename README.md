# 哲学家就餐问题

## 问题描述

5个哲学家围绕餐桌呈环形就座, 每人左右都只有一根筷子, 每个人都需要同时拿到自己左右的两根筷子才能就就餐, 哲学家会进行思考和就餐, 在Linux下利用多线程模拟死锁以及应对思路.

## 应对思路

### 问题呈现

一共5个哲学家和5根筷子, 造成死锁的唯一情况就是5个人每人一根筷子, 相互之间等待另一根筷子而造成死锁.

### 最多4人就餐

如果最多只允许4人开始就餐, 那么每个人拿筷子时最差的情况是4个人都拿到了1根筷子, 第5个人因为已经有4个人开始就餐, 所以拒绝就餐, 所以还会剩下一根筷子, 着一根筷子可以用来满足任意一个哲学家的需要, 从而避免无限相互等待而造成的死锁.

另外, 如果从限制最大量的角度来避免死锁的话, 那么设避免死锁的最少资源数为``x``, 最大同时进行量为``m``, 单个个体运行所需资源量为``n``, 那么应当满足以下关系``x = (m - 1) * (n - 1) + n``, 即按照最坏情况, ``m - 1``个进程都只差1个资源便可以运行, 要求剩下的资源满足至少运行一个进程的需求.

### 奇数哲学家先取左筷子, 偶数哲学家先取右筷子

如果奇数的哲学家左侧筷子被占用, 那么此奇数哲学家将不再取右侧筷子, 从而右侧筷子可以给相邻的偶数哲学家进行使用, ~~懒得画图,~~ 以此类推, 总会有一个哲学家拿到自己先拿的一根筷子, 并且另一根不被其他哲学家先行占用.

### 一次取两根筷子

在最完美的实现中, 应该使用and型信号量, 如果不使用and型信号量的话, 也可以使用另一个信号量保护取左筷子和右筷子的过程来曲线救国. 关于使用and型信号量完成哲学家进餐问题的代码示例如下, ~~但是本人并没有找到and型信号量的实现方式以及所需的头文件~~:

```c++
semaphore chopstick[5] = { 1, 1, 1, 1, 1 };
void philosopher(int i) {
	while (true) {
		think();
		Swait(chopstick[i], chopstick[(i + 1) % 5]);
		eat();
		Ssignal(chopstick[(i + 1) % 5], chopstick[i]);
		think();
	}
}
```

将取左筷子和右筷子做成一个原子操作, 所以哲学家拿筷子时只能拿完两个筷子(但是不能办到条件不满足时一个筷子也不拿), 这种情况下整个餐桌最多只有一个哲学家在进行取筷子的操作, 一个哲学家取了一根筷子之后, 所有哲学家都不能再取筷子, 但是可以放回筷子, 这样就保证了占用取筷子这一操作的哲学家至少能在另一根筷子使用完毕后立即进餐.  从另一个方面来说, 这种原子操作限制的方法, 也可以认为是最多4人同时进餐的1人版.

但是需要注意这一做法的最坏情况, 即0号进餐时, 1号占用了旁边的一根筷子, 但是由于另一根筷子被0号占用, 所以进入阻塞, 等0号用餐结束1号取得筷子进餐时, 2号有占用了一根筷子并且由于1号占用的筷子而进入阻塞, 依次类推, 则变成了一个队列式的逐个运行. 在此情况下, 多线程丝毫没有发挥出并发的优势, 有着极大的浪费.

对于听说的共享内存来获取其他筷子状态的方式, 有在其他人的博客中, 提到共享内存并没有被读写保护, 如果需要保护, 仍然需要自己进行信号量的操作.([原博客](https://blog.csdn.net/ljianhui/article/details/10253345))

## 使用

您可以直接下载整个仓库, 然后在根目录使用``make``命令拿到帮助信息, 目前有3个编译目标, 以``make most4``为例, 此命令将会使用``/src/main_most4.cpp``作为主文件与其他的相关文件进行编译, 编译结果为``/a.out``, 您可以直接运行此文件来查看哲学家进餐问题的模拟情况.

## 关于

本项目始于操作系统课程的实验, 由于直接在Linux的vim中进行编写, 为以防文件误操作删除源码而后悔终生, 使用了git进行管理, 索性一不做二不休, 上传上来并且做了一定的文档.
