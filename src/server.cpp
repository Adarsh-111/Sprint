//The Program to create a test TCP server
#include <server.h>
using namespace std;

int main()//Main function for the server class
{

        int connfd[5];//Array to store the connection fd of the clients
        struct sockaddr_in;
        char cmsg[MAX];//cmsg used to read and write to the client
        int sockfd;//socket file descriptor is used


        Server ser;//Object of the server file is created as ser
        sockfd=ser.ser_setup();//The socket is created using the ser_setup function
        int num=0;
        while(num<2)//Number of connection the server can accept
        {
                        connfd[num]=ser.con_accept(sockfd);//The connection fd is stored in the connfd array
                        int acc_ret=ser.Auth(connfd[num]);//Authentication function is called for the users entering the file
                        if(acc_ret==1)//1 option is required for the addition of new user to the file
                        {
                                int up_ret = ser.upt_newuser(connfd[num]);
				/*Return value of the function is stored and the option are given as:
				 * Username already exist
				 * Password should be greater than 6 characters*/
				 
                                if(up_ret == 2)
                                {
                                memset(cmsg,0,MAX);
                                string acc_str = ser.activeList(connfd[num]);
                                strcpy(cmsg, acc_str.c_str());
                                if(acc_str == "No user available\nPress Enter to Continue: ")//When the first user login and other user is active.
                                {
                                write(connfd[num],cmsg,strlen(cmsg));
                                read(connfd[num],cmsg,strlen(cmsg));
                                }
                                else//Condition when the user is logged in and we have users from before
                                {
                                        write(connfd[num],cmsg,strlen(cmsg));
                                        read(connfd[num],cmsg,strlen(cmsg));
                                        int k = int(cmsg[0])-48;
                                        ser.clientToClient(connfd[num],k);//This is for the chating between the clients 
                                }
                                }
                                if(up_ret == 3)//If the user is entering quit option and it closes the chat
                                {
                                        write(connfd[num],"eoc",3);
                                        close(connfd[num]);
                                }
                        }

			/*If the user choses the option Active Users list
			 * If the first user login then it is no user available
			 * If we have already logged in users then there connfd is displayed*/
                        else if(acc_ret == 2)
                        {
                            memset(cmsg,0,MAX);
                            string acc_str = ser.activeList(connfd[num]);
                            strcpy(cmsg, acc_str.c_str());
                            if(acc_str == "No user available\nPress Enter to Continue: ")
                            {
                                write(connfd[num],cmsg,strlen(cmsg));
                                read(connfd[num],cmsg,strlen(cmsg));
                            }
                            else
                            {
                                write(connfd[num],cmsg,strlen(cmsg));
                                read(connfd[num],cmsg,strlen(cmsg));
                                int k = int(cmsg[0])-48;
                                ser.clientToClient(connfd[num],k);//For the chat between the clients

                            }



                        }
                        else if(acc_ret==3)//If the user presses the 3 option it should give the message end of chat and connfd needs to be closed.
                        {
                                write(connfd[num],"eoc",3);
                                close(connfd[num]);
                        }
                        ++num;
        }
        return 0;
}
