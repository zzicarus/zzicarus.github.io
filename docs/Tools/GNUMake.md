---
tags:
  - tools/GNUMake
---

# GNU Make

> **资料:**

> [makefile 介绍 — 跟我一起写 Makefile 1.0 文档](https://seisman.github.io/how-to-write-makefile/introduction.html)
> [上面文档的重制版本](https://write-makefile-with-me.elabtalk.com/articles)

> **视频:**

> 一个较简单的入门 [https://www.youtube.com/watch?v=E1_uuFWibuM&t=1152s](https://www.youtube.com/watch?v=E1_uuFWibuM&t=1152s)

>[!tip] Tips
>- cc 是 C 编译器的命令。在一般的系统上（Unix/Linux），通常是一个指向实际 C 编译器（gcc）的符号链接或别名。一般可以直接把它定义为一个变量，更方便书写
>- `make -j` 可以并行编译 `make -j($nproc)` 使用当前所有核
>- 在某些命令前面可以加 `-` 表示不理会无法正确执行的步骤。例如，`-include <filename>` 就会自动忽视无法找到路径的 `makefile `

```c
## 使用过程
// 指定文件
gcc your_source_file.c -o ../your_executable
// 链接c++标准库
gcc source/pdShow.cpp pd.cpp -o source/pdShow -lstdc++
```
## 基本介绍

```makefile
target ... : prerequisites ...
    recipe
    ...
    ...
// 定义依赖关系
```

**target**
可以是一个 object file（目标文件），也可以是一个可执行文件，还可以是一个标签（label）。
**prerequisites**
生成该 target 所依赖的文件和/或 target。
**recipe**
该 target 要执行的命令（任意的 shell 命令）。
- 第一个目标会作为默认目标
### 变量

- makefile 中的变量相当于 C 中的宏定义

`def` : `objects = main.o`
`usage` : `edit : $(objects)`

### Makefile 如何工作
1. make 会在当前目录下找名字叫“Makefile”或“makefile”的文件。
2. 如果找到，它会找文件中的第一个目标文件（target），在上面的例子中，他会找到“edit”这个文件，并**把这个文件作为最终的目标文件**。
3. 如果 edit 文件不存在，或是 edit 所依赖的后面的 .o 文件的文件修改时间要比 edit 这个文件新，那么，他就会执行后面所定义的命令来生成 edit 这个文件。
4. 如果 edit 所依赖的 .o 文件也不存在，那么 make 会在当前文件中找目标为 .o 文件的依赖性，如果找到则再根据那一个规则生成 .o 文件。（这有点像一个堆栈的过程）
5. 当然，你的 C 文件和头文件是存在的啦，于是 make 会生成 .o 文件，然后再用 .o 文件生成 make 的终极任务，也就是可执行文件 edit 了。

## 书写规则

- 命令一定要以`tab`开头
>[!note] 
>现在也可以使用其他方法来避免使用空格和 Tab 之间存在错误。
### 通配符

`*`
_.o _.c
`?`
`~`
在文件名中有用途 。 比如，`~/test` 表示当前用户的 $HOME 目录下的 test 目录。

### 文件搜寻

`VPATH 变量`
`VPATH = src:../headers`
此处，用 : 分隔不同路径
`vpath 关键字`
`**vpath <pattern> <directories>**`
为符合模式<pattern>的文件指定搜索目录<directories>。
`**vpath <pattern>**`
清除符合模式<pattern>的文件的搜索目录。
`**vpath**`
清除所有已被设置好了的文件搜索目录。

### 伪目标

`.PHONY : clean`
声明这个目标是伪目标，避免与文件名重复

```makefile
.PHONY : clean
clean :
    rm *.o temp
```

**利用伪目标实现一个 makefile 编译多个文件，生成多个 exe**

```makefile
all : prog1 prog2 prog3
# 此处的依赖也是目标
.PHONY : all

prog1 : prog1.o utils.o
    cc -o prog1 prog1.o utils.o

prog2 : prog2.o
    cc -o prog2 prog2.o

prog3 : prog3.o sort.o utils.o
    cc -o prog3 prog3.o sort.o utils.o
```

**伪目标作为依赖**

```makefile
.PHONY : cleanall cleanobj cleandiff

cleanall : cleanobj cleandiff
    rm program

cleanobj :
    rm *.o

cleandiff :
    rm *.diff
```

### 多目标

- 使用一个自动化变量 `$@` ，这个变量表示着目前规则中所有的目标的集合

```makefile
bigoutput littleoutput : text.g
    generate text.g -$(subst output,,$@) > $@

#上述规则等价于：

bigoutput : text.g
    generate text.g -big > bigoutput
littleoutput : text.g
    generate text.g -little > littleoutput
```

### 静态模式

更容易定义多目标的规则

```makefile
<targets ...> : <target-pattern> : <prereq-patterns ...>
    <commands>
    ...
# Example
objects = foo.o bar.o

all: $(objects)
# $< 表示第一个依赖文件
# $@ 表示目标集（也就是“foo.o bar.o”）
$(objects): %.o: %.c
    $(CC) -c $(CFLAGS) $< -o $@
```

- `targets`

定义了一系列的目标文件，可以有通配符。是目标的一个集合。

- `target-pattern`

指明了 targets 的模式，也就是的目标集模式。

- `prereq-patterns`

是目标的依赖模式，它对 target-pattern 形成的模式再进行一次依赖目标的定义。

### \* 自动

GNU 组织建议把编译器为每一个源文件的自动生成的依赖关系放到一个文件中，为每一个 `name.c` 的文件都生成一个 `name.d` 的 Makefile 文件，` .d` 文件中就存放对应 `.c` 文件的依赖关系。
通过`gcc`命令自动生成依赖文件

```verilog
>>> gcc -MM main.c
main.o: main.c variable.h
```

在编译器生成的依赖关系中加入`.d`文件的依赖

```verilog
%.d: %.c
    @set -e; rm -f $@; \
    $(CC) -M $(CPPFLAGS) $< > $@.$$$$; \
    sed 's,\($*\)\.o[ :]*,\1.o $@ : ,g' < $@.$$$$ > $@; \
    rm -f $@.$$$$
```

## 书写命令

### 命令显示

- 通常，make 会**把其要执行的命令行在命令执行前输出到屏幕上**。当我们用 @ 字符在命令行前，那么，这个命令将不被 make 显示出来，最具代表性的例子是，我们用这个功能来向屏幕显示一些信息。

```makefile
@echo 正在编译
>>>正在编译
echo 正在编译
>>>echo 正在编译
>>>正在编译
```

- make 参数

`-n` 或 `--just-print` ，那么其只是显示命令，但不会执行命令，这个功能很有利于我们调试我们的 Makefile，看看我们书写的命令是执行起来是什么样子的或是什么顺序的。
make 参数 `-s` 或 `--silent `或 `--quiet` 则是全面禁止命令的显示。

### 命令执行

`exec:     cd /home/hchen; pwd`
不能写在两行上
使得`pwd`命令在`cd`命令基础上进行

### 嵌套执行

- 优点：模块化
-

## 示例

```makefile
objects = main.o kbd.o command.o display.o \
    insert.o search.o files.o utils.o

edit : $(objects)
    cc -o edit $(objects)

main.o : defs.h
kbd.o : defs.h command.h
command.o : defs.h command.h
display.o : defs.h buffer.h
insert.o : defs.h buffer.h
search.o : defs.h buffer.h
files.o : defs.h buffer.h command.h
utils.o : defs.h

# 表示 clean 是个伪目标文件
.PHONY : clean
clean :
    rm edit $(objects)
```
