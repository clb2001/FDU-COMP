from socket import *
import os

#此处是为了便于查看对gaia.cs.umass.edu/wireshark-labs/HTTP-wireshark-file1.html请求时缓存从无到有的变化，所以会先删掉之前存下来的这个请求的响应结果
if os.path.exists("gaia.cs.umass.edu_wireshark-labs_INTRO-wireshark-file1.html"):
    os.remove("gaia.cs.umass.edu_wireshark-labs_INTRO-wireshark-file1.html")
 
# 为代理服务器 创建一个TCP套接字、绑定端口号、设置服务器最大连接客户机数量
tcpSerSock = socket(AF_INET, SOCK_STREAM)
# Fill in start.
tcpSerSock.bind(('localhost', 12000))
tcpSerSock.listen(3)
# Fill in end.

while 1:
    # 准备从客户机接收响应消息
    print('准备从客户机接收响应消息...')
    tcpCliSock, addr = tcpSerSock.accept()
    print('接收到一个连接，来自：', addr)

    # 获取客户机发送过来的消息
    message = tcpCliSock.recv(1024).decode()
    print('客户机发送过来的消息：', message)
    if (message == ''):
        continue
    # 从消息从提取出文件名
    filename = message.split()[1].partition("//")[2].replace('/', '_')
    print('文件名：', filename)
    fileExist = "false"

    try:
        # 检查要访问的文件是否在此Web代理服务器中
        print('开始检查代理服务器中是否存在文件：', filename)
        f = open(filename, "r")
        outputdata = f.readlines()
        fileExist = "true"
        print('文件存在在代理服务器中')
        # 文件存在在代理服务器中，返回缓存中的响应消息给客户机
        # Fill in start.
        tcpCliSock.send("HTTP/1.1 200 OK\r\n".encode())
        tcpCliSock.send("Content-Type:text/html\r\n\r\n".encode())
        for i in range(0,len(outputdata)):
            tcpCliSock.send(outputdata[i].encode())
        # Fill in end.
        print('Read from cache')


    # 文件不在代理服务器当中，代理服务器就会向远端服务器请求消息，保存好了再返回给客户机
    except IOError:
        if fileExist == "false":
            print('文件不在代理服务器当中，开始向远端服务器请求网页')
            # 在代理服务器中创建一个TCP套接字
            c = socket(AF_INET, SOCK_STREAM)

            hostn = message.split()[1].partition("//")[2].partition("/")[0]
            print('Host Name: ', hostn)
            try:
                # TCP套接字c 连接到远端服务器80端口
                # Fill in start. 
                serverPort = 80
                # print((hostn, serverPort))
                c.connect((hostn, serverPort))
                print('连接成功')
                # Fill in end.

                # 根据客户端发来的请求，修改成对应向服务器发送的请求，并发送
                c.sendall(message.encode())
                # Fill in end.

                # 代理服务器 读取 从远端服务器响应的消息
                # 将代理服务器中的响应 发送到客户端套接字
                # Fill in start.
                buff = c.recv(2048)
                tcpCliSock.sendall(buff)
                # Fill in end.

                # 在代理服务器中 创建一个新的文件 用于存放这次请求的响应
                # 这样下一次客户端向代理服务器请求同样页面时，代理服务器不需要再次向服务器端发送一次请求
                tmpFile = open("./" + filename, "w")
                # Fill in start.
                tmpFile.writelines(buff.decode().replace('\r\n', '\n'))
                tmpFile.close()
                # Fill in end.

            except:
                print("代理服务器向远端服务器请求网页失败")
        else:
            # 如果客户机请求的消息在远端服务器也找不到，就说明请求不到了
            print('文件存在，但是还是出现了 IOError异常')

    # 关闭客户机 和 代理服务器的TCP套接字
    # Fill in start.
    print('关闭套接字: tcpCliSock')    
    tcpCliSock.close()
    # Fill in end.

# 关闭代理服务器 和 服务器的TCP套接字
print('关闭套接字: tcpSerSock')
tcpSerSock.close()