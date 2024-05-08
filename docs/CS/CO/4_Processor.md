# Chapter 4



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

![image-20240416220209541](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202404162202604.png)

- `WB`步骤的`Write Register`传回寄存器堆

![image-20240416220705524](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202404162207595.png)

### Data hazards

> **Consider this sequence:**
>
>  sub x2, x1,x3
>  and x12,x2,x5
>  or  x13,x6,x2
>  add x14,x2,x2
>  sd  x15,100(x2)

![image-20240422132954985](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202404221329312.png)

如何检测何时 Forwarding 哪里 Forwarding 呢

