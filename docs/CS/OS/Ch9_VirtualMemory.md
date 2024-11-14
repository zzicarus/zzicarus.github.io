# Virtual Memory

>virtual memory isn’t a physical object, but refers to *the collection of abstractions and mechanisms the kernel* provides to **manage physical memory and virtual addresses.**
>
>是一种机制

- Only part of the program needs to be in memory for execution
- Logical address space can therefore be much larger than physical address space
- Allows address spaces to be **shared by several processes**  Page共享
- Allows for more efficient **process creation**  只加载要用的部分

## Demand Paging

**Lazy swapper** – never swaps a page into memory unless page will be needed

- Swapper that deals with pages is a pager

>[!note]Transfer of a Paged Memory to Contiguous Disk Space

### Page Fault

- Operating system looks at another table (kept with PCB) to decide
	- Invalid reference  => abort
	- Just not in memory
- Get empty frame
- Swap page into frame
- Reset tables
- Set validation bit = v
- Restart the instruction that caused the page fault

>[!note]EAT 计算
>
> $$
> EAT = (1 – p) * \text{memory access } +\\
> 			\text{ p (page fault overhead
> 			           + swap page out
> 			           + swap page in
> 			           + restart overhead
>                            )}
> $$
>
>最后没有计算重新对memory access的time：这里在 Pfault 结束后，将会重启memory access指令，故下一次重启的访存就不算在本次的EAT里面了。

> 

## process creation

### Copy on write

- 发生之后两边的page table都更新

## Page Replacement

### FIFO

### Optimal

### LRU

- Counter
	- 实际上里面用的不是counter而是一个time值
- Stack

### Counter Based

![image-20241107223737126](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202411072237184.png)

### Clock

<img src="https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202411072235607.png" alt="image-20241107223533435" style="zoom:33%;" />

## Allocation Of Frames

>[!note]
>
>the minimum number of frames per process is defined by the architecture, the maximum number is defined by the amount of available physical memory

- fixed allocation
	- 比例分配
		

- priority allocation

是否可抢占其他进程的frame

- Global replacement
	- 甚至可能会使用到 kernel page  => 造成 Page fault
	
	- 一种可能的实现是建立上下的最大最小阈值

		>[!note] - 实现
		>
		> **空闲内存阈值**：系统设定一个最小阈值，当空闲内存低于此阈值时，开始触发页面回收操作；当空闲内存回升到最大阈值时，回收操作暂停，直到空闲内存再次降到最小阈值以下。
		>
		> **回收操作（Reaper）**：当空闲内存低于最小阈值时，系统会启动一个内核例程（通常叫做"回收者"或**reaper**），该例程会从系统中回收页面，通常是通过应用某种页面置换算法（如LRU近似算法）来释放内存。
		>
		> **回收过程**：假设空闲内存的量在某个时间点（例如点a）低于最小阈值，回收过程开始。回收者会从进程中回收页面，直到空闲内存达到最大阈值（例如点b）。当内存需求增加，空闲内存再次低于最小阈值（例如点c），回收操作将继续，直到内存回升到最大阈值（例如点d）。这一过程会持续进行，直到系统运行结束。
		>
		> **回收策略的调整**：当回收操作无法保持空闲内存低于最小阈值时，回收者可能会变得更加激进。例如，可以暂停二次机会算法（Second-Chance）并使用纯FIFO（先进先出）算法来更快地回收内存。另一个极端的例子是**Linux中的OOM Killer**（内存不足杀手）：当内存不足时，OOM Killer会选择终止一个进程，从而释放内存。Linux通过每个进程的**OOM得分**来决定哪个进程最有可能被终止，得分越高的进程被终止的可能性越大。OOM得分与进程使用的内存比例有关，使用内存比例越高，得分越高。
		>
		> **阈值调整**：系统可以设置默认的最小和最大阈值，或允许系统管理员根据物理内存的大小来调整这些阈值。通过合理设置这些阈值，可以优化内存管理，避免内存过度分配或浪费。

- Local replacement

## Thrashing

>a process is busy swapping pages in and out  更多时间用于交换页面上

**引发Thrashing的场景**

- **增加Multiprogram的Level**：操作系统监视CPU的使用情况。如果CPU使用率较低，它会通过增加更多进程来提高系统的吞吐量
- **全局页面替换算法**：操作系统使用全局页面替换算法，这意味着可以替换任意进程的页面，而不考虑页面属于哪个进程。随着新进程的引入，它们可能会占用其他正在运行的进程的内存帧（frames）。

**后果**

- low CPU utilization
- Queuing at paging device, the ready queue becomes empty
- operating system thinks that it needs to increase the degree of multiprogramming
	- another process added to the system

接下来介绍缓解这种Thrashing的方法， limit the effects of thrashing by using a **local replacement algo**

**rithm** (or **priority replacement algorithm**).

### Locality model

>To prevent thrashing, we must provide a process with as many frames as it needs. **But how do we know how many frames it “needs”?** One strategy starts by looking at how many frames a process is actually using. This approach defines the **locality model** of process execution.

### Working-Set Model

基于局部性假设，近似地描述程序在一段时间内活跃使用的page

![image-20241107231945798](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202411072319870.png)

- 操作系统可以依据这个工作集大小（WSS）来分配相应的页面帧数
- 总页面需求 D 超过了系统的内存总量 mmm，操作系统的策略是**挂起一个进程**，将其页面内容换出，并重新分配其内存帧给其他进程。
- 随时间监控每个进程的工作集变化。当进程的活动区域发生变化（即工作集变化）时，系统可以相应地增加或减少为该进程分配的页面帧

### PFF

限制Page Fault rate

![image-20241107233034722](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202411072330790.png)

## MMF

**Memory-Mapped Files** 是一种将文件内容直接映射到进程的内存地址空间的文件I/O方式，使得文件操作可以像操作内存一样简单。这种方法通过将文件的磁盘块映射到内存页中来实现，从而省去了频繁的系统调用如 `read()` 和 `write()`。以下是 Memory-Mapped Files 的详细解释和示例。

### 工作原理

1. **文件映射到内存**：使用 Memory-Mapped Files 时，操作系统将文件的内容映射到一个虚拟内存区域。这个区域与文件的磁盘内容同步，因此对这个区域的读写会直接反映在文件上。
2. **按需分页 (Demand Paging)**：文件内容不是一次性加载到内存中的，而是通过按需分页的方式，即只有在访问文件中的特定页时，操作系统才会将该页加载到物理内存中。
3. **普通内存访问**：一旦文件内容映射到内存，后续对文件的操作就是普通的内存读写，不再需要进行 `read()` 和 `write()` 系统调用。这不仅简化了编程，还提升了性能，因为少了系统调用的开销。
	把读写交给OS，Programer 只需要考虑普通的对内存的访问和操作 
4. **进程间共享**：多个进程可以将同一文件映射到它们各自的地址空间，这样这些进程可以共享文件内容在内存中的映射，实现跨进程的数据共享。

<img src="https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202411072342201.png" alt="image-20241107234257104" style="zoom: 50%;" />
