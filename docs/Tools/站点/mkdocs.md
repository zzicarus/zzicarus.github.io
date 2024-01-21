# 博客搭建
!!! abstract

    记录搭建 MkDocs 的过程

    参考文档：
    
    - [Material for mkdocs](https://squidfunk.github.io/mkdocs-material/)
    
    - [知乎](https://zhuanlan.zhihu.com/p/630165427)
!!! Task

    - [x] 初步搭建平台
    - [ ] 搭建笔记框架
    - [ ] 上传笔记
    - [ ] 对页面美化，风格化
        - [ ] 页面美化
        - [ ] 字数统计
!!! question
    1. 多个H1的情况，渲染会出错：主要是右侧导航栏的渲染

-------

## Test For it

数学公式
$N==S_2$

**Mention**
`Code Block`

```C linenums="1" title="Test"  
// From here
int main()
{
  return 0;
}
```

## 预下载

为了成功搭建，你需要如下预备：

- python 环境，并且安装好了 pip
- 了解基本的 git 语法（online 部署）
- 了解基本的 md 语法

## Material

> 由于`MkDocs`的原版主题确实不太好看，所以这里使用了`Material For MkDocs`进行优化

```shell  

mkdocs new     // 新建一个MkDocs

mkdocs serve   // 建立一个预览

mkdocs build   // 建立一个静态网页

```

## 额外功能

### box
!!! note "From"
    这一部分是从[xyjj的Page](https://xuan-insr.github.io/%E6%9D%82%E9%A1%B9/%E5%8D%9A%E5%AE%A2%E6%90%AD%E5%BB%BA%E8%AE%B0%E5%BD%95/#status-%E5%B0%8F%E6%96%B9%E5%9D%97)看到的

<span class="box box-blue">blue</span>
<span class="box box-green">green</span>
<span class="box box-red">red</span>
<span class="box box-yellow">yellow</span>
<span class="box box-gray">gray</span>

## Github Page 的部署

![image-20240113210407673](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202401132104761.png)

- 自动部署需要在`.github\workflows`中加入`ci.yml`文件，内容如下：

``` yml linenums="1"
name: ci
on:
  push:
    branches:
      - master
      - main
permissions:
  contents: write
jobs:
  deploy:
    runs-on: ubuntu-latest
    steps:
      - uses: actions/checkout@v4
      - name: Configure Git Credentials
        run: |
          git config user.name github-actions[bot]
          git config user.email 41898282+github-actions[bot]@users.noreply.github.com
      - uses: actions/setup-python@v4
        with:
          python-version: 3.x
      - run: echo "cache_id=$(date --utc '+%V')" >> $GITHUB_ENV
      - uses: actions/cache@v3
        with:
          key: mkdocs-material-${{ env.cache_id }}
          path: .cache
          restore-keys: |
            mkdocs-material-
      - run: pip install mkdocs-material
      - run: mkdocs gh-deploy --force
```

## 一些用法 | 测试格式

### md 格式的调整

代码见CSS部分

1. 有序列表
2. 有序列表
-------
- 无序列表


*斜体*

**加粗**

> 引用

[链接]:(http://127.0.0.1:8000/#github-page)

:bread:


--------

### annotation


``` md
!!! 或者 ???

???+ 折叠，默认展开状态
```


!!! note "Note"

    Lorem ipsum dolor sit amet, consectetur adipiscing elit. Nulla et euismod
    nulla. Curabitur feugiat, tortor non consequat finibus, justo purus auctor
    massa, nec semper lorem quam in massa.

!!! info "info"
    info 

!!! abstract "Abstt"
    abd

!!! tip "tip" 
    octicons/squirrel-16

??? success "success"
    success

??? quote "quote"
    quote

??? question "question"
    question


??? warning  inline end "warning"
    warning

???+ inline bug "bug"
    bug

!!! example inline end "example"
    example

!!! failure "failure"
    failure
