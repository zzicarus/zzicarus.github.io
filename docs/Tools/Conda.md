# Conda

!!! abstraction "Conda"

	Conda是一个管理Python环境和版本的工具。

- [知乎](https://zhuanlan.zhihu.com/p/44398592)
- [官方](https://conda.io/projects/conda/en/latest/user-guide/getting-started.html)

[CPU 算力](https://developer.nvidia.com/cuda-gpus)

```python
conda create --name <env-name> python=3.6

// 查看环境
conda info --envs
conda info -e

// 回到默认环境
conda deactivate

// 安装软件包
# via environment activation
conda activate myenvironment
conda install matplotlib

# via command line option
conda install --name myenvironment matplotlib
# 查看已经安装的packages
conda list
# 查看某个指定环境的已安装包
conda list -n py35
```

## 配置 Channels

```shell
# 清华源
https://mirrors.tuna.tsinghua.edu.cn/anaconda/pkgs/main/

```

**查看当前channels信息**

```
conda config --show
conda config --get
```

**使用某个channels**

```shell
conda install xxx -c channels
conda create xxx -c channels
```

**添加 channels**

```sh
conda config --add channels
conda config --remove channels
```