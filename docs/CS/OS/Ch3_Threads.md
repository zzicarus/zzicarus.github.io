---
tags:
  - doing
  - class/OS
statistics: true
title: NOTE
author: zzicarus
date: <% tp.date.now("YYYY-MM-DD HH:mm:ss") %>
update: <% tp.date.now("YYYY-MM-DD HH:mm:ss") %>
---

# Thread & Concurrency

## Definition

**共享资源**

- code section
- data section
- the heap (dynamically allocated memory)
- open files and signals

**Advantages of Threads**

- **Economy**
	- Creating a thread is cheap

		如果已经有了一个线程，那么我们创建新的线程只需要给它分配一个栈。Code，data，heap 都已经在内存里分配好了。

	- Context switching between threads is cheap

		Cache is hot, no need to cache flush. 

- **Resource Sharing** 
	- Threads naturally share memory
	- Having concurrent activities in the same address space is very powerful
- **Responsiveness**

	如在 web server 中，一个线程在等待 I/O，当有请求来时就再分配一个线程去处理。（进程也可以，但是代价更大）

- **Scalability**
	- multi-core machine 可以并行

**Drawbacks**

- Weak isolation between threads

	如果有一个线程出错，那么整个进程都会出错。

![image-20241011083910439](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202410110839636.png)

一个 Thread 中需要存储的资源

- Registers
- Stack
- PC

`ps -ef`可以查看 kernel threads on a running Linux system

## Multicore Programming

- 并行一定并发
- 并发其实是在multi-core出现之前，多数计算机使用调度实现“多个程序同时运行的假象”

**Concurrent**

![image-20241011090434557](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202410110904669.png)

**Parallelism**

<img src="https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202410110955927.png" alt="image-20241011095520860" style="zoom:50%;" />

- 并行的种类（看他们分发到不同core的内容是什么，实际上更可能是混合使用）
	- Data Parallelism 比如数组求和，使用多个core分别计算
	- Task Parallelism  

## Multithread Models

- **kernel threads** are supported and managed directly by the operating system
- **User threads** are supported above the kernel and are managed without kernel support

![image-20241011090557088](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202410110905149.png)

### Models

- Many to one
	- The scheduling is **done completely by the thread library** and the kernel itself is not aware of the multiple threads in user-space.
	- 不能够利用多核的优势

<img src="https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202410110909111.png" alt="image-20241011090957005" style="zoom:50%;" />



- One-to-one
	- 主流方式
	- **disadvantage** 创建user和kernel 必须一一对应，可能占用大量资源

<img src="https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202410110912307.png" alt="image-20241011091256231" style="zoom:50%;" />

- Many-to-Many
	- 
	- 更加复杂
- Two-Level
	- 可供选择

<img src="https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202410110919051.png" alt="image-20241011091910947" style="zoom:50%;" />

## Thread Issues

### The `fork()` and `exec()`

在 Process 中，进行 `fork` 会创建新的进程，对于它的线程，有两种情况

- Duplicate all threads
- Duplicate only thread that calls fork. 这种情况一般是之后要紧跟着一个 `exec`，Duplicate all 没有意义

### Signal Handling

### Cancellation

**target thread**：A thread that is to be canceled is often referred to as the target thread.

Terminating a thread before it has finished

- **Asynchronous cancellation** terminates the target thread  immediately 直接关闭
- **Deferred cancellation** allows the target thread to periodically check via a flag if it should be cancelled

### Thread-Local Storage | TLS

### Thread Pool

创建好一系列 Thread, 让他们在 Pool 中等待

Ad:

- Usually slightly faster to service a request with an existing thread than create a new thread
- Allows the number of threads in the application (s) to be bound to the size of the pool 限制 thread 的数量

### Thread Activation

>Kernel 和 user level kernel 的 Communication 问题

>[!note] LWP | lightweight process
>
>intermediate data structure between the user and kernel threads.
>- If a kernel thread blocks (such as while waiting for an I/O operation to complete), the LWP blocks as well. Up the chain, the user-level thread attached to the LWP also blocks. 
>![image.png](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202410181816919.png)

在 many-to-many/two-level 的情况下，很多时候需要通过 Kernel 通知上层的 user 来进行调度

- Kernel 提供了一个 application with many virtual processors（LWPS），它负责将 user thread 映射到 available virtual processor
- **upcall**  kernel inform 
	- handled by the **thread library** with an upcall handler， upcall handlers must run on a virtual processor.

## Thread Lib

- Kernel Level 
	- Windows
- User Level

two general strategies for creating multiple threads:

- **asynchronous threading** 
- **synchronous threading**
