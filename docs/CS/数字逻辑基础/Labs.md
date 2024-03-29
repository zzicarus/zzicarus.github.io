> 期末复习用
>
> https://guahao31.github.io/2023_DD/lab5/decoder/

- 74LS138
  - G1,G2   G
- MC14495

# Lab 05  Decoder

**低电平有效**(Low-Level Active)，或称低电平触发，指的是在数字电路中，逻辑门或触发器的输入或控制信号在低电平（较低的电压值）时被视为有效或触发动作。高电平有效则与之相对。 在进行设计时，两者都是可行的选项。

## 74LS138

**74LS138** 芯片是一种 3-8 译码器芯片，用于将 3 位二进制地址输入信号转换为 8 个输出信号之一。主要端口为使能输入管脚 `G, G2A, G2B`，地址输入管脚 `A, B, C`（其中 `A` 为低地址），输出管脚 `Y0~Y7`。
![image-20240109160312524](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202401091603589.png)

## 使能信号

74LS138 有三个使能信号 `G, G2A, G2B`，其中 `G` 信号为高电平有效的主要使能信号，当它处于低电位时，所有的输出信号均处于无效电位（高电位）。

`G2A, G2B` 是看起来有些冗余的使能信号，从真值表可以看出，它们为低电平有效，当两个信号**都为**低电平且 `G` 为高电平时，3-8 译码器能正常工作；当 `G2A` 与 `G2B` 中有一个为高电平时，输出均处于无效电平。

这两个“冗余”的使能信号可以在实际应用中发挥作用，比如将 74LS138 用作**数据分配器**（或称多路分配器）时，可以将 `G2B` 置于低电平，这时地址信号对应的那个输出端口输出的电平将与 `G2A` 的电平相同。

同样的，当我们希望使用两个 74LS138 芯片组成一个 4-16 译码器时，也可以使用两个信号中的一个用于分配高一半地址与第一半地址，而保留 `G` 主使能信号的作用（如果仅有一个 `G` 使能信号，它将被用于区分高低地址，而使得到的电路需要添加额外的逻辑来实现主使能信号的作用）。

## 地址信号

我们约定 `A` 信号为最低位的地址信号，`C` 为最高位的地址信号，比如 `A, B, C` 信号值分别为 `0, 1, 1` 时，我们表达的地址为 `b110`，即对应选择 `Y6`。



# Lab 06 七段数码管

![image-20240109170314974](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202401091703017.png)

需要注意的是，这些 LED **共阳极**，我们给出 `0` 才能点亮（低电平有效）。比如，我们希望七段数码管显示为上图中“0”的样子，需要将 `g` 以外的信号设置为 `0` 表示点亮并将 `g` 设置为 `1`。

## MC14495

我们要实现的组合部件 `MyMC14495` 端口如下：

![img](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202401091704582.png)

- `D3~D0`：输入的 4 位二进制数字
- `LE`：使能信号，**低电平有效**
- `point`：用来表示小数点是否点亮，**高电平有效**
- 输出信号 `a~g, p`：均为**低电平有效**

> 在进行实现时，请注意 `LE` 为低电平有效，即值为 `1` 时所有的输出均为无效的 `1`；`point` 为高电平有效，即值为 `1` 时点亮小数点 `p` 输出为 `0`。

# Lab 07 Multiplexer

# 计数器和计时器

## 74LS161

74LS161 芯片具有**同步四位二进制计数器**功能，其引脚如下：

![img](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202401101516207.png)

- `CP`：接入时钟信号，**上升沿**触发
- `CRn`：清零端，**低电平有效**，且为**异步清零**
- `LDn`：置数控制端，**低电平有效**
- `D3~D0`：置数数据端，当 `LDn` 有效时将数据写入
- `CTT, CTP`：使能端，两脚均为**高电平**时启用计数功能，**任意一脚**为低电平时计数器保持原状态
- `Q3~Q0`：数据输出端
- `CO`：进位输出端，当输出位均为 1 时置 1

请特别关注输出改变时机：**异步清零**意味着不论时钟信号为何当清零端有效时**立即**改变输出为 0；**清零外**的所有输出改变都发生在**时钟上升沿**（包括置数与计数）。其功能表如下：

![img](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202401101516865.png)
