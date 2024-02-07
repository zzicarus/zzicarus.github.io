# 博客搭建

!!! abstract

    记录搭建 MkDocs 的过程

    参考文档：

    - [Material for mkdocs](https://squidfunk.github.io/mkdocs-material/)

    - [知乎](https://zhuanlan.zhihu.com/p/630165427)

!!! Task

    - [x] 初步搭建平台
    - [x] 搭建笔记框架
    - [x] 上传笔记
    - [x] 对页面美化，风格化
        - [x] 页面美化
        - [x] 字数统计
        - [ ] Comment系统

!!! question 

    1. ~~多个 H1 的情况，渲染会出错：主要是右侧导航栏的渲染~~
    

---

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

## Github Page 的部署

![image-20240113210407673](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202401132104761.png)

- 自动部署需要在`.github\workflows`中加入`ci.yml`文件，内容如下：

```yml linenums="1"
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

## 功能

!!! info "介绍"
    
    这里我选了几个自己之后应该常用的，记一下用法

### 选项卡

#### 分组代码块

````
=== "C"

    ``` c
    #include <stdio.h>

    int main(void) {
      printf("Hello world!\n");
      return 0;
    }
    ```

=== "C++"

    ``` c++
    #include <iostream>

    int main(void) {
      std::cout << "Hello world!" << std::endl;
      return 0;
    }
    ```
````
=== "C"

    ``` c
    #include <stdio.h>

    int main(void) {
      printf("Hello world!\n");
      return 0;
    }
    ```

=== "C++"

    ``` c++
    #include <iostream>

    int main(void) {
      std::cout << "Hello world!" << std::endl;
      return 0;
    }
    ```

#### 嵌入格式

!!! example "嵌入"

    === "Unordered List"

        ``` markdown
        * Sed sagittis eleifend rutrum
        * Donec vitae suscipit est
        * Nulla tempor lobortis orci
        ```

    === "Ordered List"

        ``` markdown
        1. Sed sagittis eleifend rutrum
        2. Donec vitae suscipit est
        3. Nulla tempor lobortis orci
        ```


### box

!!! note "From"

    这一部分是从[xyjj 的 Page](https://xuan-insr.github.io/%E6%9D%82%E9%A1%B9/%E5%8D%9A%E5%AE%A2%E6%90%AD%E5%BB%BA%E8%AE%B0%E5%BD%95/#status-%E5%B0%8F%E6%96%B9%E5%9D%97)看到的

```css
<span class="box box-blue">blue</span>
<span class="box box-green">green</span>
<span class="box box-red">red</span>
<span class="box box-yellow">yellow</span>
<span class="box box-gray">gray</span>
```

<span class="box box-blue">blue</span>
<span class="box box-green">green</span>
<span class="box box-red">red</span>
<span class="box box-yellow">yellow</span>
<span class="box box-gray">gray</span>

### 字数统计

直接使用了一位[学长的插件](https://github.com/TonyCrane/mkdocs-statistics-plugin)

### 优化vsc中的工作流程
1. 快捷键  Markdown ShortCuts 插件
2. 自定义Snippet


## 一些用法 | 测试格式

### Code Block

1. 突出显示特定行

  ```py hl_lines="2 3"
  def bubble_sort(items):
      for i in range(len(items)):
          for j in range(len(items) - 1 - i):
              if items[j] > items[j + 1]:
                  items[j], items[j + 1] = items[j + 1], items[j]
  ```

  ````

  ```py hl_lines="2 3"
  def bubble_sort(items):
      for i in range(len(items)):
          for j in range(len(items) - 1 - i):
              if items[j] > items[j + 1]:
                  items[j], items[j + 1] = items[j + 1], items[j]
  ```

  ````

2. 高亮内部代码

````
The `#!python range()` function is used to generate a sequence of numbers.
````

The `#!python range()` function is used to generate a sequence of numbers.

### md 格式的调整

代码见CSS部分

1. 有序列表
2. 有序列表

-------

- 无序列表

*斜体*

**加粗**

> 引用
>
[链接](http://127.0.0.1:8000/#github-page)

------
下面的是一些拓展的，在markdown - extension中可以选择加入（建议读[官方文档](https://squidfunk.github.io/mkdocs-material/setup/extensions/python-markdown-extensions/#arithmatex-docsjavascriptsmathjaxjs)）

```md
:bread:
~~删除~~
==突出显示==
^^插入^^
````

:bread:

~~删除~~

==突出显示==

^^插入^^

---

### annotation

```md
!!! 或者 ???

???+ 折叠，默认展开状态
```

!!! note "Note"

    Lorem ipsum dolor sit amet, consectetur adipiscing elit. Nulla et euismod
    nulla. Curabitur feugiat, tortor non consequat finibus, justo purus auctor
    massa, nec semper lorem quam in massa.

!!! info "info"

    info

!!! abstract "abstract"

    abstract

!!! tip "tip"
    octicons/squirrel-16

??? success "success"
    success

??? quote "quote"

    quote

??? question "question"

    question

??? warning inline end "warning"

    warning

???+ inline bug "bug"

    bug

!!! example inline end "example"

    example

!!! failure "failure"

    failure
