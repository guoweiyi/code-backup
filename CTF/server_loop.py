import socket
import threading

HOST = '127.0.0.1'
PORT = 65432

def handle_client(conn, addr):
    print(f"[+] Connected by {addr}")
    while True:
        data = conn.recv(1024)
        if not data:
            print(f"[-] Client {addr} disconnected.")
            break
        message = data.decode().strip()
        if message.lower() == "exit":
            print(f"[x] Client {addr} exited.")
            break
        print(f"\n[Client {addr}]: {message}")

        # 服务器端输入并发送消息
        reply = input("[Server]: ")
        conn.sendall(reply.encode())
        if reply.lower() == "exit":
            print("[x] Server exiting chat...")
            break

    conn.close()

def start_server():
    server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    server_socket.bind((HOST, PORT))
    server_socket.listen(1)
    print(f"[*] Server listening on {HOST}:{PORT}")

    conn, addr = server_socket.accept()
    handle_client(conn, addr)

    server_socket.close()
    print("[*] Server stopped.")

if __name__ == "__main__":
    start_server()