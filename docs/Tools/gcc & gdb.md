---
tags:
  - doing
  - Tools/GCC
statistics: true
title: NOTE
author: zzicarus
date: <% tp.date.now("YYYY-MM-DD HH:mm:ss") %>
update: <% tp.date.now("YYYY-MM-DD HH:mm:ss") %>
---

# GCC
默認情況下，進行 gcc 编译生成的是 release 版本的可执行文件，如果要进行 debug 要去实现 debug 版本
## 基本编译
- `gcc -o <exename> file.c` 对单文件生成可执行文件
- `gcc -c <object name> file.c` 只进行编译而不进行链接，/<object name/>为可选值
- `gcc -S test` 生成汇编代码
- `gcc -O2 -o output file.c` 编译优化
- `gcc -g -o output file.c` 生成调试信息
- `gcc -std=c11 -o ...` 指定版本
- `gcc -Wall -o output file.c` 开启编译器警告
- `gcc -D MACRO_NAME=value -o output file.c` 定义宏
- `gcc -I/path/to/include -o output file.c` 指定寻找目录（在 makefile 中可用作查询路径）
  