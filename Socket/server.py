import socket
import threading

connections=[]
total_conn=0

class Client(threading.Thread):
    def __init__(self,socket,address,id,name,signal):
        threading.Thread.__init__(self)
        self.socket=socket
        self.address=address
        self.name=name
        self.signal=signal
        self.id=id

    def run(self):
        while self.signal:
            try:
                data=self.socket.recv(32)
            except:
                print("Client disconected!")
                connections.remove(self)
                self.signal=False
                break
            if data!="":
                print("New message from ID="+str(self.id)+": "+str(data.decode("utf-8")))
                for client in connections:
                    if client.id==self.id:
                        client.socket.sendall(data)
                        break

def newConn(socket):
    while True:
        sock,addr=socket.accept()
        global total_conn
        connections.append(Client(sock,addr,total_conn,"name",True))
        total_conn+=1
        print("New connection with ID = "+str(connections[len(connections)-1].id))
        connections[len(connections)-1].start()

def main():
    host=input("Host : ")
    port=int(input("Port : "))
    sock=socket.socket(socket.AF_INET,socket.SOCK_STREAM)
    sock.bind((host,port))
    sock.listen(5)
    print("Server is running...")
    newThread=threading.Thread(target=newConn, args=(sock,))
    newThread.start()

main()

        


