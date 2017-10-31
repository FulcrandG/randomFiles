/*
** client.c for UdpMulticastSocket in /home/guilhem/Bureau/testUdp/C/
**
** Made by Guilhem Fulcrand
** Login   <guilhem.fulcrand@epitech.eu>
**
** Started on  Fri Sep 22 16:31:25 2017 Guilhem Fulcrand
** Last update Fri Sep 22 16:32:29 2017 Guilhem Fulcrand
*/

#include "include.h"

void        sender(t_info *info)
{
    struct  sockaddr_in addr;
    int     fd;
    char    msg[BUFF_SIZE];

    // Create Socket
    if ((fd = socket(AF_INET,SOCK_DGRAM, 0)) < 0)
    {
	    fprintf(stderr, "Could't open socket\n");
	    exit(1);
    }
    
    // Set TTL for Multicast purpose
    if (setsockopt(fd, IPPROTO_IP, IP_MULTICAST_TTL, &info->ttl, sizeof(info->ttl)) < 0)
    {
        fprintf(stderr, "setsockopt failed\n");
        exit(1);
    }
    memset(&addr,0,sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = inet_addr(info->mul_addr);
    addr.sin_port = htons(info->port);
    memset(msg, 0, sizeof(msg));
    while (fgets(msg, BUFF_SIZE, stdin))
    {
	    if (sendto(fd, msg, strlen(msg), 0, (struct sockaddr *) &addr, sizeof(addr)) < 0)
        {
	        fprintf(stderr, "sendto failed \n");
	        exit(1);
	    }
        memset(msg, 0, sizeof(msg));
    }
}
