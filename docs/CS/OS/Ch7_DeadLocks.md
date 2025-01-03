# Dead Locks

## Intro

- The Deadlock Problem
	- Definition
		- **A set** of **blocked processes** each holding a resource and waiting to acquire a resource held by another process in the set.
	- Resource instance
- System Model
	- Resource-Allocation Graph
		- 有环可能存在死锁
		- 无环不存在死锁
			![image-20241210214443900](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202412102144988.png)
- Deadlock Characterization
	- **互斥(mutual exclusion)**：死锁中的资源必须是非共享的，即一次只能被一个进程/线程使用；
	- **持有并等待(hold & wait)**：死锁中的进程/线程在等待资源的同时，也必须持有至少一个资源
	- **非抢占(no preemption)**：死锁中的进程/线程只能在使用完资源后主动释放资源，其持有的资源无法被其它进程/线程抢占
	- **循环等待(circular wait)**：死锁中的进程存在环状的等待资源关系，即 wait for graph 中存在环

- Methods for Handling Deadlocks
	- OS不做处理，交给programmer
	- 死锁预防、避免
	- 死锁检测、恢复
- Deadlock Prevention (预防)
	- 破坏死锁产生的必要条件之一
	- Mutual Exclusion
	- Hold and Wait 
		- 要么只有在没有任何资源的时候才能获取资源
		- 要么在执行之前（进入execute）获得所有资源
	- No preemption
		- 一个已经持有了部分资源的process申请其他不能被马上得到的资源时，当前的所有资源都被释放
		- 抢占可能使得另一个进程的任务被打断
	- Circular Wait
		- 通过给资源编号，规定进程/线程只能按特定的顺序申请资源，就不会出现循环等待的情况；
- Deadlock Avoidance (避免)
	- def
		- 阻止可能让系统进入死锁状态的行为
		- Requires that the system has some additional a priori information available
	- **safe sequence**
		- <img src="https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202412102202957.png" alt="image-20241210220238897" style="zoom:50%;" />
	- **Algorithms**
		- Single instance of a resource type.  Use a **resource-allocation graph**
		- Multiple instances of a resource type.  Use the **banker’s algorithm**
- Deadlock Detection 
	- 每个资源类别中**只有一个实例**
		- wait-for graph

<img src="https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202412102233172.png" alt="image-20241210223352092" style="zoom:50%;" />

- Recovery from Deadlock 