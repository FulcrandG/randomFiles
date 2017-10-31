/*
** server.c for UdpMulticastSocket.c in /home/guilhem/Bureau/testUdp/C/
**
** Made by Guilhem Fulcrand
** Login   <guilhem.fulcrand@epitech.eu>
**
** Started on  Fri Sep 22 16:32:03 2017 Guilhem Fulcrand
** Last update Tue Oct 17 13:56:04 2017 Guilhem Fulcrand
*/

#include "include.h"

void                    listener(t_args *args)
{
    struct sockaddr_in  addr;
    socklen_t           addrlen;
    int                 fd;
    int                 sockfd;
    int                 msg_len;
    char                msg_buff[BUFF_SIZE];
    struct pollfd       pfd[200];
    int                 nfds;
    int                 rc;
    int                 current_size;
    int                 i;

    // Opening an AF_INET socket on the couple addr/port
    if ((fd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
	     fprintf(stderr, "Couldn't open socket\n");
	     exit(1);
    }
    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = htonl(INADDR_ANY);
    addr.sin_port = htons(args->port);

    // Set so_reuseaddr in order to not accumulate sockets in TIME_WAIT mode
    if (setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &(int){ 1 }, sizeof(int)) < 0)
    {
        fprintf(stderr, "setsockopt failed\n%s\n", strerror(errno));
        close(fd);
        exit(1);
    }

    // Initialize the pollfd structure
    memset(&pfd, 0, sizeof(struct pollfd));

    // Set up the epoll listening socket
    pfd[0].fd = fd;
    pfd[0].events = POLLIN;

    // Bind the socket
    if (bind(fd, (struct sockaddr *) &addr, sizeof(addr)) < 0)
    {
	    fprintf(stderr, "Couldn't bind to address %d\n", INADDR_ANY);
        close(fd);
	    exit(1);
    }
    // Start listening
    if (listen(fd, MAX_CLIENTS) < 0)
    {
        fprintf(stderr, "Couldn't listen()\n%s\n", strerror(errno));
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
            if ((sockfd = accept(fd, (struct sockaddr *) &addr, &addrlen)) < 0)
            {
                fprintf(stderr, "Couldn't accept()\n%s\n", strerror(errno));
                exit(1);
            }
            if ((msg_len = recv(sockfd, msg_buff, BUFF_SIZE, 0)) < 0)
            {
                fprintf(stderr, "Couldn't recv()\n%s\n", strerror(errno));
                close(fd);
                exit(1);
            }

            /*** EVIL TEST ONGOING ****
            int rand = random() % 100;
            rand == 0 ? msg_buff[random() % BUFF_SIZE]++ && printf("It's a TRAP!\n"): 0;
            **** EVIL TEST ONGOING ***/
            
            if (args->verbose)
                printf("Packet received\n");

            // Echoing data
            if (send(sockfd, msg_buff, BUFF_SIZE, 0) < 0)
            {
               fprintf(stderr, "send() failed \n");
               close(fd);
               exit(1);
            }
            close(sockfd);
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
