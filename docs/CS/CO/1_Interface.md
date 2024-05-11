# Computer Abstraction

!!! info "info"
	这一章是总览性质的，没有特别的知识点，很多都是性质、概述。
	要注意**Time的计算**

- **Instruction set architecture（ISA,指令集系统结构）** ---- the interface between hardware and lowest-level software

## 组成

![image-20240304132944381](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202403041329575.png)

![image-20240304132928429](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202403041329606.png)

<div align="right" style="font-size: small;">Graph From https://xuan-insr.github.io/</div>

```mermaid
graph LR
1[Computer System]
2[Software]
3[Hardware]
2.1[Application Software]

2.2[System Software]

2.2.1[Operation System]
2.2.2[GCC]
2.2.3[Firmware/Driver Software]

1 --> 2
1-->3
2-->2.1
2-->2.2
2.2-->2.2.1
2.2-->2.2.2
2.2-->2.2.3

3.1[CPU]
3.2[Memory]
3.3[I/O interface]
3.1.1[Control unit]
3.1.2[DataPath]
3-->3.1
3-->3.2
3-->3.3
3.1-->3.1.1
3.1-->3.1.2
3.3.1[Input: keyboard]
3.3.2[Bidirectional: RS-232,USB]
3.3.3[Output: VGA，LCD]
3.3-->3.3.1
3.3-->3.3.2
3.3-->3.3.3
```

> 没想到期中考试竟然考了Software部分的框图

**SoftWare**

<img src="https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202405110909409.png" alt="image-20240508224122838" style="zoom:50%;" />

## I/O Interface



## Memory

![image-20240226144640896](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202402261448379.png)

## 语言转换

```mermaid
graph
高级编程语言--Compiler-->汇编--ASsembler-->3[Machine Code]
```



## * Time的计算

> 处理器执行时间由处理频率， 程序执行的指令数目和每条指令的性能决定； 而每条指令的性能，由每条指令所需时钟数决定

**Response time/execution time**     响应时间/执行时间

- How long it takes to do a task   

**Throughput (bandwidth)**  吞吐率

- Total work done per unit time
  - e.g., tasks/transactions/… per hour

??? example "了解cost"
	![image-20240303174345204](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202405082244115.png)

**Performance = 1/Execution Time**

![image-20240303173746612](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202403031737699.png)

> **一个指令周期，包含多个 CPU 周期，而一个 CPU 周期包含多个时钟周期。**

![image-20240303174004398](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202403031740452.png)

![image-20240303174148845](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202403031741903.png)

![image-20240303174238435](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202403031742498.png)

![image-20240508230703505](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202405082307568.png)

> example
>
> ![image-20240226153306228](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202402261533384.png)

- **CPI** : 每条指令的平均**周期**数(Average cycles per instruction)  --> CPU 周期

![image-20240303174634151](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202403031746233.png)

> example
>
> ![image-20240303174752066](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202403031747130.png)

![image-20240303175836955](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202403031758000.png)

![image-20240303175847002](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202403031758040.png)

> example
>
> ![](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202403031759200.png)



- **MIPS: Millions of Instructions Per Second**

![image-20240303180042738](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202403031800789.png)

## **Eight Great Ideas**

- Design for Moore’s Law  （设计紧跟摩尔定律） 

- Use Abstraction to Simplify Design (  采用抽象简化设计  ) 

- Make the Common Case Fast (  加速大概率事件  ) 

- Performance via **Parallelism**   (  通过并行提高性能  ) 

- Performance via **Pipelining** (  通过流水线提高性能  ) 

- Performance via Prediction (  通过预测提高性能  ) 

- Hierarchy of Memories (  存储器层次  ) 

- Dependability via Redundancy ( 通过冗余提高可靠性) 

## 补充

### Power Trend

![image-20240511090835195](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202405110908448.png)

![image-20240511091018574](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202405110910724.png)

> 期中考到了, 题目大意跟上图一致，计算$\frac{P_{new}}{P_{old}}$

## 题目

### Eight Idea

![image-20240508232316480](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202405082323553.png)