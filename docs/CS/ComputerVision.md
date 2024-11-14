- 序贯算法

- 边界跟踪算法
- 形态学

![image-20241105195426453](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202411051954590.png)

- 边缘检测
  - 概念
  - 基于一阶导数
  - 基于二阶导数
  	- 拉普拉斯算子
  	- LoG算子
  - **Canny 边缘检测**
  	- 高斯滤波平滑 去噪声
  	- 一阶偏导有限差分计算梯度幅值、方向
  	- 对梯度幅值进行**NMS 非极大值抑制**
  	- 双阈值算法检测连接边缘
- **Curve**
	使用曲线这种模型来表示轮廓
	- 曲线表示
		- Chain Code
		- 长度-斜率表示
		- 图
		- 斜率密度
		- **\* 分线段拟合 Douglas Peucker**
			- ![image-20241111191543193](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202411111915552.png)
	- 曲线拟合
		- 
	- **Hough 变换**
		- 输入：一般是进行 Canny 边缘检测之后的结果

![image-20241111195148822](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202411111951050.png)

## Image Local Feature

### Edge Detection

### Feature detection

#### Harris Corner Detector

