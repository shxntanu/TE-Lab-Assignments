import socket

SERVER_IP = '127.0.0.1'  # Server's IP address
PORT = 8080

def main():
    client = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    client.connect((SERVER_IP, PORT))

    while True:
        message = input("Enter a message to send to the server (or 'quit' to exit): ")
        if message == 'quit':
            break
        client.send(message.encode())
        data = client.recv(1024)
        print(f'Server echoed: {data.decode()}')

    client.close()

if __name__ == '__main__':
    main()
