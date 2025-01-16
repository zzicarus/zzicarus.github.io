# 题目汇总

## Overview

![image-20241024132806286](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202410241328386.png)

---

**进程与线程**

![image-20250103222601359](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202501032226464.png)

![image-20250103202946188](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202501032029303.png)

![image-20250103205848659](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202501032058738.png)

- 一个进程镜像由程序、数据和PCB组成，其中==共享代码段==必须用可重入编码
- 区分饥饿和死锁
	- 死锁是由于对临界资源访问，等待lock
- 一个进程在互斥信号量mutex上执行V(mutex)导致唤醒了另一个进程，执行V后，**mutex <= 0**
- 系统有n个进程，ready queue最多n-1个，wait queue最多n个
- ==After== do P(S), 使得该进程进入等待队列的条件是 S < 0 (注意这里是在做了P(S)之后的状态)
- 在临界区的时候，其他进程/线程都可以进行调度，只是他们不能够访问相同的临界区资源

**内存**

- 工作集页面都在==主存==内（而不是虚拟存储器中）则能够使进程有效运行，否则出现频繁的swap in & out
- 页面分配策略为固定分配的情况下，不能使用的替换策略是全局替换
	- 连续内存分配(contiguous memory allocation)问题中，我们认为所有进程都被囊括在一段完整的内存中。而在内存分配的动态过程中，整个内存中空闲的部分将有可能被分配给索取内存的进程，而被分配的内存在释放之前都不能被分配给其它进程。在进程执行完毕后，内存会被释放，切我们对于进程何时释放内存不做假设。
	- 所以不可能发生进程之间的 swap-in&out

![image-20250103222644101](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202501032226175.png)

- 页缓冲队列用于存储最近换出的页面，帮助提高页面重新加载的效率。
	- 它优化了页面调入速度，但不会改变缺页是否发生，因此不影响缺页率。

![image-20250103223332693](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202501032233790.png)
