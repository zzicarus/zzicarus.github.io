# Arithmetic for Computer

> 3.1  Introduction
>
> - 数值表达
> - 
>
> 3.2  Signed and Unsigned Numbers   -   Possible Representations
>
> - 溢出
>
> 3.3  Arithmetic--Addition & Subtraction and ALU
>
> - CLA
> - 行波
> - 
>
> 3.4  Multiplication
>
> 3.5  Division
>
> 3.6  Floating point numbers

![image-20240306223108682](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202403062231782.png)

![image-20240306223509613](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202403062235693.png)

## Introduction

- 一个数字只是一个数字，未指明含义它并不表征任何意义

![image-20240312165004533](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202403121650863.png)

## Arithmetic

![image-20240312165144314](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202403121651356.png)

**overflow**

$OverFlow = C_{n} \oplus C_{n-1}$

![image-20240312185026542](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202403121850769.png)

![image-20240312191301238](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202403121913372.png)

**Delay的计算**

这里跟数字逻辑的基本相同

![image-20240510183616936](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202405101836096.png)

### CLA

![image-20240510184007561](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202405101840648.png)

<img src="https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202405101840532.png" alt="image-20240510184057455" style="zoom:50%;" />

## Multiplication	

> Multiplicand=被乘数	
>
> Multiplier=乘数

- 乘法不能用补码操作

### V1

- 不断移动位置（左移动），做加法
- 移动被乘数
- 对乘数的最后一位判断，是1，结果加上当前的被乘数

![image-20240312195956267](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202403121959446.png)

### V2

- 不移动被乘数，而是移动乘积product
- 对于128bits的product，高64bits进行算术运算，然后不断右移

![image-20240312195752959](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202403121957100.png)

!!! example "example"
	![image-20240510190901115](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202405101909198.png)

### V3

- 之前V2里面的Product低64bits没有任何用处，这里用来装乘数，使之右移移除的bit进行判断

![image-20240312200527853](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202403122005111.png)

- 129bits是为了保存进位（个人感觉用不到啊

### 有符号乘法

- 记录符号，转为绝对值相乘

**Booth Algorithm**

> 适用于式子中1比较多的情况，将多的加法转换为shift（左到右的序列）
>
> 根据相邻的两个bits判断对这一位要做什么操作，+/-被乘数

- 与上面的思想类似，在一个寄存器左半部分，右半部分 分别 放置  Result，乘数；每次根据乘数最低位的序列对Result部分进行操作，比如 add 被乘数；
- 需要注意的是，计算这个序列是从 -1 位（默认为0）开始的
- shift操作每次都要进行  11、00 的情况相当于operation环节是空的

![image-20240312201717153](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202403122017346.png)

![image-20240312201709567](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202403122017722.png)

![image-20240312201848223](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202403122018448.png)

> Example
>
> <img src="https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202403122040896.png" alt="image-20240312204028709" style="zoom:50%;" />
>
> <img src="https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202403122034183.png" alt="image-20240312203417014" style="zoom:50%;" />

## Division

> Dividend=被除数，
>
> Divisor=除数
>
> Quotient 商

<img src="https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202403111422074.png" alt="image-20240311142246915" style="zoom:50%;" />

### V1

<img src="https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202403111424916.png" alt="image-20240311142420751" style="zoom:50%;" />

- 除数最开始在Divisor左64bits，被除数在Remainder右64bits，



> [!NOTE]
>
> <img src="https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202403111438530.png" alt="image-20240311143852286" style="zoom:50%;" />

### V2

**改进**

![](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202403172154020.png)

- 除数不动，被除数左移，进行计算，小于零则回退，左移remainder置0；大于零左移remainder置1

- `shift right` 针对的是最后一步，把余数部分的结果右移1bit

> example
>
> - 注意最后一步
>
> <img src="https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202403172158603.png" alt="image-20240317215819530" style="zoom:50%;" />

### 有符号除法

![image-20240317220036596](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202403172200669.png)

- `remainder` 高位，符号由被除数决定
- 低位  商
- **Overflow and division-by-zero** don’t produce errors
  - Just return defined results
  - Faster for the common case of no error

## Floating point Numbers

<img src="https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202403172204464.png" alt="image-20240317220442408" style="zoom:50%;" />

- **单精度**  float       1 +  8  +  23
- **双精度**  double   1 + 11 +   52

为了节省符号位的空间，`exponent`我们都加上了一个`biased`
$$
于是可以表示： \ \ (-1)^{sign}(1+significand)*2^{exponent - bias}
$$
<img src="https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202403172212979.png" alt="image-20240317221248926" style="zoom:50%;" />

### **Range **  

**Exponents** 

- **00000000 and 11111111 reserved**

<img src="https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202403172222643.png" alt="image-20240317222259589" style="zoom:50%;" />

<img src="https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202403172225819.png" alt="image-20240317222514753" style="zoom:67%;" />

### 精度

<img src="https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202403172222136.png" alt="image-20240317222225083" style="zoom:50%;" />

计算精度与小数位数相关

### 加法

- Alignment  对齐  一般由较小的数向大的变
- The proper digits have to be added  
- Addition of significands  
- Normalization of the result  归一化处理
- Rounding  进位

![image-20240317223335199](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202403172233256.png)

#### Algorithm

!!! example "example"
	![image-20240317223843919](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202405102012039.png)

<img src="https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202403172244708.png" alt="image-20240317224424583" style="zoom: 67%;" />

### 乘法

<img src="https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202403172248430.png" alt="image-20240317224822328" style="zoom:50%;" />

- 记得exponent部分相加之后减去一个 `bias` 
  - $y={exponent - bias},y_1+y_2=ex_1+ex_2-2*bias,ex_1+ex_2=y+2*bias$


![image-20240317224909204](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202403172249288.png)

### IEEE 拓展 精确算术运算

![image-20240321094206216](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202403210942554.png)

!!! warning "注意！"
	这个Blog定义的概念跟课本上的不一致

- [Blog ](https://www.cnblogs.com/cn-bear/p/16986645.html) 



- 这些bits的作用是在**运算过程中**保留精度便于之后进位损失的精度不超过0.5ulp
- `sticky bit` 在Round bit之后的所有位中只要有1就存为1，这个bit不一定要用到，是为了检测类似`2.500000000与2.500000001`的区别
- `Guard bit`    要保留的最低位之后的第一位
- `Round bit`   
- **舍入规则**:
  - 如果guard bit是0，那么直接截断。
  - 如果guard bit是1且round bit或sticky bit至少一个是1，那么向上舍入（加1至尾数的最后一位）。
  - 如果仅仅guard bit是1，那么执行向偶数舍入（如果尾数的最后一位是0则不变，如果最后一位是1则加1）。



## 题目

### 浮点数计算

![image-20240510210024267](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202405102100345.png)

??? info "Answer"
	![image-20240510210201785](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202405102102873.png)

![image-20240510210659311](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202405102106372.png)

![image-20240510210338244](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202405102103329.png)

??? info "Answer"
	![image-20240510213038403](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202405102130493.png)
	如果先计算后两个数，结果会发生变化，因为中间过程的GRTbit发生了变化，导致保持的精度变化
	