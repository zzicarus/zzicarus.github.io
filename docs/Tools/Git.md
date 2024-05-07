# Git

!!! info "Docs"
    - [Command 汇总](https://www.ruanyifeng.com/blog/2015/12/git-cheat-sheet.html)
    - [Learn Branch ：一个分支的练习\学习网站](https://learngitbranching.js.org/?locale=zh_CN)
## basic usage

!!! note ""
    英文状态下按`q`可以退出`git log`等输出信息的命令

```
git init 

git add

git commit -m "message"

git status

git diff

git push

git pull
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
    


## 