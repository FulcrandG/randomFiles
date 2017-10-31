/*
** client.c for TcpSocket in /home/guilhem/Bureau/testTCP/
**
** Made by Guilhem Fulcrand
** Login   <guilhem.fulcrand@epitech.eu>
**
** Started on  Thu Oct 12 14:44:08 2017 Guilhem Fulcrand
** Last update Fri Oct 13 09:50:44 2017 Guilhem Fulcrand
*/

#include "include.h"

void                    sender(t_info *info)
{
    struct sockaddr_in  addr;
    int                 fd;
    char                msg[BUFF_SIZE];



    memset(msg, 0, sizeof(msg));
    while (fgets(msg, BUFF_SIZE, stdin))
    {
        if ((fd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
        {
            fprintf(stderr, "Couldn't open socket\n");
            exit(1);
        }
        memset(&addr,0,sizeof(addr));
        addr.sin_family = AF_INET;
        addr.sin_addr.s_addr = inet_addr(info->addr);
        addr.sin_port = htons(info->port);
        if (connect(fd, (struct sockaddr *) &addr, sizeof(addr)) < 0)
        {
            fprintf(stderr, "connect() failed\n%s\n", strerror(errno));
            exit(1);
        }
	    if (send(fd, msg, strlen(msg), 0) < 0)
        {
	        fprintf(stderr, "send() failed \n");
	        exit(1);
	    }
        close(fd);
        memset(msg, 0, sizeof(msg));
    }
}
