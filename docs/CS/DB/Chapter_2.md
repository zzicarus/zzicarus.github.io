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

![image-20240307180351107](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202403071803221.png)

## Keys

![image-20240307101955968](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202403071019133.png)

- primary key 的约束条件

- Foreign

  - $R_1$中的一个属性，是另外一个参照$R_2$的 primary key
  - 约束条件比较强，必须是 A的属性 B的`primary key`

- referential integrity constraint 参照完整性约束

  - 约束条件较弱，

  

  ![image-20240307102805922](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202403071028221.png)

![image-20240307102148622](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202403071021764.png)

## Database

![image-20240307103017347](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202403071030505.png)

## Relation Algebra

![image-20240307104513774](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202403071045958.png)

![image-20240307181950631](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202403071819720.png)

![image-20240307182236752](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202403071822871.png)

![image-20240307182324973](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202403071823048.png)

- project 竖向选择