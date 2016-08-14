#include <stdio.h>
#include <string.h>
#include <time.h>
using namespace std;

#ifdef _WIN32
    #include <winsock.h>
#else
    #include <sys/socket.h>
    #include <arpa/inet.h>
    #include <netdb.h>  /* Needed for getaddrinfo() and freeaddrinfo() */
    #include <unistd.h> /* Needed for close() */
#endif // _WIN32

#include "defs.hpp"
#include "system.hpp"

int main(int argc, char **argv){

    SystemEntry system;//constructor starts everything
/*
system.users.CreateNew("D3thAdd3r","ec:44:4a:67:cb:d8","Lee Weber",0);
system.SaveUserData();


UserEntry *u = system.users.Find("ec:44:4a:67:cb:d8");
if(u != NULL){
    printf("found it...%s\n",u->name);
}

return 1;
*/
    if(system.critical_err){
        printf("----Failed to initialize system. Error:%d\n",system.critical_err);
        Sleep(2000);
        return system.critical_err;
    }
    PrintTime();
    printf(":System initialized, listening at:");

    char buf[96];
    gethostname(buf, sizeof(buf));
    struct hostent *phe = gethostbyname(buf);

    for(int i=0;phe->h_addr_list[i];i++){
        struct in_addr addr;
        memcpy(&addr, phe->h_addr_list[i], sizeof(struct in_addr));
        if(i > 0)
            printf(",");
        printf("%s:%d",inet_ntoa(addr),LISTEN_PORT);
    }

    printf("\n");

    printf("Logging server events to file:log.txt(no further console notifications)\n>log.txt");


//system.GenerateWebPage();


    while(!system.Update());

    //printf("\n\nSystem terminated with code:%d\n",system.critical_err);
    return system.critical_err;
}

