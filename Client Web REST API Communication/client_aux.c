#include "client.h"

TUser *alocareUSer()
{
    TUser *aux = malloc(sizeof(struct TUser));
    if(aux == NULL)
        return NULL;

    char buff[INPUT_SIZE];
    printf("username=");

    fgets( buff, INPUT_SIZE, stdin );
    int dim = strlen( buff );
        
    if(buff[dim - 1] == '\n')
        buff[--dim]='\0';

    aux->username = malloc(INPUT_SIZE);
    if(aux->username == NULL)
    {    
        free(aux);
        return NULL;
    }
    strcpy(aux->username, buff);

    printf("password=");
    aux->password = malloc(INPUT_SIZE);
    if( aux->password == NULL)
    {    
        free(aux->username);
        free(aux);
        return NULL;
    }

    fgets(buff, INPUT_SIZE, stdin);
    dim = strlen(buff);

    if( buff[dim - 1] == '\n')
        buff[--dim] = '\0';

    strcpy(aux->password, buff);

    return aux;

}

TCarte *alocareCarte()
{
    TCarte *aux = malloc(sizeof(struct TCarte));
    if( aux == NULL )
        return NULL;

    char buff[INPUT_SIZE];
    int dim;

    printf("id=");
    fgets(buff, INPUT_SIZE, stdin);
    dim = strlen(buff);

    if(buff[dim - 1] == '\n')
        buff[--dim]='\0';

    aux->id = atoi(buff);
    
    // title
    printf("title=");

    fgets(buff, INPUT_SIZE, stdin);
    dim = strlen(buff);

    if(buff[dim - 1] == '\n')
        buff[--dim]='\0';

    aux->title = malloc(INPUT_SIZE);
    strcpy(aux->title, buff);


    // author
    printf("author=");
    aux->author = malloc(INPUT_SIZE);

    fgets(buff, INPUT_SIZE, stdin);
    dim = strlen(buff);

    if( buff[dim - 1] == '\n')
        buff[--dim] = '\0';

    strcpy(aux->author, buff);


    // genre
    printf("genre=");
    aux->genre = malloc(INPUT_SIZE);

    fgets(buff, INPUT_SIZE, stdin);
    dim = strlen(buff);

    if( buff[dim - 1] == '\n')
        buff[--dim] = '\0';

    strcpy(aux->genre, buff);

    // publisher
    printf("publisher=");
    aux->publisher = malloc(INPUT_SIZE);

    fgets(buff, INPUT_SIZE, stdin);
    dim = strlen(buff);

    if( buff[dim - 1] == '\n')
        buff[--dim] = '\0';

    strcpy(aux->publisher, buff);


    // page_count
    printf("page_count=");

    fgets(buff, INPUT_SIZE, stdin);
    dim = strlen(buff);

    if( buff[dim - 1] == '\n')
        buff[--dim] = '\0';

    int nr = atoi(buff);
    aux->page_count = nr;




    return aux;

}

void freeUser(struct TUser **user)
{
    free( (*user)->username);
    free( (*user)->password);
    free( (*user));
}

void freeCarte(struct TCarte **carte)
{
    free( (*carte)->title);
    free( (*carte)->genre);
    free( (*carte)->publisher);
    free( (*carte)->author);
    free( (*carte));
}

char* get_token(char* response) {
    if(!response) return NULL;

    char* json_part_response = basic_extract_json_response(response);
    if(json_part_response == NULL) 
        return NULL;

    JSON_Value* aux = json_parse_string(json_part_response);
    JSON_Object* p_aux = json_value_get_object(aux);

    char* token = strdup(json_object_get_string(p_aux, "token"));
    json_value_free(aux);

    return token;
}

char* construieste_body_data_user(struct TUser* user) {
    // initializare
    JSON_Value* aux = json_value_init_object();
    JSON_Object* p_aux = json_value_get_object(aux);

    /* set fields of json object: */
    json_object_set_string(p_aux, "password", user->password); 
    json_object_set_string(p_aux, "username", user->username);

    char* body_data = json_serialize_to_string_pretty(aux);

    // free memmory
    json_value_free(aux);

    return body_data;
}


char* construieste_body_data_carte(TCarte* carte) {
   
    JSON_Value* aux = json_value_init_object();
    JSON_Object* p_aux = json_value_get_object(aux);

    json_object_set_number(p_aux, "id", carte->id);
    json_object_set_string(p_aux, "title", carte->title);
    json_object_set_string(p_aux, "author", carte->author);
    json_object_set_string(p_aux, "genre", carte->genre); 
    json_object_set_number(p_aux, "page_count", carte->page_count);
    json_object_set_string(p_aux, "publisher", carte->publisher); 

    char* body_data = json_serialize_to_string_pretty(aux);

    json_value_free(aux);

    return body_data;

}

char* get_error(char* response) 
{
    if(response == NULL) 
        return NULL;

    char* error = (char*) malloc( SIZE * sizeof(char));
    if(error == NULL) 
        return NULL;

    char* json_part_response = basic_extract_json_response(response);
    if(json_part_response == NULL)
        return NULL;

    JSON_Value* aux = json_parse_string(json_part_response);
    JSON_Object* p_aux = json_value_get_object(aux);

    const char* err_message = json_object_get_string(p_aux, "error");
    if(err_message == NULL) 
        return "";

    sprintf(error, "%s","Error:\n");
    strcat(error, err_message);

    json_value_free(aux);

    return error;
}

int check_status(char* response, int success_code, char* success_msg) 
{
    if(response == NULL || success_msg == NULL) 
        return 0;
    char* pch = strchr(response, ' ');
    if(!(pch++)) 
        return 0;

    char* next_pch = strchr(pch, ' ');

    if(next_pch) 
        *next_pch = '\0';
    
    int code = atoi(pch);
    if(next_pch) 
        *next_pch = ' ';

    if(code == success_code) 
    {
        printf("%s\n", success_msg);
        return 1;
    }

    // daca nu intoarce succes, intoarce eroare
    char* error = get_error(response);
    if(error) 
    {
        printf("%s\n", error);
        free(error);
    }  
   
    return 0;
}

void get_cookie2(char* response, char** cookie) 
{

    char* header = strstr(response, "connect.sid=");
    if(header == NULL) 
        return ;

    char* p = strchr(header, ';');
    if( p == NULL ) 
        return ;

    *p = '\0';

    * cookie = strdup(header);
    // refacem stringul cum era inainte
    *p = ';';

}


int Register(char** message, char** response)
{
    int sockfd = open_connection(HOST, PORT, AF_INET, SOCK_STREAM, 0);

    struct TUser *user = alocareUSer();

    int body_data_fields_count = 1;
    char *body_data = construieste_body_data_user(user);
    
    int cookies_count = 0;
    char* cookies = NULL;
    
    *message = compute_post_request(HOST, "/api/v1/tema/auth/register", "application/json", 
                                        &body_data, body_data_fields_count , NULL, 0, NULL);
    send_to_server(sockfd, *message);

    *response = receive_from_server(sockfd);

    // in caz de timeout trimitem si reprimim mesajul
    if( strlen(*response) == 0)
    {
        sockfd = open_connection(HOST, PORT, AF_INET, SOCK_STREAM, 0);
        send_to_server(sockfd, *message);
        *response = receive_from_server(sockfd);
    }
           
    freeUser(&user);

    close_connection(sockfd);

    return check_status(*response, 201, "Inregistrare cu succes.");
    
}

void Login(char **message, char** response, char** cookie)
{
    int sockfd = open_connection(HOST, PORT, AF_INET, SOCK_STREAM, 0);

    struct TUser *user = alocareUSer();

    int body_data_fields_count = 1;
    char *body_data = construieste_body_data_user(user);
    
    int cookies_count = 0;
    char* cookies = NULL;
    
    *message = compute_post_request(HOST, "/api/v1/tema/auth/login", "application/json", 
                                        &body_data, 1 , NULL, 0, NULL);
    send_to_server(sockfd, *message);

    *response = receive_from_server(sockfd);

    // in caz de timeout trimitem si reprimim mesajul
    if( strlen(*response) == 0)
    {
        sockfd = open_connection(HOST, PORT, AF_INET, SOCK_STREAM, 0);
        send_to_server(sockfd, *message);
        *response = receive_from_server(sockfd);
    }
   
    freeUser(&user);

    close_connection(sockfd);

    
    int ret = check_status(*response, 200, "Logare cu succes.");
    if(ret == 1)
    {    
        get_cookie2(*response, cookie);
    }
  
}

/*char *compute_get_request(char *host, char *url, char *query_params,
                            char **cookies, int cookies_count)*/

int Logout(char **message, char** response, char** cookie)
{   
    int cookies_count = 0;
    if(*cookie != NULL)
        cookies_count = 1;

    int sockfd = open_connection(HOST, PORT, AF_INET, SOCK_STREAM, 0);

    *message = compute_get_request(HOST, "/api/v1/tema/auth/logout", NULL, 
                                        cookie, cookies_count, NULL);
    send_to_server(sockfd, *message);
    
    *response = receive_from_server(sockfd);

    // in caz de timeout trimitem si reprimim mesajul
    if( strlen(*response) == 0)
    {
        sockfd = open_connection(HOST, PORT, AF_INET, SOCK_STREAM, 0);
        send_to_server(sockfd, *message);
        *response = receive_from_server(sockfd);
    }

    
    close_connection(sockfd);
    
    return check_status(*response, 200, "Logout cu succes.");
    
}

void Enter_Library(char** message, char **response, char** cookie, char** token)
{
    int cookies_count = 0;
    if(*cookie != NULL)
        cookies_count = 1;

    int sockfd = open_connection(HOST, PORT, AF_INET, SOCK_STREAM, 0);

    *message = compute_get_request(HOST, "/api/v1/tema/library/access", NULL, 
                                        cookie, cookies_count, *token);
    send_to_server(sockfd, *message);

    *response = receive_from_server(sockfd);

    if( strlen(*response) == 0)
    {
        sockfd = open_connection(HOST, PORT, AF_INET, SOCK_STREAM, 0);
        send_to_server(sockfd, *message);
        *response = receive_from_server(sockfd);
    }

    int ret = check_status(*response, 200, "Intrare in biblioteca cu succes.");
    
    // daca se executa cu succes, salvam tokenul
    if(ret == 1)
    {    
        *token = strdup( get_token(*response));
    }
}

void Add_Book(char** message, char** response, char** cookie, char** token)
{
    int sockfd = open_connection(HOST, PORT, AF_INET, SOCK_STREAM, 0);

    TCarte *carte = alocareCarte();
    if( carte == NULL)
        return ;

    int body_data_fields_count = 1;
    char *body_data = construieste_body_data_carte(carte);


    *message = compute_post_request(HOST, "/api/v1/tema/library/books", "application/json", 
                                        &body_data, body_data_fields_count , NULL, 0, *token);
    send_to_server(sockfd, *message);
    
    *response = receive_from_server(sockfd);

    // in caz de timeout trimitem si reprimim mesajul
    if( strlen(*response) == 0)
    {
        sockfd = open_connection(HOST, PORT, AF_INET, SOCK_STREAM, 0);
        send_to_server(sockfd, *message);
        *response = receive_from_server(sockfd);
    }
   
    freeCarte(&carte);

    close_connection(sockfd);

    int ret = check_status(*response, 200, "carte adauga cu succes.");

}

void Delete_Book(char** message, char** response, char** cookie, char** token)
{
    int sockfd = open_connection(HOST, PORT, AF_INET, SOCK_STREAM, 0);
    char buff[SIZE];

    printf("id=");
    fgets( buff, INPUT_SIZE, stdin );
    int dim = strlen( buff );
        
    if(buff[dim - 1] == '\n')
        buff[--dim]='\0';

    char *link = malloc(SIZE * sizeof(char));
    memset(link, 0, SIZE);
    
 
    
    sprintf(link, "%s", "/api/v1/tema/library/books/");
    strcat(link, buff);

  /*  char *compute_delete_request(char *host, char *url, 
                          char **cookies, int cookies_count, char *token)*/

    *message = compute_delete_request(HOST, link, NULL, 0 , *token);

    send_to_server(sockfd, *message);
    
    *response = receive_from_server(sockfd);

    // in caz de timeout trimitem si reprimim mesajul
    if( strlen(*response) == 0)
    {
        sockfd = open_connection(HOST, PORT, AF_INET, SOCK_STREAM, 0);
        send_to_server(sockfd, *message);
        *response = receive_from_server(sockfd);
    }


    close_connection(sockfd);

    int ret = check_status(*response, 200, "carte eliminata cu succes.");
}

void Get_Book(char** message, char** response, char** cookie, char** token)
{
    int sockfd = open_connection(HOST, PORT, AF_INET, SOCK_STREAM, 0);
    char buff[SIZE];

    printf("id=");
    fgets( buff, INPUT_SIZE, stdin );
    int dim = strlen( buff );
        
    if(buff[dim - 1] == '\n')
        buff[--dim]='\0';

    char *link = malloc(SIZE * sizeof(char));
    memset(link, 0, SIZE);
    
 
    
    sprintf(link, "%s", "/api/v1/tema/library/books/");
    strcat(link, buff);
    
   

    /*
    char *compute_get_request(char *host, char *url, char *query_params,
                            char **cookies, int cookies_count, char* token); */

    int cookies_count = 0;
    if(cookie != NULL)
        cookies_count = 1;
    *message = compute_get_request(HOST, link, NULL, cookie, cookies_count, *token);

    send_to_server(sockfd, *message);
    
    *response = receive_from_server(sockfd);
    // in caz de timeout trimitem si reprimim mesajul
    if( strlen(*response) == 0)
    {
        sockfd = open_connection(HOST, PORT, AF_INET, SOCK_STREAM, 0);
        send_to_server(sockfd, *message);
        *response = receive_from_server(sockfd);
    }

    close_connection(sockfd);

    int ret = check_status(*response, 200, "carte vizualizata cu succes.");
    
    char* json_part = NULL;
    if( ret == 1)
    {
        json_part = basic_extract_json_response(*response);
    }

    JSON_Value *jValue = NULL;
    if(json_part)
        jValue = json_parse_string(json_part);

    if(jValue)
        json_object_set_number(json_value_get_object(jValue), "id", atoi(buff));

    char *book_str = NULL;
    if(jValue)
        book_str = json_serialize_to_string_pretty(jValue);
    
    if( book_str != NULL)
    {    
        printf("%s\n", book_str);
        free(book_str);
        json_value_free(jValue);
        free(link);
    }     
}
