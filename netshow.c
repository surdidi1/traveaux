#define _XOPEN_SOURCE 600
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#include <ifaddrs.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ADDR_MAX 32


int main(int argc, char *ifname[])
{
        int i;
        char *vide="x";
        if (argc <= 1) {
                printf("Le programme n'a reçu aucun argument\n");
                ifname[1]="x";
        }
        else{
                printf("Vous avez saisie : ");
                for (i = 1; i < argc; i++) {
                printf("%s\n\n", ifname[i]);
                }
        }

        static char buf[ADDR_MAX];
        struct ifaddrs *list;
        struct ifaddrs *it;

        printf("ADRESSES EN IPV6 :\n");
        if (getifaddrs(&list) != 0) {
                perror("getifaddrs");
                return EXIT_FAILURE;
        }
        it = list;
        //printf('%s',it);
        while (it != NULL) {
                struct sockaddr_in *addr;

                        addr = (struct sockaddr_in *)it->ifa_addr;     
                        if (addr != NULL && it->ifa_addr->sa_family == AF_INET6) {
                                if (inet_ntop(AF_INET6, &addr->sin_addr, buf, ADDR_MAX) == NULL) {
                                        perror("inet_ntop");
                                        exit(EXIT_FAILURE);
                                }
                                if(strcmp(ifname[1],vide)==0){
                                        printf("%s: %s\n", it->ifa_name, buf);

                                }else if (strcmp(ifname[1],it->ifa_name)==0){
                                        printf("%s: %s\n", it->ifa_name, buf);
                                }
                                else{;}                
                                
                        }
                it = it->ifa_next;
        }
        freeifaddrs(list);

        printf("\nADRESSES EN IPV4 : \n");
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
                        if(strcmp(ifname[1],vide)==0){
                                printf("%s: %s\n", it->ifa_name, buf);

                        }else if (strcmp(ifname[1],it->ifa_name)==0){
                                printf("%s: %s\n", it->ifa_name, buf);
                        }else{;}  
                }
                it = it->ifa_next;
        }
        freeifaddrs(list);
        return 0;
}