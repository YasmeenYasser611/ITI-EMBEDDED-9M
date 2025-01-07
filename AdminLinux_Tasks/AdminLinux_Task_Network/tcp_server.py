import socket

# Server settings
HOST = '10.145.16.245'  # Listen on all available interfaces
PORT = 5000    # Port to listen on

# Create a socket
server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
server_socket.bind((HOST, PORT))
server_socket.listen(1)  # Allow only 1 connection at a time

print(f"Server listening on {HOST}:{PORT}...")

# Accept a connection
conn, addr = server_socket.accept()
print(f"Connected by {addr}")

while True:
    data = conn.recv(1024).decode()  # Receive data (max 1024 bytes)
    if not data:
        break
    
    # Parse received data
    try:
        num1, num2 = map(float, data.split(","))
        result = num1 + num2
        print(f"Received numbers: {num1} and {num2}, sending back sum: {result}")
        conn.sendall(f"The sum is: {result}".encode())  # Send the result back
    except ValueError:
        conn.sendall(b"Invalid input. Please send two numbers separated by a comma.")

conn.close()
server_socket.close()
