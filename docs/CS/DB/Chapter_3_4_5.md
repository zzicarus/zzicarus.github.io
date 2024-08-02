---
tags:
  - class/DB
---
# SQL

- A query returns a single table 

## Essential

### **DDL**

**Create**

```sql
create table student
(
    id int,
	name varchar(8) not null,
    ...
    <完整性约束>
    primary key(id),
    foreign key(..) references department
);
```

**Select**

```sql
SELECT * FROM Websites 
WHERE xx>15
AND (country = 'US' or 'CN')
;
// 去重复
SELECT DISTINCT country FROM Websites;
// 自然连接  考虑的是不同关系中都出现的属性，取这些相同属性都相等的tuple;
select A
from r1 natural join R2 using <attributes>
// 排序
order by salary desc, name asc
```

- **The operands of the logical connectives can be expressions involving** **the comparison operators <, <=, >, >=, =, and <>.**

**order by (conlumns) ASC|DESC**



**Insert INTO**

```SQL
INSERT INTO table_name (column1,column2,column3,...)
VALUES (value1,value2,value3,...);

INSERT INTO table_name
VALUES (value1,value2,value3,...);

insert into table1 select * from table1

insert into instructor
    select ID, name, dept_name, 18000
    from student 
    where dept_name = 'Music' and total_cred > 144;
```

**Update**

> where 限制很重要！！

```SQL
UPDATE Table
SET name = "666",Country = 'CN'
WHERE id = 4;
```

### DML

**Delete**

```sql
delete from Table   删除所有属性
where ...
// 在执行任何删除之前对所有元组完成处理很重要，否则执行过程中可能会发生变化
delete from instructor
where salary < (select avg (salary) 
                from instructor);
```

**Drop**

```
drop table r; 删除
```

**Alter** 

alter 操作针对的是attribute

https://www.runoob.com/mysql/mysql-alter.html

```sql
alter table r add att Domain


alter table r drop att
```

```sql
alter table drop foreign key <约束名>;
alter table takes add constraint tb_id foreign key(id) references student(id);
```



### 操作

**Limit**

```
限制选中的数目
limit number;
```

### 附加的操作

#### 更名

- 用于区分同一个关系的笛卡尔积

```sql
select distinct T.name
from instructor as T, instructor as S
where T.salary > S.salary and S.dept_name = ""
```

#### string

使用 `LIKE` 字符来完成模式匹配

- % 匹配任意字符串 "%dar%"
- _ 匹配任意一个字符   "_ _ _" 三个字符

用`escape`来定义转义字符

```sql
where building like '%ab\%cd%' escape '\'
// 包含ab%cd
```

### 集合 | Set Operation

```sql
// 自动去重
A union B
A union all B

A intersect B

A except B
```

### null

![image-20240315193850154](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202403151938307.png)

- 算术表达  结果为空
- 比较  unknown

```sql
select count (distinct ID)
from teaches
where semester = 'Spring' and year = 2018;
```



### 聚集函数

avg min max sum count

- `group by`
- `having`

![image-20240315195244446](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202403151952509.png)

```sql
select dept_name, avg (salary) as avg_salary
from instructor
group by dept_name;

select count (*)
from course;

select dept_name, avg (salary) as avg_salary
from instructor
group by dept_name
having avg (salary) > 42000;
```

### Nested | 嵌套子查询

```sql
select distinct course_id
from section
where semester = 'Fall' and year= 2017 and 
course_id in (select course_id
            from section
            where semester = 'Spring' and year= 2018);
```

- `some`  `all`  `exists`

```sql
select name
from instructor
where salary > some (select salary
                    from instructor
                    where dept name = 'Biology')
                    
select distinct
    S.ID,
    S.name
from
    student as S
where
    not exists (
        (
            select
                course_id
            from
                course
            where
                dept_name = 'Biology'
        )
        except
        (
            select
                T.course_id
            from
                takes as T
            where
                S.ID = T.ID
        )
    );
```

![image-20240315200906988](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202403152009106.png)

- `unique` `not unique`

> SQL 中unique用于约束

```sql
select T.course_id
from course as T
where unique ( select R.course_id
                from section as R
                where T.course_id= R.course_id
                and R.year = 2017);	
```

```sql
select id,name,course_code,score,year
from 
	student natural join takes as C
where (id,course_code) in
(
	select distinct id, course_code
    from takes as T
    where C.id = T.id
);
```



- `from`

```sql
# Error : Every derived table must have its own alias
select id,name,course_code,score,year
from 
(
	select id,name,course_code,score,year
    from student natural join takes
    where id = '0001'
# ' as course ' here is bound to be added
) as course
where score >= 90;
```



- `with`

```sql
with max_budget (value) as 
    (select max(budget)
    from department)
    
select department.name
from department, max_budget
where department.budget = max_budget.value;
```



- `Scalar `

Scalar （标量） subquery is one which is used where a single value is expected

```sql
```

- `case`

```sql
case 
	when pred then result
	when pred then result
	else result
end

update student S
set score = case
	when ... t.hen
	else 0
end
```

## Intermediate

<img src="https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202403222054777.png" alt="image-20240322205454482" style="zoom:80%;" />

### Join

![image-20240322190735289](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202403221907652.png)

- `natural join`  只保留一组相同的元素; 使用 on condition 的join操作将会存在两个重复的condition属性

![image-20240328110344699](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202403281103953.png)

```sql
natural left/right/full outer join
using (attribute)
on condition
例如
using course_id
on takes.course_id = student.course_id
```

### Views

- 一种虚关系

```sql
create view v as <query>

create view departments_total_salary (dept_name, total_salary) as
	select dept_name , sum salary
	from instructor
	group by dept_name
```

![image-20240322192419777](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202403221924074.png)

- Recursive case 的expand?

#### Materialized Views | 物化视图

- 物理存储 ：不需要在每次调用时重新进行查询操作（虚关系需要）
- If relations used in **the query are updated, the materialized view（视图维护） result**
  **becomes out of date**
  - Need to **maintain the view**, by updating the view whenever the
    underlying relations are updated.

#### 视图更新

- 更新一个视图必须要给出对实际关系的修改

![image-20240328111247284](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202403281112508.png)

Most SQL implementations allow updates only on simple views

- The from clause has **only one database relation**.
- The **select** clause contains only attribute names of the relation, and
  does not have any expressions, aggregates, or distinct
  specification.
- Any attribute **not listed in the select clause can be set to null**
- The query **does not have a group by or having clause.**

![image-20240322232447783](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202403222324891.png)

### Transaction | 事务

**Atomic transaction**

事务是由查询和（或）更新语句的序列组成。SQL语句规定当一条语句开始时，一个事务开始执行，下面的语句会终止一个事务

- `commit work` :  提交事务
- `rollback work` : 回滚事务

> 在SQL的实现中，很多情况下都默认一条语句自成一个事务，一旦执行完成就会提交

### Integrity Constraints

**Constraints on a Single Relation** 

- **not null**
- **primary key**
- **unique **  ? a super key
- **check** (P), where P is a predicate

#### check & assertion

- 谓词检测

```sql
create table section 
(
    course_id varchar (8),
    sec_id varchar (8),
    semester varchar (6),
    year numeric (4,0),
    building varchar (15),
    room_number varchar (7),
    time slot id varchar (4), 
    primary key (course_id, sec_id, semester, year),
	check (semester in ('Fall', 'Winter', 'Spring', 'Summer'))
)
```



- assertion的维护代价比较高

```sql
create assertion <assertion-name> check <predicate>;

// 插入修改tuple时要check，time_slot改变时也要check
check (time_slot_id in (select time_slot_id from time_slot) )



create assertion credits_earned_constraint check (
    not exists (
        select
            ID
        from
            student
        where
            tot cred <> (
                select
                    coalesce(sum(credits), 0)
                from
                    takes natural
                    join course
                where
                    student.ID = takes.ID
                    and grade is not null
                    and grade <> 'F'
            )
    )
);
```



#### referential intergrity | 参照完整性

> 不同于外码约束，参照完整性约束并不要求目标属性是某个关系的主码。但是，foreign key 要求至少是候补码

```sql
foreign key () references _
on delete set NULL
// 级联
on delete cascade
on update cascade
```

![image-20240323113006090](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202403231130214.png)

#### 增加与删除

```sql
ALTER TABLE <数据表名> ADD CONSTRAINT <外键名>
FOREIGN KEY(<列名1>) REFERENCES <主表名> (<列名2>);
# 注意，外键名是用户定义的，

alter table takes add constraint tb_id foreign key(id) references student(id);
```



### Data Type & Schema

#### Data

![image-20240323103600907](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202403231036007.png)

**Time**

**默认值**

```sql
create table student
(
	ID varchar(5),
	tot_cred numeric(3,0) default 0
)
```

#### Index

```sql
create index <name> on <relation name> (attribute);

create table student(
    ID varchar (5),
    name varchar (20) not null,
    dept_name varchar (20),
    tot_cred numeric (3, 0),
    default 0,
    primary key (ID)
);
create index studentID_index on student(ID)
// 删除索引
drop index student_id on student;

The query:
select *
    from student
    where ID = '1001'
can be executed by using the index to find the required record, without
looking at all records of studen
```

#### Large Object | 大对象类型

![image-20240323103953403](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202403231039520.png)

```sql
bookreview clob (2KB)
image blob (10MB)
movie blob (2GB)
```

- When a query returns a large object, **a pointer （定位器）** is returned rather
  than the large object itself.

#### User-defined Type

>  **这里介绍的是distinct Type**

```sql
create type Dollars as numeric (12,2) final

create domain DDollars as numeric (12,2) not null 
constraint Dollars_test check ...;

create table department
	(
	dept_name varchar (20)
	building varchar (15)
	budget Dollars
	);
```

**cast 数值转换**

`cast(department.budget to numeric(12,2))`

对于强类型检查，必须这样处理

#### Domain

![image-20240323104839949](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202403231048068.png)

### Authorization

![image-20240323105439274](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202403231054436.png)

```sql
grant / revoke <privileges list>
on <关系/视图>
to <user list>

grant update(dept)
on department
to Alan
```

<user list>

- a `user id`
- `public` , which allows all valid users the privilege granted
- A `role` 

#### Role

- 创建一个 role，这个role可以授予给其他role/user，也可以接受授权(给我的感觉像是一个Tag)

```sql
create role instructor

grant class to instructor
```

![image-20240323110705186](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202403231107351.png)

#### 视图的授权

- 视图的创建者不需要视图上的所有权限

#### 模式的授权

#### 权限转移

`with grant option`

```sql
grant select on depart to Aimit with grant option
```

![image-20240323111237646](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202403231112771.png)

#### 权限收回

- 默认情况下，权限的收回是级联的

```sql
revoke select on department from Amit , Satoshi cascade

revoke select on department from Amit , Satoshi restrict
```

## Advanced

### 程序语言

<img src="https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202403281855924.png" alt="image-20240328185505818" style="zoom:67%;" />

#### ODBC



#### JDBC

![image-20240328185829835](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202403281858930.png)

![image-20240328190320525](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202403281903628.png)

- try 将异常抛出  到  catch

**Prepared Statement**

![image-20240328190851639](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202403281908742.png)

**SQL Injection**

![image-20240328191151219](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202403281911336.png)

**Metadata Features**

![image-20240328191336117](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202403281913225.png)

![image-20240328191440311](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202403281914412.png)

**Transaction Control in JDBC**

![image-20240328191551765](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202403281915858.png)

#### SQLJ

![image-20240328192129853](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202403281921964.png)

#### Embedded

![image-20240328232604932](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202403282326053.png)

```sql
# 连接到数据库
EXEC SQL connect to server user user-name using password;
# 宿主变量用 : 加以区分
# They are preceded by a colon (:) to distinguish from SQL variables (e.g., :credit_amount )
# must be declared within DECLARE section,
EXEC-SQL BEGIN DECLARE SECTION
int credit-amount ;
EXEC-SQL END DECLARE SECTION;
```

```sql
EXEC SQL
# 用c作为标识
    declare c cursor for 
    select ID, name
    from student
    where tot_cred > :credit_amount
END_EXEC

EXEC SQL open c ;
```

<img src="https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202403282339614.png" alt="image-20240328233934296" style="zoom: 50%;" />

<img src="https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202403282340043.png" alt="image-20240328234051755" style="zoom:50%;" />

![image-20240328234254779](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202403282342200.png)

### 函数和过程 | function and procedures





### 触发器 | Trigger

![image-20240326212406023](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202403262124139.png)

- **Event : **
  delete  、 insert 、update(`create trigger <trigger name> after <Event> of <relation> on <attribute>`)
  - before 触发  维护完整性约束；有助于外键的插入
  - after 触发  

>  **TIPS：**
>
> IN **MySQL**, 下面的语句是不存在的，要使用关键字 `old` `new` 来表征
>
> ```sql
> referencing new row as nrow;
> referencing old row as orow;
> ```
>

```sql
create trigger <trigger name> after <Event> on <relation>
	referencing new row as nrow;
	referencing old row as orow;
# 指定为行级触发，对于每一行触发的tuple都执行下述行为
for each row
when ( condition )
	begin atmotic
	end;
```

```sql
# 对学分的更新
create trigger credits_earned
after
update
    of takes on (grade) referencing new row as nrow referencing old row as orow for each row
    when nrow.grade <> 'F'
    and nrow.grade is not null
    and (
        orow.grade = 'F'
        or orow.grade is null
    ) begin atomic
update
    student
set
    tot_cred = tot_cred + (
        select
            credits
        from
            course
        where
            course.course_id = nrow.course_id
    )
where
    student.id = nrow.id;
end;
```

#### 何时不应使用触发器

![image-20240327101947978](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202403271019379.png)

![image-20240327102101899](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202403271021130.png)

### Function

```sql
create function dept_count (dept_name varchar(20))
returns integer

begin
    declare d_count integer;
    select count (* ) into d_count
    from instructor
    where instructor.dept_name = dept_name
    return d_count;
end

# The function dept_count can be used to find the department names and budget of all departments with more that 12 instructors.
select dept_name, budget
    from department
    where dept_count (dept_name ) > 12
```

- 注意下面的 return 和 returns

![image-20240329130929020](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202403291309383.png)

### Procedure

![image-20240329131320593](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202403291313962.png)

## 例题

### Trigger

![image-20240329094627809](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202403290946089.png)

- 插入多行的一种用法 `insert into select from`

```sql
create trigger insert_depositor
after insert on depositor 
referencing new row as nrow
for each row 
begin
insert into
    select branch_name, customer_name
    from depositor, account
    where nrow.account_number = account.account_number
end;

create trigger insert_customer
after insert on customer
referencing new row as nrow
for each row 
begin
insert into
    select branch_name, customer_name
    from depositor, account
    where nrow.account_number = depositor.account_number
end;
```

