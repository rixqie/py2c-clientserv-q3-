import socket # Import socket module
import sys # Import socket module
from ctypes import *

def main():
    server_addr = ('127.0.0.1', 8080)
    s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    BUFFER_SIZE = 1024

    try:
        s.connect(server_addr)
        print("Connected at {:s}".format(repr(server_addr)))

        for i in range(1):
            msg = input("\nEnter message: ")
            buff = msg.encode()
            ssent = s.sendto(buff, server_addr)
            #print('sent %s bytes to %s\n' % (ssent, server_addr))
            buff, server_addr = s.recvfrom(BUFFER_SIZE) # buffer size is 1024 bytes
            msg = buff.decode('windows-1252').strip()
            print ("\n" + msg + "\n")
            #print('received %s bytes from %s\n' % (len(buff), server_addr))


    except AttributeError as ae:
        print("Error creating the socket: {}".format(ae))
    except socket.error as se:
        print("Exception on socket: {}".format(se))
    finally:
        print("Closing socket")
        s.close()


if __name__ == "__main__":
    main()
