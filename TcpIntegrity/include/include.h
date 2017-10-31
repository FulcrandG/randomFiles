/*
** include.h for UdpMulticastSocket in /home/guilhem/Bureau/testUdp/C/include/
**
** Made by Guilhem Fulcrand
** Login   <guilhem.fulcrand@epitech.eu>
**
** Started on  Fri Sep 22 09:51:58 2017 Guilhem Fulcrand
** Last update Tue Oct 17 14:58:15 2017 Guilhem Fulcrand
*/

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <getopt.h>
#include <string.h>
#include <time.h>
#include <sys/poll.h>
#include <errno.h>
#include <sys/stat.h>
#include <fcntl.h>

#define EXIT_S              0
#define EXIT_F              1
#define DEFAULT_ADDR        "127.0.0.1"
#define DEFAULT_PORT        1230
#define BUFF_SIZE           1024
#define TIMEOUT             -1 // 60000 // poll timeout on server
#define MAX_CLIENTS         50
#define MAX_SLOTS           8
#define MAX_THREADS         MAX_CLIENTS * MAX_SLOTS

typedef struct  s_args
{
    char        *addr;
    int         port;
    int         client_mode;
    int         server_mode;
    int         slots;
    int         verbose;

}               t_args;

/* MODES */

void    client_threading_loop(t_args *args);
void    listener(t_args *args);

/* PARSING AND HELP */

void    help();
void    parse_args(t_args *args, int ac, char **av);
