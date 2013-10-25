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
        if (packet.tcp.syn == 1 and ntohs(packet.tcp.dest) == port){
            char data[sizeof(unsigned int) + 1] = { '\0' };
            packet.tcp.seq ^= FUZZER;
            bcopy(&packet.tcp.seq, data, sizeof(unsigned int));
            printf("%s", data);
            fflush(stdout);
        }
        close(sock);
    }
}

