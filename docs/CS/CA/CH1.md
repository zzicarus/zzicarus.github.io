## Intro

![image.png](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202410072007906.png)

### 分类

![image.png](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202410071704251.png)

### Concept

MTTF: Mean Time To Failure

MTTR:  Mean Time To Repair

FIT   : Failure In Time = 1/MTTF

MTBF: Mean Time Between Failure = MTTF+MTTR

Module Availability = MTTF / (MTTF + MTTR)

**Performance Metrics**

- Response Time (or execution time)
	- Time between start and end of an event
- Throughput 
	- Total amount of work done in a given time

**MIPS**

![image.png](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202410072024144.png)

### Performance

#### 测定

![image.png](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202410072036170.png)

**Normalized Geometric Mean**

![image.png](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202410072038727.png)

### Quantitative Principles

- Take advantage of parallelism
	- **Most important** methods of improving performance
	- 
- Principle of Locality
	- 空间
	- 时间
- Focus on  the common case
	- Amdahl's Law 
	  ![image.png](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202410072042112.png)
	- $Speedup_{overall} = \frac{Performance_{new}}{Performance_{old}} = \frac{ExecTime_{old}}{ExecTime_{new}} = \frac{1}{1-\%_{enhanced}+\frac{\%_{enhanced}}{Speedup_{enhanced}}}$
	  受影响部分的，未受影响部分的
- CPU Performance Equation

## Ch 2 Pipelining

- **CPI 计算**

### Hazard

- 结构竞争
	- 存储器：指令和数据存储分离
	- Registers： double bump，使用 WRITE-AFTER-READ
- 数据竞争
- 分支竞争
	- branch delay slots 
![image.png](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202410072151358.png)
**把一些必然会执行的指令放在 slots 中**

**关于浮点的 pipelining**
![image.png](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202410072155999.png)
![image.png](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202410072159950.png)

- Ex 阶段可以更长
- DIV 不是 pipeline 的，可能发生结构竞争
- 需要更多的寄存器
- WAW 可能发生（周期不同）

## Ch 3 存储层次

### Cache

![image.png](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202410072247564.png)

## 例题

### Ch 1 关于概念的计算

### Ch 2 Pipeline

![image.png](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202410072147531.png)

### Ch 3 Cache

![5f54b3aa1dee10452ec381b9e88d333.jpg](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202410081457676.png)
