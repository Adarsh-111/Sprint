//This is the header file for client 
#include <iostream>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#define ADDRSERV "127.0.0.1"
#define PORTNO 8008//Port number used is 8008
#define MAX 256

int writechat(int sockfd);//Function to read the message from the client through the server
int readchat(int sockfd);//Function to write the message to the other client through the server
