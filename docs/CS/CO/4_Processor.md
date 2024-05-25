# Chapter 4 | Processor



## Part 1 Data Path



## Part 2 流水线

![image-20240415141757404](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202404151418595.png)

![image-20240415141814602](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202404151418760.png)

- a pipline in which one instruction is in each stage
- **CPI is decreased to 1, since one instruction will be issued (or finished) each cycle.** 

### 竞争 | Hazards

> 导致下一条指令无法正常进行的

#### 结构竞争 | Structure

> A **required resource is busy**

- **In RISC-V pipeline with a single memory**
  - Load/store requires data access
  - Instruction fetch would have to *stall* for that cycle
    - Would cause a pipeline “bubble”

- 把指令和数据分开存储

#### 数据竞争 | Data

> Need to wait for previous instruction to complete its data read/write

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

> Deciding on control action depends on previous instruction

![image-20240416212441149](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202404162124223.png)

- 例如，对`beq`，`IF`需要得知要去的地址，会把计算提前到`ID`步骤

##### Prediction

- Can predict branches not taken
- Fetch instruction after branch, with no delay

### RISC-V Pipelined Datapath

#### Form

![image-20240416213943317](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202404162139375.png)

![image-20240416214740739](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202404162147804.png)

![image-20240416214800619](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202404162148679.png)![image-20240416214931469](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202404162149535.png)

#### Control 指令

<img src="https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202404162202604.png" alt="image-20240416220209541" style="zoom:67%;" />

- `WB`步骤的`Write Register`传回寄存器堆

<img src="https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202404162207595.png" alt="image-20240416220705524" style="zoom:50%;" />

### Data hazards

> **Consider this sequence:**
>
> sub x2, x1,x3
> and x12,x2,x5
> or  x13,x6,x2
> add x14,x2,x2
> sd  x15,100(x2)

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

> 考虑两个地方都触发了数据竞争
>
> add x1,x1,x2
> add x1,x1,x3
> add x1,x1,x4

需要对`Mem/WB`级的特判

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

- Load的时候，在`IF/ID`步骤需要判断，因为

![](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202405042317621.png)

- `ld`的结果在`EX/Mem`阶段才能得到

Bubble：空挡

<img src="https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202405042321949.png" alt="image-20240504232137871" style="zoom:50%;" />

<img src="https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202405042326178.png" alt="image-20240504232637109" style="zoom:50%;" />

### Branch hazard | Control

![image-20240512232013934](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202405122320030.png)

- 

### Exceptions and Interrupts | 异常与中断

!!! note "Interrupts"
	改变CPU的 work flow 的两种形式

	**predictable** 比如beq、bne等命令发生跳转
	
	**unpredictable**  出现异常

![image-20240512234655478](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202405122346617.png)

> 很多时候二者不加区分, 广义的Exception包括Interrupt

遇到异常需要处理两件事：
- 在哪里处理异常，如何跳过去
- 如何回去

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

![alt text](images/custom-image-1.png)

- `precise` 按照异常的先后实现
- `imprecise` 
    - Let the handler work out

