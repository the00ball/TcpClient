import socket
import sys
import codecs

def from_bytes (data, big_endian = False):
    if isinstance(data, str):
        data = bytearray(data)
    if big_endian:
        data = reversed(data)
    num = 0
    for offset, byte in enumerate(data):
        num = num | (byte << (offset * 8))
    return num

# Create a TCP/IP socket
sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
# Bind the socket to the port
server_address = ('localhost', 10000)
print >>sys.stderr, 'starting up on %s port %s' % server_address
sock.bind(server_address)
# Listen for incoming connections
sock.listen(1)
while True:
    # Wait for a connection
    print >>sys.stderr, 'waiting for a connection'
    connection, client_address = sock.accept()
    try:
        print >>sys.stderr, 'connection from', client_address
        # Receive the data in small chunks and retransmit it
        while True:
            value_data = bytearray([0x00, 0x00, 0x00, 0x00])
            connection.recv_into(value_data, 4)
            value = socket.ntohl(from_bytes(value_data))
            print >>sys.stderr, 'Receiving "%d" bytes' % value
            data = connection.recv(value)
            if data:
                print >>sys.stderr, 'received "%s"' % data
                print >>sys.stderr, 'sending data back to the client'
                connection.sendall(data)
            else:
                print >>sys.stderr, 'no more data from', client_address
                break
    finally:
        # Clean up the connection
        connection.close()
