# Relation

> § Structure of Relational Databases
>
> § Database Schema  数据库模式
>
> - A relation instance *r* defined over schema *R* is denoted by *r* (*R*)
>
> § Keys
>
> § Schema Diagrams
>
> § Relational Query Languages
>
> § The Relational Algebra

## Structure of Relational Databases

### Attributes

- 原子性 --> 不可拆分（数组、结构体之类不可）

- The set of allowed values for each **attribute** is called the **domain** **（域）** of the attribute

- The special value **null** **（空值）** is a member of every domain. Indicated that the value is “unknown”

- 无序性，顺序没有影响

## Database Schema  数据库模式

schema  关系模式，logical structure

instance 某一瞬间的快照

![image-20240307180351107](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202403071803221.png)

## Keys

- super key 超码 可以唯一标识

- candidate key 最小单元的超码

- primary key 的约束条件 任意一个候选码都可以作为主键；不能是null

- Foreign
    - $R_1$中的一个属性，是另外一个参照$R_2$的 primary key
    - 约束条件比较强，必须是 A的属性 B的`primary key`

- referential integrity constraint 参照完整性约束
    - 约束条件较弱，

![image-20240307102805922](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202403071028221.png)

![image-20240307102148622](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202403071021764.png)

## Database

含有多个relation

![image-20240307103017347](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202403071030505.png)

## Relation Algebra
