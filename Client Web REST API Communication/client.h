#include <stdio.h>      /* printf, sprintf */
#include <stdlib.h>     /* exit, atoi, malloc, free */
#include <unistd.h>     /* read, write, close */
#include <string.h>     /* memcpy, memset */
#include <sys/socket.h> /* socket, connect */
#include <netinet/in.h> /* struct sockaddr_in, struct sockaddr */
#include <netdb.h>      /* struct hostent, gethostbyname */
#include <arpa/inet.h>
#include "helpers.h"
#include "requests.h"
#include "parson.h"

#define HOST "34.254.242.81"
#define PORT 8080

#define SIZE 300
#define INPUT_SIZE 100
 
typedef struct TUser 
{
    char* username;
    char* password;
}TUser;

typedef struct TCarte 
{
	unsigned int id;
	char *title;
	char *author;
	char *publisher;
	char *genre;
	unsigned int page_count;
	
}TCarte;

struct TUser *alocareUSer();
void freeUser();

struct TCarte *alocareCarte();
void freeCarte();

int Register(char** message, char** response);
void Login(char **message, char** response, char** cookie);
int Logout(char **message, char** response, char** cookie);
void Enter_Library(char **message, char **response, 
						char **cookie, char **token);
void Add_Book(char** message, char** response, char** cookie, char** token);
void Delete_Book(char** message, char** response, char** cookie, char** token);
void Get_Book(char** message, char** response, char** cookie, char** token);