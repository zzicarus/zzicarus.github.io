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
>- 

>[!note] 传输层协议
TCP 面向连接的
UDP
MAC 唯一的，基于网卡的

>[!info] Four Internet Model
>![image.png](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202409121558575.png)

## 交换方式
`Router` 对收到的 packet 进行存储转发实现分组交换
- 电路交换
  有线电话网络。
	- 连接建立 —— 数据传送 —— 连接释放
	- 缺点：中间节点无法发现并纠正错误；建立连接时间长
- 报文（message）交换 ——使用存储转发技术
  将 data 和其他数据封装
- 分组交换 —— 在报文交换的基础上，对较长的 message 进行划分，在头部加上数据段形成新的 packet
	- 可以进行流水线化处理

## 计算机网络的分类
## 性能指标
- **Speed**：连接到网络上的节点在数字信道上传送数据的速率，又称之为数据传输速率、比特率，单位 b/s 、bit/s 、bps
- **Bandwidth 带宽**：最高数据传输速率
- **Throughput 吞吐量**：单位时间通过某个网络的实际数据量
- **Delay 时间延迟**: 发送延迟 + 传播延迟 + 处理延迟 + 排队延迟
	- 发送时延又称为传输时延，一个分组传输的的时间
	- 传播时延是从某个 router 到另一个 router，是两台路由器之间距离的函数
- **时延带宽积** = 传播时延 * 信道带宽，是发送的第一个 bit 到达终点时，发送端发出的 **bit 数**
- **Round-Trip Time | RTT 往返时延**: 
- 
>[!caution] 注意审题
>看看清楚 bits 还是 byte，1 B = 8 bits

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
  传输单位为 ``。
- Data Link Layer 
  将来自网络层的 IP 分组封装成 **frame**，可靠地传输到相邻结点的网络层。可以将强物理层传输原始比特流的功能，将物理层可能出错的错误进行修正
  > The data link layer operates between two directly connected nodes and does not provide end-to-end communication。




IP Service
**simple service**
- Datagram
- Unreliable
- Best Effort
- Connectionless
**features**
- End-to-end

- 阻止 packets 永远 loop
	- TTL
- Fragment packet
- Header to checksum 
- 可拓展，增加新的 options 到 header

**IPV4**
![image.png](http://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202409241207369.png)

- Version： IPV 4/6
- Total Packer Length ：Header and data
- Type Of service: how important
- Packet ID
- Flags
- Fragment Offset
- Protocol ID：说明 data 是哪种类型，将 data 交给相应的 code 进行处理。（ == 6 ）
- TTL

采用 three-way handshake 方法

**TCP**

Forwarding table 