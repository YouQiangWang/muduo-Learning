
## Buffer
+ 该模块是缓存模块，通过vector<char>实现了一个缓存，这个缓存默认大小是1024+8个字节。
+ 默认前8个字节是预设位，从第八个字节往后作为读写区，第9个字节到readerIndex之间是已经读取过的区域，在可写区域不足时可以通过移动未读区域的数据到“开头”处
 以扩大连续可写区域的大小，readerIndex与writerIndex之间是可读区域，writerIndex与size之间是可写区域。当通过“移动”的方式也无法满足写入数据所需空间大小时在writerIndex往后扩容len大小。

 ## Socket && SocketsOps
+ 封装了socket的基本bind、listen、accept、connect等基本操作，以及读写、设置及获取socket的选项，如TCP_NODELAY、SO_REUSEADDR、SO_REUSEPORT、SO_KEEPALIVE等。
+ TCP_NODELAY 即关闭Nagle算法。TCP套接字默认使用Nagle算法交换数据，因此最大限度地进行缓冲，直到收到ACK才发送下一组数据。 关闭Nagle算法后，数据到达输出缓冲后立即被发送出去，不需要等待ACK返回，优点是网络流量未受太大影响时传输速度更快（典型场景是传输大文件数据），缺点是存在一定的可能性发送的数据大小远小于TCP信息头部大小，浪费大量带宽。总之，我们应当准确地判断数据特性来判断是否需要禁用Nagle算法。
+ SO_REUSEADDR：启用后允许将Time-wait状态下的套接字端口号重新分配给新的套接字，即允许服务器bind一个地址(IP+Port)，即使这个地址当前已经存在已建立的连接。一般服务器的监听socket都应该打开它。
+ SO_REUSEPORT：启用后多进程或者多线程创建多个绑定同一个IP:Port的监听socket(独立的listen()和accept())，提高服务器的接收链接的并发能力,程序的扩展性更好(例如nginx多进程同时监听同一个IP:Port)。
+   int connfd = ::accept4(sockfd, sockaddr_cast(addr),&addrlen, **SOCK_NONBLOCK | SOCK_CLOEXEC**);
+   

