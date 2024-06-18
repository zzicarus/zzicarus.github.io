# Recovery

## Failure Classification

![image-20240612151527971](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202406121515145.png)

![image-20240614141438208](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202406141414311.png)



## 事务的物理实现

![image-20240614141933638](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202406141419745.png)

## 日志记录

![image-20240614141623670](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202406141416749.png)

## 事务恢复

![image-20240614142545583](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202406141425650.png)

一个事务的Commit标志：日志写入稳定存储器

A transaction is said to have committed when its commit log record is output to stable storage 

- All previous log records of the transaction must have been output already 

这时的修改不一定写到了磁盘

**立即修改**

The **immediate-modification** scheme allows updates of **an uncommitted transaction to be made to the buffer**, **or the disk itself**, **before the transaction commits**

**redo undo**

- redo 历史重演
- undo 需要记录日志  redo-only，完成后，记录 <T abort>
    - 正常执行过程中的回滚
    - 系统崩溃后恢复发现没有结束

### Check Point

<img src="https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202406141436856.png" alt="image-20240614143612811" style="zoom:33%;" />

**fuzzy check point**

![image-20240614150924069](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202406141509142.png)

### 事务回滚

补偿日志记录

![image-20240614143814771](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202406141438835.png)

### 



## 缓冲区管理

![image-20240614150207603](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202406141502665.png)

**log force**  将缓冲的日志强行写到Disk

![image-20240614150540972](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202406141505023.png)

## Logical Undo

> Redo是按照物理执行

![image-20240614152757110](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202406141527169.png)

![image-20240614152909188](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202406141529239.png)

## ARIES

- 每个记录一个日志顺序号 LSN

Typically an offset from beginning of log file to allow fast access

- 在数据页中记录一个LSN - Page LSN
    - 更新发生，日志的LSN记录进去
    - 防止 重复的 redo

![image-20240614154435835](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202406141544891.png)

- Log Record

![image-20240614154636492](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202406141546537.png)

- Special redo-only log record called **compensation log record (CLR)** used to log actions taken during recovery that never need to be undone
    - 在回滚时，有助于跳过已经回滚的日志

- **Physiological redo**



- Dirty Page Table
    - 在后台周期性写回，而不是在Check Point


记录脏页<img src="https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202406141550483.png" alt="image-20240614155029448" style="zoom:33%;" />

- Fuzzy Check Point

 only records information about dirty pages,  and does not require dirty pages to be written out at checkpoint time

![image-20240614155331333](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202406141553388.png)

### 流程

![image-20240614155635517](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202406141556573.png)

- 分析
    - 得到redo的位置RedoLSN —— 至少在Check Point 之前，对脏页Table的Rec取Min
    - undo-list  
        ![image-20240614155930834](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202406141559884.png)
        从Check Point 往下扫描，完善undo list
    - 更新脏页表
        ![image-20240614160001232](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202406141600273.png)

- Redo
    - 脏页表，注意是跟log record中的LSN比较
    - 磁盘页
    - ![image-20240614160210994](../../../../../../AppData/Roaming/Typora/typora-user-images/image-20240614160210994.png)
- Undo

![image-20240614160502406](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202406141605474.png)

![image-20240614161912321](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202406141619370.png)

- 
