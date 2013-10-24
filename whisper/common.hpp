#ifndef COMMON_HPP
#define COMMON_HPP

// Written by Jacques Labuschagne (jlabusch@acm.org), 2013
// Based on Covert_TCP 1.0 (c) 1996 Craig H. Rowland (crowland@psionic.com)
// Some Covert_TCP code is based on ping.c (c) 1987 Regents of the University of California.

extern "C"{
    #include <assert.h>
    #include <stdio.h>
    #include <stdlib.h>
    #include <signal.h>
    #include <string.h>
    #include <time.h>
    #include <errno.h>
    #include <unistd.h>
    #include <netdb.h>
    #include <netinet/in.h>
    #include <sys/socket.h>
    #include <arpa/inet.h>
    #include <linux/ip.h>
    #include <linux/tcp.h>
}

unsigned short in_cksum(unsigned short *ptr, int nbytes);

extern const unsigned int FUZZER;

#endif

