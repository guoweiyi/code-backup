import socket
import threading


def receive_messages(client_socket):
    while True:
        data = client_socket.recv(1024)
        if not data:
            print("[Server disconnected]")
            break
        message = data.decode().strip()
        print(f"\n[Server]: {message}\n[You]: ", end="")
        if message.lower() == "exit":
            print("[x] Server ended chat.")
            client_socket.close()
            break

def start_client(first_time_launch):
    client_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    client_socket.connect((HOST, PORT))
    print(f"[*] Connected to server {HOST}:{PORT}")

    # 启动接收线程
    threading.Thread(target=receive_messages, args=(client_socket,), daemon=True).start()

    # 主线程用于发送消息
    while True:
        if(first_time_launch):
            msg = input("[You]: ")
            first_time_launch = False
        else:
            msg = input()
        client_socket.sendall(msg.encode())
        if msg.lower() == "exit":
            print("[x] Exiting chat...")
            client_socket.close()
            break

if __name__ == "__main__":
    HOST = '127.0.0.1'
    PORT = 65432
    first_time_launch = True
    start_client(first_time_launch)