//Server.h
//This include the class server and all the data members as well as the member functions of this class
#include <iostream>
#include <signal.h>
#include <unistd.h>
#include <string.h>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>//Used for vectors
#include <algorithm>
#include <array>//Used for arrays
#include <set>
#include <sys/socket.h>
#include <arpa/inet.h>
#define ADDRSERV "127.0.0.1"
#define PORTNO 8008//Port Number for the server
#define MAX 256

using namespace std;

//This class includes the user, password authentication function and also the Chat functions
class Server
{
        public:
        char cmsg[MAX];
        Server();//Constructor to open the file
        Server(string username,string passwd);//Constructor for storing username and password
        Server(string user, int connfd);//Constructor for storing username and connectionId

//-Function to setup the server---------------------------
        int ser_setup();
        int con_accept(int sockfd);
//--------------------------------------------------------

        string convertToString(char *a);
        string tolowercase(string to_change);
        bool validUser(string username);
        bool getExistPassword(int connfd);
        bool validPassword(string passwd);

        int Auth(int);//Authentication Function to check the authentication
//--------------------------------------------------------------------------------

        string getNewUser(int connfd);
        string getNewUserPwd(int connfd);
        int updateDetails(string,string);
        bool updateUser(string);

        int upt_newuser(int connfd);//Main function to update the new users in the file
//--------------------------------------------------------------------------------
        string activeList(int connfd);
        int clientToClient(int connfd0,int connfd1);
//--------------------------------------------------------------------------------
	private:

        string user;//To store the usernames
        string passwd;//To store the password
        int connfd;
        vector <Server> users;//Vector to save the username and password
        vector <Server> connect;//Vector to save username and connection id
};
