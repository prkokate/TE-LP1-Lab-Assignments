import socket
import threading
import sys 

def receive(socket,signal):
    while signal:
        try:
          data=socket.recv(32)
          if data!="":
            print("Server : "+str(data.decode("utf-8")))
        except:
            print("Connection lost!!")
            signal=False
            break
        

host=input("Host : ")
port=int(input("Server Port : "))
sock=socket.socket(socket.AF_INET,socket.SOCK_STREAM)
try:
    sock.connect((host,port))
    print("Connected to server...\n")
except:
    print("Unable to connect to the host..\n")
    input("enter to quit")
    sys.exit(0)
recThread=threading.Thread(target=receive, args=(sock,True))
recThread.start()

while True:
    msg=input("Enter message to send : ")
    sock.sendall(msg.encode("utf-8"))