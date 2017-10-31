/*
** include.h for UdpMulticastSocket in /home/guilhem/Bureau/testUdp/C/include/
**
** Made by Guilhem Fulcrand
** Login   <guilhem.fulcrand@epitech.eu>
**
** Started on  Fri Sep 22 09:51:58 2017 Guilhem Fulcrand
** Last update Thu Oct 12 17:13:30 2017 Guilhem Fulcrand
*/

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <getopt.h>
#include <string.h>
#include <time.h>
#include <sys/poll.h>
#include <errno.h>

#define EXIT_S              0
#define EXIT_F              1
#define DEFAULT_ADDR        "127.0.0.1"
#define DEFAULT_PORT        1234
#define DEFAULT_TTL         1
#define BUFF_SIZE           255
#define TIMEOUT             60000 // timeout of 60 sec on server
#define MAX_CLIENTS         50

typedef struct  s_info
{
    char        *addr;
    int         port;
    int         client_mode;
    int         server_mode;
    u_char      ttl;
}               t_info;

/* MODES */

void    sender(t_info *info);
void    listener(t_info *info);

/* PARSING AND HELP */

void    help();
void    parse_args(t_info *info, int ac, char **av);
