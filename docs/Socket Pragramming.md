**参考：**
- [微软官方文档 · Winsock 入门](https://learn.microsoft.com/zh-cn/windows/win32/winsock/getting-started-with-winsock)
- [Youtube视频 · C++ Network Programming](https://www.youtube.com/watch?v=gntyAFoZp-E)

Server 的端口由 code 指定，client 由 OS 分配

WinSocket 的操作是针对某个 socket 的

Socket act as pipe

**Server**

- Bind
  将 Socket 和 IP 和 Port 进行绑定
- Listening
  
**Client**
- Bind
- Connected

## 服务器

1. 初始化 Winsock。`WASStartup`
2. 创建套接字。 `socket`
3. 绑定套接字。`bind`
4. 侦听客户端的套接字。 `listen`
5. 接受来自客户端的连接。 `accept connect`
6. 接收和发送数据。 `recv send secvfrom sendto`
7. 断开连接。 `closesocket`

## 客户端

1. 初始化 Winsock。
2. 创建套接字。
3. 连接到该服务器。
4. 发送和接收数据。
5. 断开连接。