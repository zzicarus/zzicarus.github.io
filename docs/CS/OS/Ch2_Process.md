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

# Process

## Concept

A `process` is one program being executing. (`job` 是历史遗留的称呼)

>[!note] 内存布局
>- Text 运行的代码
>- Data 全局变量、静态变量
>- heap 运行时动态申请
>- stack 调用函数的临时变量
>
>![image.png](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202409281535558.png)
>
>>[!note] 一个 C 程序中各部分的内存布局
>>![](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202409251532666.png)
>>使用 `size <executable_file_name>` 命令查看，
>>
>>```c
>>text     data     bss     dec      hex       filename
>>1382     600       8    1990     7c6        test
>>```

### State

![image.png](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202409251520016.png)

- `Scheduler dispatch ` : OS 进行 CPU 调度

### Process Control Block | PCB

上面提到单个进程在 memory 中的内存布局以及 state 的转换，但我们的操作系统同时会运行多个进程，这些进程不断地切换，所以我们需要 PCB 来保存一些管理资源的必要信息。

- PCB 相关的维护代码在 kernel 部分，在中断时调用更新 PCB 的值

**PCB 的一般结构**
![image.png](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202409251548836.png)

>[!note] 两个进程的示意图
>通过 PCB 的切换来切换进程
>![image.png](http://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202409251549111.png)

## Process Scheduling

>In general, most processes can be described as either I/O bound or CPU bound. 按照花费时间的多寡分类
>
>An **I/O-bound process** is one that spends more of its time doing I/O than it spends doing computations.
>
>A **CPU-bound process**, in contrast, generates I/O requests infrequently, using more of its time doing computations.

### Scheduling Queues

![image.png](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202409281624763.png)

- Job queue – set of **all processes** in the system
- Ready queue – set of all processes residing in main memory, ready and waiting to execute
- Device queues – set of processes waiting for an I/O device
- I/O waiting queue
- ......

**运行示意图**
![image.png](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202409281618875.png)

### Process Scheduler

- **Long-term scheduler**  (or **job scheduler**) – selects which processes should be brought into memory (the ready queue) 选择哪一个程序进行运行
	- 控制 degree of multiprogramming
- **Short-term scheduler**  (or **CPU scheduler**) – selects which process should be executed next and allocates CPU 
- **Medium term** 进行 **swapping**，可以将一个 process 从内存移动到 disk，降低 multiprogram 的程度，之后再存回来
![image.png](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202409281627397.png)

## Process Operation

>Linux 可以使用 `ps/pstree` 命令查看当前进程
![image.png](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202409281633165.png)

- 不同 process 之间使用 pid 区分
- Systemd pid = 1

### Creation

![image.png](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202409281709506.png)

- `Fork` 创建一个新的进程，对于新创建的子进程，其返回值为 0  returns the child’s pid to the parent, and 0 to the child.

>[!note] From Linux `fork` Manual
>The child process is an  exact  duplicate  of  the  parent process except for the following points:
>
>- does not inherit its  parent's  memory  locks
>
>**Return value**
>On success, the PID of the child process  is  returned  in the  parent,  and 0 is returned in the child.  On failure, -1 is returned in the parent, no child process is created, and err no is set appropriately.
>
>>[!Example]example
>>How many processes does this C program create?
>> ```
>> int main (int argc, char *arg[])
>> {
>>     fork ();
>>     if (fork ()) {
>>         fork ();
>>     }
>>     fork (); 
>> }
>> ```
>>
>>The answer should be 12.
>>
>>#todo:给出树形图

- `Exec` 载入新的二进制程序，顶替之前的镜像。用在`fork`函数调用之后
- `wait` 父进程阻塞，等待子进程

**Resource sharing 的分类**

- 子进程和父进程共享
- 子进程的资源严格限制在父进程的子集中
- No resource sharing

**父进程在创建子进程之后**

两种可能性（都进入 ready queue，根据调度算法决定）

- 阻塞，等待 child process
- 并行执行

**子进程**

- 要么是父进程的 duplicate
- 要么 load 另一个程序

```c
#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>
int value = 10;
int main()
{
    pid_t pid;
    pid = fork();
    value += 10;
    if (pid == 0)
    { /* child process */
        value += 5;
        printf("CHILD: value = %d", value); /* LINE C 25 */ 
    }
    else if (pid > 0)
    { /* parent process */
        wait(NULL);
        printf("PARENT: value = %d", value); /* LINE A 20 */
        exit(0);
    }
}
```

### Termination

**Exit** : A process terminates when it finishes executing its final statement and asks the operating system to delete it by using the ` exit() ` system call. 运行结束
- 为 waiting 中的父进程返回 status value 
- Deallocated 所有分配的资源

**Abort** : Parent may terminate execution of children processes

- Child has exceeded allocated resources
- Task assigned to child is no longer required
- Parent 存在
	- **cascading termination** ：部分操作系统不允许没有父进程的子进程存在，在父进程中止时会级联中断子进程
	- In some other operating systems, the child gets **orphaned** – and its parent becomes the “init” process (PID=1).  父进程不调用 wait 的情况下，子进程成为“孤儿”，这时部分操作系统会把父进程设置为 systemd，其周期性调用 wait 函数

>[!note] 
>所有中断的进程都会变成 **zombie** process，只有在父进程调用 wait 之后，进程相关的 process table 的内容才会被释放

## Interprocess Communication | IPC

<img src="https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202410102221772.png" alt="image-20241010222119675" style="zoom:67%;" />

- Shared Memory 速度会更快，减少了对kernel代码的调用 (Message Passing requires the more time-consuming task of kernel intervention.)
- Message Passing 实现起来更简单  useful for exchanging smaller amounts of data for no conflicts to be considered

### Shared Memory

>[!note]
>
> **Producer-Consumer Problem**
>
> - **unbounded-buffer** places no practical limit on the size of the buffer. Consumer has to *wait if no new item.* buffer不会填满
> - **bounded-buffer** assumes that there is a fixed buffer size. Producer must *wait if buffer full.*
>
>共享内存 —— sharing memory

### Message Passing

- 需要 copy 多次内存/Buffer  （在内存和内核之中）

### Synchronization

#TODO

看之后吧	
