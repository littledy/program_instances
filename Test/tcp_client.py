import socket

s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
server_ip = '127.0.0.1'
server_port = 10011
# s.bind((server_ip, 10012))
s.bind((server_ip, 0))
s.connect((server_ip, server_port))
print("客户端套接字：{}".format(s.getsockname()))
s.send('客户端已连接服务器：{}:{}'.format(server_ip, server_port).encode('utf-8'))
# recv_msg = s.recv(1024)
# print(recv_msg.decode('utf-8'))

while True:
    client_msg = input('客户端发送：')
    if client_msg == 'exit':
        s.send('客户端 {} 断开连接'.format(s.getsockname()).encode('utf-8'))
        s.close()
    
    s.send(client_msg.encode('utf-8'))
    recv_msg = s.recv(1024).decode('utf-8')
    if recv_msg.strip() != '':
        print('从服务器接收：{}'.format(recv_msg))
