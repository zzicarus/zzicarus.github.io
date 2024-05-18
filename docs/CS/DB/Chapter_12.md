# Physical Storage

## Overview

![](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202405062252951.png)

![](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202405062248692.png)
- 三级存储 offline storage
    - optical disk 光学存储器  CD
    - tape disk  磁带
      访问必须从头开始，顺序访问


![s](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202405062250332.png)

## Flash Memory | 闪存

**NOR快闪**

- 可以访问单个字

- 速度可以与主存媲美

**NAND快闪 SSD**

- Reading from NAND flash requires **an entire page of data**, which is very commonly 4096 bytes, to be fetched from NAND flash into main memory.

- 更经常用的

**闪存特点**

- 写操作比较复杂，一旦完成写操作，想要复写必须擦除之后再写
- The erase operation must be performed on a group of pages, called an **erase block**
- 容易损坏
  Further, **there is a limit to how many times a flash page can be erased**, typically around 100,000 to 1,000,000 times. Once this limit is reached, **errors in storing bits are likely to occur.**

## Magnetic Disk

<img src="https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202405062255334.png" alt="image-20240506225525215" style="zoom:50%;" />

- 通过机械运动，比较慢

![image-20240506225916221](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202405062259320.png)
- 扇区是最小的读写单元
![image-20240506230134356](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202405062301480.png)

### Performance

![image-20240506230243627](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202405062302736.png)

![image-20240506230303285](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202405062303370.png)

![image-20240506230647171](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202405062306267.png)

- 上面的IOPS支持的操作是Random的R/W

### Optimization

![image-20240506231917955](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202405062319028.png)

![image-20240506231927819](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202405062319883.png)

![image-20240506231845491](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202405062318583.png)