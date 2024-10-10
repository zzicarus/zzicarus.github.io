---
tags:
  - tools/shell
---

# Shell

**环境变量**

`echo $path`

```
$ which echo
$ pwd
$ cd .  current
$ cd .. parent
```

`ls -l`

**``drwxr-xr-x``** 是文件或目录的权限表示方式中的一部分。在这个例子中，**``drwxr-xr-x``** 表示一个目录的权限。

- 第一个字符 **``d``** 表示这是一个目录。如果是文件，该字符会是 **``-``**。
- 接下来的三个字符 **``rwx``** 表示所有者（owner）对该文件或目录的权限。在这个例子中，**``rwx``** 表示所有者具有读（read）、写（write）和执行（execute）的权限。
- 接下来的三个字符 **``r-x``** 表示组（group）对该文件或目录的权限。在这个例子中，**``r-x``** 表示组具有读和执行的权限，但没有写的权限。
- 最后的三个字符 **``r-x``** 表示其他用户对该文件或目录的权限。在这个例子中，**``r-x``** 表示其他用户具有读和执行的权限，但没有写的权限。

因此，**``drwxr-xr-x``** 表示这个目录的所有者具有读、写和执行的权限，组和其他用户具有读和执行的权限，但没有写的权限。

`rmdir` `mkdir` `man`

`ctrl + L`清除

`cat`

## streams

重定向

```shell
missing:~$ echo hello > hello.txt
missing:~$ cat hello.txt
hello
missing:~$ cat < hello.txt
hello
missing:~$ cat < hello.txt > hello2.txt
missing:~$ cat hello2.txt
hello
```

追加

\>\>

pipe

|

sudo    :   super user

## 关于Unix中的root用户

```
我们可以使用 ls -l 来查看详细信息
使用 chmod 来修改
```

在UNIX或类UNIX系统中，每个文件或目录都有一个所有者（owner），一个组（group）和其他用户（others）。

- 所有者（owner）是创建文件或目录的用户。所有者对文件或目录具有最高的权限，可以读取、写入和执行。
- 组（group）是一组用户，可以共享对文件或目录的访问权限。组成员具有与组相关联的权限，可以是读取、写入和执行。
- 其他用户（others）是除了所有者和组之外的所有用户。其他用户具有独立于所有者和组的权限，可以是读取、写入和执行。

使用**``chmod``**命令时，可以使用以下缩写来指定不同用户类别的权限：

- **``u``** 代表所有者（user）。
- **``g``** 代表组（group）。
- **``o``** 代表其他用户（others）。

例如，**``chmod u+rwx,g+rw,o+x file.txt``** 将为文件 **``file.txt``** 分配如下权限：

- 所有者具有读取、写入和执行权限。
- 组具有读取和写入权限。
- 其他用户具有执行权限。

这样的权限设置将确保不同用户类别具有适当的权限，以控制对文件或目录的访问。

## Bash 编程

- shell中的空格十分重要`foo=bar` `foo = bar`前者正常工作，后者找不到foo命令
- 编写shell函数时
    - `$0` - 脚本名
    - `$1` 到 `$9` - 脚本的参数。 `$1` 是第一个参数，依此类推。
    - `$@` - 所有参数
    - `$#` - 参数个数
    - `$?` - 前一个命令的返回值
    - `$$` - 当前脚本的进程识别码
    - `!!` - 完整的上一条命令，包括参数。常见应用：当你因为权限不足执行命令失败时，可以使用 `sudo !!`再尝试一次。
    - `$_` - 上一条命令的最后一个参数。如果你正在使用的是交互式 shell，你可以通过按下 `Esc` 之后键入 . 来获取这个值。

**进程替换**  `<(CMD) `  将会执行CMD并将结果输出到一个临时文件中，并将`<(CMD)`替换为临时文件名。注意，返回值通过文件而不是STDOUT

```shell
#!/bin/bash

echo "Starting program at $(date)" # date会被替换成日期和时间

echo "Running program $0 with $# arguments with pid $$"

for file in "$@"; do
    grep foobar "$file" > /dev/null 2> /dev/null
    # 如果模式没有找到，则grep退出状态为 1
    # 我们将标准输出流和标准错误流重定向到Null，因为我们并不关心这些信息
    if [[ ""$?" -ne 0 ]]; then
        echo "File $file does not have any foobar, adding one"
        echo "# foobar" >> "$file"
    fi
done
```

There\`s a `test` to check

**通配符**

```shell
ls *.py
ls project?
{}
```

### prompt

<span class="box box-blue">xargs</span>

### Instance

```shell
#!/bin/bash
# Test run in Git bash

date1="2021 02 03"
content="today\nI get a little bit happy\n"

echo "hello"
echo "--- Running to Get the Exe ---"
# gcc source/pdRemove.cpp source/pd.cpp -o pdRemove -lstdc++
# gcc source/pdAdd.cpp source/pd.cpp -o pdAdd -lstdc++
# gcc source/pdList.cpp source/pd.cpp -o pdList -lstdc++
# gcc source/pdShow.cpp source/pd.cpp -o pdShow -lstdc++
echo "--- Complete ---"

# 将脚本中的内容作为参数传递给pdAdd命令
echo -e "$date1\n$content" | xargs ./pdAdd
```

在这个示例中，我们使用echo -e来打印字符串，并使用管道符（|）将其重定向到xargs命令的stdin。然后，xargs命令将这些输入数据作为参数传递给pdAdd命令