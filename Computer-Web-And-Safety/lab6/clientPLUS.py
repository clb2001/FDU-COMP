from socket import *
import base64
from base64 import b64encode
msg = "I love computer networks!"  #要发送的消息内容
endmsg = "\r\n.\r\n"
# Choose a mail server 
mailserver = "smtp.163.com"

# Create socket called clientSocket and establish a TCP connection with mailserver
# Fill in start
# 建立TCP套接字，使用IPv4协议
clientSocket = socket(AF_INET, SOCK_STREAM)
# 向服务器发起连接
clientSocket.connect((mailserver, 25))
# Fill in end

#第一步 建立连接返回代码220
recv = clientSocket.recv(1024).decode()
print(recv)
if recv[:3] != '220':     
    print ('220 reply not received from server.')

# Send HELO command and print server response.开始与服务器的交互，服务器将返回状态码250
heloCommand = 'HELO Alice\r\n'
clientSocket.send(heloCommand.encode())
recv1 = clientSocket.recv(1024).decode()
print(recv1)
if recv1[:3] != '250':
    print('250 reply not received from server.')

# send AUTH LOGIN command  发送"AUTH LOGIN"命令，开始验证身份，服务器将返回状态码235
# Fill in start
res = 'AUTH LOGIN' + '\r\n'
clientSocket.send(res.encode())
recv0 = clientSocket.recv(1024).decode()
print(recv0)
if recv0[:3] != '334':
    print('334 reply not received from server.')

account = 'clb245000'
res_1 = base64.b64encode(account.encode()) + '\r\n'.encode()  # base64编码函数
clientSocket.send(res_1)
recv2 = clientSocket.recv(1024).decode()
print(recv2)
if recv2[:3] != '334':
    print('334 reply not received from server.')

pwd = 'UFUQWEHFKJOBMBAI'
res_2 = base64.b64encode(pwd.encode()) + '\r\n'.encode() # base64编码函数
clientSocket.send(res_2)
recv3 = clientSocket.recv(1024).decode()
print(recv3)
if recv3[:3] != '235':
    print('235 reply not received from server.')
# Fill in end

# Send MAIL FROM command and print server response.发送"MAIL FROM"命令，并包含发件人邮箱地址，服务器将返回状态码250
# Fill in start
send_mail_addr = 'clb245000@163.com'
mailCommand_1 = 'MAIL FROM: <' + send_mail_addr + '>\r\n'
#接下来clientSocket.send并接受返回的消息
clientSocket.send(mailCommand_1.encode())
recv4 = clientSocket.recv(1024).decode()
print(recv4)
if recv4[:3] != '250':
    print('250 reply not received from server.')
# Fill in end

# Send RCPT TO command and print server response.发送"RCPT TO"命令，并包含收件人邮箱地址，服务器将返回状态码250
# Fill in start
rcpt_mail_addr = '2470681163@qq.com'
mailCommand_2 = 'RCPT TO: <' + rcpt_mail_addr + '>\r\n'
clientSocket.send(mailCommand_2.encode())
recv5 = clientSocket.recv(1024).decode()
print(recv5)
if recv5[:3] != '250':
    print('250 reply not received from server.')
# Fill in end

# Send DATA command and print server response.发送"DATA"命令，表示即将发送邮件内容，服务器将返回状态码354
# Fill in start
data = 'DATA' + '\r\n'
clientSocket.send(data.encode())
recv6 = clientSocket.recv(1024).decode()
print(recv6)
if recv6[:3] != '354':
    print('354 reply not received from server.')
# Fill in end

# Send message data.发送邮件内容
# Fill in start
html_data = base64.b64encode(b'<img src="cid:image1">')
with open("demo.jpg", "rb") as f:
    image_data = base64.b64encode(f.read())
msg = "FROM: clb245000@163.com\r\nTO: 2470681163@qq.com\r\nSubject: Transmit Image by E-mail\r\nMIME-Version: " \
        "1.0\r\nContent-Type:multipart/related; boundary='12345678'\r\n\r\n--12345678\r\nContent-Type: text/html; " \
        "charset=UTF-8\r\nContent-Transfer-Encoding: base64\r\n\r\n".encode()
msg += html_data
msg += "\r\n\r\n--12345678\r\nContent-Type: image/jpeg; name='demo.jpg'\r\nContent-Transfer-Encoding: " \
        "base64\r\nContent-ID: image1\r\n\r\n".encode()
msg += image_data
msg += "\r\n\r\n--12345678--\r\n".encode()
#发送mailmsg
clientSocket.send(msg)
#发送邮件结尾信息 
clientSocket.send(endmsg.encode())
# Fill in end 

#服务器将返回状态码250，判断是否为250，输出
# Fill in start
recv7 = clientSocket.recv(1024).decode()
print(recv7)
if recv7[:3] != '250':
    print('250 reply not received from server.')
# Fill in end

# Send QUIT command and get server response.发送"QUIT"命令，断开与邮件服务器的连接。
# Fill in start
clientSocket.send("QUIT\r\n".encode())
recv8 = clientSocket.recv(1024).decode()
print(recv8)
if recv8[:3] != '221':
    print('221 reply not received from server.')
# Fill in end

# close
clientSocket.close()