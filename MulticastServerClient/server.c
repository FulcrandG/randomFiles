/*
** server.c for UdpMulticastSocket.c in /home/guilhem/Bureau/testUdp/C/
**
** Made by Guilhem Fulcrand
** Login   <guilhem.fulcrand@epitech.eu>
**
** Started on  Fri Sep 22 16:32:03 2017 Guilhem Fulcrand
** Last update Fri Sep 22 16:33:40 2017 Guilhem Fulcrand
*/

#include "include.h"

void                listener(t_info *info)
{
    struct          sockaddr_in addr;
    struct          ip_mreq mreq;
    int             fd;
    int             msg_len;
    int             addrlen;
    char            msg_buff[BUFF_SIZE];
    struct pollfd   pfd[200];
    int             nfds;
    int             rc;
    int             current_size;
    int             i;

    // Opening an AF_INET socket on the couple addr/port
    if ((fd = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
    {
	     fprintf(stderr, "Couldn't open socket\n");
	     exit(1);
    }
    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = htonl(INADDR_ANY);
    addr.sin_port = htons(info->port);

    // Bind the socket
    if (bind(fd, (struct sockaddr *) &addr, sizeof(addr)) < 0)
    {
	    fprintf(stderr, "Couldn't bind to address %d\n", INADDR_ANY);
	    exit(1);
    }
    mreq.imr_multiaddr.s_addr = inet_addr(info->mul_addr);
    mreq.imr_interface.s_addr = htonl(INADDR_ANY);

    // Initialize the pollfd structure
    memset(&pfd, 0, sizeof(struct pollfd));

    // Set up the epoll listening socket
    pfd[0].fd = fd;
    pfd[0].events = POLLIN;

    if (setsockopt(fd,IPPROTO_IP,IP_ADD_MEMBERSHIP,&mreq,sizeof(mreq)) < 0)
    {
	fprintf(stderr, "setsockopt failed\n");
        close(fd);
	exit(1);
    }
    while (1)
    {
        // Launching the poll event
        nfds = 1;
        rc = poll(pfd, nfds, TIMEOUT);
        if (rc < 0)
        {
            fprintf(stderr, "Poll failed\n");
            close(fd);
            exit(1);
        }

        // If TIMEOUT was depassed
        if (rc == 0)
        {
            printf("Poll timed out. End program.\n");
            break;
        }

        // Checking for I/O on the socket
        current_size = nfds;
        i = 0;
        while (i < current_size)
        {
            if (pfd[i].revents == 0)
                continue;

            // In case it was't a POLLIN event
            if(pfd[i].revents != POLLIN)
            {
                printf("Error on revents = %d\n", pfd[i].revents);
                break;
            }

            // Handling connexion
            addrlen = sizeof(addr);
            if ((msg_len = recvfrom(fd, msg_buff, BUFF_SIZE, 0, (struct sockaddr *)&addr, (socklen_t * restrict)&addrlen)) < 0)
            {
                fprintf(stderr, "Couldn't recvfrom\n");
                close(fd);
                exit(1);
            }
            printf("%s", msg_buff);
            memset(msg_buff, 0, msg_len + 1);

            // Incrementing the index of file descriptor used for polling
            i++;
        }
    }
    i = 0;
    while (i < nfds)
    {
        close(pfd[i].fd);
        i++;
    }
    close(fd);
}
