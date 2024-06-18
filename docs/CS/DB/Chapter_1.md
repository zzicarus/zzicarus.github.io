

```mermaid
flowchart LR
0{概述}
0-->1
1[View Of Data]-->2[Data Abstraction]


1-->b[Data Models]

0-->0.1[Schema and instances 模式与实例]
0.1-->区分
0.1-->0.1.1[Physical Data Independence]
0-->1.2[Language]
1.2-->1.2.1[DDL:Data Difinition Language]
1.2-->1.2.2[DML:Data Manipulation Language]
1.2.2-->声明式:SQL
1.2.2-->过程式

0-->4[Database Design]
4-->4.1[E-R模型 实体-联系模型]
4-->4.2[规范化]

0-->3[Database Engine]
3-->1.8
3-->3.2[Storage Manager]
3-->3.3[The Query Processor]
3.3-->3.3.1[DDL interpreter]
3.3-->3.3.2[DML compiler]
3.3-->3.3.3[Query evaluation engine]
1.8[事务管理器]-->1.8.1[并发控制管理器]
1.8-->1.8.2[恢复管理器]
```

- **Database Management System (DBMS)**

> A **database** system is a collection of interrelated **data** and a set of **programs** that allow users to access and modify these data. 

**Characteristics of Databases**

​	data persistence (数据持久性)

​	convenience in accessing data (数据访问便利性)

​	data integrity (数据完整性)

​	concurrency control for multiple user (多用户并发控制)

​	failure recovery (故障恢复) 

​	security control (安全控制)

**file system的问题**

![image-20240614182114786](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202406141821854.png)

## View Of data

![image-20240305151254876](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202403051513004.png)

![image-20240305151433756](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202403051514827.png)

## Language

### DDL 

**Data dictionary**  contains metadata

- 数据模式
- 完整性约束
- 授权

### DML

**SQL**

- A query takes as **input several** **tables** (possibly only one) and always returns **a single table**.

- **SQL does not support** actions such as input from users, output to 

  displays, or communication over the network. 

