/* simple irc library built for gcc */

#if defined (_WIN32)
#define WIN_TEXT "this is a windows machine"
#include <windows.h>
#include <winsock2.h>
#include <winsock.h>
#include <ws2tcpip.h>
#include <wininet.h>
#include <stdio.h>
#include <pthread.h>
#define IS_SOCKET_ERROR(a)	((a)<0)
#define DEFAULT_PORT "6667"
typedef int				socket_t;
#endif

struct sockinf {
    SOCKET sock;
    char *msg;
	char *username;
} sockinf;

char addressing[100];
int fgets_lnl(PCSTR *addressing) {
    fgets(addressing,99,stdin);
    char *nl = strchr(addressing, '\n');
    if (nl != NULL)
        *nl = '\0';
    return addressing;
}

void substring(char s[], char sub[], int p, int l) {
   int c = 0;
   while (c < l) {
      sub[c] = s[p+c-1];
      c++;
   }
   sub[c] = '\0';
}

int strpos(char *haystack, char *needle)
{
   char *p = strstr(haystack, needle);
   if (p)
      return p - haystack;
   return -1;   // Not found = -1.
}

int send_data(SOCKET sock, char * data) {
    return send(sock, data, strlen(data), 0);
}

//((struct sockinf*)sock)->sock

void *istream(void *sock) {
    
	char message[100];
	int Error = WSAGetLastError();
	while (1) {
        fgets_lnl(message);
        if (send_data(((struct sockinf*)sock)->sock,message) == NULL)
        {
            printf("message not sent.\n");
        }
        else {
			int Error = WSAGetLastError();
            printf("message sent. %d\n",Error);
        }
    }
    pthread_exit(NULL);
}

int WSAAPI getaddrinfo (const char*,const char*,const struct addrinfo*,
                        struct addrinfo**);

#if !defined  (_WIN32)
#define WIN_TEXT "this is not a windows machine"
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <fcntl.h>

#define IS_SOCKET_ERROR(a)	((a)==SOCKET_ERROR)

typedef SOCKET socket_t;
#endif

char *windows = WIN_TEXT;

#include "mul.h"

typedef struct irc_wsasession {
    socket_t sock;
    char *lasterror;
} wsasession_irc;

void checkwina16() {
    printf("%s",windows);
}

// sock commands windows

#if defined (_WIN32)
void print_WSA_data(WSADATA wsaData) {
    printf("\nDESC::: %s",wsaData.szDescription);
    printf("\nSTATUS: %s",wsaData.szSystemStatus);
    printf("\nMAXUDP: %s",wsaData.iMaxUdpDg);
    printf("\nVENDIN: %s",wsaData.lpVendorInfo);
}
void print_ADDR_info(struct addrinfo *result) {
    printf("\n%d",result[0].ai_flags);
    printf("\n%d",result[0].ai_family);
    printf("\n%d",result[0].ai_socktype);
    printf("\n%d",result[0].ai_protocol);
    printf("\n%d",result[0].ai_addrlen);
    printf("\n%s",result[0].ai_canonname);
}

int init_con(PCSTR *address,socket_t * socket_t, int * iResult, WSADATA wsaData,struct sockaddr_in server, PCSTR *channel, PCSTR *username) {

    struct addrinfo *result = NULL,
                         *ptr = NULL,
                          hints;

    struct in_addr addr;

    iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (iResult != 0) {
        printf("\nwsatartup failed: %d\n", iResult);
        return 1;
    }
    else {
        printf("wsastartup success.\n");
    }

    ZeroMemory( &hints, sizeof(hints) );
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;

    DWORD dwRetval;

    struct hostent *remoteHost;

    printf("calling gethostbyname with %s\n", address);
    remoteHost = gethostbyname(address);
    if (!remoteHost)
    {
        printf("failed to get %s(s) host by name... Error: %d\n", address, WSAGetLastError());
        getch();
        exit(1);
    }
    printf("successfully retrieved host by name...\n");
    int i = 0;
    while (remoteHost->h_addr_list[i] != 0)
    {
        addr.s_addr = *(u_long *) remoteHost->h_addr_list[i++];
        printf("ip address #%d: %s\n", i, inet_ntoa(addr));
    }

    SOCKET sock;

    dwRetval = getaddrinfo(inet_ntoa(addr), "27015", &hints, &result);
    if ( dwRetval != 0 ) {
        printf("\ngetaddrinfo failed with error: %d\n", dwRetval);
        WSACleanup();
        return 1;
    }
    else
    {
    }

    char *ipaddr = inet_ntoa(addr);
    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock == INVALID_SOCKET)
    {
        printf("socket is an invalid socket...\n");
        getch();
        exit(1);
    }

    printf("gathered all ip adresses... \nusing %s\n", ipaddr);
    ZeroMemory(&server, sizeof(&server));
    server.sin_addr.s_addr = inet_addr(ipaddr);
    server.sin_family = AF_INET;
    server.sin_port = htons(6667);

    if (connect(sock, (struct sockaddr *)&server, sizeof(server)) == 0)
    {
        printf("connected.\n");
        Sleep(2000);

        pthread_t threads[3];

        struct sockinf *  sockinfo = (struct sockinf *)malloc(sizeof(struct sockinf));
        sockinfo->sock = sock;
		int hostname[100];
		
		gethostname((int *)hostname,strlen(hostname));
		printf("%d",hostname);
		
		char usermessage[200];
		strcpy(usermessage, "USER ");
		strcat(usermessage, username);
		strcat(usermessage, " ");
		strcat(usermessage, address);
		strcat(usermessage, " ");
		strcat(usermessage, ipaddr);
		strcat(usermessage, " ");
		strcat(usermessage, ":Erroneous");
		strcat(usermessage, "\n");
		
		char servermessage[200];
		strcpy(servermessage, "SERVER ");
		strcat(servermessage, address);
		strcat(servermessage, "\n");
		
		char pongmessage[200];
		strcpy(pongmessage, "PONG ");
		strcat(pongmessage, ipaddr);
		strcat(pongmessage, "\n");
		
		char joinmessage[200];
		strcpy(joinmessage, "JOIN ");
		strcat(joinmessage, channel);
		strcat(joinmessage, "\n");
		
		char nickmessage[200];
		strcpy(nickmessage, "NICK ");
		strcat(nickmessage, username);
		strcat(nickmessage, "\n");
		
		printf("\n\n%s\n",servermessage);
		printf("\n\n%s\n",usermessage);
		printf("\n\nADDRESS:-> %s\n",address);
		
		printf("\nSTRLEN USERMESSAGE:%d\n",strlen(usermessage));
		
		send(sock, nickmessage, strlen(nickmessage), 0);
		send(sock, "PASS security\n", strlen("PASS security\n"), 0);
		send(sock, usermessage, strlen(usermessage), 0);
		
		
        int mret;
        char rbuf[4096];;
        while (1)
        {
            ZeroMemory(&rbuf, sizeof(rbuf));
            mret = recv(sock, rbuf, sizeof(rbuf), 0);
            if (!mret)
            {
                printf("Connection broke...\n");
                getch();
                exit(1);
            }
            else
            {
                if(rbuf)
                    printf("%s\n", rbuf);
                if(strstr(rbuf, "No Ident response") != NULL) {
                    pthread_create(threads[1], NULL, istream, (void *)sockinfo);
                    Sleep(30);
                }
				if(strstr(rbuf, "PING") != NULL) {
					printf("%s",pongmessage);
                    send(sock, pongmessage, strlen(pongmessage), 0);
                    Sleep(30);
                }
				if(strstr(rbuf, "To connect type /QUOTE PONG") != NULL) {
					printf("\nquote this");
					int strpos_rbuf = strpos(rbuf,"PONG");
					int rbuf_diff = strlen(rbuf) - strpos_rbuf;
					printf("\nSTRPOS:->%d\n BUFDIF:->%d",strpos_rbuf,rbuf_diff);
					char str_tp[100];
					substring(rbuf,str_tp,strpos_rbuf+1,rbuf_diff-1);
					strcat(str_tp, "\n");
					printf("\n%s",str_tp);
					send(sock, str_tp, strlen(str_tp), 0);
					send(sock, "hello\n", strlen("hello\n"), 0);
                    Sleep(30);
                }
				if(strstr(rbuf, "End of /MOTD command.") != NULL) {
					send(sock, joinmessage, strlen(joinmessage), 0);
				}
            }
        }
    }
}

#endif