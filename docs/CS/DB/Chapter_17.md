# 事务管理

## Concepts

**ACID**

- 原子性
- 一致性
- 隔离性
- 持久性

![image-20240530193111598](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202405301931187.png)

## Concurrent Executions

## Serializability

### Conflict Serializability | 冲突可串行

> 从冲突的视角看，通过交换冲突可以达成serial

If a schedule *S* can be transformed into a schedule *S’* by a series of swaps of non-conflicting instructions, we say that *S* and *S’* are **conflict** **equivalent**

冲突等价：通过交换非冲突的指令，

### View Serializability | 视图可串行

## **Recoverable Schedules**

必须在
