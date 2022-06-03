//The Program to create a test TCP chat client
#include <client.h>
using namespace std;

int main()
{//To create a connection with the server through the socket
        struct sockaddr_in servaddr;
        int sockfd,mlen,structlen ;
        char smsg[MAX], rmsg[MAX];//smsg to send the message to the server and recieve message from the server through rmsg

        structlen = sizeof(sockaddr_in);
        memset(&servaddr,0,structlen);
        memset(smsg,0,MAX);
        memset(rmsg,0,MAX);

        servaddr.sin_family = AF_INET; //To use Internet Family of Addressing
        servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
        servaddr.sin_port = htons(PORTNO);

        sockfd = socket(AF_INET,SOCK_STREAM,0);

        connect(sockfd,(struct sockaddr *)&servaddr,structlen);

        //-----------------Authentication--------------------
        mlen=read(sockfd,rmsg,MAX);
        write(1,rmsg,MAX);
        mlen=read(0,smsg,MAX);
        write(sockfd,smsg,mlen);

        mlen=read(sockfd,rmsg,MAX);
        write(1,rmsg,MAX);
        mlen=read(0,smsg,MAX);
        write(sockfd,smsg,MAX);

        //-- Authentication complete----------------------

        //Add User
        bool notbye = true;
        int chat1=3,chat2=3;
        int flag1=1,flag2=1;//k=flag1, s=flag2
        while(notbye)
        {
                memset(rmsg,0,MAX);
                memset(smsg,0,MAX);
                mlen=read(sockfd,rmsg,MAX);
                chat1=strcmp(rmsg,"chat1");//0is this
                chat2=strcmp(rmsg,"chat2");

         if(chat1==0)
         {
                while(flag1 == 1 && flag2 == 1)
                {
                flag1 =writechat(sockfd);
                //cout<<"flag1"<<flag1;
                if(flag1==0)
                        exit(0);
                
                else
                        flag2 =readchat(sockfd);
                }

         }
        else if(chat2==0)
        {
                while(flag1 == 1 && flag2 == 1)
                {
                flag1= readchat(sockfd);
                if(flag1==0)
                        exit(0);
                        
                else
                        flag2= writechat(sockfd);
                }
                

        }
        else
        {
                write(1,rmsg,MAX);
                mlen=read(0,smsg,MAX);
                notbye=strcmp("eoc",smsg);
                if(notbye)
                {
                        write(sockfd,smsg,mlen);
                }
        }

        }

        close(sockfd);
	return 0;


}

