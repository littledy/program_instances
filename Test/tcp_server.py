import socket

s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
local_server_ip = '127.0.0.1'
local_server_port = 10011
s.bind((local_server_ip, local_server_port))
s.listen()

print("等待客户端连接中")
conn, addr = s.accept()
server_msg = conn.send("服务器监听：{}".format(s.getsockname()).encode('utf-8'))
# recv_msg = conn.recv(1024)
# print(recv_msg.decode('utf-8'))

while True:
    recv_msg = conn.recv(1024).decode('utf-8')
    print(recv_msg)
    if recv_msg.strip() != '':
        print("从客户端接收：".format(recv_msg))
    send_msg = input("服务器发送：")
    if send_msg == 'exit':
        conn.send('服务器关闭！'.encode('utf-8'))
        print('服务器关闭！')
        conn.close()
        s.close()
    else:
        conn.send(send_msg.encode('utf-8'))