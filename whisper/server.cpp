#include "common.hpp"

int main(int argc, char** argv){
    unsigned short port = 12345;

    if (argc > 1){
        port = atoi(argv[1]);
    }else{
        fprintf(stderr, "No port specified, listening for 12345\n");
    }

    struct {
        struct iphdr ip;
        struct tcphdr tcp;
        char buffer[10000];
    } packet;

    while (true){
        int sock = socket(AF_INET, SOCK_RAW, 6);
        if (sock < 0){
            perror("Can't open socket");
            exit(EXIT_FAILURE);
        }
        read(sock, &packet, sizeof(packet));
        unsigned int last_seq = 0;
        if (packet.tcp.syn == 1 and ntohs(packet.tcp.dest) == port){
            packet.tcp.seq ^= FUZZER;
            char data[sizeof(unsigned int) + 1] = { '\0' };
            bcopy(&packet.tcp.seq, data, sizeof(unsigned int));
            const char* p = data;
            if ((last_seq&0xff) == (packet.tcp.seq&0xff00)>>16){
                p+=2;
            }
            printf("%s", p);
            fflush(stdout);
            last_seq = packet.tcp.seq;
        }
        close(sock);
    }
}

