from socket import *
import time
import threading

# 这个代码跟server.py一样
def webProcess(connectionSocket):
    try:        
        message = connectionSocket.recv(1024)
        print(message)
        if len(message.split()) < 1:
            print("error!")
        filename = message.split()[1]                      
        f = open(filename[1:])
        outputdata = f.read()
        #Send one HTTP header line into socket         
        # need to print the infomation of f
        print(outputdata)
        output = 'HTTP/1.1 200 OK\nConnection: close\nDate: %s\nContent-Type: text/html\nContent-Length: %d\n\n' \
            % (time.strftime('%Y-%M-%D %H:%M:%S',time.localtime(time.time())), len(outputdata))
        connectionSocket.send(output.encode()) 
        #Send the content of the requested file to the client
        for i in range(0, len(outputdata)):
            connectionSocket.send(outputdata[i].encode())
        connectionSocket.close()
    except IOError:
        #Send response message for file not found
        text = "404 Not Found: cannot get the file!"
        connectionSocket.send(text.encode())
        #Close client socket
        connectionSocket.close() 

serverSocket = socket(AF_INET, SOCK_STREAM)
# Prepare a sever socket
serverPort = 12000
serverSocket.bind(('127.0.0.1', serverPort))
serverSocket.listen(10)

while True:
    # Establish the connection
    print('Ready to serve...')
    connectionSocket, addr = serverSocket.accept()#connectionSocket: <class 'socket.socket'>
    thread = threading.Thread(target=webProcess, args=(connectionSocket,))
    thread.start()
serverSocket.close()
