
#include <server.h>//Header file which includes the server class having member functions and data members
using namespace std;

Server::Server()//Constructor to open the file and read the data  username and password from the file
{


        string strerr;//Error String
        fstream input;//Object of file To read from the file
        try
        {
                input.open("/home/cguser8/sprint/data/userpwd.dat");
                if (!input.is_open())
                {
                         throw strerr;
                }
        }
        catch(string strerr)
        {
                cout<<"File does not Opened"<<endl;
        }
                string line;//Read from the file and store to the line string
                while (getline(input , line))
                {
                        int count = 0;
                        stringstream ss(line);//To read the file contents as string
                        string user;
                        string password;
                        if(getline(ss,user,':'))//Read username save to user variable : is the separator
                        {
                                count++;
                        }
                        if(getline(ss,password,':'))//Read password and have
                        {
                                count++;
                        }
                        if(count == 2)
                        {
                                if(user != "\0" && password != "\0")
                                {
                                        users.push_back(Server(user,password));//Pushing the username and password to the vectors
                                }
                                else
                                {
                                        cout<<"Both field are not present";
                                }
                        }
                }
                input.close();
}

//This is for the storing of username and passwd
Server::Server(string user, string passwd)
{
        this->user=user;
        this->passwd=passwd;
}
//This is for storing the username and the connfd
Server::Server(string user, int connfd)
{
        this->user=user;
        this->connfd=connfd;
}
//This is the function to setup the server
//Creating the socket part
int Server::ser_setup()
{
        struct sockaddr_in servaddr, cliaddr;
        char cmsg[MAX];
        int sockfd,slen,ret;

        slen = sizeof(sockaddr_in);
        memset(&servaddr,0,slen);
        memset(&cliaddr,0,slen);
        memset(cmsg,0,MAX);

        servaddr.sin_family = AF_INET; //To use Internet Family of Addressing
        servaddr.sin_addr.s_addr = INADDR_ANY;
        servaddr.sin_port = htons(PORTNO);

        sockfd = socket(AF_INET,SOCK_STREAM,0);
        if (sockfd < 0){
                fputs("Error: Unable to create Socket",stderr);
                exit(EXIT_FAILURE);
        }
        ret = bind(sockfd,(const struct sockaddr *)&servaddr, slen);
        if (ret < 0){
                fputs("Error: Unable to bind Socket",stderr);
                exit(EXIT_FAILURE);
        }
        ret = listen(sockfd,5);
        if (ret < 0){
                fputs("Error: Unable to Listen on Socket",stderr);
                exit(EXIT_FAILURE);
        }
        return sockfd;
}

//Used to accept the connection from the client
int Server::con_accept(int sockfd)
{

        int connfd;
        struct sockaddr_in cliaddr;
        socklen_t clen=0;
        memset(&cliaddr,0,clen);
        connfd= accept(sockfd,(struct sockaddr *) &cliaddr,&clen);
        return connfd;
}
//Character pointer can be converted to the array-
string Server::convertToString(char *a)
{
       int i=0;
       string s="\0";
       for(i=0;i<=256;i++)
       {
               if(a[i] == 0x0A)
               {
                       return s;
               }


            s = s+a[i];

       }
       return "\0";
}
//To change to the lower case-----------------------------
string Server::tolowercase(string s)
{
        int size = s.size();
        for(int i=0;i<=size;i++)
        {

        s[i]=tolower(s[i]);
        }
        return s;
}
//To check for the valid user----------------------------
bool Server::validUser(string chckuser)
{
           chckuser = tolowercase(chckuser);
           for(auto Server:users)
           {
                   if(tolowercase(Server.user) == chckuser)
                   {
                           return true;
                   }
           }
           return false;
}

bool Server::validPassword(string chckpwd)
{
          for(auto Server:users)
          {
                  if(Server.passwd == chckpwd)
                  {
                          return true;
                  }
          }
          return false;
}

bool Server::getExistPassword(int connfd)
{
        read(connfd,cmsg,MAX);
        string chckpwd="";
        chckpwd = convertToString(cmsg);
        return(validPassword(chckpwd));
}

int Server::Auth(int connfd)
{
        write(connfd,"Enter the user name \0",22);
        read(connfd,cmsg,MAX) ;
        string chckuser ="";
        chckuser = convertToString(cmsg);
        if(validUser(chckuser))
        {
                write(connfd,"Enter the password \0",21);
                while(getExistPassword(connfd) == false)
                {
                        write(connfd,"Your password mismatched Re enter your password\0",48);
               }
        }
        else
        {
                write(connfd,"Your user name mismatched \0",28);
                return 0;
        }


        connect.push_back(Server(chckuser,connfd));

        write(connfd,"You are authenticated successfully ----\nEnter \n1 to Add User \n2 Active List \n3 Quit\0",80);
        memset(cmsg,0,MAX);
        read(connfd,cmsg,2);
        int k=(int(cmsg[0]) -48);
        return k;
}

//Adding new user Functions
//Check existing user list
string Server::getNewUser(int connfd)
{

         read(connfd,cmsg,MAX);
         string uptUser ="";
         uptUser=convertToString(cmsg);
         if(updateUser(uptUser) && uptUser != "")
         {
                 return uptUser;
         }
         else
         {
                return "";
         }
}
//Password size check
string Server::getNewUserPwd(int connfd)
{
         string temp = "\0";
         int k=0;
         read (connfd,cmsg,MAX);
         temp = convertToString(cmsg);
         k =temp.size();
         if(k > 4)
         {
                return temp;
         }
         else
         {
                return "\0";
         }
}

bool Server::updateUser(string upuser)
{
           string temp="";
           temp = upuser;
           temp = tolowercase(temp);
           for(auto Server:users){
                   if(tolowercase(Server.user)== temp){
                           return false;
                           }
                   }
           return true;
}
//This is for updating in user password file
int Server::updateDetails(string upuser ,string password)
{
           ofstream log;
           log.open("userpwd.dat",ios::app);
           if(!(log.is_open())){
                   perror ("cannot open file");
                   return -1;
           }
           else{


                   log<<upuser<<":"<<password<<endl;
                   log.close();

           }
           return 0;
}
//This is the main function to add the users
int Server::upt_newuser(int connfd)
{

         write(connfd,"enter the user name \0",21);
         string newUser ="\0";
         newUser = getNewUser(connfd);
         while (newUser== "\0")
         {
                 write(connfd,"user name already taken enter the user name \0",46);
                 newUser =getNewUser(connfd);
         }

         write (connfd,"enter the password \0",21);
          string pwd ="\0";
          pwd = getNewUserPwd(connfd);
          while(pwd == "\0")
          {
                write(connfd,"password contains atleast 5 character\0",39);
                pwd = getNewUserPwd(connfd);
          }
         updateDetails(newUser,pwd);
         write(connfd,"thank you for register press 2 for active user press 3 for quit\0",67);
         memset(cmsg,0,MAX);
        read(connfd,cmsg,2);
        int k=(int(cmsg[0]) -48);
        return k;
}
//------Active User (The users who are online at that particular time------
string Server::activeList(int connfd)
{
            string s;
            string k;
            for(auto Server:connect)
            {
                    if(Server.connfd!=connfd)
                    {
                        k=to_string(Server.connfd);
                        s=s+" "+Server.user+"="+k;
                    }
            }
            if(s != "" )
            {
                k="please select respective id to chat";
                s=k+s;
                return s;
            }
            else
            {
                return "No user available\nPress Enter to Continue: ";

            }


}
//Chat between a client to the other client
int Server::clientToClient(int connfd1,int connfd0)//Connection Id of both the clients is passed and saved here
{
                int count=0;
                int notbye = 1;
                while(notbye!=0)
                {

                        memset(cmsg,0,MAX);
                        if (count == 0)
                        {
                                write(connfd1,"chat1",5);
                                write(connfd0,"chat2",5);
                        }
                        read(connfd1,cmsg,MAX);
                        notbye = ((strcmp(cmsg,"bye\n")));
                        cout<<notbye<<endl;
                        write(connfd0,cmsg,strlen(cmsg));
                        if(notbye==0)//Check for the not bye condition.If the user types bye the program terminate
                        {
                                close(connfd1);
                                close(connfd0);
                        }
                        else
                        {
                        memset(cmsg,0,MAX);
                        read(connfd0,cmsg,MAX);
                        notbye = ((strcmp(cmsg,"bye\n")));
                        cout<<notbye<<endl;
                        write(connfd1,cmsg,strlen(cmsg));
                        count++;
                        }

                }
        return 0;
}

