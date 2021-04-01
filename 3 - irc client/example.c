	#include <stdio.h>
	#include <windows.h>
	#include <winsock2.h>
	#include <ws2tcpip.h>
	#include <wininet.h>
	#include <conio.h>
	
typedef int				socket_t;

socket_t * sock;
int a,b, *iResult;
WSADATA wsaData;
PCSTR *args[3];
PCSTR address[100], username[100], channel[100];
struct sockaddr_in server;

int main(){
	system("cls");
	
	checkwina16();
	printf("\n");
	
	printf("\n");
	printf("ADDRESS:->");
	fgets_lnl(address);
	printf("\n");
	printf("USERNAME:->");
	fgets_lnl(username);
	printf("\n");
	printf("CHANNEL:->");
	fgets_lnl(channel);

	init_con(address,sock,iResult,wsaData,server,channel,username);
}