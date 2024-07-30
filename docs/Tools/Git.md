# Git

!!! info "Docs"
    - [Command 汇总](https://www.ruanyifeng.com/blog/2015/12/git-cheat-sheet.html)
    - [Learn Branch ：一个分支的练习\学习网站](https://learngitbranching.js.org/?locale=zh_CN)
    - 推荐阅读：ProGit
## Git 配置

- 查看配置文件 ` git config --list --show-origin` 
- 查看配置信息 `git config --list`
- 配置用户信息
```c++
$ git config --global user.name "ZZIcarus"
$ git config --global user.email 2450606426@qq.com
```

## gitignore的写法
通配符
```text
# 忽略所有的 .a 文件
*.a

# 但跟踪所有的 lib.a，即便你在前面忽略了 .a 文件
!lib.a

# 只忽略当前目录下的 TODO 文件，而不忽略 subdir/TODO
/TODO

# 忽略任何目录下名为 build 的文件夹
build/

# 忽略 doc/notes.txt，但不忽略 doc/server/arch.txt
doc/*.txt

# 忽略 doc/ 目录及其所有子目录下的 .pdf 文件
doc/**/*.pdf
```

## Usage

!!! note ""
    英文状态下按`q`可以退出`git log`等输出信息的命令

**git log**

![alt text](images/custom-image-2.png)

```
git init 

git add

git commit -m "message"

git status

git diff

git push origin main

git pull origin main

```

### 版本回退

HEAD表示最新版本，HEAD^,HEAD^^,HEAD~100表示前一个、前两个、前100个版本

`d16f1504a39840ea6962aa3e464a51bd8f72f298`是版本号，可以在`git log`命令中查看

如果在一次回退之后想要回到“未来”，使用`git relog`, 可以查看之前的命令

```shell
git reset --hard HEAD
git reset --hard d16f1504a39840ea6962aa3e464a51bd8f72f298
```

### 远程连接

!!! tip "SSH"
    

**关联远程库**
- origin 是当前的仓库名
`git remote add origin ...`

### 分支管理

!!! info "分离Head"
    分离的 HEAD 就是让其指向了某个具体的提交记录而不是分支名。

`git checkout HEAD`
![alt text](images/custom-image-1.png)
```shell
git checkout -b dev  // 创建并跳转
# 创建 移动分支
git branch dev
git checkout dev
# 移动指定分支到指定位置
git branch -f main HEAD~3

git branch          // 查看当前分支

# 分支合并
git checkout main
git merge dev

# 删除分支
git branch -d dev

```

#### 分支合并

两种方式`git merge` `git rebase`

### Tag

## Errors

### 冲突
[stockOverflow](https://stackoverflow.com/questions/20467179/git-push-rejected-non-fast-forward/20467414#20467414)

![alt text](images/custom-image.png)

```shell
 ! [rejected]        main -> main (non-fast-forward)
error: failed to push some refs to 'github.com:zzicarus/zzicarus.github.io.git'   
hint: Updates were rejected because the tip of your current branch is behind      
hint: its remote counterpart. Integrate the remote changes (e.g.
hint: 'git pull ...') before pushing again.
hint: See the 'Note about fast-forwards' in 'git push --help' for details.  
```

### 分支

> 切换到新建的分支后，进行push报错

需要将本地新建的分支与远程的分支建立连接

方法1：`git push --set-upstream origin dev` 这里的dev是新的分支

方法2： 

```shell
fatal: The current branch dev has no upstream branch.
To push the current branch and set the remote as upstream, use

    git push --set-upstream origin dev

To have this happen automatically for branches without a tracking
upstream, see 'push.autoSetupRemote' in 'git help config'.
```

### 代理问题
!!! info ""
    **问题**
    ```shell
    Connection reset by 20.205.243.160 port 443
    fatal: Could not read from remote repository.

    Please make sure you have the correct access rights
    and the repository exists.
    ```
    由于设置的代理与当前的代理不同。一般是翻墙之后，网络代理发生变化。

**Solution**
```shell
git config --global http.proxy http://127.0.0.1:7890 
git config --global https.proxy http://127.0.0.1:7890

# 取消代理
git config --global --unset http.proxy
git config --global --unset https.proxy
```

??? note "关于代理"
    