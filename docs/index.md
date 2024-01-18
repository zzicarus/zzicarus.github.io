> 记录搭建 MkDocs 的过程
>
> 参考文档：
>
> - [Material](https://squidfunk.github.io/mkdocs-material/)
> - [知乎](https://zhuanlan.zhihu.com/p/630165427)

# 预下载

为了成功搭建，你需要如下预备：

- python 环境，并且安装好了 pip
- 了解基本的 git 语法（online 部署）
- 了解基本的 md 语法

# Material

- [官方文档]: https://squidfunk.github.io/mkdocs-material/

> 由于`MkDocs`的原版主题确实不太好看，所以这里使用了`Material For MkDocs`进行优化

```

mkdocs new     // 新建一个MkDocs

mkdocs serve   // 建立一个预览

mkdocs build   // 建立一个静态网页
```

# Github Page 的部署

[官方文档]: https://docs.github.com/en/pages/quickstart
[ 知乎]: https://zhuanlan.zhihu.com/p/76063614

![image-20240113210407673](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202401132104761.png)

- 自动部署需要在`.github\workflows`中加入`ci.yml`文件，内容如下：

```yml
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
