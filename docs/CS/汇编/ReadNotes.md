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

- 

## Ch 1

## Ch 2 

**register**

- 通用寄存器
- 段 Segment寄存器
- System 寄存器

**Modes of Operation**

- the process from real to 64

**Memory Management**

- 满足

	- Relocation 重定位

	- Protection

	- Sharing

- Scheme

	- Segmentation
		- SMT
	- Page

**Memory Addressing**

- Real mode

	- wrap-around

- Protected Mode

	- Selector
	- Descriptor
		- Table
			- Global
				- First null
			- Local 不一定存在
			- Interrupt
		- GDTR LDTR的寻址方式

	- **必考：** 粒度位G相关的计算 P73

	- Privilege Level
		- DPL 描述符
		- RPL 请求
		- CPL 目前CPU
