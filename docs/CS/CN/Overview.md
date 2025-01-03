---
tags:
  - doing
  - CN
statistics: true
title: NOTE
author: zzicarus
date: <% tp.date.now("YYYY-MM-DD HH:mm:ss") %>
update: <% tp.date.now("YYYY-MM-DD HH:mm:ss") %>
---

# Overview

## 实验部分 | 了解一些术语和基本协议

>[!note] Terms
>- ISP（Internet Service Provider）因特网服务提供商。端系统通过 ISP 连接到网络
>- host/end system 主机/端系统
>- message
>	- packet 将较长的 message 进行分组后的结果。当一台端系统要向另一台端系统发送数据时，发送端系统将数据分段，并为每段加上首部字节。
>- communication Link 通信链路
>- packet switch 分组交换机
>	- router 路由器
>	- link-layer switch 链路层交换机
>- socket interface 套接字接口是数据发送端需要遵循的一种规则，这样数据才能正常发送
>- 区分 Internet 和 internet

>[!note] 传输层协议
TCP 面向连接的
UDP 
MAC 唯一的，基于网卡的

>[!info] Four Internet Model
>![image.png](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202409121558575.png)

>

## OSI 模型 & TCP/IP 模型

![image.png](http://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202409242000269.png)

### OSI

![image.png](http://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202409242003204.png)

- Service
- Interface
- Protocol



**各层级的作用**

- Physical Layer 物理层并不是物理介质，不包括电缆线等这些介质。规定了一些电路接口、信号
- Network Layer
  传输单位为 `packet`。
- Data Link Layer 
  将来自网络层的 IP 分组封装成 **frame**，可靠地传输到相邻结点的网络层。可以将强物理层传输原始比特流的功能，将物理层可能出错的错误进行修正

  >The data link layer operates between two directly connected nodes and does not provide end-to-end communication。

### **IP Service**

> [!note]
>
> ![image-20241028152518801](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202410291100041.png)

**simple service**

- Datagram
- Unreliable
- Best Effort
	- 只有在出错的时候才会直接丢掉

- Connectionless

> [!note] Why Ip So Simple
>
> - Simple, dumb, minimal, faster
> - End - to - end principle
> 	- done by software
> - more top layer choice
> 	- udp tcp
> - work at any link layer
> 	- 泛用性

**features**

- End-to-end
- 阻止 packets 永远 loop
  - TTL
- Fragment packet
	- 链路层的带宽一定
	- Header提供信息帮助Fragment
- Header to checksum 
- 可拓展，增加新的 options 到 header
- Version
	- IPv4  32bits
	- IPv6  128bits

**IPV4**
![image.png](http://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202409241207369.png)

- Version： IPV 4/6
- Total Packer Length ：Header and data | MAX = 64KB
- Type Of service: how important is the packet  
- Packet ID
- Flags | 帮助分段
- Fragment Offset
- Protocol ID：说明 data 是哪种类型，将 data 交给相应的 code 进行处理。（  == 6 ）
- TTL

采用 three-way handshake 方法

- SYN （Synch）
- SYN / ACK
- ACK

**TCP**

Forwarding table 

- `traceroute` Linux
	[traceroute使用与实现原理分析 - 知乎 (zhihu.com)](https://zhuanlan.zhihu.com/p/36811672)
- 

#### Principle

1. **Packet Switching**

- 在中间的Router使用Switching Table
- Simple packet forwarding
	- 交换机不需要任何关于flow的信息，可以处理independent packet
- Efficient sharing of links

**Data traffic is bursty**

- 

2. **Layering**

3. **Encapsulation**

> [!note] Big endian/ Little Endian
>
> > 在不同的架构主机采用的大小端不同，但是网络层统一为大端，网络编程提供了一些helper function帮助转化
>
> 网络顺序和主机顺序的转换
>
> - `htons()`

> [!note] IPv4
>
> **Netmask 网络掩码**：用于判断是否在同一个
>
> 网络掩码(Netmask)又称[子网掩码](https://baike.so.com/doc/4236543-4438579.html) 用于从[IP地址](https://baike.so.com/doc/4252723-4455111.html)中提取网络号或[主机](https://baike.so.com/doc/5331327-5566564.html)号。网络掩码就是结构为[网络号](https://baike.so.com/doc/2026144-2143986.html)全部是1，主机号全部是0的IP地址。
>
> - 如果在一个子网下，转发信息不通过router

> [!note] LPM | Longest Prefix Match
>
> 路由表中的每个表项都指定了一个网络，所以一个目的地址可能与多个表项匹配。最明确的一个表项——即[子网掩码](https://zh.wikipedia.org/wiki/子网掩码)最长的一个——就叫做最长前缀匹配。
>
> 之所以这样称呼它，是因为这个表项也是路由表中，与目的地址的高位匹配得最多的表项。
>
> > **网络前缀越长，其地址块就越小，意味着路由就越具体(more specific)越准确**

> [!note] Address Resolution Protocol | ARP
>
> **地址解析协议：**在局域网中将IP地址映射到物理地址（MAC地址）的网络协议。ARP的主要作用是在同一网络中，设备通过已知的IP地址来获取目标设备的MAC地址，以便进行数据包的传输。
>
> ![image-20241028170616900](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202410281706074.png)
>
> - Hardware：1（Ethernet）
> - protocol：0x0800（IP）
> 	- protocol address：IP地址
> - opcode：Request/Response
>
> > [!example] - 例子
> >
> > #### 步骤：
> >
> > 1. **ARP请求**：
> > 	- 主机A生成ARP请求，内容为：
> > 		- 源IP：`192.168.1.2`
> > 		- 源MAC：`AA:BB:CC:DD:EE:FF`
> > 		- 目标IP：`192.168.1.3`
> > 		- 目标MAC：`00:00:00:00:00:00`（未知）
> > 	- 主机A将该请求广播到局域网。
> > 2. **ARP响应**：
> > 	- 主机B接收到ARP请求，发现目标IP匹配自己的IP地址，于是发送ARP响应，内容为：
> > 		- 源IP：`192.168.1.3`
> > 		- 源MAC：`FF:EE:DD:CC:BB:AA`
> > 		- 目标IP：`192.168.1.2`
> > 		- 目标MAC：`AA:BB:CC:DD:EE:FF`
> > 	- 主机B将ARP响应单播回主机A。
> > 3. **缓存更新**：
> > 	- 主机A收到ARP响应后，将`192.168.1.3`和对应的MAC地址`FF:EE:DD:CC:BB:AA`存储在ARP缓存中，以便下次直接使用。



![](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202410281523829.png)



**What is Internet layer**

## Internet