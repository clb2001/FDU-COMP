from socket import *
serverName = 'localhost'
serverPort = 12000
clientSocket = socket(AF_INET, SOCK_STREAM) # 建立TCP套接字，使用IPv4协议
clientSocket.connect((serverName,serverPort)) # 向服务器发起连接

while True:
	#这里的Connetction: close不同于浏览器常见的keep-alive,
	#close表示要求服务器在发送完被请求的对象后就关闭这条链接
	Head = '''GET /HelloWorld.html HTTP/1.1\r\nHost: localhost:12000\r\nConnection: close\r\nUser-agent: Mozilla/5.0\r\n\r\n'''
	clientSocket.send(Head.encode('utf-8'))
	data = clientSocket.recv(1024)
	print(data)
	with open("response.html","wb") as f:
		f.write(data)