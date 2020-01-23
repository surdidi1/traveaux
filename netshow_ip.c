#define _XOPEN_SOURCE 600
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#include <ifaddrs.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ADDR_MAX 32

#define vrai 0
#define faux 1

int compare(const char* chaine1, const char* chaine2)
{   unsigned int i=0;
    if( strlen(chaine1) != strlen(chaine2) )
        return faux;
    for(i=0;i<strlen(chaine1);i++)
        if( chaine1[i] != chaine2[i])
            return faux;
    return vrai;
 
}

int main(void)
{
        static char buf[ADDR_MAX];
        struct ifaddrs *list;
        struct ifaddrs *it;

        if (getifaddrs(&list) != 0) {
                perror("getifaddrs");
                return EXIT_FAILURE;
        }
        it = list;
        while (it != NULL) {
                struct sockaddr_in *addr;

                addr = (struct sockaddr_in *)it->ifa_addr;
                if (addr != NULL && it->ifa_addr->sa_family == AF_INET) {
                        if (inet_ntop(AF_INET, &addr->sin_addr, buf, ADDR_MAX) == NULL) {
                                perror("inet_ntop");
                                exit(EXIT_FAILURE);
                        }
                        if((compare(it->ifa_name,argv[1])) == 0){
                                printf("%s: %s\n", it->ifa_name, buf);
                        } 
                }
                it = it->ifa_next;
        }
        freeifaddrs(list);
        return 0;
}
