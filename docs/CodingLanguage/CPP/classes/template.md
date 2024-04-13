# 模板和泛型编程

!!! info "INFO"
    



## 模板

### 函数模板
```cpp
template <typename T>
T info(T &a, T &b)
{
}
```
#### 模板定义

**非类型参数**
```cpp
template <typename T,unsigned m,unsigned n>
T info(const char (&p1)[m],const char (&p1)[n])
{
}
```
**inline**

`template <> inline `

### 类模板
```cpp
template <typename T>
class S
{
}
```

**显式模板实参**  vector<int>

