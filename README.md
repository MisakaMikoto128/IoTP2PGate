# IoTP2PGate 
## 项目地址
[IoTP2PGate](https://github.com/MisakaMikoto128/IoTP2PGate)
## 描述
&emsp;&emsp;为了解决物联网通信模块无法方便的与手机或其他物联网设备快速实现点对点的通信，IoTP2PGate应运而生。IoTP2PGate之主要用于简单的开发验证，毕竟写它的时候为的是毕业设计使用方便。

## 特性
1. 支持且只支持两个物联网设备点对点通信。
2. 设备将(ip,port)看作另一个设备的地址，隐藏背后的服务器转发的过程。

## 使用
1. 准备拥有公网IP，Linux系统的云服务器一台。(请确保服务器上的防火墙和云服务提供商平台提供的防火墙都已经打开相应的端口)
2. 输入以下命令下载编译IoTP2PGate ：

```bash
git clone https://github.com/MisakaMikoto128/IoTP2PGate.git
cd IoTP2PGate
make
```
或者

```bash
git clone https://gitee.com/liuyuanlin6445/IoTP2PGate.git
cd IoTP2PGate
make
```
3.使用：

```bash
./p2pgate <port> [debug]
```
- debug为可选参数，用于查看通信过程中的信息等。
- port为端口号，必选。例如**666**
- eg: `./p2pgate 666` 
4. 此时在两台网联网设备上通过socket.connect(服务器公网IP,PORT)的方式建立其TCP连接，两个设备之间就可以相互通信了。
## 注意事项
1. 两个socket客户端与服务器建立连接后相互通信的通道正式建立。
2. 之后IoTP2PGate会拒绝其他sockt连接直至原来的两个socket客户端的一个或全部断开与服务器的连接。

