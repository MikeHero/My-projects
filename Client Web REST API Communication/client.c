#include "client.h"

unsigned int id_carte = 0;

int main(int argc, char *argv[])
{
    char *message = NULL;
    char *response = NULL;
    char *cookie = NULL;
    char *token = NULL;

    char buff[SIZE];
    // int sockfd = -1;
    while(1)
    {
        fgets( buff, SIZE, stdin );
        int dim = strlen( buff );
        
        if(buff[dim - 1] == '\n')
            buff[--dim]='\0';

        if( strncmp(buff, "register", 8) == 0 )
        {
            Register(&message, &response);
        }
        else if (strncmp(buff, "login", 5) == 0 )
        {
            // efectuam login si actualizam cookie, in caz de login esuat, ramane NULL
            Login(&message, &response, &cookie);
        }
        else if( strncmp(buff, "exit", 4) == 0)
            break;
        // input invalid / erori format intrare
        else if( strncmp( buff, "logout", 6) == 0)
        {
            Logout(&message, &response, &cookie);
            cookie = NULL;
            token = NULL;
        }
        else if(strncmp( buff, "enter_library", 13) == 0)
            Enter_Library(&message, &response, &cookie, &token);
        else if(strncmp(buff, "add_book", 8) == 0)
            Add_Book(&message, &response, &cookie, &token);
        else if(strncmp(buff, "delete_book", 11) == 0)
            Delete_Book(&message, &response, &cookie, &token);
        else if(strncmp(buff, "get_book", 8) == 0)
            Get_Book(&message, &response, &cookie, &token);
        else
            continue;
        
        
        response = NULL;
        message = NULL;
      


        free(message);
        free(response);
    }
   
    return 0;
}
