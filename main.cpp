#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <iostream>
#include <string>
#include <sstream>
#include <cstdlib>
#include <fstream>
using namespace std;
int main(int argc, char *argv[]) {
    if (argc <= 1)
    {
        cout << "Please run the program correctly. You have not entered a "
                "program start option"
             << '\n';
        // exit(1);
    }
    struct addrinfo hints, *res;
    int sockfd;
    char buf[2056];
    int byte_count;
    int myint;

    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    getaddrinfo("localhost/index.html", "80", &hints, &res);
    sockfd = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
    printf("Connecting...\n");
    connect(sockfd, res->ai_addr, res->ai_addrlen);
    printf("Connected!\n");
    char *header = "GET /index.html HTTP/1.1\r\nHost: "
                   "localhost"
                   "index.html\r\n\r\n";
    send(sockfd, header, strlen(header), 0);
    printf("GET Sent...\n");

    stringstream convert(argv[1]);

    if (!(convert >> myint))
        myint = 1;

    if (myint == 1) {
        int nsize;
        while ((nsize = recv(sockfd, buf, sizeof(buf) - 1, 0)) !=
               SO_ERROR)
        {
            for (int i = 0; i < nsize; ++i)
                printf("%c", buf[i]);
            break;
        }
    }
    else {
        if (argc == 3)
        {
            int nsize;
            ofstream fout;
            fout.open(argv[3]);
            while ((nsize = recv(sockfd, buf, sizeof(buf) - 1, 0)) !=
                   SO_ERROR)
            {
                for (int i = 0; i < nsize; ++i)
                    fout << buf[i];
                break;
            }
            fout.close();
        }
    }
}