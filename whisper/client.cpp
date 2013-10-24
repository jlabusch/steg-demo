#include "common.hpp"

#include <vector>
using std::vector;

int whisper(unsigned int data,
            unsigned int source_addr, unsigned short source_port,
            unsigned int dest_addr, unsigned short dest_port)
{
    struct{
        struct iphdr ip;
        struct tcphdr tcp;
    } packet;

    packet.ip.ihl = 5;
    packet.ip.version = 4;
    packet.ip.tos = 0;
    packet.ip.tot_len = htons(40);
    packet.ip.id = (int)(255.0*rand()/(RAND_MAX+1.0));
    packet.ip.frag_off = 0;
    packet.ip.ttl = 64;
    packet.ip.protocol = IPPROTO_TCP;
    packet.ip.check = 0;
    packet.ip.saddr = source_addr;
    packet.ip.daddr = dest_addr;

    packet.tcp.source = htons(source_port); // TODO: data
    packet.tcp.seq = data;
    packet.tcp.dest = htons(dest_port);

    packet.tcp.ack_seq = 0;
    packet.tcp.res1 = 0;
    packet.tcp.doff = 5;
    packet.tcp.fin = 0;
    packet.tcp.syn = 1;
    packet.tcp.rst = 0;
    packet.tcp.psh = 0;
    packet.tcp.ack = 0;
    packet.tcp.urg = 0;
    packet.tcp.ece = 0;
    packet.tcp.cwr = 0;
    packet.tcp.window = htons(512);
    packet.tcp.check = 0;
    packet.tcp.urg_ptr = 0;

    struct sockaddr_in sin;
    sin.sin_family = AF_INET;
    sin.sin_port = packet.tcp.source;
    sin.sin_addr.s_addr = packet.ip.daddr;

    int sock = socket(AF_INET, SOCK_RAW, IPPROTO_RAW);
    if (sock < 0){
        perror("Can't create socket in whisper()");
        return 1;
    }

    assert(sizeof(iphdr) == 20);
    packet.ip.check = in_cksum((unsigned short*)&packet.ip, 20);

    struct{
        unsigned int saddr;
        unsigned int daddr;
        unsigned char placeholder;
        unsigned char proto;
        unsigned char length;
        struct tcphdr tcp;
    } header;

    header.saddr = packet.ip.saddr;
    header.daddr = packet.ip.daddr;
    header.placeholder = 0;
    header.proto = IPPROTO_TCP;
    header.length = htons(20);
    assert(sizeof(tcphdr) == 20);
    bcopy((char*)&packet.tcp, (char*)&header.tcp, 20);

    assert(sizeof(header) == 32);
    packet.tcp.check = in_cksum((unsigned short*)&header, 32);

    ssize_t n = sendto(sock, &packet, 40, 0, (struct sockaddr*)&sin, sizeof(sin));
    if (n < 0){
        perror("sendto() failed in whisper()");
        return 2;
    }
    if (n != 40){
        perror("Write incomplete.");
        return 3;
    }
    return 0;
}

unsigned int parse_host(const char* host){
    static struct in_addr i;
    struct hostent* h;
    i.s_addr = inet_addr(host);
    if (i.s_addr < 0){
        h = gethostbyname(host);
        if (!h){
            perror("Cannot resolve host");
            exit(EXIT_FAILURE);
        }
        bcopy(h->h_addr, (char*)&i.s_addr, h->h_length);
    }
    return i.s_addr;
}

int main(int argc, char** argv){
    srand(time(NULL));

    if (argc != 6){
        fprintf(stderr, "Usage: %s <src-ip> <src-port> <dest-ip> <dest-port> <text>\n", *argv);
        return EXIT_FAILURE;
    }

    unsigned int    src_host = parse_host(argv[1]);
    unsigned short  src_port = strtol(argv[2], NULL, 10);
    unsigned int    dst_host = parse_host(argv[3]);
    unsigned short  dst_port = strtol(argv[4], NULL, 10);

    int n = strlen(argv[5]);
    vector<unsigned int> data((n/4)+1, 0);
    bcopy(argv[5], (char*)&data[0], n);
    for (vector<unsigned int>::iterator d = data.begin(); d != data.end(); ++d){
        whisper((*d) ^ FUZZER, src_host, src_port, dst_host, dst_port);
        usleep(100*1000);
    }
}

