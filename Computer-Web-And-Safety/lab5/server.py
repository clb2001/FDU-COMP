#import socket module
from socket import *
import time
serverSocket = socket(AF_INET, SOCK_STREAM) 
#Prepare a sever socket 
#Fill in start 
serverPort = 12000
serverSocket.bind(('127.0.0.1',serverPort))
serverSocket.listen(1)
#Fill in end 
while True:    
    #Establish the connection   
    print ('Ready to serve...')    
    connectionSocket, addr = serverSocket.accept()
    try:        
        message = connectionSocket.recv(1024)
        print(message)
        if len(message.split()) < 1:
            continue
        filename = message.split()[1]                      
        f = open(filename[1:])
        outputdata = f.read()
        #Send one HTTP header line into socket         
        #Fill in start  
        # need to print the infomation of f
        print(outputdata)
        output = 'HTTP/1.1 200 OK\nConnection: close\nDate: %s\nContent-Type: text/html\nContent-Length: %d\n\n' \
            % (time.strftime('%Y-%M-%D %H:%M:%S',time.localtime(time.time())), len(outputdata))
        connectionSocket.send(output.encode())
        #Fill in end   
        #Send the content of the requested file to the client
        for i in range(0, len(outputdata)):
            connectionSocket.send(outputdata[i].encode())
        connectionSocket.close()
    except IOError:
        #Send response message for file not found
        #Fill in start
        text = "404 Not Found: cannot get the file!"
        connectionSocket.send(text.encode())
        #Fill in end
        #Close client socket
        #Fill in start
        connectionSocket.close()
        #Fill in end   
          
serverSocket.close()