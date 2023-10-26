import socket
import threading

SERVER_IP = '127.0.0.1'  # Server's IP address
PORT = 8080

def receive_messages(client_socket):
    while True:
        try:
            message = client_socket.recv(1024)
            print(message.decode())
        except:
            print("Connection to the server closed.")
            client_socket.close()
            break

def main():
    client = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    client.connect((SERVER_IP, PORT))

    receive_thread = threading.Thread(target=receive_messages, args=(client,))
    receive_thread.start()

    while True:
        message = input("Enter a message to broadcast: ")
        if message.lower() == 'quit':
            break
        client.send(message.encode())

    client.close()

if __name__ == '__main__':
    main()
