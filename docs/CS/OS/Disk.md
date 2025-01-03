- ==Disk==
  - 调度
    - FCFS
    - SSTF
    - SCAN / LOOK
      - 反弹
    - CSCAN / CLOOK
      - 完全单向，到头之后回到0重新向这个方向扫描
- RAID
  - Strip
  	- Block level
  	- bit level
  - type
  	- RAID 0
  	- RAID 1
  	- RAID 4
  	- RAID 5
  	- RAID 6
  	- 变种 RAID 0 + 1  RAID 1 + 0
  		![image-20241225145108858](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202412251451044.png)
- Stable Storage
  - 日志先行  WAHL
- ==Speed==:smile_cat: tertiary storage
  - bandwidth
  - latency 

![image-20241225151028244](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202412251510637.png)

![image-20241225151626902](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202412251516191.png)

## I/O

- 包含哪些要素
  - 连接线
    ![image-20241227095127378](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202412270951510.png)
    - PCI
  - 
- 如何和外部设备通信？
  - Polling
  	- 由CPU不断轮询
  	- busy-wait In first step
  - Interrupt
  	- 如何把这个信息传给CPU？
  		- maskable
  		- non-maskable
  - DMA 直接内存访问
- Blocking Non-Blocking I/O
  - Non-Blocking
  - 异步
- Spooling
  - 借助可共享的大容量磁盘，将独占型的慢速I/O设备虚拟化位每一个进程一个的共享设备
- Subsystem
  - Scheduling
  - Buffer
  - Cache
  - Protection