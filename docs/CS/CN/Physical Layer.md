---
tags:
  - doing
statistics: true
title: NOTE
author: zzicarus
date: <% tp.date.now("YYYY-MM-DD HH:mm:ss") %>
update: <% tp.date.now("YYYY-MM-DD HH:mm:ss") %>
---

# Physical Layer

尽可能地屏蔽掉不同传输媒体和通信手段的差异，为数据链路层提供一个统一的数据传输服务

- 速率
	- **码元传输速率/波特率** ：单位时间数字通信系统传输的码元数  Baud
	- **信息传输速率/比特率 max data rate** ： 单位时间内数字通信系统传输的二进制码元数  b/s
- 带宽
	- 在模拟信号系统，某个信道传输信号的频率范围 Hz
	- 计算机网络，网络的通信线路传输数据的能力——**最高数据率**，b/s
- Maximum Data Rate
	- **Nyquist’s theorem**  在理想低通（无噪声、宽带有限）的条件下，避免码间串行
		- 极限码元传输速率为 2W Baud （W 为 channel 的频率带宽）
		- 极限数据传输速率 = $2Wlog_2V$ (V 为每个码元的离散电平数目——多少种不同的码元)
	- **Shannon’s formula** for capacity of **a noisy channel**
		- Max data rate = $Wlog_2{(1+\frac{S}{N})}$  S 传输信号的平均功率，N 高斯噪声功率，信噪比 = S/N = $10lgS/N$ dB

>[!note] 
>二进制信号在信噪比为 127:1 的 4kHz 信道上传输，求最大数据传输速率。根据 Nyquist's theroem，最大数据率为 2 \* 4k \* log_2(2) b/s = 8kb/s；根据 Shannon's theroem，最大数据率为 4k * log_2(1+127) b/s = 28kb/s。二者均为上界，取较小的一个，因此最大数据传输速率为 8kb/s

- 编码：数据 -> 数字信号
	- **归零编码 Return to Zero (RZ)**: 每个时钟周期均跳变到低电平（归零）
	- **非归零编码 Non-Return to Zero (NRZ)**
	- **反向非归零编码 NRZ Insert (NRZI)**：信号翻转代表 1，不翻转代表 0
	- **曼彻斯特编码 Manchester**: 将码元分割成两个相等的间隔，下跳表示 1，上跳表示 0. 电平跳变既是时钟信号用于同步，又是数据信号
		- 以太网使用
	- **差分曼彻斯特编码**：电平跳变仅仅表示时钟信号，码元开始处无跳变为 1 有则为 0
	![image.png](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202409261002264.png)

- 调制：数据 -> 模拟信号 module
	- FM 应用广泛
	- PM 改变载波的相位来表示 1/0，用相位 $0/pai$ 表示——绝对调相
	- QAM 正交幅度调制 ：在频率相同的条件下，结合 AM、PM
	![image.png](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202409261020490.png)
- 多路复用 multiplexing

![image-20241218113821739](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202412181138930.png)

## Guided Transmission Media

- Persistent storage
- Twisted pairs 双绞线
- Coaxial cable 同轴电缆
- Power lines
- Fiber optics 光纤
	- Essentially infinite bandwidth
	- 

## Wireless

## From Waveforms to bits

- 傅里叶变换
  ![image.png](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202409251023470.png)

- Bandwidth-limited signals
![image.png](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202409260926012.png)

## Multiplexing

### Frequency Division Multiplexing | FDM 频分复用

![image.png](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202409261034571.png)

- 同时不同频
- 中间留有一段保护频道

### Time Division Multiplexing

![image.png](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202409261034127.png)

- 按时间分时

### Code Division Multiplexing | CDM | CDMA

- 码分，更加灵活可以灵活调整带宽的分配
- 同频又同时，同时发出但存在规律可以反解码
![image.png](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202409261044456.png)
- 0 silence，-1 发送 0，1 发送 1

### Wavelength Division Multiplexing

- 不同光的频率不同，本质上是频分
![image.png](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202409261046301.png)

## 设备 | 中继器

![image.png](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202409261055974.png)

- 上面的方式 A/D 转换次数多，信噪比低，传输速率低
- Trunk