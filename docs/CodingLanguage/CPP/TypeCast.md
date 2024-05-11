# Type Cast

!!! info
    - **隐式类型转换**
    - **显式类型转换**
    - **整型提升**
    - **无符号类型转换**
    ![Alt text](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202404261107274.png)

## 强制类型转换

`cast-name<type>(expression)`

### static_cast

> 只要不包含底层的const就可以使用

- `static_cast` 在相关的类型之间转换，比如
    - 一个父类和派生类之间的转换
    - `void * `到其他指针类型之间的转换
    - `int` `float`等类型之间的转换
- 它的安全性比较高，

```CPP
double m;
void *p = &m;
double *dp = static_cast<double *>(p);
```

### const_cast

> 只能改变底层const
>



### reinterpret_cast

> 为转换对象的位模式提供更低层次的重新解释
>
