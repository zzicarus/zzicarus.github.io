# 并发控制

## **Two-Phase Locking Protocol** | 两阶段封锁协议

<img src="https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202406120054297.png" alt="image-20240612005442143" style="zoom:33%;" />

- 无法保证可恢复性

=> 是冲突可并行的充分条件，但不是必要条件；满足两阶段封锁协议，一定可冲突串行化，但可冲突串行化，不一定满足两阶段封锁协议

**strict | 严格的**

a transaction must hold all its exclusive locks **till it commits/aborts.**

- 排他锁维持更长的时间
- Ensures recoverability and avoids cascading roll-backs

**rigorous | 强**

- 所有的锁都到最后（commit/abort）才释放 
- Transactions can be serialized in the order in which they commit.

### Lock Conversion

U Lock, 先读后面可能会写

**Growing**

- upgrade

**Shrinking**

- downgrade

### Automatic Acquisition of Locks

`write`

```sql
 The operation write(D) is processed as:
 if Ti has a lock-X on D
 then
 	write(D)
 else begin
 	if necessary wait until no other trans. has any lock on D,
 	if Ti has a lock-S on D
 		then
 			upgrade lock on D to lock-X
 	else
		grant Ti a lock-X on D
 	write(D)
 end;
```

## Dead Lock | 死锁

> System is **deadlocked** if there is a set of transactions such that every transaction in the set is waiting for another transaction in the set.  两个事务相互等待。
>
> - 死锁是基于锁协议共有的问题
>
> ![image-20240611232202759](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202406112322824.png)

**Deadlock Prevention**



**Timeout-Based Schemes**

- a transaction waits for a lock only for a specified amount of time. After that, the wait times out and the transaction is rolled back.

- thus deadlocks are not possible

- simple to implement; but **starvation** is possible. Also **difficult to determine good value** of the timeout interval. 一直无法获得锁，一直在等待

### Detection

**wait-for Graph**

- $T_i -> T_j，前一个等待后面的$

### Recovery

- Some transaction will have to rolled back (made a **victim**) to break deadlock.  选择牺牲者
    - Select that transaction as victim that will incur minimum cost.
- Rollback -- determine how far to roll back transaction  回滚
    - **Total rollback:** Abort the transaction and then restart it.
    - **Partial rollback**: Roll back victim transaction only as far as necessary to release locks that another transaction in cycle is waiting for.

##  Graph-Based 

>  对数据的访问有一定“预知”

### Tree Protocol

<img src="http://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202406112347099.png" alt="image-20240611234708975" style="zoom:33%;" />



1. 只有排他锁
2. 第一个锁可以加到任何地方，但是之后的锁要加的数据 的父节点一定要有锁
3. 锁用过之后就可以随时放掉
4. 同一个节点不能重复加锁（lock - unlock - lock ×）

**好处**

- 冲突可串行
- 不会产生死锁，deadlock-free
- 可以早点放锁，提高了并发度、吞吐率

**缺点**

- 不保证可恢复性  recoverability. 可能读取脏数据
    - 可通过添加“提交依赖”来保证这一点
- 可能锁住更多不需要的数据，lock more data items 
    —— 比如同时访问根节点和某一个叶子节点，就需要按照Tree的一条path锁到叶子节点

## Multiple Granularity | 多粒度

Granularity of locking (level in tree where locking is done):

-  **Fine granularity** (细粒度) (lower in tree): high concurrency, high locking overhead
- **Coarse granularity** (粗粒度) (higher in tree): low locking overhead, low concurrency

<img src="https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202406120004561.png" alt="image-20240612000432340" style="zoom: 50%;" />

- 可以在更大的粒度上面加锁

**Intension Lock**

在一个节点显式加锁之前, 对他的父节点加意向锁

**相容表**

<img src="https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202406120015105.png" alt="image-20240612001459905" style="zoom: 33%;" />

- 在粗粒度上面加锁，可以先不去管下面的细粒度是否会冲突；**意向**

![image-20240612011019748](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202406120110999.png)

!!! example "example"
	![image-20240612001931663](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202406120019972.png)
	- 加锁从上面
	- Unlock从下面



## Insert and Delete Operations

- Locking rules for insert/delete operations
    - An exclusive lock must be obtained on an item before it is deleted	自动加排他锁
    - A transaction that inserts a new tuple into the database  automatically gives an X-mode lock on the tuple

### Phantom Phenomenon | 幻读

<img src="https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202406121904493.png" alt="image-20240612190420368" style="zoom: 33%;" />

### 谓词锁

### **Index Locking To Prevent Phantoms** | 索引封锁

- 在索引上面锁住一段

### **Next-Key Locking to Prevent Phantoms**

- 锁住单独的数据

![image-20240612192118855](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202406121921950.png)