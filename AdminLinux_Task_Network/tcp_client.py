import socket

# Server details
HOST = '10.145.25.84'  # Replace with the server's IP address
PORT = 5000          # Same port as the server

# Create a socket
client_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
client_socket.connect((HOST, PORT))
print(f"Connected to server {HOST}:{PORT}")

while True:
    # Input two numbers from the user
    num1 = input("Enter the first number (or 'exit' to quit): ")
    if num1.lower() == 'exit':
        break
    num2 = input("Enter the second number: ")
    
    # Send numbers as comma-separated values
    client_socket.sendall(f"{num1},{num2}".encode())
    
    # Receive response from server
    data = client_socket.recv(1024).decode()
    print(f"Server replied: {data}")

client_socket.close()
