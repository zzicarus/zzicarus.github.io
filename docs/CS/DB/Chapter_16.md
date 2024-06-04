# 查询优化

## Intro

<img src="https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202405240932765.png" alt="image-20240524093225598" style="zoom:50%;" />

- An **evaluation plan** defines exactly what algorithm is used for each operation, and how the execution of the operations is coordinated.

## Equivalent

![image-20240524093727214](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202405240937419.png)

![image-20240524094120149](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202405240941413.png)

![image-20240524094237455](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202405240942637.png)

![image-20240524094510255](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202405240945424.png)

![image-20240524094500703](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202405240945894.png)

![image-20240524094539962](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202405240945146.png)

- 上面的式子左右可以相互转换
- 自然连接可交换、结合
- Select往叶子上push

1. $\theta _2上面有索引$

## **Statistics for Cost Estimation**

![image-20240524094735803](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202405240947987.png)

**Size Estimation**

## **Choice of Evaluation Plans**

## **Additional** **Optimization** **Techniques**

