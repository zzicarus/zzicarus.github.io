---
tags:
  - doing
  - tools/Docker
statistics: true
type: NOTE
processp:
  - ongoing/wait/complete/quit
---
# Docker

>[!info] 和虚拟机的不同之处
>他们都是通过对 operating system 进行虚拟化来实现

## image
```shell
# 以交互形式打开
docker run --name=base-container -ti ubuntu
docker stop base-container
docker rm -f base-container
```
## container

## build
>[!note] 
>运行`docker build`命令来创建新镜像时，Docker 会执行 Dockerfile 中的每个指令，并按照指定的顺序为每个命令创建一个层。对于每条指令，Docker 都会检查是否可以重用先前构建中的指令。如果它发现您之前已经执行过类似的指令，Docker 无需重做。相反，它会使用缓存的结果。
```shell
docker build -t my-username/my-image .

```