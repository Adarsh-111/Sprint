#include <client.h>

using namespace std;
//Function To write the chat to the other client
int writechat(int sockfd)
{
        char cmsg[MAX];//cmsg to read from the socket of the server
        memset(cmsg,0,MAX);
        write(1,"Enter Your Message: ",20);
        read(0,cmsg,MAX);
        write(sockfd,cmsg,strlen(cmsg));
        if(strcmp(cmsg,"bye\n")==0)//It compares the message with bye and return a 0 value in case of a match
        {
                return 0;
        }
        return 1;
}

int readchat(int sockfd)//Function to read from the other client through server
{
        char smsg[MAX];//This is to send to the socket the message
        memset(smsg,0,MAX);
        read(sockfd,smsg,MAX);
        write(1,smsg,strlen(smsg));
        if(strcmp(smsg,"bye\n")==0)
        {
                return 0;
        }
        return 1;
}

