# CA

## Cache

![image-20241022153457116](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202410221534291.png)

### Miss Penalty Reduction

#### Critical Word First

这是一个优化内存读取性能的技术。当 CPU 从内存中读取一个块（通常是一个缓存行）时，如果发生了缓存未命中（cache miss），而且 CPU 需要的只是这个块中的某个特定字，传统方法会从内存中将整个块依次读取到缓存中，然后再提供给 CPU。

“Critical Word First” 的策略是优先传输 CPU 当前所需要的那个字（critical word），而不是等待整个缓存行被传输完毕。这使得 CPU 可以尽快继续处理，而无需等待整个块加载完毕。这样可以减少缓存未命中带来的等待时间，提高系统的响应速度。

#### Early Restart

**例子**

假设某个缓存行由 16 个字组成（比如从 `0x1000` 到 `0x103F`），CPU 请求的字是 `0x1004`。在“Early Restart”下：

- 当内存控制器从内存开始加载这个缓存行时，一旦 `0x1000` 到 `0x1004` 的部分数据被加载到缓存，内存控制器就立即将这些已加载的数据交给 CPU。

#### Giving Priority to Read Misses over Writes

- If a system has a write buffer, writes can be delayed to come after reads. 

- The system must, however, be careful to check the write buffer to see if the value being read is about to be written. 

在缓存系统中，缓存需要处理读操作和写操作。当发生缓存未命中时，读操作（read miss）意味着 CPU 需要的数据当前不在缓存中，而写操作（write）则是将 CPU 产生的数据写入缓存或内存。在这两者发生冲突时，优先处理哪一种操作会影响系统的性能。

“Giving Priority to Read Misses over Writes” 是一种策略，即当系统检测到读未命中和写操作同时发生时，它会优先处理读未命中。原因是读操作通常对 CPU 的性能有更大影响，因为 CPU 需要读取数据来执行指令。如果读操作被延迟，CPU 就必须等待，而写操作一般可以稍后再执行。

**例子**

假设一个系统正在执行以下操作：

- CPU 请求从内存中读取一个数据，但该数据不在缓存中（读未命中）。
- 同时，缓存中还有一些待写入内存的数据（写操作）。

在这种情况下：

- 系统会优先处理读操作，尽快将读请求的数据从内存加载到缓存中，这样 CPU 就可以继续执行。
- 写操作被延迟，等到读操作完成后再处理。这种做法的目的是减少读操作的延迟，避免 CPU 停滞，提高系统性能。

### Reduce 

1.Reduce the miss penalty 	        	

2. Reduce the miss rate

- Complier Optimization
	- Loop
	- Matrix
	- Loop Fusion
	- Merging Array





### Reduce the miss penalty and miss rate via parallelism

- Nonblocking Caches
	- The cache to continues to supply hits while processing read misses ( **hit under miss , hit under multiple miss** ). 

- Hardware Prefetching of Instructions and data
	- reduces compulsory misses 
	- 

- Compiler-controlled prefetch
  - Binding prefetch
  - Non-Binding prefetch

​			

3. Reduce the time to hit in the cache. 

**Small and Simple Caches**

Direct-mapped is faster than set associative for both reads and writes. 

Fitting the cache on the chip with the CPU is also very important for fast access times. 



**Avoiding Address Translation during Indexing of the Cache**

**pipelined Cache Access**

**Trace Cache**

## Memory

organizing memory to improve bandwidth

- Main memory is usually made from DRAM while caches use SRAM.

### Improving Performance

#### Wider Main Memory

#### simple Interleaved Memory

<img src="https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202410291411064.png" alt="image-20241029141107912" style="zoom:33%;" />

#### Independent Memory Banks

### Memory Tech

- Access time ----- time between when a read is requested and when the desired word arrives
- Cycle time ----- minimum time between requests to memory. One reason that cycle time is greater than access time is that the memory needs the address lines to be stable between accesses.

[内存基础 - HobbitQia的笔记本](https://note.hobbitqia.cc/Logic/logic07/#ram)

如何激活使用激活快捷方式（默认：田+ Shift +@） 屏幕上将显示覆盖区。单击并按住主鼠标按钮，然后拖动以激活捕获。文本将保存到剪贴板。