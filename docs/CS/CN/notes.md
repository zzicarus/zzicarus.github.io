# Computer Network

## Data Link Layer

### 功能

 成帧 （Framing）

- 将比特流划分成“帧”的主要目的是为了检测和纠正物理层在比特传输中可能出现的错误，数据链路层功能需借助“帧”的各个域来实现

 差错控制 （Error Control）

- 处理传输中出现的差错，如位错误、丢失等

 流量控制 （Flow Control）

- 确保发送方的发送速率，不大于接收方的处理速率
	- 避免接收缓冲区溢出

#### 成帧

##### 字节计数

![image.png](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202410111632475.png)

##### 带字节填充的定界符法

![image.png](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202410111631960.png)

![image.png](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202410111632503.png)

>[!note] 
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

>[!note]
>
> **The error-detection and error-correcting properties of**  **a code depend on its Hamming distance.**
>
>To detect *d* errors:
>
> - you need *d+1* Hamming distance code. (Because with  such a code there is no way that *d* single-bit errors can change a valid code into another valid codeword).
>
>To correct *d* errors: 
>
> - you need *2d*+1 Hamming distance code. (Because that way the legal codewords are so far apart that even with *d* changes (A->A’), the original codeword *A* is still closer to *A’* than any other codeword *B*, so it can be uniquely determined.) 
>
>>[!note] 练习
>>
>>Ex2: consider a coding scheme: • 00 => 00000 00000 • 01 => 00000 11111 • 10 => 11111 00000 • 11 => 11111 11111 • Its Hamming distance is ?

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

只适用于time slot

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
>- **10 Base-T**  10 Mbps 双绞线
>- **1000Base-T** 1000 Mbps 双绞线
>- **100Base-FX**  光纤
>- **10Base5** 同轴电缆 最大传输距离 500m
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
	- 等待随机一段时间后重发，那么这个时间长度如何确定?
		![image-20241022114144279](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202410221141384.png)

![image-20241022113323331](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202410221133436.png)

![image-20241022113347786](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202410221133939.png)

- 使用ipconfig /all命令查看MAC地址
- 前导码
	- 7 byte 同步码
	- 1 byte **帧开始定界符**  只有开始，没有结束定界符 <= 曼彻斯特编码，电平容易区分

- **源地址后面的两个字节**，Ethernet V2将其视为上一层的协议类型，IEEE802.3将其视为数据长度
  - 大的表示长度
  - 小的表示类型
- **数据字段**
  - 46 ~ 1500字节
  - 最小帧长 = 46+18 = 64B
  - 最大帧长 = 1500+18 = 1518B （MTU：1500B）
  - 数据字段不足46字节，需要填充整数字节（Padding）至46字节，以保证以太网MAC帧不小于64字节。
  - 以太网规定最短有效帧长为 64 字节，凡长度小于 64 字节的帧都是由于冲突而异常中止的无效帧。
- 校验和
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

#### **基于Mac地址的学习和转发**

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
| **数据接收方式**    | 接收完整帧                           | 读取到目标MAC地址后立即转发  | 接收前 64 字节后再转发                |
| **错误检查**        | 完整检查帧校验序列（FCS）             | 不进行错误检查               | 检查前 64 字节                       |
| **延迟**            | 较高（需等待完整帧）                   | 较低（目标MAC地址解析后立即转发） | 中等（接收 64 字节后转发）             |
| **可靠性**          | 高（能过滤错误数据帧）                 | 低（可能传播错误数据帧）         | 中等（过滤大部分碰撞和错误帧）         |
| **适用场景**        | 企业级网络、数据中心                  | 高性能计算、金融交易、实时通信  | 一般网络环境，有中等时延和可靠性要求     |
| **网络带宽效率**    | 较低（过滤错误帧，消耗带宽）           | 较高（快速转发，无错误检查）     | 适中（减少小部分无效流量）              |
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

- ID最小的交换机（网桥）成为生成树的根
- 根桥的所有端口都处在转发状态

(2) 为每个非根桥选出一个根端口（Root Port）。

- 每个非根桥，通过比较其每个端口到根桥的根路径开销，选出根端口
- 具有最小根路径开销的端口被选作根端口
	- 根路径开销相同，则端口ID最小的端口被选作根端口
- 非根桥只能有一个根端口，根端口处于转发状态

![image-20241024121200596](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202410241212773.png)

(3) 为每个网段确定一个指定端口（Designated Port）。

- 对于每一个网段， 在所有连接到它的交换机（网桥）端口中进行选择
	- 一个具有最小根路径开销的端口，作为该网段的指定端口
- 指定端口处于转发状态，负责该网段的数据转发

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

> [!note] 范围问题
>
> • 传输范围(TX-Range)：成功接收帧的通信范围，取决于发送功率和无线电波传输特性
>
> • 物理层侦听范围（PCS-Range ）：检测到该传输的范围，取决于接收器的灵敏度和无
>
> 线电波传输特性
>
> • 干扰范围（IF-Range ）：在此范围内的节点如果发送不相关的帧，将干扰接收端的接
>
> 收并导致丢帧
>
> ![image-20241027145806406](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202410271458503.png)
>
> 

#### 组网模式

![image-20241027145221051](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202410271452277.png)

#### 体系结构

#### IEEE 802.11

**隐藏终端 | 暴露终端 问题**

![image-20241027145651784](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202410271456905.png)

#### CSMA/CA

不同帧间隙控制优先级

- SIFS（Short IFS）：最高优先级，用于Ack, CTS, 轮询响应等
- PIFS（PCF IFS）：中等优先级（SIFS+1槽口时间），轮询服务
- DIFS（DCF IFS）：最低优先级（ SIFS+2槽口时间），异步数据服务

### WAN 广域网 和 



## Network

> [!note]
>
> - 点到点通信：由物理层、数据链路层和网络层组成的通信子网
> - 端到端通信：传输层
>
> | **特性**     | **端到端（End-to-End）**                  | **点到点（Point-to-Point）**                                 |
> | ------------ | ----------------------------------------- | ------------------------------------------------------------ |
> | **连接结构** | 源和目标之间可能有多个中间路由            | 只有两个端点直接相连                                         |
> | **协议层**   | 传输层和应用层                            | 物理层、链路层、网络层                                       |
> | **应用场景** | 互联网中的远程通信，如浏览网页、流媒体等  | 局域网中或物理上直接连接的设备之间的通信                     |
> | **传输控制** | 复杂可靠性控制机制，如 TCP 提供的可靠传输 | 直接传输，中间不含有中间设备（两个设备直接通信）通常不涉及复杂的可靠性控制 |

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

> 有些时候和转发表不加以区分
>



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

- Fragment Offset 指明分片在原始数据包中的位置，以 8 字节为单位，帮助接收方重新组合分片。
- Protocol ID：说明 data 是哪种类型，将 data 交给相应的 code 进行处理。（  == 6 ）
- TTL

- Option:可选择

> [!tip]
>
> 1. 不同的单位
>   - Header Length 4B
>   - Total Length B
>   - Fragment Offset 8B 
> 2. IP首部字节以0x45开头 - > IPv4, 没有Option选项
> 2. IP Header 为 20 bytes

> [!note] IPV4 地址
>
> 
>
> <img src="https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202411091836867.png" alt="image-20241109183615724" style="zoom:50%;" />
>
> - A
> - B
> - C
> - D 常用于组播 multicasting
>
> ![image-20241109170849547](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202411091708743.png)
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
> > **步骤：**
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

> [!note] Ping
>
> - Ping 命令工作在应用层
> - 使用ICMP回送请求和回送回答报文
>
> ![image-20241109181715786](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202411091817956.png)

> [!note]Traceroute
>
> - 工作在应用层

### 路由算法

这里讨论动态路由算法

#### Vector Distance

> 最常用的是RIP，使用跳数估计距离

利用 bellman-ford 算法，计算单源最短路径

![image-20241109185157264](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202411091851425.png)

#### 链路 link state

使用Dijkstra算法

> 将邻居状态发送给所有nodes

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
- 使用层次结构的区域划分，上层区域称之为主干区域，其他区域都必须和主干区域相连
	- 区域边界路由器 (Area Bounder Router，ABR)
	- 内部路由器 IR
	- 自治系统边界路由器 ASBR

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



## 总结

### 设备

- 如果一个存储转发设备实现了某个层次的功能，那么他可以互联两个在该层次上使用不同协议的网络/网段
- 冲突域：能产生介质冲突的
- 广播域：能收到同一广播的

==第一层==

- 不能划分冲突域
- 不能隔离广播域

**集线器**

**中继器**

- 不能互联两个物理层不同的网段

---

==第二层==

- 划分冲突域
- 不能隔离广播域

**网桥**

- 可以互联两个物理层和数据链路层不同的网段

**交换机**

- 

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

## 题目

> [!note]
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

> [!faq]
>
> ![image-20241111231723602](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202411112317735.png)

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

> [!faq]
>
> 在互联网数据报中，私有地址不会出现在公共网络中，RFC 1918 指定了以下三个私有 IP 地址范围：
>
> 1. **10.0.0.0 - 10.255.255.255**（10.0.0.0/8）
> 2. **172.16.0.0 - 172.31.255.255**（172.16.0.0/12）
> 3. **192.168.0.0 - 192.168.255.255**（192.168.0.0/16）
>
> 根据这些范围，我们可以分析给出的地址：
>
> - **10.3.18.82**：属于 10.0.0.0/8 范围，是私有地址。
> - **192.168.8.3**：属于 192.168.0.0/16 范围，是私有地址。
> - **10.214.0.1**：属于 10.0.0.0/8 范围，是私有地址。
> - **172.33.8.8**：不在 172.16.0.0 - 172.31.255.255 的范围内，因此不是私有地址。
>
> **结论**：**172.33.8.8** 不是私有地址，它可能出现在互联网数据报中。

## 小测

![image-20241104234453384](../../../../../../AppData/Roaming/Typora/typora-user-images/image-20241104234453384.png)

