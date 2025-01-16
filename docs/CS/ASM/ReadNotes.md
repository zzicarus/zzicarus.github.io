---
  tags:
  - doing
Statistics: true
Title: Reading
Author: zzicarus
date: <% tp.date.now("YYYY-MM-DD HH:mm:ss") %>
update: <% tp.date.now("YYYY-MM-DD HH:mm:ss") %>
---

- 总线
	- 数据总线
	- 控制总线
	- 地址总线
	在 PC 中，CPU 通过总线与其他器件连接/进行控制（通过拓展卡槽），并不能直接控制

> - 这里的一个word指的是两个字节！
> - 课件里的例题很重要
> - 101012模式
> - 指令前缀 - REX 理解什么时候启用
> - 中断向量
> - 特权级别（考的不多）

## Ch 1

- Intel 是 little-endian format
	- string 没有权重，直接按照从左到右的顺序 ==无论大小端==

![image-20241227161934184](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202412271619369.png)

### 数制转换

![image-20241227163402405](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202412271634538.png)

### BCD

![image-20241227161746049](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202412271617276.png)

### IEEE 754 标准

- 32 bit
	- 1
	- 8 
	- 23

![image-20241227162259190](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202412271622314.png)

- special value

![image-20241227162510977](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202412271625237.png)

- normalized number
- denormalized number

![image-20241227162623942](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202412271626122.png)

- 进位方式
	- 一般四舍六入五凑偶

![](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202412271629319.png)

![image-20241227163118127](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202412271631235.png)

## Ch 2 微处理器及其结构

### register

- 通用寄存器
	- 64 bit 模式下多了 R8 - R15（还有很多小的分块如R8D，但是==这几个拓展寄存器不能单独访问16bit 下的高八位 AH, BH, CH, DH这几个也只能在没有REX前缀的情况下使用==）
	- ![image-20241227164047800](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202412271640967.png)
	- A 类
		- 做add指令会更短
			- 提高编码密度，单条指令的效果并不改变
	- 部分寄存器
		- 不能重命名然后乱序执行
			![image-20241227165112102](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202412271651216.png)

- 状态寄存器 RFLAGS | EFLAGS | 
	- `OF` : 针对有符号数，无符号数这个值没有什么意义
	- ![image-20241227165526347](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202412271655492.png)
	- ![image-20241227165717811](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202412271657934.png)
	  - 加的结果和 9 进行比较，大于则加6
	  	![image-20250102192332627](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202501021923886.png)
	
	- D Flag
	  - 决定`SI` `DI`的方向
	
- 段 Segment寄存器 64bit的分页管理只有部分寄存器`CS GS FS`
  - CS
  - DS
  - ES
  - SS
  	- BP addresses data within the stack segment
  	- SP 共同决定stack起点
- System 寄存器

### Modes of Operation

- 8086、8088到80186都是实模式、80286、80386、80486都是保护模式，兼容8086所 以有了 Virtual-8086 mode

![image-20241227170853911](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202412271708057.png)

### the process from real to 64

![image-20241227171125714](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202412271711847.png)

- 进入`real mode`
- `CR0.PE` -> `protected mode`
- `EFER.LME = 1, CR4.PAE = 1（物理地址拓展），CR0.PG = 1`  -> `兼容模式`
- `CS.L = 1` - > `64-bit mode`
- 任何模式下，只要发生了`SMI`系统管理中断，就会进入系统管理模式。`RSM` 返回

### **Memory Management**

- 满足
	- Relocation 重定位
	- Protection
	- Sharing
- Scheme
	- Segmentation
		- SMT
	- Page

![image-20241227172416948](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202412271724095.png)

### **Memory Addressing**

#### **Real mode**

- 只分段
	![image-20241227172639392](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202412271726541.png)
	- 各个段其实可以重叠
- wrap-around `segment 左移四位之后再加上offset可能超出限制，这时做地址回滚（把超出部分截断了）`
	![image-20241227172926270](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202412271729409.png)

#### Protected Mode

<img src="https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202501021938395.png" alt="image-20250102193823075" style="zoom:50%;" />

- 要满足隔离，刚刚的模式不行
- Selector 用来定位描述符的位置
	![image-20241227173408504](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202412271734621.png)
- Descriptor
  - Table
  	- Global | GDT 所有软件可见
  		- 至少有两个：代码段的，数据段的
  		- First null ：第一个必须是`null`；如果
  	- Local | LDT 不一定存在局部描述符表
  	- Interrupt | IDT 安全管理
  - GDTR LDTR的寻址方式
  

  	`TI = 0 GDTR`

  
  	<img src="https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202412271933429.png" alt="image-20241227193351312" style="zoom:50%;" />
  
- <img src="https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202412271941265.png" alt="image-20241227194128140" style="zoom:50%;" />
- ==**必考：** 粒度位G相关的计算 P73==
  - G = 1, 一位代表 4k 的大小
  - <img src="https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202501021944325.png" alt="image-20250102194436068" style="zoom: 33%;" />

  	<img src="https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202412271743596.png" style="zoom:33%;" />

- Privilege Level
  - [details](https://www.yanfukun.com/read/ospinciple/cpl-dpl-rpl#d940x2) 不过它里面对于栈的访问的条件判断个人感觉不对
  - **权限级别值越小00，优先级越高**
  - DPL 描述符的权限级别，规定了哪个特权级别的代码可以访问该段
  - RPL 请求者的权限级别，是Selector（段选择子）中的；决定对段的访问权限
  - CPL 目前CPU的权限级别，**处理器当前运行代码的特权级别**
    - 防止发生越权访问
  - 访问情况
    - 访问数据 ==CS和Selector中优先级较低的也要高于等于Descriptor==，从值上来说：$DPL\ge\max(RPL,CPL)$
    	![image-20241227192936027](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202412271929142.png)
    - 访问Stack 必须严格等于
    	![image-20241227192908209](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202412271929340.png)
  

### 四种内存地址类型及其转换关系

<img src="https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202501022003732.png" alt="image-20250102200356395" style="zoom:33%;" />

- **Effective Address**  偏移地址
	- 这里不太需要关注，之后会详细介绍这种寻址
		<img src="https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202412271943738.png" alt="image-20241227194305559" style="zoom: 25%;" />
- **Logical Address**
  - 64bit flat mem 下，LA == EA
- **Linear Addresses (virtual addresses)**
  - ![image-20241227194816489](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202412271948589.png)
- **Physical Addresses**

### 页

>OS学了

- 控制寄存器
  - <img src="https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202412272001821.png" alt="image-20241227200143667" style="zoom:67%;" />
  - `CR3` 20bit 指向首级的PDT
- `101012模式`
	<img src="https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202412272004096.png" alt="image-20241227200406965" style="zoom:50%;" />
	<img src="https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202501022013243.png" style="zoom:33%;" />
	- 这里的`*4`是因为每个目录项都是四字节，所以需要计算偏移字节量
	- 注意`CR3`中包含的是高20bit（按4KB大小的页对齐）

## Ch 3 Addressing Mode

![image-20241227202308236](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202412272023371.png)

### Data-Addressing Modes

![image-20250102210356898](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202501022103153.png)

- immediate operand 立即数寻址
	- 16位数的前面如果是字母开头，一定要加上一个0
		![image-20241227203115486](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202412272031635.png)
- 寄存器寻址
	- `MOV` 操作数的宽度要匹配
- 内存寻址
	- direct addressing
	- displacement addressing
		- ![image-20241227204249803](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202412272042987.png)
			- 段的基地址：除了BP、ESP使用`SS`，其他默认使用`DS`
	- 不能直接`MOV [内存] [内存]`
		- 不允许两个同时都是内存，除了字符串
		- 一条指令中至少有一个要确定操作数长度`MOV [DI], 10H is ambiguous`
			- Directive 伪指令 `MOV BYTE PTR [DI],10H` 指示内存操作数长度
- **Base-Plus-Index Addressing** 
	- ![image-20241227205719437](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202412272057600.png)
		- Scale只能是 1 2 4 8
- **RIP-relative addressing**  64位模式引入
	- <img src="https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202412272102408.png" alt="image-20241227210250233" style="zoom:50%;" />
	- 64 位地址的高16位必须要是符号拓展，要么`FFFF` OR `0000`
		![image-20241227210400901](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202412272104023.png)

- Stack Memory-Addressing Modes
  - This mode involves stack registry operations, e.g., PUSH AX
- Program Memory-Addressing Modes
- ==一定要注意ESP不能作为Index==

![image-20241227210652217](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202412272106428.png)

### 代码相关的寻址

- 在不确定长度的情况下，需要加上`JUMP NEAR PTR`等标签表示`displacement`的长度

![image-20241227211713666](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202412272117810.png)

- 看清楚加 3 是从哪里开始

![image-20241227211416748](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202412272114963.png)

![image-20241227211620425](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202412272116596.png)

### Stack 相关

- Push、Pop 至少两个字节
	- 先入高的部分再低的部分（仍然是小端模式）
- 栈的位置
  - `SS` 基地址，16位 => 拼凑20位的地址要左移四位
  - `SP` 偏移量
- `PUSH`
- `PUSHA`
- `PUSHF`

<img src="https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202412272122312.png" alt="image-20241227212202148" style="zoom:33%;" />

### 数据在内存中的存放规律：小端字节序

## Ch 4  Data Movement Instruction

![image-20241228171344187](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202412281713311.png)

- 不同的寻址方式是如何实现的

![image-20241227164659861](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202412271647062.png)

### Operation Mode

- Prefix
- Opcode
- MOD
- 

![image-20241228171009451](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202412281710655.png)

![image-20241228171033288](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202412281710489.png)

- Address Mode 地址
	![image-20241228165908582](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202412281659806.png)
	![image-20241228165937422](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202412281659567.png)
- 操作数
- 前缀
	- `66H`改变默认的数据长度
	- `67H`改变默认的地址长度
		![image-20241228170102592](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202412281701734.png)

### 前缀

![image-20241228172450590](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202412281724795.png)

- 每一组不能同时出现
	- LOCK 需要写到内存  需要影响到内存
		- An undefined opcode exception (#UD) occurs if the LOCK prefix is used with any other instruction. 如果不影响内存的指令使用了这个前缀，那么将出现`exception`
	- 更改类寄存器
		- ![image-20241228172746161](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202412281727350.png)
	- 操作数前缀
		![image-20241228172949434](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202412281729601.png)
		![image-20241228173435278](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202412281734443.png)
	- 地址前缀
		![image-20241228173502395](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202412281735588.png)
		- ![image-20241228173708537](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202412281737693.png)

#### REX

- REX前缀是一组值
- 两个地方用到
	- 访问拓展寄存器
	- 拓展操作数为64位

==REX 寄存器拓展前缀== 为了寻找64位下，拓展的8个通用寄存器

![image-20241228171928221](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202412281719357.png)

- `0100`
- `W 操作数长度` 在64位模式下生效，默认长度 32 位，开启后64位
- `R`  这里的作为高位，
- `X`  是否做scale，`R/M`
- `B`
- ![image-20241228172247309](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202412281722447.png)
- ![image-20241228172330714](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202412281723899.png)
- 转义编码 Escape Sequence
  - OF 开头
  	![image-20241228174022395](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202412281740538.png)

### Load Effective Address 偏移地址

移地址 

**LEA | Effective address**

- 用于获取地址 OFFSET（`Near `）
- flag 不变(==MOV都是这样==)
	- 跳转的判断条件不要使用
		![image-20241228174344360](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202412281743531.png)

**OFFSET Label**

- 静态计算
- 后面只能跟着Label
- `LEA SI, DATA1` `MOV SI, OFFSET DATA1`二者等效
	- `OFFSET`更加高效


**加载远地址**

- LSS 堆栈的段地址
- `LDS` 数据段
	- 高地址为段地址
	- 低地址为偏移地址

![image-20241228174856360](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202412281748538.png)

### String Data Transfers

至少一个操作数是内存

- LODS  **内存 -> 寄存器**
- STOS 
- MOVS **内存和内存**
- INS 
	- 从**端口到内存**
	- DI 放内存地址
	- DX 放设备端口
- OUTS
- SCAS CMPS

**相关寄存器**

- DI SI / EDI ESI
- Flag - DF 
	- CLD
	- STD
- Repeat Prefix
	- REP
	- REPZ REPE
- CX | ECX 作为 counter

### MISCELLANEOUS DATA TRANSFER

- **XCHG**
	
	- **交换**一个寄存器和一个寄存器/内存的值
		- `XCHG AL,[DI] is identical to the XCHG [DI],AL`
		- 不能是段寄存器
	- 实现锁 有一个是内存，加`LOCK`前缀
		- ![image-20241228180032304](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202412281800521.png)
	
- LAHF SAHF
	- XFLAG 的低八位和AH寄存器
	- `LAHF` 加载到AH中
	- `SAHF` AH存储到XFLAG中 
	
- **XLAT | TABLE Look-up Translation**
	
	- **查表使用**
	- 相当于`MOV AL, [seg:BX + AL]`，这是一个非法的指令
	- **参数**
		- BX 基地址（一个表的基地址）
		- AL
			- 作为偏移
			- 作为目的寄存器 最终结果
	- ![image-20241228180804159](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202412281808375.png)
	- 注意这里的`BX + AL`
		![image-20241228180942632](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202412281809800.png)
	
- **IN OUT**
	
	- 对寄存器 A 系列和端口进行数据交换
	- ![image-20241228181453640](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202412281814807.png)
	- ![image-20241228181536489](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202412281815682.png)
		- `set`  
	
- MOVSX MOVZX
	- 符号拓展 零拓展
		![image-20241228181954958](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202412281819171.png)
	
- BSWAP
	- 大小端模式转换
		![image-20241228182202420](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202412281822587.png)
	
- **CMOVcc**
	
	- 条件跳转
	
	- `COMVZ` zero flag = 1
	
	- `COMVS` 负数跳转
	

		`COMVP` 是parity

		![image-20241228182528349](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202412281825522.png)

	
	- ![image-20241228182426150](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202412281824330.png)
	
	- 减少由于投机失败的惩罚：`cmovcc`CPU不会guess
	
	- 基本块更大

### SEGMENT Override Prefix

![image-20241228182959731](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202412281829890.png)

### Assembler Detail

- [知乎文章](https://zhuanlan.zhihu.com/p/139785404)

**伪指令**

>Directives: tell assembler how to do
>
>Instructions: tell CPU what to do
>
>![image-20241228193343822](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202412281933974.png)	
>
> - `DUP`
> 	- The DUP directive allows multiple initializations to the same value. e.g., `DB 100 DUP(6)` reserves 100 bytes of 6 进行初始化
> 	- DUP(?) 未指定

- Storing Data
	- `DB` `DW` `DD` define ...
	- 

		`ALIGN 2`二字节对齐，不然上面的部分为奇地址

		![image-20241228193629362](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202412281936565.png)

>Problem ： ==P113 例题 必看！==
>
>![image-20241228194054485](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202412281940633.png)
>
> **注意**
>
> 1. 把内存画出来分析，注意小端模式
> 2. `DW`标签有一个`07H`内存中需要补0
> 3. 注意`string`, 放入 ASCII 码

- EQU 可读性考虑，也可以把标签“重命名”
	- EQU伪指令定义的符号名不能与其他符号名重名，符号名必须唯一，且不能被重新定义，而使用等号伪指令定义的符号名可以重名，可以被重新定义、重新赋值。

![image-20241228194801879](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202412281948059.png)

- ORG
  - 改变入口点，确定它的位置（绝大部分情况不需要）
- ASSUME
  - 段的名字和类型的关系，`ASSUME [保留关键字]:[段的名字]`
- THIS 多功能标签，同一个地址空间但是不同的管理粒度
  - 指定与当前地址计数器相等的一个地址单元的类型

![image-20241228194942434](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202412281949574.png)

<img src="https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202412281951850.png" alt="image-20241228195128700" style="zoom:50%;" />

- `DATA1 DATA2`指向同一个位置
	- `DATA1`一开始在低端，取值之后，`AX = BX`
- LABEL
  - 为当前存储单元定义一个指定类型的变量或标号
- PROC ENDP 
  <img src="https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202412282007126.png" alt="image-20241228200748999" style="zoom:50%;" />
  - 定义Procedure
  	<img src="https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202412282008357.png" alt="image-20241228200831194" style="zoom:50%;" />
- MACRO ENDM
  - 定义宏, 可以有参数
  	![image-20241228200944342](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202412282009548.png)
  	![image-20241228201130285](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202412282011502.png)
- INCLUDE
	- 


**Memory Organization**

- Full-segment
	- ![image-20241228201254843](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202412282012996.png)
		![image-20241228201442547](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202412282014769.png)
	- The ideal place to put assume directives is before all procedures in a program.
- `END`
	<img src="https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202412282019548.png" alt="image-20241228201933381" style="zoom:33%;" />

![image-20241228201741530](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202412282017748.png)

- `.DATA`：初始化数据段。
- `.DATA?`：未初始化数据段。
- `.CODE`：代码段。
- `.STACK`：栈段。

**Memory**

1. 全段定义
2. uses models
	1. `.MODEL`
	2. `@DATA @STACK` 获取指定的段

**段寄存器不能直接move进数据，必须通过通用寄存器**

```ASM
MOV AX,DATA_SEG
MOV ES,AX
MOV DS,AX
```

- 在代码段开始，要做一部分段的初始化。前期相当于一个占位符，并不知道真正的值

![image-20241228202152935](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202412282021104.png)

![image-20241228202239572](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202412282022753.png)

## Ch 5 Arithmetic and Logic Ins

**除了取非（Logic NOT）都会设置flag**

- 一旦出现填充问题，就要去区分究竟是正数还是负数

### Addition

- ADD 半加
- ADC 带进位的，全加器 P15
  ![image-20241229142733154](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202412291427342.png)

  - 分段累加
  - `CLC` 清除Carry
  - 过程中不要对Carry变化
  	- 使用LEA, INC, DEC 

  		```ASM
  		LEA r15,[r15 + 8]
  		```

  - ADCX ADOX 为了并行性 P17 *
  	- 使用不同的进位链，Carry Overflow

![image-20241229143256284](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202412291432513.png)

- INC
  - 对寄存器、内存(必须使用长度的伪指令)，不允许对段寄存器
  	`INC BL` `INC WORD PTR[SI]`
  - **保持Carry flag不变其他都可能变化**
  	- 即使产生进位也不会变化
  	- 为循环递增变量不产生干扰
  		- 防止递增变量INC产生进位导致Flag变化

​	P10 16bit sum

- **XADD**  exchange and add `XADD des, src ` P22
	- 先交换 `des src`，然后`des = des + src`
	- 可以作为锁
		- 乐观锁 冲突可能性小
			- 先进行操作
			- 通过一个version标签
		- 如果前后版本号不一致需要rollback

![image-20241229143706288](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202412291437523.png)

### Subtraction

- SUB
- DEC
	- 只改变CF
- SBB 带 borrow 的
	![image-20241229144115139](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202412291441304.png)
- CMP
  - 更新所有的flag
  - 不更改目的寄存器
- **CMPXCHG des, src (AL/AX/EAX)**  P29
  ![image-20241229144415679](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202412291444896.png)
  ![image-20241229144559297](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202412291445472.png)
  - 可以作为锁 P33 *
  	- 无锁数据结构
  - 先CMP后Exchange 
  	- `des == accu, then des = src, ZF =1`
  	- CMP des 和 累加寄存器的值
  
- CMPXCHG8B `CMPXCHG8B [mem64-operand]`
- CMPXCHG16B

### Multiplication

- 分为有符号和无符号
	- 有符号（`IMUL`）
		- 可能存在多个 2 / 3 操作数
		- 可能使用imm
		- 高位零拓展
	- 无符号 `MUL`
		- 单个操作数，乘数
		- 不能使用imm
		- 高位符号拓展
- multiplicand 隐含被乘数 放在A系列寄存器
- 乘数可以为内存 `MUL WORD PTR [BX]`
- 8 bit
	- AX = AL * 
- 16 bit
	- DX:AX = AX * 
- 32 bit
	- EDX:EAX = EAX * 


**IMUL** P45

- 1 操作数
- 2 操作数 
	- 可能会被截断 truncated
		- Product 不脱战
	- 可以引入立即数
		- signed extension
	- 会被汇编为三操作数
		- `IMUL BX,16H` -> `IMMUL BX,BX,16H`
- 3 操作数

![image-20241229150229048](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202412291502255.png)

**Flags**

判断高位是否存在有效位

![image-20241229150423238](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202412291504510.png)

- CF
- OF
- IMUL必须判断
	- 截断前后的结果是否一致，判断结果是否正确
		![image-20241229150534441](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202412291505686.png)

### Division P50

- 除法不能有立即数
- DIV
- IDIV

**errors**

- overflow
- divide by zero 
- 8 bit P52
	- 使用 16 bit 的 AX 作为隐含寄存器
	- 除数可以是寄存器/memory
	- AL：商 Quotient 
	- AH：余数 Remainder
	- ![image-20241229150701633](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202412291507844.png)
- 16 bit
	- AX 商
	- DX 余数
	- 被除数  DX : AX
- 32 bit
  ![image-20241229150910211](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202412291509443.png)

- IDIV P55
	- round to zero 的舍入方式
		- -16 / 3 = -5 ··· -1
		- 余数的符号和被除数相同

**填充指令** P59

- signed
	- CBW/CWDE/CDQE
		- 针对A类寄存器
		- Convert byte word
	- CWD/CDQ/CQO
		- 将A类寄存器拓展到D类
			- 比如在16bit除法，被除数需要是DX ：AX
				![image-20241217230142456](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202412172301578.png)
			- DX:AX
	- **MOVSX reg, reg/mem** 
	
- MOVZX reg, reg/mem

**余数处理**

- 

### BCD | ASCII

**BCD**

- 先做正常加法之后做调整
- DAA
	- 对AL寄存器
	- 跟在加法之后
		![image-20241229151459378](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202412291514609.png)

- DAS

**ASCII**

- AAA
	- 生成的是`unpacked`的BCD码结果，每一个数字占一个字节

![image-20241229152200112](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202412291522367.png)

![image-20241229151943650](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202412291519896.png)

### Logic Instruction

![image-20241229152325242](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202412291523481.png)

- NOT 取反
	- ==不会改变Flag==
- NEG 取补
	- ![image-20241229153157415](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202412291531611.png)
	- `neg ax` if ax = 0, CF = 0
		![image-20241229153413936](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202412291534139.png)
- AND
	- masking
- OR
- XOR
	- 可以用于清空所有的Flags`XOR AL,AL ; AL = 0`
- TEST
	- 测试，==执行AND== 影响flag而不影响操作数
		![image-20241229152528313](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202412291525478.png)
		![image-20241229152652571](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202412291526783.png)
- bit test指令 设置的是==CF==
	- BT
	- BTS
	- BTR
	- BTC
		![image-20241229152928801](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202412291529994.png)



**Shift**

- 实际上，移动的这个值是一个取模的值

![image-20241229153530336](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202412291535548.png)

![image-20241229153614663](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202412291536897.png)

- **SAR**
	- 在移位下，需要对被除数做调整。
	- ![image-20241229153949181](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202412291539403.png)
	- 如何修正？
		- 被除数修正
			![image-20241229154231661](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202412291542949.png)
		- 右移k bit

**Rotate**

- `ROL/ROR/RCL/RCR REG/MEM, Count `
- ![image-20241229154829403](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202412291548665.png)

**Bit scan**

- :TODO

![image-20241229155051515](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202412291550785.png)

- **CMPS**
	- if CX = 0 and ZF =1, then two strings match.
	- if CX ≠ 0 or ZF = 0, then the strings do not match
	- ![image-20241229155334605](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202412291553841.png)

## Ch 6 跳转

### 无条件跳转

- JMP
	- JMP imm
	- JMP reg 直接跳转到对应

跳转类型

- Short
	- 两字节指令，offset只有一个字节
	- 注意这张图中的IP位置
		![image-20241229155653738](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202412291556957.png)

- Near
	- 两个字节的offset
		![image-20241229155954516](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202412291559745.png)

- Far
  - `JMP TABLE [SI]`
  	- 
  - `JMP FAR PTR [SI]`或者`JMP TABLE [SI]` 并且TABLE data被定义为DD
  - 怎样表示
    - `JMP FAR PTR START`
    - 定义标签 `EXTRN START:FAR` 或者是 `START::`
  - 先offset后seg
    ![image-20241229160110408](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202412291601581.png)
- 

### 有条件 JCC

- 注意对有符号数无符号数两种比较

![image-20241218215439397](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202412182154544.png)

![image-20241218215539206](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202412182155302.png)

### Conditional Set 

![image-20241218220720920](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202412182207010.png)

### Loop

- `LOOP Label`
	- 使用C系列寄存器
	- 不改变Flag
	
- `LOOPE | LOOPZ`
  - `CX != 0 && Equal`继续循环
  - 循环条件为Equal，找首个不匹配
- `LOOPNE | LOOPNZ`
  - 循环条件为not Equal，找首个匹配

![image-20241229162334000](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202412291623202.png)

### 控制流的伪指令

<img src="https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202412182237779.png" alt="image-20241218223716704" style="zoom:67%;" />

![image-20241229162640490](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202412291626732.png)

- `.REPEAT`
	- `.UNTIL AL == 0DH`
	- `.UNTILCXZ`

![image-20241229163104793](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202412291631036.png)

![image-20241229163234174](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202412291632452.png)

### Procedures

- NEAR
- FAR : 全局的函数

```ASM
Name PROC NEAR/FAR USE BX CX DX
	USES ; 
	RET ; 
Name ENDP
```

![image-20241229163354648](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202412291633889.png)

- CALL
	- Near
		- 3 byte long，两个字节的displacement
		- **先把下一条指令的地址的`offset`入栈**
		- `CALL AX`绝对的CALL
		- `CALL <LABEL>`相对的CALL
			![image-20241229163801518](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202412291638727.png)
	- Far
		- 入栈的是下一条指令的`seg:offset`
	- Inter-privilege-level far call
	  - 跨安全级别的跳，哪怕距离近，但只要跨安全级别
	  	![image-20241219105548109](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202412191055206.png)
	- Task switch
	
- RET
	- `RET n` 在跳回去之前清理多少个栈
		![image-20241229164118394](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202412291641590.png)

### Interrupts

- ISP interrupt service procedure 
	- IVT 4 bytes
	- IDT 8 bytes

![image-20241229164655571](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202412291646777.png)

- Interrupt
	中断:外部硬件/内部软件**主动**(voluntary requests by program)发起,大部分是异步,软件发出的是同步的（using INT）
	- External
		- 分类
			- maskable 
				![image-20250103100739543](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202501031007796.png)
				- INTR pin
				- FLAGS.IF
			- non maskable | NMI
		- STI 操纵Interrupt Flags`INTR`，IF
		- CLI
	- Software
		- `INT n` e.g `INT 80h`
	- ![image-20241229165203657](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202412291652859.png)
- Exception
	- 分类
		- <img src="https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202501031010926.png" alt="image-20250103101051594" style="zoom:50%;" />
		- <img src="https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202412191449364.png" alt="image-20241219144938283" style="zoom:50%;" />
	- 助记符 `#GP（0）` general protection exception with error code 0
	  ![image-20241219144804751](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202412191448855.png)
	- ![image-20241219145202904](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202412191452985.png)



**double fault**

- 两个异常的嵌套并且符合下面的组合
	![image-20241229175419249](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202412291754502.png)

- error code
	- 放在栈上
	- ![image-20241229175553841](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202412291755100.png)
- **实模式下的处理**
	- IRET is used in real mode and IRETD in the protected mode.

![image-20241229175914728](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202412291759917.png)

- 软中断的处理
	- `INT N`和`far CALL`相近
		- `INT N` 还会把Flag入栈，使用`IRET`
	- `INT N` 这里的N就是中断向量号，相当于一个index
		- `INT 10H` 内存位置`40H`的地方放着它的描述信息
	- ![image-20241229180708419](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202412291807615.png)
- `INT3` 做断点指令
	- `INT 3` `INT3` 作用相同，编码长度不同
		- 方便指令的对齐，防止破坏其他的指令
	- ![image-20241229181307566](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202412291813811.png)
- `INTO` 主动看overflow是否被set
	- 如果set直接去处理

### MACHINE CONTROL AND MISCELLANEOUS INSTRUCTIONS

![image-20241229181517558](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202412291815854.png)

![image-20241229181529875](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202412291815152.png)

- LOCK 前缀
	- 对内存进行修改
	- ==算数/logic 才能加Lock,MOV就不可以==
	- 会报`#UD`
- BOUND
	- `BOUND REG, MEM`
	- ![image-20241229182019612](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202412291820878.png)

==!!!重要!!!==

- Stack Frame
	![image-20241229182301188](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202412291823365.png)
- `EBP`
	- 一个稳定的参考点，整个函数运行过程中不变
	- calling convention
		- 先保存老的EBP,把ESP的值赋给EBP形成新的基准点
		- 退出函数需要恢复EBP
	- EBP + n 访问父亲的para（其实是父亲给的参数）,EBP - n 访问 local var
		- 这里可以看出来EBP的值是在function开始运行的时候才赋予 的
	- ![image-20241229183257255](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202412291832456.png)
- Enter / LEAVE P148
	- <img src="https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202412291834648.png" alt="image-20241229183451440" style="zoom:50%;" />
	- 注意这里EBP指向的位置
		![image-20241229183810770](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202412291838015.png)

**保护模式下的梳理**

>这一块课上似乎没讲？（
>
>在第六章最后的PPT有

<img src="https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202501031042498.png" alt="image-20250103104237253" style="zoom:50%;" />

<img src="https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202501031044601.png" alt="image-20250103104455365" style="zoom:33%;" />

## Ch 9 **8086/8088 Hardware**

- 8086 16 个 AD
	![image-20241224213552477](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202412242135617.png)
	- Minimum mode
		- **ALE ：**地址锁存使能
			- 0 containing data
		- **BLE** 访问总线上的高八位
		- 单独一个处理器，直接输出信号
		  ![image-20241224214443211](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202412242144373.png)
	- Maximum mode
		- 

![image-20241218234840067](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202412182348149.png)

![image-20241224213823568](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202412242138698.png)

**内存的访问**

![image-20241230195130059](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202412301951277.png)

![image-20241230195324361](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202412301953558.png)

![image-20241230195413070](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202412301954287.png)

### Basic Interface

![image-20241230200317593](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202412302003826.png)

- 连接
	- output interface - `latch`
	- input interface - 输入设备通过`three state buffer`接到总线上
- IO地址编码
	- Isolated IO
		- 和内存地址不同，独立编码：使用独立的指令`IN OUT`
	- MM
		- 不需要额外的指令，速度更快
			- 更慢的反应速度
			- 限制了内存地址的大小
- 系统预定义端口
	- ![image-20241230200930800](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202412302009998.png)
	- 
- 同步的解决（本身存在状态的设备，异步设备：如何做同步）
	- strobing 单项选通
		- 分类
			- 数据源
				![image-20241230202508256](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202412302025460.png)
			- 目的
				![image-20241230202526304](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202412302025519.png)
	- handshaking polling 双向
		- 需要两条信号线
		- ![image-20241230202801122](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202412302028322.png)
	- polling
		- 
- 物理器件
	- TTL
		![image-20241230201149478](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202412302011675.png)
	- CMOS 比例定义动态范围

### IO PORT ADDRESS DECODING

>端口的数据和地址宽度是两件事

![image-20241230203329912](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202412302033144.png)

**单字节输出**

- 额外引入`BHE`，对内存地址进行访问
- ![image-20241230204237355](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202412302042566.png)

**十六位输出**

- <img src="https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202412302045088.png" alt="image-20241230204521847" style="zoom:50%;" />

**三十二位**

- ![image-20241230204621634](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202412302046841.png)

### 82C55 | 可编程并行接口

>端口和数据都是八位
>
>![image-20241230205117458](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202412302051662.png)
>
> - 使用A1,A2 选择端口，可变端口在中间部分

- 控制组
	- 端口A和B作数据，C口是用作握手的控制信号
		
		- C口的reading可以一次读取整个字节，但设置必须按照bit
			- 设置C口方向的前提是他没有被占用
		

		![image-20241230204857682](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202412302048866.png)

- 操作
	<img src="https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202412302053849.png" alt="image-20241230205350663" style="zoom:50%;" />
- Port
	- A 输入输出都有一组单独的latch和buffer
	- B 共享
	- C 共享，按bit进行操作（其余两个按字节操作）
- **Mode**
	- 0 : 基本输入输出（无选通信号）只能选择单项，只有数据交互，和always-on设备
	- 1：选通握手(A & B) 外部设备可能有时序
	- 2：双向的bus(A only)
		![image-20241230210128581](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202412302101768.png)
- **命令字**
	<img src="https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202412302105655.png" alt="image-20241230210544446" style="zoom:67%;" />
	
	- A（同时设置 A B）
	- B（对端口C进行按位设置）

![image-20241231192105677](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202412311921894.png)

#### mode 0

- Programming
  ![image-20241230210921511](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202412302109705.png)
  - 写A类/B类指令字
  - 比如一个设备占据了`700H - 703H`四个端口，那么我们根据端口选择信号就可以判断使用哪一个端口

![image-20241230212145349](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202412302121536.png)

#### mode 1

![image-20241231182258748](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202412311823995.png)

- example
	![image-20241231182946348](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202412311829559.png)

**output**

![image-20241231183715914](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202412311837304.png)

![image-20241231183727629](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202412311837845.png)

![image-20241231184936506](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202412311849777.png)

**combination**

![image-20241231185642207](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202412311856422.png)

![image-20241231185649013](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202412311856213.png)

#### mode 2

![image-20241231190714832](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202412311907044.png)

![image-20241231191510097](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202412311915319.png)

![image-20241231191720881](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202412311917080.png)

![image-20241231191741155](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202412311917343.png)

### 8254 | 

>电平触发：在CLK上升沿被采样，进而出发计数
>
>边沿触发：在任意时刻，GATE一旦产生上升沿，就会被内部的 flip-flop 采样保存，维持该信号，直到被下一个 CLK 上升沿采样到，然后下降沿触发计数

- 发控制信号
- 作为定时器，内部含有三个timer
	- 8259A 产生中断
	- 动态内存 DRAM 的flash
	- 和外部设备相关
		- 每一个timer的组成
			![image-20241231192828463](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202412311928662.png)

![image-20241231192750347](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202412311927571.png)

![image-20241231193256025](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202412311932220.png)

- 一个counter的内部结构

![image-20241231193744359](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202412311937699.png)

- 命令字
	- 每一个计数器都要设置control word
	- 选择一个counter
	- 如何进行读写
	- 选择二进制 or BCD

		先减后判断，最大初始值为0；注意模式 2 和 3 的最小 Count为2（需要连续高低交替的电平）

		![image-20241231194433205](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202412311944392.png)

	- **规范**
		- 先写control后写计数初值
		- 计数初值：具体怎么写和上面命令相关（可以只写单独一个byte也可以写两个byte）
			- 可以随时写（control写完之后/运行中）
				- 先在CR锁存然后一次加载到 CE
			- 但是在同一个counter中，如果正在写一个16位寄存初值并且还没有写完，这时不能切换；（中间不能夹杂别的东西，必须要连续的写数据）
				
				- `control` -> `LSB` -> `MSB`
				

				![image-20241231195127804](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202501021417060.png)

**不同的Mode介绍**

- mode 2 连续波形
- mode 3 连续的方波

![image-20241231195815585](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202412311958795.png)

- 共性
	- ![image-20250102142612835](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202501021426036.png)
- 不同
	- 图中有些不正确的地方，==Mode 2/3 是两种触发方式都有==
		![image-20250102142854514](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202501021428714.png)

- 对于不同mode下对Gate的变化响应
	- 

![image-20250102143553715](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202501021435912.png)

#### Mode 0

- 高电平有效
	- 在输入命令字之后变低电平，`counter`触发之后
- 上升沿采样GATE
	- ![image-20250102143502655](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202501021435858.png)
- 下降沿dec同时也可能更新计数值
	- ![image-20250102143729393](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202501021437580.png)

#### mode 1 硬件控制的 one-shot

>搞明白这里的边沿是怎么搞的
>
> - GATE 上升沿会被一个内部的 flip-flop 锁存
> 	- 上升沿的作用不是 enable 而是initialize counter

- 高电平触发
- 但是
	- CW一写入，就变高
	- ~~门控信号有效之后~~装入初始值，才会变为低
	- 之后在下降沿会把初始值装入
- Gate
	- 门控信号不需要一直保持
	- 
- ![image-20250102144323447](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202501021443661.png)

![image-20250102154254269](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202501021545298.png)

#### mode 2 N-分频器

- 计数到1产生低电平，之后自动装入原来的初始值重新计数
	![image-20250102144817993](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202501021448251.png)
- duty cycle = $\frac{N-1}{N}$
- Gate信号会使得重新计数，并且会使得输出一直为高
	![image-20250102145032477](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202501021450675.png)

#### mode 3 方波产生

![image-20250102145324305](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202501021453535.png)

#### Mode 4 software 触发（选通）

- 触发 => 产生一个周期低电平

![image-20250102145421766](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202501021454984.png)

#### Mode 5 

- 不像其他模式必须要做时钟上升沿采样

![image-20250102145641244](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202501021456454.png)

#### 例子

![image-20250102145952514](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202501021459751.png)

- 计算counter（都是N-分频）
	- 要注意是否能够写进去
	- 可能需要串联分频
- 写命令字
- 写counter初始值
	- 先写低
	- 再写高（必须写，否则状态机状态不对）

![image-20250102150417015](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202501021504247.png)

#### 读寄存器

**simple read**

**Counter latch command**

- 读取counter

![image-20250102150940881](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202501021509101.png)

- 读取例子
	- 根据之前设置的命令进行读
	- ![image-20250102151049100](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202501021510340.png)

**Read-Back Command**

- 读取的信息更多
	![image-20250102151243981](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202501021512216.png)
- 如果同时，那么先读取status
	- ![image-20250102151400418](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202501021514656.png)
	- ![image-20250102151706996](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202501021517214.png)

#### DC Motor Speed and Direction Control 

考试不考，电路没太看懂

大体思路就是利用H桥，通过控制占空比，进而操作电机的方向（使用相位差）

### 16550 串行通信

#### 串行的基本概念

![image-20250102154840881](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202501021548100.png)

![image-20250102155100906](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202501021551178.png)

1. CPU通过数据总线将数据送给串行通信接口（Convert parrallel to serial） 
2. 给数据头尾加一些信息（一些控制位，例如校验位、同步信号） 
3. 发送给目的端串行通信芯片 
4. 对控制位进行校验和分析，抽取出有效数据部分（Convert serial to parallel）

**时钟同步**

- 异步数据通信 asy
	- baud rate 每秒钟传输多少个bit，使用`bps`衡量，但是要注意的是，实际过程中传输的有效数据的值会远远小于这个理论值（其他信号 + 停顿 之类的会夹杂）
	- ==BCLK 波特率时钟== baud clock
		- 异步传输接收端实际使用的时钟
			- `BCLK = baud rate * baud rate divisor` 进行过采样
		- 分频的计算 查表
			![image-20250102162259350](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202501021622556.png)
- 同步数据通信 sy
	- 使用统一的外部时钟
	- 或者
- UART 异步，更简单
- USART 可用同步/异步

#### 正式介绍

![image-20250102163334040](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202501021633250.png)

![image-20250102163454307](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202501021634520.png)

- 提供了 16 个 byte 大小的 FIFO 缓冲区
- 停止位 stop bit 比较特殊，可以是 1 / 2 / 1.5位(维持半个时钟)
- Modem control functions 内置的调制解调
- Status reporting
- 可以全双工工作
- 一共可以使用 12 个端口

<img src="https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202501021649681.png" alt="image-20250102164957415" style="zoom:50%;" />

<img src="https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202501021651460.png" alt="image-20250102165158210" style="zoom:50%;" />

#### 编程

![image-20250102165646704](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202501021656914.png)

- Control 命令字

<img src="https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202501021659688.png" style="zoom:50%;" />

![image-20250102170145672](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202501021701895.png)

**具体流程**

![image-20250102170623391](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202501021706634.png)

- **初始化**
	- 选择波特率时钟
		![image-20250102170359681](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202501021703893.png)

![image-20250102171221066](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202501021712313.png)

- **发送数据**

![image-20250102171420909](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202501021714144.png)

- 接收数据

![image-20250102171719461](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202501021717710.png)

### 模拟信号 ADC DAC

>主要介绍DAC. 

- 零阶保持的
	- 低通滤波
		![image-20250102172031997](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202501021720230.png)

- Binary

![image-20250102172100336](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202501021721596.png)

![image-20250102172327772](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202501021723014.png)

- R-2R

![image-20250102172500636](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202501021725872.png)

- 参考电压 REF
- 满量程电压 FS

![image-20250102182407971](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202501021824187.png)

![image-20250102182327824](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202501021823039.png)

- **参数**
	- Resolution ==这里可能出计算题==
		![image-20250102182607147](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202501021826391.png)
		- example
			![image-20250102182556712](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202501021825949.png)
	- Linearity 线性度
		- 输出电压的准确性 : 理想值和实际电压最大差值
	- Settling Time 稳定时间
		![image-20250102182720448](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202501021827696.png)

**DAC0830**

## App

### 64 bit 寻址

- **RIP-relative addressing**  64位模式引入
- <img src="https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202412272102408.png" alt="image-20241227210250233" style="zoom:50%;" />
- 64 位地址的高16位必须要是符号拓展，要么`FFFF` OR `0000`
![image-20241227210400901](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202412272104023.png)
