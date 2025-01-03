# Computer Network

> [!note]
>
> - [zjucomp 实验网站](https://zjucomp.net/)
>
> [TOC]

## Overview 

![image-20241217102836462](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202412171028674.png)

- 以太网 | Ethernet

计算机网络的功能：

- **数据通信 最基础的功能**
- 资源共享

**按逻辑分**

- 通信子网
- 资源子网

### 交换方式

`Router` 对收到的 packet 进行存储转发实现分组交换

- 电路交换
	有线电话网络。
	- **连接建立 —— 数据传送 —— 连接释放**
	- 缺点：中间节点无法发现并纠正错误；建立连接时间长
- 报文（message）交换 ——使用存储转发技术
	将 data 和其他数据封装
	- 将L位数据报文，以R bps的速率，发送到链路中： 需要L/R秒

- 分组交换 packet switching —— 在报文交换的基础上，对较长的 message 进行划分，在头部加上数据段形成新的 packet
	- 可以进行流水线化处理

<img src="https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202412171032461.png" alt="image-20241217103208274" style="zoom:67%;" />

### 计算机网络的分类

**工作方式**

![image-20241217095855631](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202412170959938.png)



### 性能指标

- **Speed**：连接到网络上的节点在数字信道上传送数据的速率，又称之为数据传输速率、比特率，单位 b/s 、bit/s 、bps
- **Bandwidth 带宽**：最高数据传输速率
- **Throughput 吞吐量**：单位时间通过某个网络的实际数据量
- **goodput 有效吞吐量** ：正确接收到的有用信息的数目
- **Delay 时间延迟**: 发送延迟 + 传播延迟 + 处理延迟 + 排队延迟
	- 发送时延又称为**传输时延 | transmission delay**，一个分组传输的的时间
	- **传播时延 | propagation delay**
		- 是从某个 router 到另一个 router，是两台路由器之间距离的函数
	- **处理时延 | processing delay**
		- 主机或路由器在收到分组时，为处理分组（例如分析首部、提取数据、差错检验或查找路由）所花费的时间
	- **排队时延 | queueing delay**
		- 分组在路由器输入输出队列中排队等待处理所经历的时延
- **时延带宽积** = 传播时延 * 信道带宽，是发送的第一个 bit 到达终点时，发送端发出的 **bit 数**
- **Round-Trip Time | RTT 往返时延**
- **Packet Per Second | packet 转发率**
	- 


>[!caution] 注意审题
>
>1. 看看清楚 bits 还是 byte，1 B = 8 bits
>2. **中间有几个路由器**
>	1. 比如甲乙通过一个路由器相连，那么它们分组转发的时候，第一组需要2t的时间，之后的按照流水线形式每一个间隔t的时间就能够到达
>3. 注意是否要计算 propagation dalay 和 transmission delay
>	1. Transmission delay一般都要计算，要形成流水线也是先发送之后，再去传播，传播时可以接着发送





### 协议与分层结构

#### network protocol

![image-20241217103406517](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202412171034773.png)

- 协议 Protocol
	- 语法 | **Syntax**。数据和控制信息的格式。如报文段格式
	- 语义 | **Semantics**。需要发出何种控制信息、完成何种动作及做出什么应答。比如TCP三次握手时所执行的操作。
	- 同步/时序 | **Synchronization**。执行操作的条件、时序关系。比如TCP三次握手的时序
- 不是所有的本层的功能都是service
- SAP | Service Access Point 接口
- 服务原语
	- Request  ->  Confirmation
	- Indication  ->  Response
	- Response
	- Confimation

**Service Primitives**

- 典型服务：面向连接传输服务，无连接传输服务
- 原语告诉服务执行某些操作或报告对等实体所采取的操作

![image-20241217103608808](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202412171036010.png)

#### OSI

 

物理层（Physical Layer）

•  定义如何在信道上传输0、1：Bits on the wire

•  机械接口（Mechanical）：网线接口大小形状、线缆排列等

•  电子信号（Electronic）：电压、电流等

•  时序接口（Timing）：采样频率、波特率、比特率等

•  介质（Medium）：各种线缆、无线频谱等



数据链路层 (Data Link Layer)

•  实现相邻（Neighboring）网络实体间的数据传输

•  成帧（Framing）：从物理层的比特流中提取出完整的帧

•  **错误检测与纠正**：为提供可靠数据通信提供可能

•  物理地址（MAC address）：48位，理论上唯一网络标识，烧录在网卡，不便更改

•  **流量控制**，避免“淹没”（overwhelming）:当快速的发送端遇上慢速的接收端，接收端缓存溢出

•  共享信道上的访问控制（MAC）：同一个信道，同时传输信号。如同：同一间教室内，多人同时发言，需要纪律来控制



网络层 (Network Layer)

•  将数据包跨越网络从源设备发送到目的设备（host to host）

•  路由（Routing）：在网络中选取从源端到目的端转发路径，常常会根据网络可达性动态选取最佳路径，也可以使用静态路由

•  路由协议：路由器之间交互路由信息所遵循的协议规范，使得单个路由器能够获取网络的可达性等信息

•  服务质量（QoS）控制：处理网络拥塞、负载均衡、准入控制、保障延迟

•  异构网络互联：在异构编址和异构网络中路由寻址和转发



传输层 (Transport Layer)

•  将数据从源端口发送到目的端口（**进程到进程 端到端**）

•  网络层定位到一台主机（host），传输层的作用域具体到主机上的某一个进程

•  网络层的控制主要面向运营商，传输层为终端用户提供端到端的数据传输控制

•  两类模式：可靠的传输模式，或不可靠传输模式

•  可靠传输：可靠的端到端数据传输，适合于对通信质量有要求的应用场景，如文件传输等

•  不可靠传输：更快捷、更轻量的端到端数据传输，适合于对通信质量要求不高，对通信响应速度要求高的应用场景，如语音对话、视频会议等



应用层

**七层ISO/OSI**

1. **会话层（Session Layer）**：
	- 负责建立、管理和终止应用程序之间的会话。
	- 涉及会话的同步和检查点，以允许会话在通信失败后恢复。
	- 提供了会话管理功能，如会话建立和终止。
2. **表示层（Presentation Layer）**：
	- 负责数据的表示、安全和压缩。
	- 转换数据格式以确保一个系统的应用层所发送的信息可以被另一个系统的应用层读取。
	- 涉及数据加密、解密、编码和转换。



**OSI模型和TCP/IP模型的不同之处**

1. TCP/IP**的网际层仅仅只有一种无连接的通信方式，而传输层支持无连接和面向连接**
2. OSI/ISO **在网络层支持无连接和面向连接，但在传输层仅支持面向连接的通信**

**概念**

1. **PDU**   Protocol Data Unit，协议数据单元
	1. 

2. **PCI**  Protocol Control Information，协议控制信息
3. **SDU**  Service Data Unit，服务数据单元; 来自上一层的数据

$$
PDU_n = PCI_n+SDU_n\\
$$





## Physical Layer 



## Data Link Layer

![image-20241219215259584](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202412192153820.png)

### 功能

 成帧 （Framing）

- 将比特流划分成“帧”的主要目的是为了检测和纠正物理层在比特传输中可能出现的错误，数据链路层功能需借助“帧”的各个域来实现
	

 差错控制 （Error Control）

- 处理传输中出现的差错，如位错误、丢失等

 流量控制 （Flow Control）

- 确保**发送方**的发送速率，不大于接收方的处理速率
	- 避免接收缓冲区溢出

#### 成帧

1. 帧定界
2. 透明传输
	1. 无论是什么值都要能够正常传输
3. 帧同步

![image-20241219215324853](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202412192153286.png)

##### 字节计数

![image.png](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202410111632475.png)

##### 带字节填充的定界符法

![image.png](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202410111631960.png)

![image.png](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202410111632503.png)

>[!note]  示例
>
>![image-20241011163429012](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202410111634101.png)

##### 带**比特**填充的定界符法 HDLC

![image-20241011163521376](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202410111635477.png)

![image-20241011163538953](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202410111635038.png)

![image-20241011163552157](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202410111635251.png)

##### 物理层编码违例

![image-20241011163853843](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202410111638975.png)

#### 差错控制

![image-20241011163959106](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202410111639208.png)

#### 流量控制

![image-20241011164012459](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202410111640536.png)

### 差错检测和纠正

**如何解决信道传输差错问题**

![image-20241011165139877](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202410111651973.png)

- **code word 码字**：包含m个数据位和r个校验位的n位单元
	- 描述为 (n, m) 码，n=m+r
- **码率 (code rate)**：码字中不含冗余部分所占的比例，可以用m/n表示
- **海明距离 (Hamming distance)**
	- **两个码字的海明距离**：两个码字之间*不同对应比特的数目*
	- 例：0000000000 与0000011111的海明距离为5
	- 如果两个码字的海明距离为d，则需要d次单比特纠错就可以把一个码字转换成另一个码字
	- 最小汉明距离意味着纠错的能力大小，不会被误认为其他比特
- [更多相关题目/原理的介绍](https://math.bme.hu/~pollux/codingtech/02en.pdf)

>[!note]
>
>**The error-detection and error-correcting properties of**  **a code depend on its Hamming distance.**
>
>To detect *d* errors:
>
>- you need *d+1* Hamming distance code. (Because with  such a code there is no way that *d* single-bit errors can change a valid code into another valid codeword).
>
>To correct *d* errors: 
>
>- you need *2d*+1 Hamming distance code. (Because that way the legal codewords are so far apart that even with *d* changes (A->A’), the original codeword *A* is still closer to *A’* than any other codeword *B*, so it can be uniquely determined.) 
>
>>[!note] 练习
>>
>>Ex2: consider a coding scheme: • 00 => 00000 00000 • 01 => 00000 11111 • 10 => 11111 00000 • 11 => 11111 11111 • Its Hamming distance is ?
>
>> [!note] 练习
>>
>> ![image-20241219234240295](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202412192342537.png)
>>
>> > [!note]
>> >
>> > ![image-20241219234257956](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202412192342172.png)

#### • 检错码（error-detecting code）

• 主要用在高可靠、误码率较低的信道上，例如光纤链路

• 偶尔发生的差错，可以通过重传解决差错问题

##### 奇偶检验 (Parity Check)

**交错检验**

![image-20241011171937581](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202410111719734.png)

##### 校验和 (Checksum)

主要用于TCP/IP体系中的网络层和传输层

![image-20241011171422172](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202410111714271.png)

- 溢出位的1要加入

![image-20241011172237002](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202410111722131.png)

##### 循环冗余校验 (Cyclic Redundancy Check，CRC)

数据链路层广泛使用的校验方法

![image-20241011174239132](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202410111742227.png)

- 这里的计算实质上都是对两个数进行亦或操作

>[!example] example
>
><img src="https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202410111740560.png" alt="image-20241011174045439" style="zoom:50%;" />

#### • 纠错码（error-correcting code)

• 主要用于错误发生比较频繁的信道上，如无线链路

• 也经常用于物理层，以及更高层（例如，实时流媒体应用和内容分发）

• 使用纠错码的技术通常称为前向纠错（FEC，Forward Error Correction)

![image-20241011214126847](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202410112141952.png)

##### 海明码 Hamming codes

- 被检验数据位的海明位号等于检验的各个检验位的海明位号之和

**如何求编码后的码字**

<img src="https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202410112154090.png" alt="img" style="zoom: 80%;" />

- 把一个数据为拆为某几个检验位的和，$P_n$检验位的值就等于所有使用到这个检验位的数据位$D_i$的异或的结果
- 检验原理:

**见王道 P62 **

##### Reed-Solomon code

![image-20241011220647011](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202410112206154.png)

##### 卷积码 convolutional codes

![image-20241011220756739](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202410112207810.png)

- 一个不断移动的输入序列，对它做convolution
- 卷积码的输出由当前输入和之前若干位输入决定，影响当前输出的此前输入位数称为 约束长度 constraint length。如图这种卷积码的约束长度为 6，每个输出 bit 会带来 2 bits 的输出，其中第一个是第 0, 2, 3, 5, 6 位的模二加法（0 指输入位，1~6 指 S1~S6 的值），第二个是第 0, 1, 2, 3, 6 位的模二加法。比如输入序列为 111，输入第一个 1 时 0~6 位是 1000000，因此输出是 11，然后 S1~S6 右移一位变成 100000；输入第二个 1 时为 1100000，因此输出是 10；输入第三个 1 时为 1110000，因此输出是 01。因此编码后为 111001。

>[!example] example
>
>![image-20241011221423389](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202410112214496.png)

**解码**

在所有可能的输出序列中找出与接收到的序列最相近的那一个，解码为这个序列对应的输入序列。

>[!example]example
>
>![image-20241011221157854](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202410112211964.png)
>
> - S表示不同的输入记忆，通过新的输入进入下一个状态的S

##### 里所罗门码 Reed-Solomon codes

##### 低密度奇偶校验码 LDPC, Low-Density Parity Check

### 基本的数据链路层协议

![image-20241011224107845](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202410112241982.png)

**关键假设**

![image-20241011224237214](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202410112242324.png)

#### 乌托邦式单工协议 A Utopian Simplex Protocol

• 单工（Simplex）协议：数据单向传输

• 完美信道：帧不会丢失或受损

• 始终就绪：发送方/接收方的网络层始终处于就绪状态

• 瞬间完成：发送方/接收方能够生成/处理无穷多的数据

![image-20241011224340934](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202410112243043.png)

#### 无错信道上的停等式协议 A Simplex Stop-and-Wait Protocol for an Error-Free Channel

- 数据传输保持单向, 但是需要双向传输链路（半双工物理信道）

接收方每当接收一个帧并处理完成后，发回一个确认帧；发送方在收到确认帧后（不需要处理，因为此时唯一的可能就是确认帧），则可以发送下一帧。这种协议在数据传输上是单工的，但是接收方需要发回消息，因此需要使用半双工信道。这种方案的实际问题在于，没有考虑出现错误的情况。

![image-20241011224519328](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202410112245441.png)

#### 有错信道上的单工停等式协议

![image-20241011225307188](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202410112253309.png)

![image-20241011231558665](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202410112315784.png)

- 考虑 3 种可能的错误 
- **接收到的帧检出错误**  为了解决第 1 种错误，我们引入一个新的事件 CKSUM_ERR 表示校验和有误；因而接收方在收到一个帧后应当校验正确性，发回一个表示正确或者错误的确认帧；如果检出错误，则直接抛弃该帧等待重传。如果发送方收到了表示错误的确认帧导致事件 CKSUM_ERR 发生，那么发送方将重新发送上一帧。
- **发送方发送的帧完全丢失**   对于第 2 种错误，**接收方完全没有接到一个帧，因而也不可能对此作出确认。**为了避免这种情况，发送方每次发送一个帧后启动或重置一个计时器，这个计时器的时间应当长于预期正常情况下收到确认帧的时间。如果计时器超时发送方仍未收到确认帧（事件 TIMEOUT），那么第 2 种错误有可能发生，此时发送方会将（缓存下来的）刚刚发出去的那一帧重新发出一次。直至发送方收到一个积极的确认帧，此时发送方再加载下一帧，上一帧的缓存即可以被覆盖掉。
- **接收方的确认帧丢失，重发可能导致收到重复的帧**     但是需要考虑的是，除了第 2 种错误，这种问题也可能导致发送方没有收到确认帧，因此可能会将一个正确收到（没有被抛弃）的帧重发，导致接收方收到两个该帧；如果不加限制，接收方的网络层则可能收到重复两次的该数据段，引起错误。我们需要防止这种重复的发生。考虑到发送方发送第 i + 1 帧的充要条件是第 i 帧已经收到了正确的确认，而这一确认的必要条件是接收方已经正确收到了第 i 帧。因此我们只需记录每一帧序号的奇偶性，并将其包含在帧头中（称为字段 seq）。如果接收方接收到了预期的（与前一帧相反的）奇偶标记，那么就将其保存；否则就说明前一帧被重复发送了，此时则直接抛弃该帧，同时发回一个确认（作为对前一个丢失确认帧的补充）。

#### 效率的评估

• F = frame size (bits) 

• R = channel capacity (Bandwidth in bits/second)

• I = propagation delay + processor service time (second)

• 每帧发送时间 (Time to transmit a single frame) = F/R

• 总延迟 (Total Delay) = D =2I

• 停止等待协议的发送工作时间是F/C，空闲时间是D

• 当 F<D 时：信道利用率 (line utilization)=F/(F+R·D) < 50%

### 滑动窗口协议

>[!note]
>
> **捎带确认 piggybacking**
>
>![image-20241012144857669](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202410121448774.png)

发送方和接收方都具有一定容量的缓冲区（即窗口），发送端在收到确认之前可以发送多个帧 

**目的**

- 对可以连续发出的最多帧数（已发出但未确认的帧）作限制

**序号使用**

- 循环重复使用有限的帧序号

**流量控制**：接收窗口驱动发送窗口的转动

- 发送窗口：其大小记作WT，表示在收到对方确认的信息之前，可以连续发出的最多数据帧数
- 接收窗口：其大小记作WR ，为可以连续接收的最多数据帧数

**累计确认**：不必对收到的分组逐个发送确认，而是对按序到达的最后一个分组发送确认

![image-20241012144611307](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202410121446430.png)

- 接收到接收窗口之外的帧会丢弃

#### 回退N协议 Go-Back-N | GBN

其中 N 代表 sending window 的大小，而这种协议中 receiving window 的大小始终为 1。当当前 sending window 的第一帧的计时器（实际上每一帧发出后都启动一个独立的计时器）超时仍未得到 ACK 时，回退 N 位到 sending window 的开头重新发送这 N 帧；而由于 receiving window 的大小是 1，因此提前到达的帧都会被抛弃。

![image-20241012150736516](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202410121507621.png)

**接收方：**

1. 窗口尺寸：WR=1
2. 按序接收：按照PDU编号依序接收，出错、乱序PDU一律丢弃
3. 确认含义：ACK(k)表示对k-1及以前各编号的PDU的确认，同时期望接收第k号PDU
4. 确认策略：按序到达的PDU可立即确认，也**可延迟确认(收到多帧后一起确认)**，但出错或乱序的PDU，确认ACK(k)（期望接收k号PDU）或不应答

>[!example]example
>
>![image-20241012151653444](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202410121516540.png)
>![image-20241012151710027](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202410121517152.png)

>[!note]
>
> **发送窗口的最大尺寸问题**
>
>$1<W_T\leq2^n-1$​
>
>**序号是重复使用的**

#### 选择重传协议 SR

![image-20241012152412858](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202410121524965.png)

![image-20241012153621823](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202410121543464.png)

发送方必须响应的三件事

• 上层的调用：检测有没有可以使用的序号，如果有就发送

• 收到ACK：如果收到的是最小序号的ACK，窗口滑动。如果收到其他序号的 ACK，进行标记

• 超时事件：每个PDU都有定时器，哪个超时重传哪个

>[!example]example
>
>![image-20241012153814965](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202410121538080.png)
>
>![image-20241012153832425](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202410121538522.png)

### 数据链路协议实例

#### PPP协议 | Point-to-Point Protocol

目前使用最多的数据链路层协议之一

![image-20241012154747738](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202410121547917.png)

- NCP 网络控制协议
- 但是HDLC是 bit 填充的，PPP是byte填充
- 不适用序号和确认机制只保证无差别接受，不可靠服务
- 只支持全双工点对点链路
- 两端可以运行不同的网络层协议

**帧格式**

![image-20241012154635886](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202410121546970.png)

![img](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202410121550052.png)

![image-20241012155543411](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202410121555491.png)

### 信道利用率

#### Stop-Wait | SW 停等协议

王道 P69

利用率 $U = \frac{T_D}{T_D+RTT+T_A}$

发送时间延迟 $T_D = \frac{分组长度}{传输速率}$，接收方发送确认message的时间延迟$T_A$​一般忽略不计

往返时延 RTT

#### 连续ARQ协议

ARQ包括GBN和SR

利用率$U=\frac{nT_D}{T_D+RTT+T_A}$

可能达到1，在一个周期内发送不完，不间断发送

## 介质访问子层 | MAC

>[!note] 知识点
>
>![image-20241022102654624](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202410221027770.png)

<img src="https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202410221027307.png" alt="image-20241022102754213" style="zoom:50%;" />

**网络链路**

- 点到点连接
- **使用广播通道**  multiaccess channel / random access channel
![](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202410191140439.png)

![image.png](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202410191142275.png)

>[!note]- 关于广播信道
>
>![image-20241022104448204](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202410221044357.png)
>
> - 可能两个（或更多）站点同时请求占用信道
>
> **静态方法**
>
> - FDM 分频
> - TDM 分时

### 多路访问协议

<img src="https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202410221049634.png" alt="image-20241022104933535" style="zoom:50%;" />

#### ALOHA

**纯种Aloha**
![image.png](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202410191154902.png)
吞吐率max：$\frac{1}{2e}$

**分槽**

必须等到下一个时间槽开始的时刻才能发送数据

<img src="https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202410221053360.png" alt="image-20241022105336275" style="zoom:50%;" />

$\frac{1}{e}$

>[!note] 性能分析
>
> **帧时**：发送一个标准长的帧所需的时间
>
> **吞吐量(Throughout) S** ： 在发送时间T内发送成功的平均帧数
>
> **运载负载(Carried load) G**，又称网络负载：时间T内所有通信站总共发送的帧平均值(包括原发和重发的分组)
>
> **$P_0$**：$P_0$是一帧发送成功(即未发生冲突)的概率
>
> - 可以得到$S = G*P_0$​
> 	- 对于纯的，$P_0=e^{-2G}$
> 	- slotted，$P_0=e^{-G}$
>
> **单向传播延迟Delay**：D
>
> **冲突危险期：**2*D
>
> - 不遭受冲突：$P_0=e^{-2G}$
>
>>[!note] - $P_0的计算$
>>
>>![image-20241022105906778](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202410221059893.png)

#### 载波侦听多路访问协议 | CSMA | Carrier Sense Multiple Access

##### 1 - Persist CSMA

![image.png](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202410191202157.png)

**存在冲突的情况**

- 如果存在两个站同时侦听一条信道，之后会同时发送，也会冲突
- 由于propagation delay，在发送过程中另外一个站侦听到的信道是空闲的

##### non-persist

![image.png](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202410191209747.png)

- 一定程度上避免了上述情况 1 

##### p-persist

只适用于时分信道

- 只是修改了概率，将空闲时的发送改为概率 p 发送
- 忙的时候，会持续监听（在下一个时隙）

##### 带冲突检测的 CSMA / CD

- 网络只能采用半双工通信
- 争用期 = 2 * 时延
- 最短帧长（争用期内发送的数据长度） =  时延  *  2  *  传播速率
	- 发送时间太短无法区分是哪个出了问题
- 如果争用期无冲突，则后续也无冲突

![image-20241022110650602](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202410221108833.png)

![image-20241019154627044](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202410191546129.png)

#### 无冲突协议 | 受控访问协议

##### 位图协议

![image-20241022111114180](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202410221111316.png)

![image-20241019155120470](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202410191551555.png)

##### Token ring

![ ](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202410191628644.png)

##### Binary Counter

![image-20241022111433492](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202410221114627.png)

![image-20241019162818450](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202410191628621.png)

#### Limited-contention protoco 有限竞争协议

**自适应树遍历协议**

![image-20241019164136695](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202410191641768.png)

[自适应树游走协议题目题解_牛客竞赛OJ (nowcoder.com)](https://ac.nowcoder.com/acm/problem/blogs/222206)

### 以太网

>[!note] 需要记忆
>- **10 Base-T**  10 Mbps 双绞线 twisted pair 
>- **1000Base-T** 1000 Mbps 双绞线
>- **100Base-FX**  光纤 optical
>- **10Base5** 同轴电缆 最大传输距离 500m   coaxial-cable
>- **10Base2** 同轴电缆 最大传输距离 185m

- 以太网通过 二进制指数后退 binary exponential backoff 算法确定每次冲突后的等待时间。
	我们将时间按照 51.2μs 分块；在第 i = 1 ~ 15 次冲突发生后，站等待 0 ~ min((2^i-1), 1023) 个时间槽后再次尝试发送；在发生 16 次冲突后，它放弃发送并给上层返回一个失败报告；高层协议负责进一步的恢复工作。这种算法的考量是，如果等待时间的上限较低，那么多个站发生冲突的时候很可能再次发生冲突；而如果上限较高，则很有可能发生很多无意义的延迟。这种算法可以保证：如果只有少量站发生冲突，则可以保证较低的延迟；当许多站发生冲突时，它也可以保证在一个相对合理的时间内解决冲突。

#### 经典以太网

##### 物理层

- 使用曼彻斯特编码
- 使用同轴电缆和中继器连接

<img src="https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202410221132270.png" alt="image-20241022113251135" style="zoom:50%;" />

##### Mac层

- 主机运行CSMA/CD协议
	- 网络层不负责重传，会直接丢弃不符合要求的Packet
	- 等待随机一段时间后重发，那么这个时间长度如何7确定?
		![image-20241022114144279](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202410221141384.png)

![image-20241022113323331](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202410221133436.png)

![image-20241022113347786](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202410221133939.png)

- 使用ipconfig /all命令查看MAC地址
- **前导码**
	- 7 byte 同步码
	- 1 byte **帧开始定界符**  只有开始，没有结束定界符 <= 曼彻斯特编码，电平容易区分
- **源地址后面的两个字节**，Ethernet V2将其视为上一层的协议类型，IEEE802.3将其视为数据长度
  - 大的表示长度
  - 小的表示类型
- **数据字段**
  - **IP datagram** 46 ~ 1500字节
  - 最小帧长 = 46+18 = 64B
  - 最大帧长 = 1500+18 = 1518B （MTU：1500B）
  - 数据字段不足46字节，需要填充整数字节（Padding）至46字节，以保证以太网MAC帧不小于64字节。
  - 以太网规定最短有效帧长为 64 字节，凡长度小于 64 字节的帧都是由于冲突而异常中止的无效帧。
- **校验和**
  - 采用CRC编码

#### 交换式以太网

使用集线器（HUB）组建以太网

![image-20241023230010544](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202410232300717.png)

- 交换式以太网的核心是交换机（Switch）
	- 工作在数据链路层，检查 MAC 帧的目的地址对收到的帧进行转发
	- 交换机通过高速背板把帧传送到目标端口

>[!note] - hub & switch
>
>![](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202410221147602.png)

### 数据链路层交换原理

- 数据链路层设备扩充网络
	- 网桥或交换机
	- 分隔了冲突域

![image-20241023230221005](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202410232302148.png)

#### 基于Mac地址的学习和转发

透明网桥使用 **MAC地址** 进行数据包的转发，而不依赖于IP地址或其他高层协议。这种方式是透明的，因为：

- 网桥在监听数据包时，不改变数据包的内容。
- 它通过监听网络中的流量，**学习每个设备的MAC地址**，并将其记录在内部的转发表中（称为 **MAC地址表**）。
- 当网桥第一次接收到数据包时，会查看目的MAC地址是否在MAC地址表中。
	- 如果存在，网桥会直接将数据包转发到相应的端口。
	- 如果不存在，网桥会将数据包**泛洪**到除发送端口外的所有端口，这样确保数据包能够到达目标设备。
	- 当目标设备响应时，网桥就可以学习到该设备的MAC地址，并将其加入MAC地址表，以便将来能够直接转发。

**MAC地址的构建**

- 增加表项：帧的源地址对应的项不在表中
- 删除表项：老化时间到期
- 更新表项：帧的源地址在表中，更新时间戳

![image-20241023230805281](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202410232308423.png)

**入境帧的处理**

![image-20241023230919595](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202410232309760.png)

![image-20241023230925282](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202410232309406.png)

![image-20241023230952859](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202410232309986.png)

•  广播帧：目的地址为FF-FF-FF-FF-FF-FF的数据帧

•  未知单播帧：目的地址不在MAC地址转发表中的单播数据帧

#### 链路层交换机

![image-20241023231532271](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202410232315415.png)

**交换方式 ： 带宽**

- 对称
- 非对称

![image-20241023231548802](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202410232315927.png)

| **特性**            | **存储转发模式（Store and Forward）** | **直通模式（Cut-through）** | **无碎片模式（Fragment-free）**      |
|---------------------|------------------------------------|-----------------------------|-------------------------------------|
| **数据接收方式**    | 接收完整帧                           | ==读取到目标MAC地址后立即转发== | 接收前 64 字节后再转发                |
| **错误检查**        | 完整检查帧校验序列（FCS）             | 不进行错误检查               | 检查前 64 字节                       |
| **延迟**            | 较高（需等待完整帧）                   | 较低（目标MAC地址解析后立即转发） | 中等（接收 64 字节后转发）             |
| **可靠性**          | 高（能过滤错误数据帧）                 | 低（可能传播错误数据帧）         | 中等（过滤大部分碰撞和错误帧）         |
| **适用场景**        | 企业级网络、数据中心                  | 高性能计算、金融交易、实时通信  | 一般网络环境，有中等时延和可靠性要求     |
| **网络带宽效率**    | 较低（过滤错误帧，消耗带宽）           | 较高（快速转发，无错误检查 => ==只检查目的地址 6bytes，所以最小的转发时延 = 6/...==） | 适中（减少小部分无效流量）              |
| **碰撞检测**        | 完全检测                              | 无检测                        | 前 64 字节内检测                      |
| **数据完整性保证**  | 最好                                  | 最差                          | 中等                                |

#### 生成树协议

打破了物理环，维护一个逻辑无环树

**Why Choose It**

![image-20241023231656883](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202410232316021.png)

**生成树协议**

- **根桥ID（Root ID）**: 被选为根的桥ID。
	- 桥ID共8字节，由2字节的优先级和6字节的MAC地址组成的。
- **根路径开销（Root Path Cost）**: 到根桥的最小路径开销。
- **指定桥ID（Designated Bridge ID）**: 生成和转发BPDU的桥ID
- **指定端口ID（Designated Port ID）**: 发送BPDU的端口ID

**选举过程**

![image-20241024121411262](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202410241214410.png)

(1) 选举根桥(Root Bridge) 。

- **ID最小**的交换机（网桥）成为生成树的根
- 同一广播域中的所有交换机均参与选举
- **根桥的所有端口都处在转发状态**

(2) 为每个非根桥选出一个根端口（Root Port）。

- 每个非根桥，通过比较其**每个端口到根桥的根路径开销**，选出根端口
- 具有**最小根路径开销的端口被选作根端口**
	- 根路径开销相同，则端口ID最小的端口（连接的网桥的ID）被选作根端口
	- 再比较链路端口ID比如 Fa0/2 Fa0/3
- 非根桥只能有一个**根端口，根端口处于转发状态**

![image-20241024121200596](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202410241212773.png)

(3) 为每个网段确定一个指定端口（Designated Port）。

>[!note] 关于什么是一个网段
>
> **物理角度**：网段是交换机端口通过线缆连接的链路。比如两台交换机 A 和 B 之间有一根以太网线，那么这就是一个网段。
>
> **逻辑角度**：网段是广播域的一部分，位于生成树拓扑结构中的一个单元，用于选举数据流的最佳路径。	

- 对于每一个网段， 在所有连接到它的交换机（网桥）端口中进行选择
	- 一个具有最小根路径开销的端口，作为该网段的指定端口
- 指定端口处于转发状态，负责该网段的数据转发
- 根桥的所有端口都是指定端口，除非自身形成环路
- 指定端口的每一个网段
	- 如果两个端口的根路径开销相同，那么比较
		- 网桥ID
		- 链路ID

![image-20241024121438376](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202410241214507.png)

### 虚拟局域网 | VLAN

>[!note]- 广播域的概念
>
>![image-20241024121721384](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202410241217512.png)

- 一个VLAN（Virtual LAN）是一个独立的广播域
- 交换机通过划分VLAN，来分隔广播域

![image-20241024121825431](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202410241218594.png)

- 不同VLAN的成员通信需要通过三层设备

![image-20241024121854740](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202410241218906.png)

**Tagged Frame** 

![image-20241024122158300](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202410241221425.png)

**Access 链路类型端口**

![image-20241024122220556](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202410241222696.png)

**Trunk 链路类型端口**

![image-20241024122250978](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202410241222146.png)

### 无线局域网 wireless LAN

LAN 本质上都是广播的

- WLAN使用802.11

>[!note] 范围问题
>
>• 传输范围(TX-Range)：成功接收帧的通信范围，取决于发送功率和无线电波传输特性
>
>• 物理层侦听范围（PCS-Range ）：检测到该传输的范围，取决于接收器的灵敏度和无
>
>线电波传输特性
>
>• 干扰范围（IF-Range ）：在此范围内的节点如果发送不相关的帧，将干扰接收端的接
>
>收并导致丢帧
>
>![image-20241027145806406](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202410271458503.png)

#### 组网模式

P105

![image-20241027145221051](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202410271452277.png)

- 另一种是无固定基础设施：自组网络 | ad hoc network

#### 体系结构

#### IEEE 802.11

**隐藏终端 | 暴露终端 问题**

![image-20241027145651784](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202410271456905.png)

#### CSMA/CA

不同帧间隙控制优先级

- SIFS（Short IFS）：最高优先级，用于Ack, CTS, 轮询响应等
- PIFS（PCF IFS）：中等优先级（SIFS+1槽口时间），轮询服务
- DIFS（DCF IFS）：最低优先级（ SIFS+2槽口时间），异步数据服务

![image-20241228235910925](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202412282359246.png)

![image-20241228235932336](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202412282359620.png)

### WAN 广域网

- 广域网和局域网不是包含的关系
- 广域网通常是点对点连接而局域网是广播信道

## Network

>[!note]
>
> - 点到点通信：由物理层、数据链路层和网络层组成的通信子网
> - 端到端通信：传输层
>
>| **特性**     | **端到端（End-to-End）**                  | **点到点（Point-to-Point）**                                 |
>| ------------ | ----------------------------------------- | ------------------------------------------------------------ |
>| **连接结构** | 源和目标之间可能有多个中间路由            | 只有两个端点直接相连                                         |
>| **协议层**   | 传输层和应用层                            | 物理层、链路层、网络层                                       |
>| **应用场景** | 互联网中的远程通信，如浏览网页、流媒体等  | 局域网中或物理上直接连接的设备之间的通信                     |
>| **传输控制** | 复杂可靠性控制机制，如 TCP 提供的可靠传输 | 直接传输，中间不含有中间设备（两个设备直接通信）通常不涉及复杂的可靠性控制 |

### 服务

**网络中的传输是否有确认和网络层提供的两种服务没有关系**

#### Virtual Circuit

**优劣**

#### Datagram

#### 拥塞控制

**检测拥塞**

**处理拥塞**

### 路由器

#### 路由表 | Routing Table

>有些时候和转发表不加以区分

### 网络层协议

#### IPv4

![image-20241029110503003](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202410291105217.png)

- Version： IPV 4/6
- **Total Packer Length** ：Header and data | MAX = 64KB
- **Type Of service**: **how important is the packet**  
- **Packet ID**
- **Flags** | 帮助分段
	- **第 1 位**：保留位，必须为 0。
	- **第 2 位（DF, Don't Fragment）**：不分片位，如果设置为 1，数据包不能被分片
	- **第 3 位（MF, More Fragments）**：更多分片位，若为 1 表示后面还有分片，若为 0 表示这是最后一个分片
- **Fragment Offset** 指明分片在原始数据包中的位置，以 8 字节为单位，帮助接收方重新组合分片。
- Protocol ID：说明 data 是哪种类型，将 data 交给相应的 code 进行处理。（  == 6 ）
- TTL
- Option:可选择

>[!tip]
>
> 1. 不同的单位
>   - Header Length 4B
>   - Total Length B
>   - Fragment Offset 8B 
> 2. IP首部字节以0x45开头 - > IPv4, 没有Option选项
> 	2. IP Header 为 20 bytes

>[!note] IPV4 地址
>
>
>
><img src="https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202411091836867.png" alt="image-20241109183615724" style="zoom:50%;" />
>
> - A
> - B
> - C
> - D 常用于组播 multicasting
>
>![image-20241109170849547](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202411091708743.png)
>
> - 私有IP地址
> 	- A类 10.0.0.0 - 10.255.255.255
> 	- B类 172.16.0.0 - 172.31.255.255
> 	- C类 192.168.0.0 - 192.168.255.255

##### 分片

MTU（Maximum Transmission Unit）, 最大传输单元

- 链路MTU
- 路径MTU (Path MTU)
	- 以太网的MTU = 1500B

#### NAT | 网络地址转换

- 普通路由器仅仅工作在网络层，而NAT还需要查看和转换传输层的端口号

#### 子网划分

##### CIDR 无类域间路由和路由聚合

#### DHCP动态主机配置协议

> **基于UDP的应用层协议**

当主机加入IP网络，允许主机从DHCP服务器动态获取IP地址

![image-20241109172352337](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202411091723462.png)

![image-20241109173448753](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202411091734876.png)

#### ARP

**在不同网络传输，MAC帧会改变**

![image-20241109174047628](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202411091740765.png)

>[!note] Address Resolution Protocol | ARP
>
> **地址解析协议：**在局域网中将IP地址映射到物理地址（MAC地址）的网络协议。ARP的主要作用是在同一网络中，设备通过已知的IP地址来获取目标设备的MAC地址，以便进行数据包的传输。
>
>![image-20241028170616900](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202410281706074.png)
>
> - Hardware：1（Ethernet）
> - protocol：0x0800（IP）
> 	- protocol address：IP地址
> - opcode：Request/Response
>
>>[!example] - 例子
>>
>> **步骤：**
>>
>> 1. **ARP请求**：
>> 	- 主机A生成ARP请求，内容为：
>> 		- 源IP：`192.168.1.2`
>> 		- 源MAC：`AA:BB:CC:DD:EE:FF`
>> 		- 目标IP：`192.168.1.3`
>> 		- 目标MAC：`00:00:00:00:00:00`（未知）
>> 	- 主机A将该请求广播到局域网。
>> 2. **ARP响应**：
>> 	- 主机B接收到ARP请求，发现目标IP匹配自己的IP地址，于是发送ARP响应，内容为：
>> 		- 源IP：`192.168.1.3`
>> 		- 源MAC：`FF:EE:DD:CC:BB:AA`
>> 		- 目标IP：`192.168.1.2`
>> 		- 目标MAC：`AA:BB:CC:DD:EE:FF`
>> 	- 主机B将ARP响应单播回主机A。
>> 3. **缓存更新**：
>> 	- 主机A收到ARP响应后，将`192.168.1.3`和对应的MAC地址`FF:EE:DD:CC:BB:AA`存储在ARP缓存中，以便下次直接使用。

#### ICMP

• ICMP 允许主机或路由器报告差错情况和提供有关异常情况的报告

• 由主机和路由器用于网络层信息的通信

• ICMP 报文携带在 IP 数据报中： IP上层协议号为1

- 类型
	- **差错报文**
		- 终点不可达：不可达主机、不可达网络，无效端口、协议
	- **询问报文**
		- ping 使用 回送请求/应答
- 不发送的类型
	- 针对ICMP报文不发送错误提示ICMP
	- **第一个分片的数据报片的所有后续数据报片**
	- 具有多播/特殊地址的数据包

![image-20241109181017066](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202411091810194.png)

>[!note] Ping
>
> - Ping 命令工作在应用层
> - 使用ICMP回送请求和回送回答报文
>
>![image-20241109181715786](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202411091817956.png)

>[!note]Traceroute
>
> - 工作在应用层

### 路由算法

这里讨论动态路由算法

#### Vector Distance

>最常用的是RIP，使用跳数估计距离

利用 bellman-ford 算法，计算单源最短路径

![image-20241109185157264](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202411091851425.png)

#### 链路 link state

使用Dijkstra算法

>将邻居状态发送给所有nodes

![image-20241109190750490](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202411091907633.png)

- tag
- age
	- 
- seq
	- 限制flooding的影响。拒绝所有 < # 该路由器收到过最大的序号

### 层次路由

**AS | Autonomous System**

- IGP
	- 同一AS内部
	- OSPF RIP IS-IS
- EGP
	- AS 之间
	- BGP

**广播 | Broadcasting**

- flooding 不加以控制容易出现广播风暴
	- sequence number controlled flooding

		![image-20241109225313515](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202411092253697.png)

	- **RPF | reverse Path Forwarding** 逆向路径转发**
	- Spanning Tree
		- 改进了逆向路径转发
		- 没有环路
		- 一个路由器可以不必知道整颗树，只需要知道在一颗树中的邻居即可
		- 消除冗余分组

		<img src="https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202411092259896.png" alt="image-20241109225939751" style="zoom: 50%;" />

**组播 multicasting**

- **IGMP INternet Group Management PRotocol**
- multicasting address 只能用于目的地址
- 不产生 ICMP 差错bao'wen

### 路由协议

这一部分看王道

#### RIP | Routing Info Protocol

王道 P187

- 使用跳数衡量到达目的网络的距离
- 周期性更新：30s
- 允许一条路径最多只能包含 15 个路由器
- 防止环路 》？
	- 触发更新
	- 毒性反转
	- 水平分割

#### OSPF | Open Shortest Path First

- 将一组网段组合在一起，称为一个区域
- 使用IP组播收发协议数据
- 向本区域所有路由器发送信息
	- 泛洪发送
	- 发送和本路由器相邻的所有路由器的链路状态

- 是网络层协议，直接以数据报形式发送
- 使用层次结构的区域划分，上层区域称之为主干区域，其他区域都必须和主干区域相连
  - 区域边界路由器 (Area Bounder Router，ABR)
  	- OSPF之间
  - 内部路由器 IR
  - 自治系统边界路由器 ASBR
  	- ASBR 是位于 OSPF 路由域与其他路由协议域（如 BGP、EIGRP、RIP）之间的边界路由器
  	- 桥接 OSPF 域与其他自治系统

![image-20241110160728951](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202411101607096.png)

#### BGP | Border Gateway Protocol

![image-20241110161328127](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202411101613262.png)

### 路由器工作原理

**控制层**

- 路由表
	- 路由选择

![image-20241112105725717](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202411121057961.png)

**数据层**

![image-20241112110247237](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202411121102542.png)

### 拥塞控制 | Congestion Control

### IPV6

Which is not a legal IPV6 address?

- 8300::1382:4567:89AB:CDEF
- **1382:4567:89AB:CDEF**
- ::211.31.20.46
- 2A43:0000:0000:0000:0123:4567:89AB:CDEF

## 传输层 | Transport

- 因特网的网络层提供**尽力而为**的服务：
	- 网络层尽最大努力在终端间交付分组，但不提供任何承诺
	- 具体来说，不保证交付，不保证按序交付，不保证数据完整，不保证延迟，不保证带宽等

- 传输层的**有所为**、**有所不为**: 

	- 传输层可以通过差错恢复、重排序等手段提供可靠、按序的交付服务

	- 但传输层无法提供延迟保证、带宽保证等服务



![image-20241126100522114](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202411261005330.png)

### Socket

**UDP version**

![image-20241126100828237](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202411261008395.png)

**TCP version**

![image-20241126101155329](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202411261011504.png)

- 客户程序不需要调用bind()，操作系统将为其在1024～5000之间分配一个端口号

### 分用和复用

![image-20241126101259682](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202411261012844.png)

**端口号的分类：**

- 熟知端口：0～1023，由公共域协议使用
	- 一般**服务器**使用，创建 socket 使用指定的 port

- 注册端口：1024～49151，需要向IANA注册才能使用
- 动态和/或私有端口：49152～65535，一般程序使用
	- **客户端一般的端口号** 由操作系统分配


**可以用来判断发送的方向**

### UDP

<img src="https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202411261034727.png" alt="image-20241126103437576" style="zoom: 50%;" />

- Header 8B
- 面向一个 **datagram**

**计算校验和**

![image-20241126103622164](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202411261036318.png)

- 发送方
	- 计算时需要包含
		- pseudoheader
		- udp header
			- checksum 全部置为 0
		- udp data
	- 还需要确保数据为偶数个字节，不然补 0
- 接收方
	- 直接求和
	- 为 0xFFFF 则为正确

**分层**

- 8192 B 的 data ， UDP总长度为 8200 B，在IP层需要分为 $\lceil\frac{8200}{1500 - 20}\rceil = 6个$

### TCP

**面向字节流**

![image-20241126110145682](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202411261101899.png)

- **head len**  单位为 4B
	- min 20B
	- max 64B



<img src="https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202411261149319.png" alt="image-20241126114940105" style="zoom:67%;" />

#### 可靠的数据传输

**发送端**：流水线式发送数据、等待确认、超时重传

- **超时重传**
	- 仅对最早未确认的报文段**使用一个**重传定时器
	- 仅在超时后重发**最早未确认**的报文段
	- **超时值设置**
		- 依赖于 RTT `EstimatedRTT`
		- 发送方每重传一个报文段，就直接将超时值增大一倍（不依赖于RTT的更新）
- **快速重传**
	- 在发送方短时间内连续发送大量数据时，接收端一直没有收到期望的序号，返回的确认包中的 ack number 都是相同的值
	- 收到3次重复确认，重发报文段

**接收端**：进行差错检测，采用累积确认机制，缓存失序的报文段

- 收到期待的报文段：发送更新的确认序号
- 否则重复

- **累计确认 + 推迟确认**
	- 为减小通信量，TCP允许接收端推迟确认
	- 接收方至少每隔一个报文段使用正常方式进行确认

![image-20241126112812014](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202411261128195.png)

#### 流量控制

![image-20241126113803610](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202411261138753.png)

**接收方**

- 一个 RcvWindow （RcvBuffer 中的可用空间）
- 接收方将RcvWindow放在报头中，向发送方通告接收缓存的可用空间

**发送方**

- 发送方限制未确认的字节数不超过接收窗口的大小
- 当接收方通告接收窗口为0时，发送方必须停止发送
	- 收到 WIN = 0之后，开启一个 persist timer，触发后发一个探测 window probe 
		- 序号为上一个段中最后一个字节的序号

#### 连接过程

##### 建立连接

##### 数据传输

##### 释放连接

#### 拥塞控制

**端到端**

- 发送方根据自己感知的网络拥塞程度，限制其发送速率

![image-20241202231243304](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202412022312533.png)

**cwnd 变化策略** AIMD

![image-20241202231339714](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202412022313897.png)

![image-20241202232041326](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202412022320530.png).

##### 慢启动 SS | Slow start

-  在**新建连接**上指数增大cwnd，直至检测到丢包（此时终止慢启动）

![image-20241202231548353](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202412022315539.png)

- 设置一个初始的阈值 **慢开始门限 | ssthresh**
- 先进行SS
	- 达到ssthresh, 进行CA
- **区分丢包事件**
	<img src="https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202412022329358.png" alt="image-20241202232919180" style="zoom:50%;" />
	- **超时**  这里的意思是只要超时就触发
		- ssthresh = cwnd / 2
		- cwnd = 1 MSS
	- 为了快重传：收到三个重复的ACK
		- ssthresh = cwnd / 2
		- TCP Reno ： cwnd = ssthresh + 3 线性增长  (更常用)
		- TCP Tahoe ：cwnd = 1 MSS. -> SS   
- 整个过程中，如果遇到网络拥塞，则马上把ssthresh变为**原来cwnd的一半**并且重新从1开始SS(不一定全部从1 比如上面的 TCP Reno)

## 应用层

### 网络应用模型

#### 客户/服务器模型 | Clinet/Server

#### P2P 模型

- Peer 对等节点

### 域名系统 | DNS

- 使用 C/S model
- 运行在UDP上使用53号端口
- 域名和主机地址、IP地址、Mac地址都没有一一对应的关系
	- 一台主机可以有多个网口就意味着有多个IP地址，每个网卡对应一个MAC地址
	- 同一台主机也可以有多个不同的域名
- IP 子网中的主机可以由不同的域名服务器来维护其映射

分为三部分

#### 层次域名空间

- **TLD | Top Level Domain 顶级域名**

#### 域名服务器

- 根域名服务器
- 顶级域名服务器 top-level name server
- 权限域名服务器 authoritative name server
	- 每台主机都必须在权限域名服务器登记
	- 将管辖的主机名转化为该主机的IP地址
- 本地域名服务器 local name server



**proxy name server（代理名称服务器）**：

- 代理名称服务器通常用作缓存DNS请求的服务器，它会代理其他DNS服务器的请求。它并不直接负责解析域名，而是将请求转发到其他服务器。
- 在静态IP配置中，通常不使用代理名称服务器。

#### 解析器

- 递归查询
- 迭代查询

都是由本地域名服务器发起

- 本地域名服务器
	- 根域名服务器
	- 顶级域名服务器
	- 权限域名服务器

### FTP

- 使用 C/S model
- 使用TCP协议
- 允许客户指明文件类型和格式，允许有存取权限
- 在FTP服务器上 数据经过
	- 应用层
	- 传输层 segment
	- 网络层 datagram
	- 数据链路层 frame
	- 物理层 byte

#### 控制连接和数据连接

使用两个TCP连接

- 控制连接 21
	- 整个会话期间
	- 也称之带外传送 out-of-band
- 数据连接 20
	- 文件传输完毕就会关闭
	- 两种模式，选择权在于客户端 ==无说明使用PORT==
		- PORT 主动模式
			- 客户端随机开放端口，发送PORT指令给服务端，服务端通过20接口连接
		- PASV 被动模式
			- 客户端发送PASV给服务端，服务端随即开放端口并告知客户端，客户端连接

### 电子邮件

P278

- 用户代理
- 接收端/发送端服务器
- 通信协议
	- 从user agent -> 发送端服务器，从发送端服务器 -> 接收端服务器 **SMTP**
	- 接收端拉取服务器的邮件 **POP3**

#### 格式问题

- 首部
	- From : xxx@qq.com
	- To : xxx@zju.edu.cn
	- Subject : About Computer Network
- 主体

#### SMTP | Simple Mail Transfer Protocol

- TCP 25
- 过程
	- 连接
		- TCP 连接直接建立在发送方和接收方之间
	- 发送
	- 释放

#### POP3 | Post Office Protocol

- TCP 110
- 在传输层使用明文传输密码，不加密
- 基于ASCII码，也需要MIME
- 由客户端决定是否将邮件保存到服务器
	- 下载并保存
	- 下载并删除
- 一个账号在服务器上只能有一个邮件接收目录

**另一个代替: IMAP**

- 可以值获取报文的某些部分
- 为用户提供了创建文件夹

---

**补充**

- 基于万维网
	- Gmail
	- 邮件服务器之间 **SMTP**
	- 其他情况 **HTTP**

#### MIME | Multipurpose Internet Mail Extension

对非ASCII码内容转换

- agent 非ASCII码 -> MIME 转为 7 位 ASCII 码 -> SMTP

### WWW | 

- URL
	- 每个文档唯一
	- `<协议>://<host>:<port>/<path>`
- HTTP
- HTML

#### HTTP

- 使用TCP 端口80
- 本身是无连接的，不需要建立HTTP连接
- 无状态的
	- 利于大量并发
	- Cookie 加 数据库
		- Cookie是由服务器产生的，存储在主机本地的
		- 记录用户访问的唯一标识码

**操作过程**

- 请求域名解析

**请求页面的时间**

- 非持续连接 1.0
	- 每个对象都要创建一个 TCP 连接，需要2*RTT
		- 第三次握手的报文段可以含有HTTP请求报文
- 持续连接 1.1
	- 

**报文结构**



<img src="https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202412091815659.png" alt="img" style="zoom:50%;" />

- HEAD 需要服务器响应但不要求返回请求对象

## 网络安全

**类别**

- integrity control 完整性控制

- Authentication 认证

- Secrecy 保密

- Nonrepudiation 不可否认

	![image-20241224095353459](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202412240954026.png)

- Kerckhoff原则：所有的算法必须是公开的，密钥的不公开的



- substitution cipher 置换密码
- transposition cipher 替代密码
- one-time pad

**公开的算法**

> ![image-20241224103111116](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202412241031385.png)

- RSA
	![image-20241224104355926](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202412241043185.png)
	- $e*d\ mod \ z  =1$​

**Symmetric-Key**

- Data Encryption Standard | DES
- Advanced Encryption Standard | AES
- 

## 总结

### 设备

- 如果一个存储转发设备实现了某个层次的功能，那么他可以互联两个在该层次上使用不同协议的网络/网段
- 冲突域：能产生介质冲突的
- 广播域：能收到同一广播的

==第一层==

- 不能划分冲突域
- 不能隔离广播域

**集线器 | Hub**
![image-20241229100548010](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202412291005300.png)

**中继器**

- 不能互联两个物理层不同的网段

---

==第二层 数据链路层==

- 划分冲突域
- 不能隔离广播域

**网桥**

- 可以互联两个物理层和数据链路层不同的网段

**交换机**

- 一般情况下，switch不能隔离广播域
- 但是支持VLAN的可以

**Adapter | 网络适配器 / NIC(Network Interface Card) 网络接口卡**

- 嵌入在主板上，实现计算机和外界局域网的连接
- 适配器和局域网的通信通过串行、适配器和计算机通过并行

****

==第三层==

**路由器**

- 划分冲突域
- 隔离广播域  ---  可以缓解广播风暴（ 不转发广播地址 255.255.255.255 ）
- 实现了物理层、数据链路层和网络层
	- 能够解析这三层的数据
- **功能**
	- **路由选择**
		- 通过协议不断更新路由表
	- **分组转发**
		- 输入接口卡
			- 转发表查询
		- 交换设备
		- 输出接口卡
- **转发表和路由表**
	- 转发表由路由表得到，是核心路由表
	- 路由表：对网络拓扑变化的计算最优化；总是软件实现
	- 转发表：查询目标最优化；可以软件/特殊硬件实现
- **交付方式**
	- 直接交付
		- 主机和目标网络在同一网络上，不通过路由器
	- 间接交付
- **默认路由**
	- 0.0.0.0 / 0
- **发送数据包的过程**
	- 源主机首先构建一个 Destination Address = ，Source Address = 的 Datagram


****

#### 题目

### 协议

#### 数据链路层

- HDLC
- SDLC
- PPP
- STP
- 帧中继



### 术语对照

### 各种帧的格式

#### MAC

![image-20241229100342273](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202412291003603.png)

![s](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202412291004478.png)

## 题目

>[!note]
>
> **Data Link Layer**
>
> **Network Layer**

### Data Link Layer

**计算SW的利用率**

- A channel has a bit rate of 4 kbps and a propagation delay of 20 msec. For what range of frame sizes does stop-and-wait give an efficiency of at least 50 percent?

---

- Consider an error-free 64-kbps satellite channel used to send 512-byte data frames in one direction, with very short acknowledgements coming back the other way. What is the maximum throughput for window sizes of 1, 7, 15? The earth-satellite propagation time is 270 msec. (give your answer as an integer)
	**A.**A. for window size=1: bps
	**A.**A. for window size=7: bps
	**A.**for window size=15: bps



---

A 100-km-long cable runs at the T1 data rate. The propagation speed in the cable is 2/3 the speed of light in vacuum. How many bits fit in the cable?

**A.** bits

---

**Go-back-n 的窗口大小**

Assume the sequence number has 5 bits. What is the maximum number of outstanding sending frames for a go back N protocol?

$2^n-1$​

---

**Go-back-n 的具体计算**

![70ab360670edaa425a7efc1b9242c42](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202411112242586.png)

![image-20241111224227878](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202411112242051.png)

- 

>[!faq]
>
>利用率
>
>$$
>U = \frac{T(传送一个frame) * \#frame}{RTT + R_s+R_r}
>$$

---

**Go-back-n 的重传机制**

After the sender first sends frames from 0 to 6 and at the end of timeout receives the acknowledgements for frame 1, 3, and 5, the next frame it will re-transmit is frame ______6__. (assume the protocol is go-back-n)

- 1
- 2
- 5
- 6

Box 1: Select the best answer

---

### MAC

ch4-2. A group of N stations share a 56-kbps pure ALOHA channel. Each station outputs a 1000-bit frame on an average of once every 100 sec, even if the previous one has not yet been sent (e.g., the stations can buffer outgoing frames). What is the maximum value of N?

**A:**  1030

---

**Q.** What is the baud rate of the standard 10-Mbps Ethernet?
**A.**  20 Mbaud

---

The reason for binary exponential backoff in the classical Ethernet is that________

- this algorithm is simple
- this algorithm is fast
- **this algorithm is adaptive to network load**
- this algorithm is scalable to network size

Box 1: Select the best answer  

---

**网络接口卡（Network Interface Card，NIC）** 主要在 **物理层** 和 **数据链路层** 工作。以下是这两个层级的具体作用：

1. **物理层（Physical Layer）**：
	- 网络接口卡负责将计算机生成的二进制数据转换为电信号（如电压或光信号）并通过物理介质（如网线或光纤）进行传输。它同样负责接收从网络介质上传输过来的电信号并将其转换回二进制数据。因此，网络接口卡在物理层上扮演了重要角色。
2. **数据链路层（Data Link Layer）**：
	- 网络接口卡在数据链路层上负责帧的构建和解析。它处理数据包的封装，将数据包封装为帧并添加数据链路层的头部信息（如源和目标 MAC 地址）。另外，它还负责错误检测和简单的纠错功能（例如通过校验和 CRC 检查数据完整性）。当接收到数据帧时，NIC 会解析这些帧并将其传递给更高层的网络协议进行进一步处理。

---

### 网络层

**CIDR 的地址分配问题**

**Q.** A large number of consecutive IP address are available starting at 198.16.0.0. Suppose that four organizations, A, B, C, and D, request 4000, 2000, 4000, and 8000 addresses, respectively, and in that order. For each of these, give the first IP address assigned, the last IP address assigned, and the mask in w.x.y.z/s notation.
**A.** Fill your answer in the blank

| Org# | First IP | Last IP | net/mask |
| ---- | -------- | ------- | -------- |
| A    |          |         |          |
| B    |          |         |          |
| C    |          |         |          |
| D    |          |         |          |

---

**IP 数据包分组问题**

![image-20241110141343128](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202411101413347.png)

----

**私有地址网络的问题**

Which is not the private address that will not appear in Internet datagram? 

A 10.3.18.82 

B192.168.8.3 

C 10.214.0.1 

D 172.33.8.8

>[!faq]
>
>在互联网数据报中，私有地址不会出现在公共网络中，RFC 1918 指定了以下三个私有 IP 地址范围：
>
> 1. **10.0.0.0 - 10.255.255.255**（10.0.0.0/8）
> 2. **172.16.0.0 - 172.31.255.255**（172.16.0.0/12）
> 3. **192.168.0.0 - 192.168.255.255**（192.168.0.0/16）
>
>根据这些范围，我们可以分析给出的地址：
>
> - **10.3.18.82**：属于 10.0.0.0/8 范围，是私有地址。
> - **192.168.8.3**：属于 192.168.0.0/16 范围，是私有地址。
> - **10.214.0.1**：属于 10.0.0.0/8 范围，是私有地址。
> - **172.33.8.8**：不在 172.16.0.0 - 172.31.255.255 的范围内，因此不是私有地址。
>
> **结论**：**172.33.8.8** 不是私有地址，它可能出现在互联网数据报中。

### 传输层

**\** 和IP层结合综合题**

见小测 5 

---



## 小测

![image-20241104234453384](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202411261021701.png)
