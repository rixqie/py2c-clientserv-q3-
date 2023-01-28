#include <sys/socket.h>//func and struct for socket ops
#include <arpa/inet.h>//IP add & netw add func
#include <unistd.h> //basic file, device,& process ops
#include <stdio.h>//input and output operations
#include <stdlib.h>//C general purpose standard library
#include <string.h>//get the length of a string@strlen
#include <time.h>// date and time func

int createSocket(int port)
{
    int sock, err;
    struct sockaddr_in server; //Declare socket variable, struct and size

    // initiate socket with address family, connection type and catching socket creation error
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        printf("ERROR: Socket creation failed\n");
        exit(1);
    }
    printf("Socket created\n");

    bzero((char *) &server, sizeof(server));
    server.sin_family = AF_INET;//address family for the socket 
    server.sin_addr.s_addr = INADDR_ANY;//address for incoming request
    server.sin_port = htons(port);//port designated for binding 

    //Bind or assigns a name to a socket.
    if (bind(sock, (struct sockaddr *)&server , sizeof(server)) < 0)
    {
        printf("ERROR: Bind failed\n"); // catching port binding error
        exit(1);
    }
    printf("Bind done\n");
    //Listen to a port for any incoming request for maximum 3 connection
    listen(sock , 3);
    
    return sock;//returning socket descriptor
}

int main()
{
    int PORT = 8080; //port address
    int BUFFSIZE = 512;// buffer size
    char buff[BUFFSIZE];// declare buffer variable
    int ssock, csock;//declare socket descriptor
    int nread;
    char client_message[2000];
    time_t ticks;
    struct sockaddr_in client;
    int clilen = sizeof(client);

    ssock = createSocket(PORT);
    printf("Server listening on port %d\n", PORT);

    while (1) {
        csock = accept(ssock, (struct sockaddr *)&client, &clilen);
        if (csock < 0)
        {
            printf("Error: accept() failed\n");
            continue;
        }

        printf("Accepted connection from %s\n", inet_ntoa(client.sin_addr));
        bzero(buff, BUFFSIZE);
        char buff[80], client_message[] = "From server xyz :";
        //reading the client message in socket decriptor
            read(csock, buff, sizeof(buff));
        // concatenates server reply to client message
            strcat(client_message, buff);
        //writes data from a buffer to a file descriptor
           write(csock, client_message, strlen(client_message));
           memset(client_message,0, sizeof(client_message));
        /*while ((nread=read(csock, buff, BUFFSIZE)) > 0)//only run if theres date to read
        {
            printf("\nReceived %d bytes\n", nread);//print out size of input
            printf("\nClient: %s\n",buff); //print out client request
            printf("Sending time request back.. \n\n");
            ticks = time(NULL);//declare variable for time object
            // writes a  human-readable formatted  ocal time to a buffer
            snprintf(client_message, sizeof(client_message), "%.24s\r\n", ctime(&ticks));
            //writes data from a buffer to a file descriptor
            write(csock, client_message, strlen(client_message));

        }*/
        printf("Closing connection to client\n");
        printf("----------------------------\n");
        close(csock);//closing socket descriptor
    }

    close(csock);//closing socket descriptor
    return 0;
}
