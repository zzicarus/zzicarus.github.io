# Chapter 6 | ER Model

## How to draw a ER graph

### 基数表示

![image-20240412173452833](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202404121734922.png)

![image-20240412095735553](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202404120958979.png)

![image-20240412095951194](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202404120959390.png)

### Weak Entity

![image-20240412174026801](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202404121740889.png)

## 转化

![](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202404121746484.png)

**多值属性**

![image-20240412174716104](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202404121747161.png)

**多对一**

![image-20240412174951128](C:/Users/orz20/AppData/Roaming/Typora/typora-user-images/image-20240412174951128.png)

- 部分可能会出现null

## 其他特性

### 特化

![image-20240616104757599](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202406161048723.png)

- 重叠特化  Overlapping  一个实体集可能属于多个特化实体集
- 不相交特化  必须属于至多一个特化实体集

### 泛化

![image-20240616104912307](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202406161049389.png)

- **Partial generalization is the default.** 
- 