# Chapter 4 | Processor

## Part 1 单周期

![image-20240604214214286](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202406042142427.png)

### Data Path

略

### Control

- 七个控制信号和一个四位的`ALU operation`

<img src="https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202406042158366.png" alt="image-20240604215831264" style="zoom: 33%;" />

![image-20240604220111242](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202406042201396.png)

- ALU 信号

![image-20240604220744730](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202406042207863.png)

## Part 2 流水线

>单周期的弊端：
>假设取指令 200ps, 寄存器读 100ps, ALU 计算 200ps, 内存访问 200ps, 寄存器写 100ps.
>那么 `add` 需要 600ps, `ld` 需要 800ps, `sd` 需要 700ps, `beq` 需要 500ps.

<img src="https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202404151418760.png" alt="image-20240415141814602" style="zoom:33%;" />

- a pipeline in which one instruction is in each stage
- **CPI is decreased to 1, since one instruction will be issued (or finished) each cycle.** 

**吞吐率 | throughput**

流水线实际上是提高了系统的**吞吐率**。但是**Latency (time for each instruction)**不会减少

### 竞争 | Hazards

>导致下一条指令无法正常进行的

#### 结构竞争 | Structure

>A **required resource is busy**  大多数是硬件问题导致

- **In RISC-V pipeline with a single memory**
  - Load/store requires data access
  - Instruction fetch would have to *stall* for that cycle
    - Would cause a pipeline “bubble”
- 把指令和数据分开存储
    如果只有一块，那么当IF需要获取指令，Mem需要获取数据时就会发生结构冒险

#### 数据竞争 | Data

>Need to wait for previous instruction to complete its data read/write

前一个的结果是后一个的操作数

![image-20240416204710770](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202404162048064.png)

- WB在下降沿触发
- ID在上升沿触发
- 插入"Bubble"进行"缓冲"

**Solution**

- **Forwarding (aka Bypassing)**

![image-20240416205238817](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202404162052953.png)

- `ld`指令

![image-20240416205530324](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202404162055510.png)

- **编译器方面**

  ![image-20240416210641497](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202404162106571.png)

![c6046a551adfecdd177565cc417c846](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202404162106899.jpg)

#### 控制竞争 | Control

>Deciding on control action depends on previous instruction

在ID阶段加入更多的硬件去判断

或者

使用Prediction技术

![image-20240416212441149](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202404162124223.png)

- 例如，对`beq`，`IF`需要得知要去的地址，会把计算提前到`ID`步骤

##### Prediction

- Can predict branches not taken
- Fetch instruction after branch, with no delay

### RISC-V Pipelined Datapath

#### Form

![image-20240416213943317](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202404162139375.png)

- 注意，上图中的Write Register是错误的

![image-20240416214740739](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202404162147804.png)

![image-20240416214931469](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202404162149535.png)

#### Control 指令

<img src="https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202404162202604.png" alt="image-20240416220209541" style="zoom:67%;" />

- `WB`步骤的`Write Register`传回寄存器堆

<img src="https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202404162207595.png" alt="image-20240416220705524" style="zoom:50%;" />

### Data hazards

> **Consider this sequence:**
>
>sub x2, x1,x3
>and x12,x2,x5
>or  x13,x6,x2
>add x14,x2,x2
>sd  x15,100(x2)

- `ID/EX`那里要使用的`RS`是其他流水线的`RD`, 就出现了数据竞争（这里的定义有些笼统，更准确地还要加上条件：需要用到`RS`）

![image-20240422132954985](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202404221329312.png)

- 注意寄存器的写法，`ID/EX.RegisterRd `

$$
1.\ EX/MEM.RegisterRd=ID/EX.RegisterRs\\
2.\ EX/MEM.RegisterRd\ !=0 \\
3.\ EX/MEM.RegWrite==1
\\ 对于MEM/WB级同理
\\ \text{需要确保发生数据竞争的上一级的Rd是要写回的，且写回的寄存器不是}X_0
$$

![image-20240504225937806](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202405042259884.png)

<img src="https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202405042248653.png" alt="image-20240504224803575" style="zoom:50%;" />

#### **Double Data Hazard**

>考虑两个地方都触发了数据竞争，选择最近的那个数据
>
>add x1,x1,x2
>add x1,x1,x3
>add x1,x1,x4

需要对`Mem/WB`寄存器的特判

`EX/MEM`

`EX/MEM.RegWrite and (EX/MEM.RegisterRd!=0) and EX/MEM.RegisterRd = ID/EX.RegisterRs1`

`MEM/WB`

<img src="https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202405042306225.png" alt="image-20240504230626155" style="zoom:50%;" />

#### **Load-Use Hazard Detection**

```mermaid
graph LR
1[IF]
2[ID]
3[EX]
4[Mem]
5[WB]
1-->2-->3-->4-->5

```

- Load的时候，在`IF/ID`步骤需要判断，因为 Load 的结果必须要到mem级才能获取，不能ID到错误的数据

![](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202405042317621.png)

- `ld`的结果在`EX/Mem`阶段才能得到

Bubble：空挡

<img src="https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202405042321949.png" alt="image-20240504232137871" style="zoom:50%;" />

- **Force control values in ID/EX register to 0**  插零后面的，把当前的ID/EX变为NOP
    - EX, MEM and WB do `nop (no-operation)`
- **Prevent update of PC and IF/ID register**  停滞之前的
    - Using instruction is decoded again

<img src="https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202405042326178.png" alt="image-20240504232637109" style="zoom:50%;" />

### Branch hazard | Control

![image-20240512232013934](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202405122320030.png)

- 需要清除分支指令到达Mem阶段时其他前面几个寄存器

#### 缩短分支延迟

>将对分支的检测提前到ID阶段

- 需要新的前递和Stall单元
    - bypass 
    - Stall ：比如计算分支地址需要的数据来自于上一级的EX、Mem
        - 上一级存在ALU操作，且存在依赖关系。Stall one bubble
        - 上一级存在ld操作，且存在依赖关系。Stall two bubbles

#### 动态预测

- Branch prediction buffer (aka branch history table)
- **Indexed by recent branch instruction addresses**  按照分支指令的低位地址定位的小存储
- Stores outcome (taken/not taken)
- To execute a branch
    - Check table, expect the same outcome
    - Start fetching from fall-through or target
    - If wrong, flush pipeline and flip prediction

分支预测单元可以放在ID级

即使存在Prediction，计算Branch Target的一个周期损失也不可避免

**Branch target buffer | 分支目标缓存**

### Exceptions and Interrupts | 异常与中断

!!! note "Interrupts"

	改变CPU的 work flow 的两种形式

	**predictable** 比如beq、bne等命令发生跳转
	
	**unpredictable**  出现异常

![image-20240512234655478](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202405122346617.png)

>很多时候二者不加区分, 广义的Exception包括Interrupt

遇到异常需要处理两件事：

- 在哪里处理异常，如何跳过去
- 如何回去

> 1.中断来了怎么办。
>
> 2.存PC到Supervisor Exception Program Counter (SEPC)，控制权交给操作系统，通过强制跳转，
>
> 3.操作系统进行预先规定的操作，也可能是执行问题分析，也可能是重复执行。
>
> 4.分析原因时使用两种方法通知系统，
>
>a. 设置SCAUSE
>
>b. 向量式中断 | vectored interrupt

- RISCV中，由硬件部分实现对多个异常的优先级排序

??? note "Privilege"

    > 了解

    > 可以看马德老师智云

    
    - 模式
    
    ![alt text](images/custom-image.png)
      
    ![image-20240513134529477](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202405131345874.png)
    
    - 与模式相关
        - 用户模式(User Mode)
        - 机器模式(Machine Mode)
        - 监督模式(Supervisor Mode)
    - 原子操作
    - 一共4096个CSR寄存器
    
    **Instruction**
    
    ![image-20240513134757839](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202405131347080.png)

- 异常控制程序

#### Multiple

![alt text](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202406130853646.png)

- `precise` 按照异常的先后实现
- `imprecise` SEPC保存的地址不一定是发生例外/异常时的地址
    - Let the handler work out
    - **Simplifies hardware, but more complex handler software**
    - Not feasible for complex multiple-issue out-of-order pipelines 对于无序的流水线不适用

#### Pipline | ITP

## Problem

### Excution Diagram的画法

![image-20240610134731066](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202406130852601.png)

??? info "Answer"

	![image-20240610134856404](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202406101348498.png)
